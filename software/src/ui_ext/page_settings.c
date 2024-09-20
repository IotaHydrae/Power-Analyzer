#include <stdio.h>

#include "hardware/watchdog.h"

#include "lvgl.h"
#include "lv_i18n/lv_i18n.h"
#include "ui/ui.h"
#include "ui/screens.h"

#include "ui_ext.h"
#include "settings.h"
#include "backlight.h"
#include "porting/lv_port_indev_template.h"

LV_FONT_DECLARE(ui_font_ns14);

enum {
    LV_MENU_ITEM_BUILDER_VARIANT_1,
    LV_MENU_ITEM_BUILDER_VARIANT_2
};
typedef uint8_t lv_menu_builder_variant_t;

static void back_event_handler(lv_event_t * e);
static void switch_handler(lv_event_t * e);
static lv_obj_t * create_text(lv_obj_t * parent, const char * icon, const char * txt,
                              lv_menu_builder_variant_t builder_variant);
static lv_obj_t * create_slider(lv_obj_t * parent,
                                const char * icon, const char * txt, int32_t min, int32_t max, volatile int32_t val);
static lv_obj_t * create_switch(lv_obj_t * parent,
                                const char * icon, const char * txt, bool chk);

lv_obj_t * root_page;
static void back_event_handler(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    lv_obj_t * menu = lv_event_get_user_data(e);

    if(lv_menu_back_btn_is_root(menu, obj)) {
        lv_obj_t * mbox1 = lv_msgbox_create(NULL, "Hello", "Root back btn click.", NULL, true);
        lv_obj_center(mbox1);
    }
}

static void switch_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * menu = lv_event_get_user_data(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        if(lv_obj_has_state(obj, LV_STATE_CHECKED)) {
            lv_menu_set_page(menu, NULL);
            lv_menu_set_sidebar_page(menu, root_page);
            lv_event_send(lv_obj_get_child(lv_obj_get_child(lv_menu_get_cur_sidebar_page(menu), 0), 0), LV_EVENT_CLICKED, NULL);
        }
        else {
            lv_menu_set_sidebar_page(menu, NULL);
            lv_menu_clear_history(menu); /* Clear history because we will be showing the root page later */
            lv_menu_set_page(menu, root_page);
        }
    }
}

