#include <stdio.h>
#include "quadrature.h"

static const int ENCODER1_DATA_PIN = 19;
static const int ENCODER1_CLK_PIN = 17;
static const int ENCODER1_SW_PIN = 18;
Quadrature_encoder<ENCODER1_DATA_PIN, ENCODER1_CLK_PIN> encoder1;

extern "C" {
    int encoder_get_count(void) {
        return encoder1.count();
    }

    bool encoder_sw_is_pressed(void) {
        return !gpio_get(ENCODER1_SW_PIN);
    }

    void encoder_hw_init(void) {
        encoder1 = Quadrature_encoder<ENCODER1_DATA_PIN, ENCODER1_CLK_PIN>();
        encoder1.begin(pull_direction::up, resolution::quarter);

        gpio_init(ENCODER1_SW_PIN);
        gpio_set_dir(ENCODER1_SW_PIN, GPIO_IN);
        gpio_pull_up(ENCODER1_SW_PIN);
    }
}