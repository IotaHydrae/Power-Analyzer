#include <string.h>

#include "lvgl.h"
#include "ui/ui.h"
#include "ui/screens.h"

#include "ui_ext.h"
#include "settings.h"
#include "porting/lv_port_indev_template.h"

#define SAMPLE_DATA_SIZE 50

static lv_coord_t ecg_sample[SAMPLE_DATA_SIZE];
static lv_timer_t *chart_current_timer;

static void add_data(lv_timer_t *t)
{
    LV_UNUSED(t);
    lv_obj_t *chart = t->user_data;

    /* Generate random dummy data for the chart */
    for (int i = 0; i < sizeof(ecg_sample) / sizeof(ecg_sample[0]); i++) {
        ecg_sample[i] = lv_rand(-800, 800);
    }
    lv_chart_set_ext_y_array(chart, lv_chart_get_series_next(chart, NULL), (lv_coord_t *)ecg_sample);
}

void page_home_finalize(void)
{
    encoder_group_add_obj(objects.home_btn_home);
    encoder_group_add_obj(objects.home_btn_statistics);
    encoder_group_add_obj(objects.home_btn_pd);
    encoder_group_add_obj(objects.home_btn_settings);

    lv_obj_t *chart = objects.home_chart_current;
    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, -1000, 1000);
    lv_obj_set_style_size(chart, 0, LV_PART_INDICATOR);
    lv_chart_series_t * ser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_YELLOW), LV_CHART_AXIS_PRIMARY_Y);

    uint32_t pcnt = sizeof(ecg_sample) / sizeof(ecg_sample[0]);
    lv_chart_set_point_count(chart, pcnt);
    lv_chart_set_ext_y_array(chart, ser, (lv_coord_t *)ecg_sample);

    chart_current_timer = lv_timer_create(add_data, 100, chart);
    lv_timer_pause(chart_current_timer);
}

void action_chart_current_pause(lv_event_t * e)
{
    lv_log("%s\n", __func__);
    if (chart_current_timer)
        lv_timer_pause(chart_current_timer);
}

void action_chart_current_resume(lv_event_t * e)
{
    lv_log("%s\n", __func__);
    if (chart_current_timer)
        lv_timer_resume(chart_current_timer);
}

static void btn_power_event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_current_target(e);
    lv_obj_t *btn_power = lv_event_get_user_data(e);
    // LV_LOG_USER("Button %s clicked", lv_msgbox_get_active_btn_text(obj));
    if (0 == strcmp(lv_msgbox_get_active_btn_text(obj), "Yes")) {
        /* TODO: if so, perform a real power off here */
        lv_log("system power off\n");
        lv_msgbox_close(obj);
    } else {
        lv_obj_add_state(btn_power, LV_STATE_DEFAULT);
        lv_timer_resume(chart_current_timer);
        lv_msgbox_close(obj);
    }
}
void action_btn_power(lv_event_t *e)
{
    lv_log("%s\n", __func__);
    lv_obj_t *btn_power = objects.home_btn_power;

    /* TODO: pop out a dialog box to confirm power off */
    static const char * btns[] = {"Yes", "No", ""};
    lv_timer_pause(chart_current_timer);

    lv_obj_t * mbox1 = lv_msgbox_create(NULL, "Warn", "Power OFF the device?", btns, true);
    lv_obj_add_event_cb(mbox1, btn_power_event_cb, LV_EVENT_VALUE_CHANGED, btn_power);
    lv_obj_center(mbox1);
}
