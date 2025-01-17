#include "./lv_i18n.h"


////////////////////////////////////////////////////////////////////////////////
// Define plural operands
// http://unicode.org/reports/tr35/tr35-numbers.html#Operands

// Integer version, simplified

#define UNUSED(x) (void)(x)

static inline uint32_t op_n(int32_t val) { return (uint32_t)(val < 0 ? -val : val); }
static inline uint32_t op_i(uint32_t val) { return val; }
// always zero, when decimal part not exists.
static inline uint32_t op_v(uint32_t val) { UNUSED(val); return 0;}
static inline uint32_t op_w(uint32_t val) { UNUSED(val); return 0; }
static inline uint32_t op_f(uint32_t val) { UNUSED(val); return 0; }
static inline uint32_t op_t(uint32_t val) { UNUSED(val); return 0; }

static lv_i18n_phrase_t zh_cn_singulars[] = {
    {"title1", "此处显示基本信息"},
    {"yes", "是"},
    {"no", "否"},
    {"note", "提示"},
    {"note_restart", "为了使配置生效，需要重启设备"},
    {"statistics_avg_current_per_second", "秒平均电流"},
    {"statistics_avg_current_per_minute", "分钟平均电流"},
    {"statistics_avg_currnet_total", "总平均电流"},
    {"statistics_rtc_time", "RTC 统计时间"},
    {"statistics_instant_peak_currnet", "瞬时峰值电流"},
    {"statistics_minimum_no_zero_currnet", "最小非零电流"},
    {"statistics_total_capacity", "总容量"},
    {"statistics_total_energy", "总能量"},
    {"pd_power_protection", "保护功率设置"},
    {"pd_func_enable", "开启PD功能"},
    {"voltage_setting", "电压设置"},
    {"settings_automatic_protection", "自保护设置"},
    {"settings_automatic_voltage_cut", "自动断开电压"},
    {"settings_automatic_current_cut", "自动断开电流"},
    {"settings_ui", "界面设置"},
    {"settings_ui_theme", "系统主题"},
    {"settings_ui_theme_light", "浅色"},
    {"settings_ui_theme_dark", "深色"},
    {"settings_ui_blk_lvl", "背光亮度"},
    {"settings_ui_refr_rate", "刷新频率"},
    {"settings_ui_disp_mode", "显示模式"},
    {"settings_ui_disp_mode_0", "指针+数字"},
    {"settings_ui_disp_mode_1", "数字+折线"},
    {"settings_ui_disp_mode_2", "折线+指针"},
    {"settings_ui_disp_mode_3", "单折线"},
    {"settings_ui_line_color", "折线颜色"},
    {"settings_ui_line_color_black", "黑色"},
    {"settings_ui_line_color_red", "红色"},
    {"settings_ui_line_color_green", "绿色"},
    {"settings_ui_line_color_blue", "蓝色"},
    {"settings_ui_line_color_yellow", "黄色"},
    {"settings_calibration", "校准"},
    {"settings_calib_mode", "校准模式"},
    {"settings_calib_mode_factory", "厂家校准"},
    {"settings_calib_mode_user", "用户校准"},
    {"settings_about", "关于"},
    {"settings_sn_code", "SN 码"},
    {"settings_sw_ver", "软件版本号"},
    {"settings_hw_ver", "硬件版本号"},
    {"settings_boot_count", "启动次数"},
    {"settings_system", "系统设置"},
    {"settings_range_sw_algo_sel", "量程切换算法选择"},
    {"settings_range_sw_algo_sel_0", "实时切换"},
    {"settings_range_sw_algo_sel_1", "平滑切换"},
    {"settings_device_addr", "设备通讯地址"},
    {"settings_factory_reset", "系统还原"},
    {"settings_language", "语言设置"},
    {"settings_lang_simplified_chinese", "简体中文"},
    {"settings_lang_english", "English"},
    {NULL, NULL} // End mark
};



