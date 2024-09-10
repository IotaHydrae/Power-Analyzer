#include <stdio.h>
#include "pico/stdlib.h"

#include "version.h"

#define SETTINGS_BASE (XIP_BASE + 2 * 1000 * 1024)

#define MAGIC_HEADER 0xfba3d0b0

typedef unsigned int u32;

struct settings {
    u32 magic;
    u32 sn[2];
    u32 sw_version;
    u32 hw_version;
    u32 boot_count;

    u32 cut_vol;
    u32 cut_curr;

    u32 ref_rate;
    u32 chart_line_color;

    u32 calibrate_mode;

    u32 bl_lvl;
    // u32 crc32;
};

static const struct settings __attribute__((section(".settings"))) __attribute__((__used__)) default_settings = {
    .magic = MAGIC_HEADER,
    .sn = UINT32_MAX,
    .sw_version = SW_VERSION_NUMBER,
    .hw_version = 0,
    .bl_lvl = 0,
    // .crc32 = 0
};

static struct settings *current_settings = (struct settings *)SETTINGS_BASE;

void save_settings(void)
{
    printf("Saving settings\n");
}

void load_settings(void)
{
    printf("Loading settings\n");
}

void restore_defaults_settings(void)
{

}

void settings_init(void)
{
    if (current_settings->boot_count == 0) {
        /* This is the first boot, do the initialization */
        printf("First boot\n");
    }

    if (current_settings->magic != MAGIC_HEADER) {
        /* The settings are corrupted, restore defaults */
        printf("Settings corrupted, restoring defaults\n");
        restore_defaults_settings();
    }

    current_settings->boot_count += 1;
    save_settings();
}
