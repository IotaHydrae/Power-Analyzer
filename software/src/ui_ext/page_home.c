#include "lvgl.h"
#include "ui/ui.h"
#include "ui/screens.h"

#include "ui_ext.h"

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
    lv_obj_t *chart = objects.home_chart_current;
    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, -1000, 1000);
    lv_obj_set_style_size(chart, 0, LV_PART_INDICATOR);
    lv_chart_series_t * ser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);

    uint32_t pcnt = sizeof(ecg_sample) / sizeof(ecg_sample[0]);
    lv_chart_set_point_count(chart, pcnt);
    lv_chart_set_ext_y_array(chart, ser, (lv_coord_t *)ecg_sample);

    chart_current_timer = lv_timer_create(add_data, 50, chart);
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
