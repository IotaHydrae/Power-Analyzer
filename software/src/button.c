#include "hardware/gpio.h"

#include "button.h"

static const uint BUTTON_KEY_1_PIN = 20;
static const uint BUTTON_KEY_2_PIN = 19;
static const uint BUTTON_KEY_4_PIN = 17;
static const uint BUTTON_KEY_5_PIN = 16;

static uint gpio_keys[BUTTON_HW_NUMS] = {
    BUTTON_KEY_1_PIN,
    BUTTON_KEY_2_PIN,
    BUTTON_KEY_4_PIN,
    BUTTON_KEY_5_PIN,
};

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

void button_hw_init(void)
{
    for (int i = 0; i < ARRAY_SIZE(gpio_keys); i++) {
        int pin = gpio_keys[i];
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_IN);
        gpio_pull_up(pin);
    }
}

bool __not_in_flash_func(button_hw_is_pressed)(uint8_t i)
{
    return !gpio_get(gpio_keys[i]);
}
