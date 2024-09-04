#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *home;
    lv_obj_t *settings;
    lv_obj_t *home_btn_home;
    lv_obj_t *home_btn_meter;
    lv_obj_t *home_btn_ops;
    lv_obj_t *home_btn_ops_lbl_pause;
    lv_obj_t *home_btn_ops_lbl_resume;
    lv_obj_t *home_btn_pd;
    lv_obj_t *home_btn_power;
    lv_obj_t *home_btn_settings;
    lv_obj_t *home_btn_statistics;
    lv_obj_t *home_btn_title;
    lv_obj_t *home_btn_title_lbl_hint;
    lv_obj_t *home_chart_current;
    lv_obj_t *home_nav_bar;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *obj10;
    lv_obj_t *obj2;
    lv_obj_t *obj3;
    lv_obj_t *obj4;
    lv_obj_t *obj5;
    lv_obj_t *obj6;
    lv_obj_t *obj7;
    lv_obj_t *obj8;
    lv_obj_t *obj9;
    lv_obj_t *settings_btn_home;
    lv_obj_t *settings_btn_meter;
    lv_obj_t *settings_btn_pd;
    lv_obj_t *settings_btn_settings;
    lv_obj_t *settings_btn_statistics;
    lv_obj_t *settings_menu_settings;
    lv_obj_t *settings_nav_bar;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_HOME = 1,
    SCREEN_ID_SETTINGS = 2,
    SCREEN_ID_NAV = 3,
};

void create_screen_home();
void tick_screen_home();

void create_screen_settings();
void tick_screen_settings();

void create_user_widget_nav(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_nav(void *flowState, int startWidgetIndex);

void create_screens();
void tick_screen(int screen_index);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/