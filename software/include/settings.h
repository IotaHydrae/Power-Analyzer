#ifndef __SETTINGS_H
#define __SETTINGS_H

enum {
    SETTINGS_LANG_ZH_CN,
    SETTINGS_LANG_EN_US,
};

void settings_init(void);
void settings_set_language(unsigned lang);
unsigned int settings_get_boot_count(void);

#endif
