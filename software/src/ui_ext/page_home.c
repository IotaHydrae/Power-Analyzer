#include <string.h>
#include <math.h>

#include "lvgl.h"
#include "ui/ui.h"
#include "ui/screens.h"

#include "ui_ext.h"
#include "settings.h"
#include "backlight.h"
#include "porting/lv_port_indev_template.h"

#define SAMPLE_DATA_SIZE 50

static lv_coord_t ecg_sample[SAMPLE_DATA_SIZE];
static lv_timer_t *chart_current_timer;

static void chart_demo_1_add_data(lv_timer_t *t)
{
    LV_UNUSED(t);
    lv_obj_t *chart = t->user_data;

    /* Generate random dummy data for the chart */
    for (int i = 0; i < sizeof(ecg_sample) / sizeof(ecg_sample[0]); i++) {
        ecg_sample[i] = lv_rand(-800, 800);
    }
    lv_chart_set_ext_y_array(chart, lv_chart_get_series_next(chart, NULL), (lv_coord_t *)ecg_sample);
}

static void chart_demo_1(lv_obj_t *chart, lv_chart_series_t *ser)
{
    uint32_t pcnt = sizeof(ecg_sample) / sizeof(ecg_sample[0]);
    lv_chart_set_point_count(chart, pcnt);
    lv_chart_set_ext_y_array(chart, ser, (lv_coord_t *)ecg_sample);

    chart_current_timer = lv_timer_create(chart_demo_1_add_data, 33, chart);
    // lv_timer_pause(chart_current_timer);
}

static void chart_demo_2_add_data(lv_timer_t *t)
{
    lv_obj_t *chart = t->user_data;

#define ZERO_BASE 80
    uint base1 = lv_rand(20, 30) + ZERO_BASE;
    uint base2 = lv_rand(320, 340) + ZERO_BASE;

    uint offs = lv_rand(0, 20);

    for (int i = 0; i < SAMPLE_DATA_SIZE; i ++) {
        lv_chart_set_next_value(chart, lv_chart_get_series_next(chart, NULL), lv_rand(base1-offs, base1+offs));
        lv_chart_refresh(chart);
    }

    for (int i = 0; i < SAMPLE_DATA_SIZE; i ++) {
        lv_chart_set_next_value(chart, lv_chart_get_series_next(chart, NULL), lv_rand(base2-offs, base2+offs));
        lv_chart_refresh(chart);
    }

    for (int i = 0; i < SAMPLE_DATA_SIZE; i ++) {
        lv_chart_set_next_value(chart, lv_chart_get_series_next(chart, NULL), lv_rand(base1-offs, base1+offs));
        lv_chart_refresh(chart);
    }
}


static void chart_demo_2(lv_obj_t *chart, lv_chart_series_t *ser)
{
    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 540);
    lv_chart_set_point_count(chart, 1000);
    chart_current_timer = lv_timer_create(chart_demo_2_add_data, 33, chart);
}

static void chart_demo_3_add_data(lv_timer_t *t)
{
    lv_obj_t *chart = t->user_data;
    for (double i = 0; i < 600; i++) {
        double data = (sin(i/50.0f) * 150) + 180 + lv_rand(10, 20);
        lv_chart_set_next_value(chart, lv_chart_get_series_next(chart, NULL), (int)data);
    }
    lv_chart_refresh(chart);
}

static void chart_demo_3(lv_obj_t *chart, lv_chart_series_t *ser)
{
    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 420);
    lv_chart_set_point_count(chart, 1200);
    chart_current_timer = lv_timer_create(chart_demo_3_add_data, 33, chart);
}

void page_home_finalize(void)
{
    encoder_group_add_obj(objects.home_btn_home);
    encoder_group_add_obj(objects.home_btn_statistics);
    encoder_group_add_obj(objects.home_btn_usb);
    encoder_group_add_obj(objects.home_btn_settings);

    lv_obj_t *chart = objects.home_chart_current;
    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, -1000, 1000);
    lv_obj_set_style_size(chart, 0, LV_PART_INDICATOR);
    lv_chart_series_t * ser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_YELLOW), LV_CHART_AXIS_PRIMARY_Y);

    // chart_demo_1(chart, ser);
    // chart_demo_2(chart, ser);
    chart_demo_3(chart, ser);
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

void action_set_blk_off(lv_event_t * e)
{
    backlight_set_level(0);
}

void action_set_blk_on(lv_event_t * e)
{
    backlight_set_level(settings_get_bl_lvl());
}
