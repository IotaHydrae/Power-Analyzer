#ifndef __UI_EXT_H
#define __UI_EXT_H

#include "lvgl/lvgl.h"

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

void page_home_finalize(void);
void page_statistics_finalize(void);
void page_usb_finalize(void);
void page_settings_finalize(void);

void ui_finalize(void);

void ddlist_add_opts(lv_obj_t *ddlist, const char **opts);

#endif