static lv_obj_t * create_text(lv_obj_t * parent, const char * icon, const char * txt,
                              lv_menu_builder_variant_t builder_variant)
{
    lv_obj_t * obj = lv_menu_cont_create(parent);

    lv_obj_t * img = NULL;
    lv_obj_t * label = NULL;

    if(icon) {
        img = lv_img_create(obj);
        lv_img_set_src(img, icon);
    }

    if(txt) {
        label = lv_label_create(obj);
        lv_obj_set_style_text_font(label, &ui_font_ns14, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_label_set_text(label, txt);
        lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
        lv_obj_set_flex_grow(label, 1);
    }

    if(builder_variant == LV_MENU_ITEM_BUILDER_VARIANT_2 && icon && txt) {
        lv_obj_add_flag(img, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
        lv_obj_swap(img, label);
    }

    return obj;
}

static lv_obj_t * create_btn(lv_obj_t * parent, const char * icon, const char * txt)
{
    lv_obj_t *cont = lv_menu_cont_create(parent);
    lv_obj_t *obj = lv_btn_create(cont);
    encoder_group_add_obj(obj);

    lv_obj_t * img = NULL;
    lv_obj_t * label = NULL;

    if(icon) {
        img = lv_img_create(obj);
        lv_img_set_src(img, icon);
    }

    if(txt) {
        label = lv_label_create(obj);
        lv_obj_set_style_text_font(label, &ui_font_ns14, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_label_set_text(label, txt);
        // lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
        lv_obj_set_flex_grow(label, 1);
        if (img)
            lv_obj_align_to(label, img, LV_ALIGN_LEFT_MID, 20, 0);
    }

    return cont;
}

static lv_obj_t * create_text_with_detail(lv_obj_t *parent, const char *txt, const char * detail)
{
    lv_obj_t * obj = lv_menu_cont_create(parent);

    lv_obj_t * lbl_left = NULL;
    lv_obj_t * lbl_detail = NULL;

    lbl_left = lv_label_create(obj);
    lv_obj_set_style_text_font(lbl_left, &ui_font_ns14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(lbl_left, txt);
    lv_obj_set_flex_grow(lbl_left, 1);

    lbl_detail = lv_label_create(obj);
    lv_obj_set_style_text_font(lbl_detail, &ui_font_ns14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(lbl_detail, detail);
    lv_obj_set_align(obj, LV_ALIGN_RIGHT_MID);

    return obj;
}

static lv_obj_t * create_slider(lv_obj_t * parent, const char * icon, const char * txt, int32_t min, int32_t max,
                                volatile int32_t val)
{
    lv_obj_t * obj = create_text(parent, icon, txt, LV_MENU_ITEM_BUILDER_VARIANT_2);

    lv_obj_t * slider = lv_slider_create(obj);
    lv_obj_set_flex_grow(slider, 1);
    lv_slider_set_range(slider, min, max);
    lv_slider_set_value(slider, val, LV_ANIM_ON);

    // if(icon == NULL) {
    //     lv_obj_add_flag(slider, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
    // }

    return slider;
}

static lv_obj_t * create_switch(lv_obj_t * parent, const char * icon, const char * txt, bool chk)
{
    lv_obj_t * obj = create_text(parent, icon, txt, LV_MENU_ITEM_BUILDER_VARIANT_1);

    lv_obj_t * sw = lv_switch_create(obj);
    lv_obj_add_state(sw, chk ? LV_STATE_CHECKED : 0);
    encoder_group_add_obj(sw);

    return obj;
}

static lv_obj_t * create_dropdown(lv_obj_t *parent, const char *icon,  const char *txt, const char *opts[])
{
    lv_obj_t * obj = create_text(parent, icon, txt, LV_MENU_ITEM_BUILDER_VARIANT_1);

    static lv_style_t style_dd;
    lv_style_init(&style_dd);
    lv_style_set_text_font(&style_dd, &ui_font_ns14);

    lv_obj_t * ddlist = lv_dropdown_create(obj);
    lv_obj_add_style(ddlist, &style_dd, LV_PART_MAIN | LV_STATE_DEFAULT);
    encoder_group_add_obj(ddlist);

    lv_dropdown_clear_options(ddlist);
    ddlist_add_opts(ddlist, opts);
    lv_dropdown_set_selected_highlight(ddlist, true);

    lv_obj_t *list = lv_dropdown_get_list(ddlist);
    lv_obj_add_style(list, &style_dd, LV_PART_MAIN | LV_STATE_DEFAULT);

    return ddlist;
}

void software_reset()
{
    *((volatile uint32_t*)(PPB_BASE + 0x0ED0C)) = 0x5FA0004;
}

static void event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_current_target(e);
    LV_LOG_USER("Button %s clicked", lv_msgbox_get_active_btn_text(obj));

    if (0 == strcmp(_("yes"), lv_msgbox_get_active_btn_text(obj))) {
        lv_msgbox_close(obj);
        LV_LOG_INFO("restarting device...\n");
        /*  TODO: restart the device */
        watchdog_reboot(0, 0, 0);
    } else {
        LV_LOG_INFO("do nothing...\n");
        lv_msgbox_close(obj);
    }
}

void raise_reboot_dialog(void)
{
    static const char *btns[3];
    btns[0] = _("yes");
    btns[1] = _("no");
    btns[2] = "";
    lv_obj_t * dialog = lv_msgbox_create(NULL, _("note"), _("note_restart"), btns, true);
    lv_obj_set_style_text_font(dialog, &ui_font_ns14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_event_cb(dialog, event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_center(dialog);
}

static void save_bl_setting(lv_timer_t *t)
{
    const lv_obj_t *slider = (const lv_obj_t *)t->user_data;
    uint bl_lvl = lv_slider_get_value(slider);
    if (bl_lvl == settings_get_bl_lvl())
        return;

    settings_set_bl_lvl(bl_lvl);
    LV_LOG_WARN("blk lvl %d was saved to flash.\n", lv_slider_get_value(slider));
    lv_timer_del(t);
}

static void slider_bl_knob_released_handler(lv_event_t *e)
{
    LV_LOG_WARN("%s", __func__);
    lv_obj_t *obj = lv_event_get_target(e);
    lv_timer_t *timer = lv_timer_create(save_bl_setting, 200, obj);
    lv_timer_set_repeat_count(timer, 1);
}

static void slider_bl_val_chg_event_handler(lv_event_t * e)
{
    backlight_set_level(lv_slider_get_value(lv_event_get_target(e)));
}

static void switch_settings_automatic_voltage_cut_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    // lv_obj_t * menu = lv_event_get_user_data(e);
    lv_obj_t * obj = lv_event_get_target(e);

    if(code == LV_EVENT_VALUE_CHANGED) {
        lv_log("%s, chk : %s\n", __func__, lv_obj_has_state(obj, LV_STATE_CHECKED)? "true" : "false");
    }

    /* save this setting to flash */
}

static void dd_settings_ui_theme_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        char buf[32];
        lv_dropdown_get_selected_str(obj, buf, sizeof(buf));
        LV_LOG_USER("Option: %s", buf);

        if (0 == strcmp(_("settings_ui_theme_light"), buf)) {
            LV_LOG_USER("Theme set to light\n");
            lv_disp_t *dispp = lv_disp_get_default();
            lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, &ui_font_ns14);
            lv_disp_set_theme(dispp, theme);
        } else if (0 == strcmp(_("settings_ui_theme_dark"), buf)) {
            LV_LOG_USER("Theme set to Dark\n");
            lv_disp_t *dispp = lv_disp_get_default();
            lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, &ui_font_ns14);
            lv_disp_set_theme(dispp, theme);
        } else {
            LV_LOG_ERROR("Given theme is Unsupported!\n");
        }
    }
}

static void dd_settings_ui_refr_rate_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        char buf[32];
        lv_dropdown_get_selected_str(obj, buf, sizeof(buf));
        LV_LOG_USER("Option: %s", buf);

        if (0 == strcmp("30Hz", buf)) {
            LV_LOG_USER("fps set to 30Hz\n");
            settings_set_refr_rate(SETTINGS_REFR_RATE_30FPS);
        } else if (0 == strcmp("45Hz", buf)) {
            LV_LOG_USER("fps set to 45Hz\n");
            settings_set_refr_rate(SETTINGS_REFR_RATE_45FPS);
        } else if (0 == strcmp("60Hz", buf)) {
            LV_LOG_USER("fps set to 60Hz\n");
            settings_set_refr_rate(SETTINGS_REFR_RATE_60FPS);
        } else {
            LV_LOG_ERROR("Given refr rate is Unsupported!\n");
        }

        // raise_reboot_dialog();
    }
}


