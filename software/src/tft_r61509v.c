// Copyright (c) 2024 embeddedboys developers

// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "tft.h"
#include "debug.h"

#if LCD_DRV_USE_R61509V

static int tft_r61509v_init_display(struct tft_priv *priv)
{
    pr_debug("%s, writing initial sequence...\n", __func__);
    priv->tftops->reset(priv);
    // dm_gpio_set_value(priv->gpio.rd, 1);
    // mdelay(150);

    write_reg(priv, 0x000, 0x0000);
    write_reg(priv, 0x000, 0x0000);
    write_reg(priv, 0x000, 0x0000);
    write_reg(priv, 0x000, 0x0000);
    mdelay(15);

    write_reg(priv, 0x008, 0x0808);
    write_reg(priv, 0x010, 0x0010);
    write_reg(priv, 0x400, 0x6200);

    write_reg(priv, 0x300, 0x0C06);
    write_reg(priv, 0x301, 0x9D0F);
    write_reg(priv, 0x302, 0x0B05);
    write_reg(priv, 0x303, 0x1217);
    write_reg(priv, 0x304, 0x3333);
    write_reg(priv, 0x305, 0x1712);
    write_reg(priv, 0x306, 0x950B);
    write_reg(priv, 0x307, 0x0F0D);
    write_reg(priv, 0x308, 0x060C);
    write_reg(priv, 0x309, 0x0000);

    write_reg(priv, 0x011, 0x0202);
    write_reg(priv, 0x012, 0x0101);
    write_reg(priv, 0x013, 0x0001);

    write_reg(priv, 0x007, 0x0001);
    write_reg(priv, 0x100, 0x0730);
    write_reg(priv, 0x101, 0x0237);
    write_reg(priv, 0x103, 0x2B00);
    write_reg(priv, 0x280, 0x4000);
    write_reg(priv, 0x102, 0x81B0);
    mdelay(15);

    write_reg(priv, 0x001, 0x0100);
    write_reg(priv, 0x002, 0x0100);
    write_reg(priv, 0x003, 0x1030);
    write_reg(priv, 0x009, 0x0001);

    write_reg(priv, 0x0C, 0x0000);

    write_reg(priv, 0x090, 0x8000);
    write_reg(priv, 0x00F, 0x0000);

    write_reg(priv, 0x210, 0x0000);
    write_reg(priv, 0x211, 0x00EF);
    write_reg(priv, 0x212, 0x0000);
    write_reg(priv, 0x213, 0x018F);

    write_reg(priv, 0x500, 0x0000);
    write_reg(priv, 0x501, 0x0000);
    write_reg(priv, 0x502, 0x005F);
    write_reg(priv, 0x401, 0x0001);
    write_reg(priv, 0x404, 0x0000);
    mdelay(15);
    write_reg(priv, 0x007, 0x0100);
    mdelay(15);

    write_reg(priv, 0x01, 0x0000);
    write_reg(priv, 0x03, 0x1038);
}

static void inline tft_r61509v_set_addr_win(struct tft_priv *priv, int xs, int ys, int xe,
                                int ye)
{
    /* set column adddress */
    write_reg(priv, 0x212, xs);
    write_reg(priv, 0x213, xe);
    write_reg(priv, 0x210, ys);
    write_reg(priv, 0x211, ye);
    
    write_reg(priv, 0x201, xs);
    write_reg(priv, 0x200, ys);

    /* write start */
    write_reg(priv, 0x202);
}

static int tft_clear(struct tft_priv *priv, u16 clear)
{
    u32 width =  priv->display->xres;
    u32 height = priv->display->yres;

    clear = (clear << 8) | (clear >> 8);

    pr_debug("clearing screen (%d x %d) with color 0x%x\n",
        width, height, clear);

    priv->tftops->set_addr_win(priv, 0, 0, width, height);
    
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            write_buf_rs(priv, &clear, sizeof(u16), 1);
        }
    }

    return 0;
}

static void tft_video_sync(struct tft_priv *priv, int xs, int ys, int xe, int ye, void *vmem, size_t len)
{
    // printf("video sync: xs=%d, ys=%d, xe=%d, ye=%d, len=%d\n", xs, ys, xe, ye, len);
    priv->tftops->set_addr_win(priv, xs, ys, xe, ye);

    /* 
     * 8080 8-bit Data Bus for 16-bit/pixel (RGB 5-6-5 Bits Input)
     *      DB 7     R4  G2
     *      DB 6     R3  G1
     *      DB 5     R2  G0
     *      DB 4     R1  B4
     *      DB 3     R0  B3
     *      DB 2     G5  B2
     *      DB 1     G4  B1
     *      DB 0     G3  B0
     * But a 16-bit Data Bus RGB565 order like this:
     * B0 - B4, G0 - G5, R0 - R4 from DB0 to DB16
     * So simply swap 2 bytes here from pixel buffer.
     */
    u16 *p = (u16 *)vmem;
    for (size_t i = 0; i < len; i++)
        p[i] = (p[i] << 8) | (p[i] >> 8);

    write_buf_rs(priv, vmem, len * 2, 1);
}

static struct tft_display r61509v = {
    .xres   = TFT_X_RES,
    .yres   = TFT_Y_RES,
    .bpp    = 16,
    .backlight = 100,
    .tftops = {
        .write_reg = tft_write_reg16,
        .init_display = tft_r61509v_init_display,
        .set_addr_win = tft_r61509v_set_addr_win,
        .clear = tft_clear,
        .video_sync = tft_video_sync,
    },
};

int tft_driver_init(void)
{
    tft_probe(&r61509v);
    return 0;
}

#endif