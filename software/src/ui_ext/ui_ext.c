#include "lvgl.h"
#include "ui/ui.h"
#include "ui/screens.h"

#include "ui_ext.h"

void ui_finalize(void)
{
    page_home_finalize();
    page_settings_finalize();
}
