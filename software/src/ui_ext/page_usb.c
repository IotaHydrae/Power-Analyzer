#include <string.h>

#include "lvgl.h"
#include "ui/ui.h"
#include "ui/screens.h"

#include "ui_ext.h"
#include "settings.h"
#include "porting/lv_port_indev_template.h"

LV_FONT_DECLARE(ui_font_ns14)

static void sw_pd_func_enable_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *sw = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED)
        LV_LOG_WARN("PD Function : %s\n", lv_obj_has_state(sw, LV_STATE_CHECKED) ? "ON" : "OFF");
}

static void dd_pd_vol_setting_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    // lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        // char buf[32];

        lv_obj_t *sw = objects.sw_pd_func_enable;
        if (lv_obj_has_state(sw, LV_STATE_CHECKED)) {
            lv_obj_clear_state(sw, LV_STATE_CHECKED);
            lv_event_send(sw, LV_EVENT_VALUE_CHANGED, NULL);
        }

    }
}

void page_usb_finalize(void)
{
    encoder_group_add_obj(objects.usb_btn_home);
    encoder_group_add_obj(objects.usb_btn_statistics);
    encoder_group_add_obj(objects.usb_btn_usb);
    encoder_group_add_obj(objects.usb_btn_settings);

    static lv_style_t style_dd;
    lv_style_init(&style_dd);
    lv_style_set_text_font(&style_dd, &ui_font_ns14);

    lv_obj_t *ddlist, *list;

    /* 完善PD功率保护设置 */
    ddlist = objects.ddlist_pd_power_protection;
    lv_obj_add_style(ddlist, &style_dd, LV_PART_MAIN | LV_STATE_DEFAULT);
    list = lv_dropdown_get_list(ddlist);
    lv_obj_add_style(list, &style_dd, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_dropdown_clear_options(ddlist);

    /* 完善PD功能开启 */
    lv_obj_t *sw_pd_func = objects.sw_pd_func_enable;
    lv_obj_add_event_cb(sw_pd_func, sw_pd_func_enable_handler, LV_EVENT_ALL, NULL);

    /* 完善PD电压设置 */
    ddlist = objects.ddlist_pd_vol_setting;
    lv_obj_add_style(ddlist, &style_dd, LV_PART_MAIN | LV_STATE_DEFAULT);
    list = lv_dropdown_get_list(ddlist);
    lv_obj_add_style(list, &style_dd, LV_PART_MAIN | LV_STATE_DEFAULT);

    const char *pd_vol_opts[] = {
        "5V",
        "9V",
        "12V",
        "15V",
        "20V",
        NULL,
    };
    lv_dropdown_clear_options(ddlist);
    ddlist_add_opts(ddlist, pd_vol_opts);
    lv_obj_add_event_cb(ddlist, dd_pd_vol_setting_handler, LV_EVENT_VALUE_CHANGED, NULL);
}
