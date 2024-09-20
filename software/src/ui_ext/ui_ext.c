#include <stdio.h>

#include "lvgl.h"
#include "ui/ui.h"
#include "ui/screens.h"

#include "ui_ext.h"
#include "settings.h"

#include "porting/lv_port_indev_template.h"

void ddlist_add_opts(lv_obj_t *ddlist, const char **opts)
{
    const char **ptr = opts;
    while (*ptr != NULL)
        lv_dropdown_add_option(ddlist, *ptr++, LV_DROPDOWN_POS_LAST);
}

void ui_finalize(void)
{
    printf("boot count : %d\n", settings_get_boot_count());
    page_home_finalize();
    page_statistics_finalize();
    page_usb_finalize();
    page_settings_finalize();
}
