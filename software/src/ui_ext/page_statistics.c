#include <string.h>

#include "lvgl.h"
#include "ui/ui.h"
#include "ui/screens.h"
#include "lv_i18n/lv_i18n.h"

#include "ui_ext.h"
#include "settings.h"
#include "porting/lv_port_indev_template.h"

LV_FONT_DECLARE(ui_font_ns14);

lv_obj_t *table;

static void draw_part_event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);
    /*If the cells are drawn...*/
    if(dsc->part == LV_PART_ITEMS) {
        uint32_t row = dsc->id /  lv_table_get_col_cnt(obj);
        uint32_t col = dsc->id - row * lv_table_get_col_cnt(obj);

        /*Make the texts in the first cell center aligned*/
        // if(row == 0) {
        //     dsc->label_dsc->align = LV_TEXT_ALIGN_CENTER;
        //     dsc->rect_dsc->bg_color = lv_color_mix(lv_palette_main(LV_PALETTE_BLUE), dsc->rect_dsc->bg_color, LV_OPA_20);
        //     dsc->rect_dsc->bg_opa = LV_OPA_COVER;
        // }
        /*In the first column align the texts to the right*/
        if(col == 0) {
            dsc->label_dsc->align = LV_TEXT_ALIGN_RIGHT;
        }

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

    table = objects.statistics_table;
    lv_obj_set_style_text_font(table, &ui_font_ns14, LV_PART_MAIN | LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_table_set_col_width(table, 0, 120);
    lv_table_set_col_width(table, 1, 120);

    lv_table_set_cell_value(table, 0, 0, _("statistics_avg_current_per_second"));
    lv_table_set_cell_value(table, 1, 0, _("statistics_avg_current_per_minute"));
    lv_table_set_cell_value(table, 2, 0, _("statistics_avg_currnet_total"));
    lv_table_set_cell_value(table, 3, 0, _("statistics_rtc_time"));
    lv_table_set_cell_value(table, 4, 0, _("statistics_instant_peak_currnet"));
    lv_table_set_cell_value(table, 5, 0, _("statistics_minimum_no_zero_currnet"));

    lv_table_set_cell_value(table, 0, 2, _("statistics_total_capacity"));
    lv_table_set_cell_value(table, 1, 2, _("statistics_total_energy"));

    /*Fill the second column*/
    lv_table_set_cell_value(table, 0, 1, "0");
    lv_table_set_cell_value(table, 1, 1, "0");
    lv_table_set_cell_value(table, 2, 1, "0");
    lv_table_set_cell_value(table, 3, 1, "0");
    lv_table_set_cell_value(table, 4, 1, "0");
    lv_table_set_cell_value(table, 5, 1, "0");

    lv_table_set_cell_value(table, 0, 3, "0");
    lv_table_set_cell_value(table, 1, 3, "0");

    lv_obj_add_event_cb(table, draw_part_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);
}
