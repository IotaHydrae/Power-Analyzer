#ifndef __BUTTON_H
#define __BUTTON_H

#include <stdint.h>
#include <stdbool.h>

#define BUTTON_HW_NUMS 4

void button_hw_init(void);
bool button_hw_is_pressed(uint8_t i);

#endif
