#ifndef __SETTINGS_H
#define __SETTINGS_H

#include "pico/stdlib.h"

enum {
    SETTINGS_LANG_ZH_CN,
    SETTINGS_LANG_EN_US,
};

enum {
    SETTINGS_REFR_RATE_30FPS,
    SETTINGS_REFR_RATE_45FPS,
    SETTINGS_REFR_RATE_60FPS,
};

enum {
    SETTINGS_CALIB_MODED_FACTORY,
    SETTINGS_CALIB_MODED_USER,
};

void settings_init(void);
unsigned int settings_get_boot_count(void);
void settings_set_refr_rate(unsigned rate);
uint settings_get_refr_rate(void);
void settings_set_calib_mode(unsigned mode);
uint settings_get_calib_mode(void);
void settings_set_language(unsigned lang);
uint settings_get_language(void);
void settings_get_sn(uint8_t *sn_out);

#endif
