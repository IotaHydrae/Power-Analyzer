// Copyright (c) 2024 embeddedboys developers
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>

#include "pico/time.h"
#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "pico/platform.h"

#include "hardware/pll.h"
#include "hardware/vreg.h"
#include "hardware/clocks.h"
#include "hardware/timer.h"

#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"
#include "lvgl/examples/lv_examples.h"
#include "lv_i18n/lv_i18n.h"
#include "porting/lv_port_disp_template.h"
#include "porting/lv_port_indev_template.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "backlight.h"

#include "debug.h"
#include "ui/ui.h"
#include "ui_ext/ui_ext.h"

QueueHandle_t xToFlushQueue = NULL;

void vApplicationTickHook()
{
	lv_tick_inc(1);
}

const TickType_t xPeriod = pdMS_TO_TICKS( 5 );
static portTASK_FUNCTION(lv_timer_task_handler, pvParameters)
{
	TickType_t xLastWakeTime;

	xLastWakeTime = xTaskGetTickCount();

	for(;;) {
		vTaskDelayUntil( &xLastWakeTime,xPeriod );
		lv_timer_handler();
        ui_tick();
	}
	vTaskDelete(NULL);
}

// Which core to run on if configNUMBER_OF_CORES==1
#ifndef RUN_FREE_RTOS_ON_CORE
#define RUN_FREE_RTOS_ON_CORE 0
#endif

// Whether to flash the led
#ifndef USE_LED
#define USE_LED 1
#endif

// Whether to busy wait in the led thread
#ifndef LED_BUSY_WAIT
#define LED_BUSY_WAIT 1
#endif

// Delay between led blinking
#define LED_DELAY_MS 2000

// Priorities of our threads - higher numbers are higher priority
#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 2UL )
#define BLINK_TASK_PRIORITY     ( tskIDLE_PRIORITY + 1UL )
#define WORKER_TASK_PRIORITY    ( tskIDLE_PRIORITY + 4UL )

// Stack sizes of our threads in words (4 bytes)
#define MAIN_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define BLINK_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define WORKER_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

#include "pico/async_context_freertos.h"
static async_context_freertos_t async_context_instance;

// Create an async context
static async_context_t *example_async_context(void) {
    async_context_freertos_config_t config = async_context_freertos_default_config();
    config.task_priority = WORKER_TASK_PRIORITY; // defaults to ASYNC_CONTEXT_DEFAULT_FREERTOS_TASK_PRIORITY
    config.task_stack_size = WORKER_TASK_STACK_SIZE; // defaults to ASYNC_CONTEXT_DEFAULT_FREERTOS_TASK_STACK_SIZE
    if (!async_context_freertos_init(&async_context_instance, &config))
        return NULL;
    return &async_context_instance.core;
}

#if USE_LED
// Turn led on or off
static void pico_set_led(bool led_on) {
#if defined PICO_DEFAULT_LED_PIN
    gpio_put(PICO_DEFAULT_LED_PIN, led_on);
#elif defined(CYW43_WL_GPIO_LED_PIN)
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
#endif
}

// Initialise led
static void pico_init_led(void) {
#if defined PICO_DEFAULT_LED_PIN
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
#elif defined(CYW43_WL_GPIO_LED_PIN)
    hard_assert(cyw43_arch_init() == PICO_OK);
    pico_set_led(false); // make sure cyw43 is started
#endif
}

void blink_task(__unused void *params) {
    bool on = false;
    printf("blink_task starts\n");
    pico_init_led();
    while (true) {
#if configNUMBER_OF_CORES > 1
        static int last_core_id = -1;
        if (portGET_CORE_ID() != last_core_id) {
            last_core_id = portGET_CORE_ID();
            printf("blink task is on core %d\n", last_core_id);
        }
#endif
        pico_set_led(on);
        on = !on;

#if LED_BUSY_WAIT
        // You shouldn't usually do this. We're just keeping the thread busy,
        // experiment with BLINK_TASK_PRIORITY and LED_BUSY_WAIT to see what happens
        // if BLINK_TASK_PRIORITY is higher than TEST_TASK_PRIORITY main_task won't get any free time to run
        // unless configNUMBER_OF_CORES > 1
        busy_wait_ms(LED_DELAY_MS);
#else
        sleep_ms(LED_DELAY_MS);
#endif
    }
}
#endif // USE_LED

// async workers run in their own thread when using async_context_freertos_t with priority WORKER_TASK_PRIORITY
static void do_work(async_context_t *context, async_at_time_worker_t *worker) {
    async_context_add_at_time_worker_in_ms(context, worker, 10000);
    static uint32_t count = 0;
    printf("Hello from worker count=%u\n", count++);
#if configNUMBER_OF_CORES > 1
        static int last_core_id = -1;
        if (portGET_CORE_ID() != last_core_id) {
            last_core_id = portGET_CORE_ID();
            printf("worker is on core %d\n", last_core_id);
        }
#endif
}
async_at_time_worker_t worker_timeout = { .do_work = do_work };

