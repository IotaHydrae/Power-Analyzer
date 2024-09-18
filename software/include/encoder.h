#ifndef __ENCODER_H__
#define __ENCODER_H__

#include <stdbool.h>

void encoder_hw_init(void);
int encoder_get_count(void);
bool encoder_sw_is_pressed(void);

#endif