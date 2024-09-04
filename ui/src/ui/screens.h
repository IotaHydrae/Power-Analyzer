#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *home;
    lv_obj_t *settings;
    lv_obj_t *button_home_1;
    lv_obj_t *button_home_2;
    lv_obj_t *button_meter_1;
    lv_obj_t *button_meter_2;
    lv_obj_t *button_ops;
    lv_obj_t *button_power;
    lv_obj_t *button_setting_1;
    lv_obj_t *button_setting_2;
    lv_obj_t *chart_current;
    lv_obj_t *label_ops_pause;
    lv_obj_t *label_ops_play;
    lv_obj_t *menu_setting;
    lv_obj_t *nav_bar_1;
    lv_obj_t *nav_bar_2;
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