void main_task(__unused void *params) {
//     async_context_t *context = example_async_context();
//     // start the worker running
//     async_context_add_at_time_worker_in_ms(context, &worker_timeout, 0);
// #if USE_LED
//     // start the led blinking
//     xTaskCreate(blink_task, "BlinkThread", BLINK_TASK_STACK_SIZE, NULL, BLINK_TASK_PRIORITY, NULL);
// #endif

    lv_init();
    lv_port_disp_init();

    lv_i18n_init(lv_i18n_language_pack);
    lv_i18n_set_locale("zh-CN");
    // lv_i18n_set_locale("en-US");

#if INDEV_DRV_USED
    lv_port_indev_init();
#endif

    printf("Starting App...\n");

    ui_init();
    ui_finalize();
    // lv_demo_benchmark();
    // pico-sdk 1.5.1 ---- 98 87% 179 68 121
    // pico-sdk 1.5.1 with 80MHz ---- 127 90% 237 107 160
    // pico-sdk 2.0.0 ---- 96 88% 173 68 122

    TaskHandle_t lvgl_task_handle;
    xTaskCreate(lv_timer_task_handler, "lvgl_task", 2048, NULL, (tskIDLE_PRIORITY + 3), &lvgl_task_handle);
    vTaskCoreAffinitySet(lvgl_task_handle, (1 << 0));

    TaskHandle_t video_flush_handler;
    xTaskCreate(video_flush_task, "video_flush", 256, NULL, (tskIDLE_PRIORITY + 2), &video_flush_handler);
    vTaskCoreAffinitySet(video_flush_handler, (1 << 1));

    backlight_driver_init();
    backlight_set_level(100);
    printf("backlight set to 100%%\n");

//     int count = 0;
    while(true) {
// #if configNUMBER_OF_CORES > 1
//         static int last_core_id = -1;
//         if (portGET_CORE_ID() != last_core_id) {
//             last_core_id = portGET_CORE_ID();
//             printf("main task is on core %d\n", last_core_id);
//         }
// #endif
//         printf("Hello from main task count=%u\n", count++);
        vTaskDelay(3000);
    }
//     async_context_deinit(context);
}

void vLaunch( void) {
    TaskHandle_t task;
    xTaskCreate(main_task, "MainThread", MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &task);

#if configUSE_CORE_AFFINITY && configNUMBER_OF_CORES > 1
    // we must bind the main task to one core (well at least while the init is called)
    vTaskCoreAffinitySet(task, 1);
#endif

    /* Start the tasks and timer running. */
    printf("calling freertos scheduler, %lld\n", time_us_64());
    vTaskStartScheduler();
}

int main( void )
{
#define CPU_SPEED_MHZ (DEFAULT_SYS_CLK_KHZ / 1000)
    if(CPU_SPEED_MHZ > 266 && CPU_SPEED_MHZ <= 360)
        vreg_set_voltage(VREG_VOLTAGE_1_20);
    else if (CPU_SPEED_MHZ > 360 && CPU_SPEED_MHZ <= 396)
        vreg_set_voltage(VREG_VOLTAGE_1_25);
    else if (CPU_SPEED_MHZ > 396)
        vreg_set_voltage(VREG_VOLTAGE_MAX);
    else
        vreg_set_voltage(VREG_VOLTAGE_DEFAULT);
    set_sys_clock_khz(CPU_SPEED_MHZ * 1000, true);
    clock_configure(clk_peri,
                    0,
                    CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLK_SYS,
                    CPU_SPEED_MHZ * MHZ,
                    CPU_SPEED_MHZ * MHZ);
    stdio_init_all();
    // stdio_uart_init_full(uart0, 115200, 16, 17);

    printf("\n\n\nPICO DM QD3503728 LVGL Porting\n");

    xToFlushQueue = xQueueCreate(2, sizeof(struct video_frame));

    /* Configure the hardware ready to run the demo. */
    const char *rtos_name;
#if (configNUMBER_OF_CORES > 1)
    rtos_name = "FreeRTOS SMP";
#else
    rtos_name = "FreeRTOS";
#endif

#if (configNUMBER_OF_CORES > 1)
    printf("Starting %s on both cores:\n", rtos_name);
    vLaunch();
#elif (RUN_FREE_RTOS_ON_CORE == 1 && configNUMBER_OF_CORES==1)
    printf("Starting %s on core 1:\n", rtos_name);
    multicore_launch_core1(vLaunch);
    while (true);
#else
    printf("Starting %s on core 0:\n", rtos_name);
    vLaunch();
#endif
    return 0;
}
