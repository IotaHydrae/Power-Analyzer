#include <stdio.h>

#include "lvgl.h"
#include "ui/ui.h"
#include "ui/screens.h"

#include "ui_ext.h"
#include "settings.h"

void ui_finalize(void)
{
    printf("boot count : %d\n", settings_get_boot_count());
    page_home_finalize();
    page_settings_finalize();
}
