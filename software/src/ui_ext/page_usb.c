#include <string.h>

#include "lvgl.h"
#include "ui/ui.h"
#include "ui/screens.h"

#include "ui_ext.h"
#include "settings.h"
#include "porting/lv_port_indev_template.h"

void page_usb_finalize(void)
{
    encoder_group_add_obj(objects.usb_btn_home);
    encoder_group_add_obj(objects.usb_btn_statistics);
    encoder_group_add_obj(objects.usb_btn_usb);
    encoder_group_add_obj(objects.usb_btn_settings);

    lv_dropdown_clear_options(objects.ddlist_pd_power_protection);
    lv_dropdown_clear_options(objects.ddlist_pd_vol_setting);
}