static uint8_t zh_cn_plural_fn(int32_t num)
{



    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t zh_cn_lang = {
    .locale_name = "zh-CN",
    .singulars = zh_cn_singulars,

    .locale_plural_fn = zh_cn_plural_fn
};

static lv_i18n_phrase_t en_us_singulars[] = {
    {"title1", "Display basic information here"},
    {"yes", "Yes"},
    {"no", "No"},
    {"note", "Note"},
    {"note_restart", "A system reboot is required to make settings valid."},
    {"statistics_avg_current_per_second", "1 second avg."},
    {"statistics_avg_current_per_minute", "1 minute avg."},
    {"statistics_avg_currnet_total", "Total avg."},
    {"statistics_rtc_time", "RTC time"},
    {"statistics_instant_peak_currnet", "Max current"},
    {"statistics_minimum_no_zero_currnet", "Min currnet"},
    {"statistics_total_capacity", "Total Capacity"},
    {"statistics_total_energy", "Total Energy"},
    {"pd_power_protection", "PD power protection"},
    {"pd_func_enable", "PD enable"},
    {"voltage_setting", "Voltage Setting"},
    {"settings_automatic_protection", "Protection"},
    {"settings_automatic_voltage_cut", "Automatic voltage cut"},
    {"settings_automatic_current_cut", "Automatic current cut"},
    {"settings_ui", "UI settings"},
    {"settings_ui_theme", "Theme"},
    {"settings_ui_theme_light", "Light"},
    {"settings_ui_theme_dark", "Dark"},
    {"settings_ui_refr_rate", "Refresh rate"},
    {"settings_ui_blk_lvl", "Backlight level"},
    {"settings_ui_disp_mode", "Display mode"},
    {"settings_ui_disp_mode_0", "Meter+Numer"},
    {"settings_ui_disp_mode_1", "Number+Line"},
    {"settings_ui_disp_mode_2", "Line+Meter"},
    {"settings_ui_disp_mode_3", "Line"},
    {"settings_ui_line_color", "Line color"},
    {"settings_ui_line_color_black", "Black"},
    {"settings_ui_line_color_red", "Read"},
    {"settings_ui_line_color_green", "Green"},
    {"settings_ui_line_color_blue", "Blue"},
    {"settings_ui_line_color_yellow", "Yellow"},
    {"settings_calibration", "Calibration"},
    {"settings_calib_mode", "Calibration mode"},
    {"settings_calib_mode_factory", "Factory calibration"},
    {"settings_calib_mode_user", "User calibration"},
    {"settings_about", "About"},
    {"settings_sn_code", "SN code"},
    {"settings_sw_ver", "Software version"},
    {"settings_hw_ver", "Hardware version"},
    {"settings_boot_count", "Boot count"},
    {"settings_system", "System"},
    {"settings_range_sw_algo_sel", "Range algorithm"},
    {"settings_range_sw_algo_sel_0", "Realtime switch"},
    {"settings_range_sw_algo_sel_1", "Smooth switch"},
    {"settings_device_addr", "Device address"},
    {"settings_factory_reset", "System recovery"},
    {"settings_language", "Language setting"},
    {"settings_lang_simplified_chinese", "简体中文"},
    {"settings_lang_english", "English"},
    {NULL, NULL} // End mark
};



static uint8_t en_us_plural_fn(int32_t num)
{
    uint32_t n = op_n(num); UNUSED(n);
    uint32_t i = op_i(n); UNUSED(i);
    uint32_t v = op_v(n); UNUSED(v);

    if ((i == 1 && v == 0)) return LV_I18N_PLURAL_TYPE_ONE;
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t en_us_lang = {
    .locale_name = "en-US",
    .singulars = en_us_singulars,

    .locale_plural_fn = en_us_plural_fn
};

const lv_i18n_language_pack_t lv_i18n_language_pack[] = {
    &zh_cn_lang,
    &en_us_lang,
    NULL // End mark
};

////////////////////////////////////////////////////////////////////////////////


// Internal state
static const lv_i18n_language_pack_t * current_lang_pack;
static const lv_i18n_lang_t * current_lang;


/**
 * Reset internal state. For testing.
 */
void __lv_i18n_reset(void)
{
    current_lang_pack = NULL;
    current_lang = NULL;
}

/**
 * Set the languages for internationalization
 * @param langs pointer to the array of languages. (Last element has to be `NULL`)
 */
int lv_i18n_init(const lv_i18n_language_pack_t * langs)
{
    if(langs == NULL) return -1;
    if(langs[0] == NULL) return -1;

    current_lang_pack = langs;
    current_lang = langs[0];     /*Automatically select the first language*/
    return 0;
}

/**
 * Change the localization (language)
 * @param l_name name of the translation locale to use. E.g. "en-GB"
 */
int lv_i18n_set_locale(const char * l_name)
{
    if(current_lang_pack == NULL) return -1;

    uint16_t i;

    for(i = 0; current_lang_pack[i] != NULL; i++) {
        // Found -> finish
        if(strcmp(current_lang_pack[i]->locale_name, l_name) == 0) {
            current_lang = current_lang_pack[i];
            return 0;
        }
    }

    return -1;
}


static const char * __lv_i18n_get_text_core(lv_i18n_phrase_t * trans, const char * msg_id)
{
    uint16_t i;
    for(i = 0; trans[i].msg_id != NULL; i++) {
        if(strcmp(trans[i].msg_id, msg_id) == 0) {
            /*The msg_id has found. Check the translation*/
            if(trans[i].translation) return trans[i].translation;
        }
    }

    return NULL;
}


/**
 * Get the translation from a message ID
 * @param msg_id message ID
 * @return the translation of `msg_id` on the set local
 */
const char * lv_i18n_get_text(const char * msg_id)
{
    if(current_lang == NULL) return msg_id;

    const lv_i18n_lang_t * lang = current_lang;
    const void * txt;

    // Search in current locale
    if(lang->singulars != NULL) {
        txt = __lv_i18n_get_text_core(lang->singulars, msg_id);
        if (txt != NULL) return txt;
    }

    // Try to fallback
    if(lang == current_lang_pack[0]) return msg_id;
    lang = current_lang_pack[0];

    // Repeat search for default locale
    if(lang->singulars != NULL) {
        txt = __lv_i18n_get_text_core(lang->singulars, msg_id);
        if (txt != NULL) return txt;
    }

    return msg_id;
}

/**
 * Get the translation from a message ID and apply the language's plural rule to get correct form
 * @param msg_id message ID
 * @param num an integer to select the correct plural form
 * @return the translation of `msg_id` on the set local
 */
const char * lv_i18n_get_text_plural(const char * msg_id, int32_t num)
{
    if(current_lang == NULL) return msg_id;

    const lv_i18n_lang_t * lang = current_lang;
    const void * txt;
    lv_i18n_plural_type_t ptype;

    // Search in current locale
    if(lang->locale_plural_fn != NULL) {
        ptype = lang->locale_plural_fn(num);

        if(lang->plurals[ptype] != NULL) {
            txt = __lv_i18n_get_text_core(lang->plurals[ptype], msg_id);
            if (txt != NULL) return txt;
        }
    }

    // Try to fallback
    if(lang == current_lang_pack[0]) return msg_id;
    lang = current_lang_pack[0];

    // Repeat search for default locale
    if(lang->locale_plural_fn != NULL) {
        ptype = lang->locale_plural_fn(num);

        if(lang->plurals[ptype] != NULL) {
            txt = __lv_i18n_get_text_core(lang->plurals[ptype], msg_id);
            if (txt != NULL) return txt;
        }
    }

    return msg_id;
}

/**
 * Get the name of the currently used locale.
 * @return name of the currently used locale. E.g. "en-GB"
 */
const char * lv_i18n_get_current_locale(void)
{
    if(!current_lang) return NULL;
    return current_lang->locale_name;
}
