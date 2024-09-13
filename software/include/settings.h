#ifndef __SETTINGS_H
#define __SETTINGS_H

#include "pico/stdlib.h"

enum {
    SETTINGS_LANG_ZH_CN,
    SETTINGS_LANG_EN_US,
};

void settings_init(void);
void settings_set_language(unsigned lang);
void settings_get_sn(uint8_t *sn_out);
unsigned int settings_get_boot_count(void);

#endif
