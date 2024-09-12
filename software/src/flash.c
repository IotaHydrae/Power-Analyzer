#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"
#include "pico/flash.h"
#include "pico/time.h"
#include "hardware/dma.h"
#include "hardware/structs/ssi.h"
#include "hardware/sync.h"
#include "hardware/flash.h"

struct flash_msg {
    uint8_t *rxbuf;
    uint8_t *txbuf;
    uint32_t flash_offs;
    size_t len;
    uint dma_chan;
};

// This example DMAs 16kB of data from the start of flash to SRAM, and
// measures the transfer speed.
//
// The SSI (flash interface) inside the XIP block has DREQ logic, so we can
// DMA directly from its FIFOs. Unlike the XIP stream hardware (see
// flash_xip_stream.c) this can *not* be done whilst code is running from
// flash, without careful footwork like we do here. The tradeoff is that it's
// ~2.5x as fast in QSPI mode, ~2x as fast in SPI mode.

void __no_inline_not_in_flash_func(flash_bulk_read)(uint32_t *rxbuf, uint32_t flash_offs, size_t len,
                                                 uint dma_chan) {
    // SSI must be disabled to set transfer size. If software is executing
    // from flash right now then it's about to have a bad time
    ssi_hw->ssienr = 0;
    ssi_hw->ctrlr1 = len - 1; // NDF, number of data frames
    ssi_hw->dmacr = SSI_DMACR_TDMAE_BITS | SSI_DMACR_RDMAE_BITS;
    ssi_hw->ssienr = 1;
    // Other than NDF, the SSI configuration used for XIP is suitable for a bulk read too.

    // Configure and start the DMA. Note we are avoiding the dma_*() functions
    // as we can't guarantee they'll be inlined
    dma_hw->ch[dma_chan].read_addr = (uint32_t) &ssi_hw->dr0;
    dma_hw->ch[dma_chan].write_addr = (uint32_t) rxbuf;
    dma_hw->ch[dma_chan].transfer_count = len;
    // Must enable DMA byteswap because non-XIP 32-bit flash transfers are
    // big-endian on SSI (we added a hardware tweak to make XIP sensible)
    dma_hw->ch[dma_chan].ctrl_trig =
            DMA_CH0_CTRL_TRIG_BSWAP_BITS |
            DREQ_XIP_SSIRX << DMA_CH0_CTRL_TRIG_TREQ_SEL_LSB |
            dma_chan << DMA_CH0_CTRL_TRIG_CHAIN_TO_LSB |
            DMA_CH0_CTRL_TRIG_INCR_WRITE_BITS |
            DMA_CH0_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_WORD << DMA_CH0_CTRL_TRIG_DATA_SIZE_LSB |
            DMA_CH0_CTRL_TRIG_EN_BITS;

    // Now DMA is waiting, kick off the SSI transfer (mode continuation bits in LSBs)
    ssi_hw->dr0 = (flash_offs << 8u) | 0xa0u;

    // Wait for DMA finish
    while (dma_hw->ch[dma_chan].ctrl_trig & DMA_CH0_CTRL_TRIG_BUSY_BITS);

    // Reconfigure SSI before we jump back into flash!
    ssi_hw->ssienr = 0;
    ssi_hw->ctrlr1 = 0; // Single 32-bit data frame per transfer
    ssi_hw->dmacr = 0;
    ssi_hw->ssienr = 1;
}

static void __flash_read(void *param)
{
    struct flash_msg *msg = (struct flash_msg *)param;

    uint src = XIP_BASE + msg->flash_offs;
    memcpy(msg->rxbuf, (void *)src, msg->len);
}

bool flash_read(uint32_t addr, void *data, size_t len)
{
    struct flash_msg msg = {
        .rxbuf = data,
        .txbuf = NULL,
        .flash_offs = addr,
        .len = len,
        .dma_chan = -1,
    };
    return (flash_safe_execute(__flash_read, (void *)&msg, 100) == PICO_OK);
}


