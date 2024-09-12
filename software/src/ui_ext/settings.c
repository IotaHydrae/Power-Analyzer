#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"

#include "version.h"
#include "flash.h"
#include "settings.h"

#define SETTINGS_BASE (2 * 1000 * 1024)
#define SETTINGS_2_BASE (2 * 1000 * 1024 + 16 * 1024)

enum {
    SETTINGS_1 = 1,
    SETTINGS_2 = 2,
};

#define MAGIC_HEADER 0xfba3d0b1

typedef unsigned int u32;

struct settings {
    u32 magic;
    u32 sn[2];
    u32 sw_version;
    u32 hw_version;
    u32 boot_count;
    u32 partition;

    u32 cut_vol;
    u32 cut_curr;

    u32 ref_rate;
    u32 chart_line_color;

    u32 calibrate_mode;

    u32 bl_lvl;
    // u32 crc32;
};

static struct settings __attribute__((section(".settings"))) __attribute__((used)) settings = {0};
static struct settings __attribute__((section(".settings_2"))) __attribute__((used)) settings_2 = {0};
static const struct settings __attribute__((section(".settings_bak"))) __attribute__((used)) default_settings = {
    .magic = MAGIC_HEADER,
    .sn[0] = 0x12345678,
    .sn[1] = 0x87654321,
    .sw_version = SW_VERSION_NUMBER,
    .hw_version = 0,
    .boot_count = 0,
    .partition = 3,
    // .crc32 = 0
};


/* current settings is read only */
static struct settings *current_settings = NULL;

/* these settings read out from flash, and could be modified at any time, then save to flash */
static struct settings runtime_settings = {
    .partition = SETTINGS_1,
};
static struct settings runtime_settings_2 = {
    .partition = SETTINGS_2,
};

static void set_curr_settings(uint n)
{
    switch (n) {
    case SETTINGS_1:
        current_settings = (struct settings *)&settings;
        break;
    case SETTINGS_2:
        current_settings = (struct settings *)&settings_2;
        break;
    default:
        current_settings = (struct settings *)&default_settings;
        break;
    }
}

void save_settings(void)
{
    printf("Saving settings\n");
    switch (current_settings->partition) {
    case SETTINGS_1:
        flash_write(SETTINGS_BASE, &runtime_settings, sizeof(runtime_settings));
        break;
    case SETTINGS_2:
        flash_write(SETTINGS_2_BASE, &runtime_settings_2, sizeof(runtime_settings_2));
        break;
    default:
        flash_write(SETTINGS_BASE, &runtime_settings, sizeof(runtime_settings));
        break;
    }
}

void load_settings(void)
{
    printf("Loading settings\n");
    switch (current_settings->partition) {
    case SETTINGS_1:
        memcpy(&runtime_settings, current_settings, sizeof(struct settings));
        break;
    case SETTINGS_2:
        memcpy(&runtime_settings_2, current_settings, sizeof(runtime_settings_2));
        break;
    default:
        memcpy(&runtime_settings, current_settings, sizeof(runtime_settings));
        break;
    }
}

void restore_defaults_settings(void)
{
    switch (current_settings->partition) {
    case SETTINGS_1:
        memcpy(&runtime_settings, &default_settings, sizeof(struct settings));
        break;
    case SETTINGS_2:
        memcpy(&runtime_settings_2, &default_settings, sizeof(struct settings));
        break;
    default:
        memcpy(&runtime_settings, &default_settings, sizeof(struct settings));
        break;
    }
    save_settings();
}

uint settings_get_boot_count(void)
{
    return current_settings->boot_count;
}

void increase_boot_count(void)
{
    switch (current_settings->partition) {
    case SETTINGS_1:
        runtime_settings.boot_count += 1;
        break;
    case SETTINGS_2:
        runtime_settings_2.boot_count += 1;
        break;
    default:
        runtime_settings.boot_count += 1;
        break;
    }
}

static void dump_settings(const struct settings *s)
{
    if (!s)
        return;

    printf("Settings:\n");
    printf("\tmagic: 0x%08x\n", s->magic);
    printf("\tsn: 0x%08x 0x%08x\n", s->sn[0], s->sn[1]);
    printf("\tsw_version: 0x%08x\n", s->sw_version);
    printf("\thw_version: 0x%08x\n", s->hw_version);
    printf("\tboot_count: %d\n", s->boot_count);
    printf("\tpartition: %d\n", s->partition);
}

static void dump_def_settings(void)
{
    dump_settings(&default_settings);
}

static void dump_curr_settings(void)
{
    dump_settings(current_settings);
}

void settings_init(void)
{
    flash_init();
    printf("settings_1 : %p\n", (void *)&settings);
    printf("settings_2 : %p\n", (void *)&settings_2);
    printf("default_settings : %p\n", (void *)&default_settings);
    set_curr_settings(SETTINGS_1);

    if (current_settings->boot_count <= 0) {
        /* This is the first boot, do the initialization */
        printf("This is the first boot, do the initialization\n");
        restore_defaults_settings();
    }
    dump_curr_settings();
    load_settings();

    // if (current_settings->magic != MAGIC_HEADER) {
    //     /* The settings are corrupted, restore defaults */
    //     printf("Settings corrupted, restoring defaults\n");
    //     restore_defaults_settings();
    // }

    increase_boot_count();
    save_settings();
}

