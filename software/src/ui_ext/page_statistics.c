#include <stdio.h>
#include <string.h>

#include "lvgl.h"
#include "ui/ui.h"
#include "ui/screens.h"
#include "lv_i18n/lv_i18n.h"

#include "ui_ext.h"
#include "settings.h"
#include "porting/lv_port_indev_template.h"

LV_FONT_DECLARE(ui_font_ns14);

#define TBL_TAG_CUR_PER_SECOND  0, 0
#define TBL_TAG_CUR_PER_MINUTE  1, 0
#define TBL_TAG_CUR_TOTAL       2, 0
#define TBL_TAG_RTC_TIME        3, 0
#define TBL_TAG_MAX_CUR         4, 0
#define TBL_TAG_MIN_CUR         5, 0
#define TBL_TAG_CAP_TOTAL       0, 2
#define TBL_TAG_ENG_TOTAL       1, 2

#define TBL_VAL_CUR_PER_SECOND  0, 1
#define TBL_VAL_CUR_PER_MINUTE  1, 1
#define TBL_VAL_CUR_TOTAL       2, 1
#define TBL_VAL_RTC_TIME        3, 1
#define TBL_VAL_MAX_CUR         4, 1
#define TBL_VAL_MIN_CUR         5, 1
#define TBL_VAL_CAP_TOTAL       0, 3
#define TBL_VAL_ENG_TOTAL       1, 3

lv_obj_t *tbl_statistics;

static void tbl_statistics_make_random_data(lv_timer_t *t)
{
    lv_obj_t *tbl = t->user_data;

    static char buf_cur_per_second[16];
    static char buf_cur_per_minute[16];
    static char buf_cur_total[16];
    static char buf_rtc_time[16];
    static char buf_max_cur[16];
    static char buf_min_cur[16];
    static char buf_cap_total[16];
    static char buf_eng_total[16];

    sprintf(buf_cur_per_second, "%02d.%02d uA", lv_rand(0, 99), lv_rand(0, 99));
    sprintf(buf_cur_per_minute, "%02d.%02d uA", lv_rand(0, 99), lv_rand(0, 99));
    sprintf(buf_cur_total, "%02d.%02d uA", lv_rand(0, 99), lv_rand(0, 99));
    sprintf(buf_rtc_time, "%02d:%02d:%02d", lv_rand(0, 24), lv_rand(0, 59), lv_rand(0, 59));
    sprintf(buf_max_cur, "%02d.%02d uA", lv_rand(0, 99), lv_rand(0, 99));
    sprintf(buf_min_cur, "%02d.%02d uA", lv_rand(0, 99), lv_rand(0, 99));
    sprintf(buf_cap_total, "%02d.%02d uAh", lv_rand(0, 99), lv_rand(0, 99));
    sprintf(buf_eng_total, "%02d.%02d uWh", lv_rand(0, 99), lv_rand(0, 99));

    lv_table_set_cell_value(tbl, TBL_VAL_CUR_PER_SECOND, buf_cur_per_second);
    lv_table_set_cell_value(tbl, TBL_VAL_CUR_PER_MINUTE, buf_cur_per_minute);
    lv_table_set_cell_value(tbl, TBL_VAL_CUR_TOTAL,      buf_cur_total);
    lv_table_set_cell_value(tbl, TBL_VAL_RTC_TIME,       buf_rtc_time);
    lv_table_set_cell_value(tbl, TBL_VAL_MAX_CUR,        buf_max_cur);
    lv_table_set_cell_value(tbl, TBL_VAL_MIN_CUR,        buf_min_cur);

    lv_table_set_cell_value(tbl, TBL_VAL_CAP_TOTAL,      buf_cap_total);
    lv_table_set_cell_value(tbl, TBL_VAL_ENG_TOTAL,      buf_eng_total);
}