static void dd_settings_calib_mode_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        char buf[32];
        lv_dropdown_get_selected_str(obj, buf, sizeof(buf));
        LV_LOG_USER("Option: %s", buf);

        if(strcmp(_("settings_calib_mode_factory"), buf) == 0) {
            settings_set_calib_mode(SETTINGS_CALIB_MODED_FACTORY);
        } else if(strcmp(_("settings_calib_mode_user"), buf) == 0) {
            settings_set_calib_mode(SETTINGS_CALIB_MODED_USER);
        } else {
            LV_LOG_ERROR("Given calib mode is Unsupported!\n");
        }

        // raise_reboot_dialog();
    }
}

/* dropdown settings language handler */
static void dd_settings_lang_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        char buf[32];
        lv_dropdown_get_selected_str(obj, buf, sizeof(buf));
        LV_LOG_USER("Option: %s", buf);

        if (strcmp(buf, _("settings_lang_simplified_chinese")) == 0) {
            LV_LOG_USER("language set to chinese");
            settings_set_language(SETTINGS_LANG_ZH_CN);
        } else if (strcmp(buf, _("settings_lang_english")) == 0) {
            LV_LOG_USER("language set to English");
            settings_set_language(SETTINGS_LANG_EN_US);
        } else {
            settings_set_language(SETTINGS_LANG_ZH_CN);
        }

        raise_reboot_dialog();
    }
}

