#ifndef __BAI2_LED_BLINKY_H__
#define __BAI2_LED_BLINKY_H__

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "global.h"
#include "config.h"

/* Chân LED trên YoloUNO (xem config.h) */
#define LED_GPIO   CFG_LED_GPIO    // LED đơn  - GPIO 48
#define NEO_PIN    CFG_NEO_PIN     // NeoPixel - GPIO 45
#define LED_COUNT  CFG_NEO_COUNT

/* Chu kỳ nhấp nháy (ms) */
#define LED_BLINK_PERIOD_MS  1000
#define NEO_BLINK_PERIOD_MS  500

void bai2_led_blinky_task(void *pvParameters);
void bai2_neo_blinky_task(void *pvParameters);

#endif
