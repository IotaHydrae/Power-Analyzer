#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_chart_current_pause(lv_event_t * e);
extern void action_chart_current_resume(lv_event_t * e);
extern void action_set_blk_off(lv_event_t * e);
extern void action_set_blk_on(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/