static void draw_part_event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);
    /*If the cells are drawn...*/
    if(dsc->part == LV_PART_ITEMS) {
        uint32_t row = dsc->id /  lv_table_get_col_cnt(obj);
        uint32_t col = dsc->id - row * lv_table_get_col_cnt(obj);

        /*In the first column align the texts to the right*/
        if(col == 0 || col == 2)
            dsc->label_dsc->align = LV_TEXT_ALIGN_RIGHT;

        if(col == 1 || col == 3)
            dsc->label_dsc->align = LV_TEXT_ALIGN_CENTER;

        /*Make every 2nd row grayish*/
        if((row != 0 && row % 2) == 0) {
            dsc->rect_dsc->bg_color = lv_color_mix(lv_palette_main(LV_PALETTE_BLUE), dsc->rect_dsc->bg_color, LV_OPA_10);
            dsc->rect_dsc->bg_opa = LV_OPA_COVER;
        }
    }
}

void page_statistics_finalize(void)
{
    encoder_group_add_obj(objects.statistics_btn_home);
    encoder_group_add_obj(objects.statistics_btn_statistics);
    encoder_group_add_obj(objects.statistics_btn_usb);
    encoder_group_add_obj(objects.statistics_btn_settings);

    tbl_statistics = objects.statistics_table;
    lv_obj_set_style_text_font(tbl_statistics, &ui_font_ns14, LV_PART_MAIN | LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_table_set_col_width(tbl_statistics, 0, 120);
    lv_table_set_col_width(tbl_statistics, 1, 95);
    lv_table_set_col_width(tbl_statistics, 2, 120);
    lv_table_set_col_width(tbl_statistics, 3, 95);

    lv_table_set_cell_value(tbl_statistics, TBL_TAG_CUR_PER_SECOND, _("statistics_avg_current_per_second"));
    lv_table_set_cell_value(tbl_statistics, TBL_TAG_CUR_PER_MINUTE, _("statistics_avg_current_per_minute"));
    lv_table_set_cell_value(tbl_statistics, TBL_TAG_CUR_TOTAL, _("statistics_avg_currnet_total"));
    lv_table_set_cell_value(tbl_statistics, TBL_TAG_RTC_TIME, _("statistics_rtc_time"));
    lv_table_set_cell_value(tbl_statistics, TBL_TAG_MAX_CUR, _("statistics_instant_peak_currnet"));
    lv_table_set_cell_value(tbl_statistics, TBL_TAG_MIN_CUR, _("statistics_minimum_no_zero_currnet"));

    lv_table_set_cell_value(tbl_statistics, TBL_TAG_CAP_TOTAL, _("statistics_total_capacity"));
    lv_table_set_cell_value(tbl_statistics, TBL_TAG_ENG_TOTAL, _("statistics_total_energy"));

    /*Fill the second column*/
    lv_table_set_cell_value(tbl_statistics, TBL_VAL_CUR_PER_SECOND, "0 uA");
    lv_table_set_cell_value(tbl_statistics, TBL_VAL_CUR_PER_MINUTE, "0 uA");
    lv_table_set_cell_value(tbl_statistics, TBL_VAL_CUR_TOTAL,      "0 uA");
    lv_table_set_cell_value(tbl_statistics, TBL_VAL_RTC_TIME,       "00:00:00");
    lv_table_set_cell_value(tbl_statistics, TBL_VAL_MAX_CUR,        "0 uA");
    lv_table_set_cell_value(tbl_statistics, TBL_VAL_MIN_CUR,        "0 uA");

    lv_table_set_cell_value(tbl_statistics, TBL_VAL_CAP_TOTAL,      "0 uAh");
    lv_table_set_cell_value(tbl_statistics, TBL_VAL_ENG_TOTAL,      "0 uWh");

    lv_obj_add_event_cb(tbl_statistics, draw_part_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);
    lv_timer_create(tbl_statistics_make_random_data, 33, tbl_statistics);
}