static void __flash_write(void *param)
{
    struct flash_msg *msg = (struct flash_msg *)param;
    size_t erase_count, program_count;

    /* erase first, should be aligned to 4kB */
    if (msg->len < FLASH_SECTOR_SIZE)
        erase_count = 1;
    else
        erase_count = (msg->len % FLASH_SECTOR_SIZE) + 1;

    flash_range_erase(msg->flash_offs, erase_count);

    if (msg->len < FLASH_PAGE_SIZE)
        program_count = 1;
    else
        program_count = (msg->len % FLASH_PAGE_SIZE) + 1;

    uint8_t buf[program_count * FLASH_PAGE_SIZE];
    memcpy(buf, (void *)msg->txbuf, program_count * FLASH_PAGE_SIZE);
    flash_range_program(msg->flash_offs, buf, program_count * FLASH_PAGE_SIZE);
}

void foo (void *param)
{
    (void)param;
}

#if 1
bool flash_write(uint32_t addr, void *data, size_t len)
{
    int ret;

    struct flash_msg msg = {
        .rxbuf = NULL,
        .txbuf = data,
        .flash_offs = addr,
        .len = len,
        .dma_chan = -1,
    };

    size_t erase_count, program_count;
    if (msg.len < FLASH_SECTOR_SIZE)
        erase_count = 1;
    else
        erase_count = (msg.len % FLASH_SECTOR_SIZE) + 1;

    if (msg.len < FLASH_PAGE_SIZE)
        program_count = 1;
    else
        program_count = (msg.len % FLASH_PAGE_SIZE) + 1;

    for (int i = 0; i < msg.len; i++) {
        printf("%02x ", ((uint8_t *)msg.txbuf)[i]);
    }
    printf("\n");

    printf("offs : %08x, erased %d, programmed %d\n", msg.flash_offs, erase_count, program_count);
    // return false;
    ret = flash_safe_execute(__flash_write, (void *)&msg, UINT32_MAX);
    switch (ret) {
        case PICO_OK:
            printf("PICO_OK\n");
            return true;
        case PICO_ERROR_TIMEOUT:
            printf("PICO_TIMEOUT\n");
            break;
        case PICO_ERROR_NOT_PERMITTED:
            printf("PICO_ERROR_NOT_PERMITTED\n");
            break;
        case PICO_ERROR_INSUFFICIENT_RESOURCES:
            printf("PICO_ERROR_INSUFFICIENT_RESOURCES\n");
            break;
        default:
            printf("unknown\n");
            break;
    }

    return false;
}
#else

uint32_t _rand(uint32_t min, uint32_t max)
{
    static uint32_t a = 0x1234ABCD; /*Seed*/

    /*Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs"*/
    uint32_t x = a;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    a = x;

    return (a % (max - min + 1)) + min;
}

void print_buf(const uint8_t *buf, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        printf("%02x", buf[i]);
        if (i % 16 == 15)
            printf("\n");
        else
            printf(" ");
    }
}

#define FLASH_TARGET_OFFSET (2 * 1000 * 1024)
const uint8_t *flash_target_contents = (const uint8_t *) (XIP_BASE + FLASH_TARGET_OFFSET);

bool flash_write(uint32_t addr, void *data, size_t len)
{
    int ret;
    uint8_t random_data[FLASH_PAGE_SIZE];
    for (uint i = 0; i < FLASH_PAGE_SIZE; ++i)
        random_data[i] = _rand(0, 255);

    printf("Generated random data:\n");
    print_buf(random_data, FLASH_PAGE_SIZE);
    printf("\n");
    print_buf(flash_target_contents, FLASH_PAGE_SIZE);

    struct flash_msg msg =  {
        .rxbuf = NULL,
        .txbuf = random_data,
        .flash_offs = FLASH_TARGET_OFFSET,
        .len = FLASH_PAGE_SIZE,
        .dma_chan = -1,
    };

    ret = flash_safe_execute(__flash_write, (void *)&msg, UINT32_MAX);
    switch (ret) {
        case PICO_OK:
            printf("PICO_OK\n");
            break;
        case PICO_ERROR_TIMEOUT:
            printf("PICO_TIMEOUT\n");
            break;
        case PICO_ERROR_NOT_PERMITTED:
            printf("PICO_ERROR_NOT_PERMITTED\n");
            break;
        case PICO_ERROR_INSUFFICIENT_RESOURCES:
            printf("PICO_ERROR_INSUFFICIENT_RESOURCES\n");
            break;
        default:
            printf("unknown\n");
            break;
    }

    printf("Done. Read back target region:\n");
    print_buf(flash_target_contents, FLASH_PAGE_SIZE);
}
#endif

void flash_init(void)
{
    // flash_safe_execute_core_init();
}