void page_settings_finalize(void)
{
    encoder_group_add_obj(objects.settings_btn_statistics);
    encoder_group_add_obj(objects.settings_btn_usb);
    encoder_group_add_obj(objects.settings_btn_home);
    encoder_group_add_obj(objects.settings_btn_settings);

    lv_obj_t *menu = objects.settings_menu_settings;
    lv_menu_set_mode_root_back_btn(menu, LV_MENU_ROOT_BACK_BTN_DISABLED);

    lv_obj_t * cont;
    lv_obj_t * section;

    /*Create sub pages*/
    lv_obj_t * sub_mechanics_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(sub_mechanics_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    lv_menu_separator_create(sub_mechanics_page);
    section = lv_menu_section_create(sub_mechanics_page);

    cont = create_switch(section, NULL, _("settings_automatic_voltage_cut"), false);
    lv_obj_add_event_cb(lv_obj_get_child(cont, 1), switch_settings_automatic_voltage_cut_handler, LV_EVENT_VALUE_CHANGED, NULL);

    cont = create_switch(section, NULL, _("settings_automatic_current_cut"), false);

    /* 界面设置菜单 */
    lv_obj_t * sub_ui_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(sub_ui_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    lv_menu_separator_create(sub_ui_page);
    section = lv_menu_section_create(sub_ui_page);

    /* 创建显示界面主题下拉菜单 */
    const char *disp_theme_opts[] = {
        _("settings_ui_theme_light"),
        _("settings_ui_theme_dark"),
        NULL
    };
    cont = create_dropdown(section, NULL, _("settings_ui_theme"), disp_theme_opts);
    lv_obj_add_event_cb(cont, dd_settings_ui_theme_handler, LV_EVENT_ALL, NULL);
    // lv_dropdown_set_selected(cont, settings_get_refr_rate());

    /* 创建背光亮度滑动条 */
    cont = create_slider(section, NULL, _("settings_ui_blk_lvl"), 0, 100, settings_get_bl_lvl());
    lv_obj_add_event_cb(cont, slider_bl_knob_released_handler, LV_EVENT_RELEASED, NULL);
    lv_obj_add_event_cb(cont, slider_bl_val_chg_event_handler, LV_EVENT_VALUE_CHANGED, NULL);

    /* 创建刷新频率下拉菜单 */
    const char *ref_rate_opts[] = { "30Hz", "45Hz", "60Hz", NULL};
    cont = create_dropdown(section, NULL, _("settings_ui_refr_rate"), ref_rate_opts);
    lv_obj_add_event_cb(cont, dd_settings_ui_refr_rate_handler, LV_EVENT_ALL, NULL);
    lv_dropdown_set_selected(cont, settings_get_refr_rate());

    /* 创建显示模式下拉菜单 */
    const char *disp_mode_opts[] = {
        _("settings_ui_disp_mode_0"),
        _("settings_ui_disp_mode_1"),
        _("settings_ui_disp_mode_2"),
        _("settings_ui_disp_mode_3"),
        NULL
    };
    create_dropdown(section, NULL, _("settings_ui_disp_mode"), disp_mode_opts);

    /* 创建折线颜色设置菜单 */
    const char *line_color_opts[] = {
        _("settings_ui_line_color_black"),
        _("settings_ui_line_color_red"),
        _("settings_ui_line_color_green"),
        _("settings_ui_line_color_blue"),
        _("settings_ui_line_color_yellow"),
        NULL
    };
    create_dropdown(section, NULL, _("settings_ui_line_color"), line_color_opts);

    /* 校准菜单 */
    lv_obj_t * sub_calib_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(sub_calib_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    lv_menu_separator_create(sub_calib_page);
    section = lv_menu_section_create(sub_calib_page);
    const char *calib_mode_opts[] = {
        _("settings_calib_mode_factory"),
        _("settings_calib_mode_user"),
        NULL
    };
    cont = create_dropdown(section, NULL, _("settings_calib_mode"), calib_mode_opts);
    lv_obj_add_event_cb(cont, dd_settings_calib_mode_handler, LV_EVENT_ALL, NULL);
    lv_dropdown_set_selected(cont, settings_get_calib_mode());

    /* 关于菜单 */
    lv_obj_t * sub_about_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(sub_about_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    lv_menu_separator_create(sub_about_page);
    section = lv_menu_section_create(sub_about_page);

    uint8_t sn_code[8];
    settings_get_sn(sn_code);
    char sn_str[16];
    sprintf(sn_str, "0x%02X%02X%02X%02X%02X%02X", sn_code[0], sn_code[1], sn_code[2], sn_code[3], sn_code[4], sn_code[5], sn_code[6], sn_code[7]);
    cont = create_text_with_detail(section, _("settings_sn_code"), sn_str);
    cont = create_text_with_detail(section, _("settings_sw_ver"), "0.0.1");
    cont = create_text_with_detail(section, _("settings_hw_ver"), "0.0.1");
    char boot_count[16];
    sprintf(boot_count, "%d", settings_get_boot_count());
    cont = create_text_with_detail(section, _("settings_boot_count"), boot_count);

    /* 系统设置 */
    lv_obj_t * sub_menu_mode_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(sub_menu_mode_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    lv_menu_separator_create(sub_menu_mode_page);
    section = lv_menu_section_create(sub_menu_mode_page);

    /* 系统设置 - 量程切换 */
    const char *range_opts[] = {_("settings_range_sw_algo_sel_0"), _("settings_range_sw_algo_sel_1"), NULL};
    cont = create_dropdown(section, NULL, _("settings_range_sw_algo_sel"), range_opts);

    /* 系统设置 - 语言 */
    const char *lang_opts[] = {
        _("settings_lang_simplified_chinese"),
        _("settings_lang_english"),
        NULL,
    };
    cont = create_dropdown(section, NULL, _("settings_language"), lang_opts);
    lv_obj_add_event_cb(cont, dd_settings_lang_handler, LV_EVENT_ALL, NULL);
    lv_dropdown_set_selected(cont, settings_get_language());

    /* 系统设置 - 设备地址配置 */
    cont = create_text_with_detail(section, _("settings_device_addr"), "0x12345678");

    /* 系统设置 - 系统还原 */
    cont = create_btn(section, LV_SYMBOL_WARNING, _("settings_factory_reset"));

    /*Create a root page*/
    root_page = lv_menu_page_create(menu, NULL);
    lv_obj_set_style_pad_hor(root_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
    section = lv_menu_section_create(root_page);

    cont = create_text(section, NULL, _("settings_automatic_protection"), LV_MENU_ITEM_BUILDER_VARIANT_1);
    lv_menu_set_load_page_event(menu, cont, sub_mechanics_page);
    encoder_group_add_obj(cont);

    cont = create_text(section, NULL, _("settings_ui"), LV_MENU_ITEM_BUILDER_VARIANT_1);
    lv_menu_set_load_page_event(menu, cont, sub_ui_page);
    encoder_group_add_obj(cont);

    cont = create_text(section, NULL, _("settings_calibration"), LV_MENU_ITEM_BUILDER_VARIANT_1);
    lv_menu_set_load_page_event(menu, cont, sub_calib_page);
    encoder_group_add_obj(cont);

    // section = lv_menu_section_create(root_page);/
    cont = create_text(section, NULL, _("settings_about"), LV_MENU_ITEM_BUILDER_VARIANT_1);
    lv_menu_set_load_page_event(menu, cont, sub_about_page);
    encoder_group_add_obj(cont);

    cont = create_text(section, NULL, _("settings_system"), LV_MENU_ITEM_BUILDER_VARIANT_1);
    lv_menu_set_load_page_event(menu, cont, sub_menu_mode_page);
    encoder_group_add_obj(cont);

    lv_menu_set_sidebar_page(menu, root_page);

    lv_event_send(lv_obj_get_child(lv_obj_get_child(lv_menu_get_cur_sidebar_page(menu), 0), 0), LV_EVENT_CLICKED, NULL);
}
