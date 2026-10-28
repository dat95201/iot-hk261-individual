#include "bai2_led_blinky.h"

/* ============================================================
 * BÀI 2 - LED BLINKY TRÊN YOLOUNO
 *   Chân LED : GPIO 48 (LED đơn) / GPIO 45 (NeoPixel)
 *   Chu kỳ   : sáng 1000 ms - tắt 1000 ms
 *   Mỗi lần đổi trạng thái đều in log ra Serial Monitor.
 * ============================================================ */

void bai2_led_blinky_task(void *pvParameters)
{
  uint32_t seq = 0;   // so thu tu: lien tuc = mat byte, nhay coc = mat ca message
  pinMode(LED_GPIO, OUTPUT);
  Serial.printf("[BAI2] LED blinky start on GPIO %d, period %d ms\n",
                LED_GPIO, LED_BLINK_PERIOD_MS);
  Serial.flush();

  while (1)
  {
    digitalWrite(LED_GPIO, HIGH);        // bật LED
    Serial.printf("[BAI2][%lu] LED state: ON\n",  (unsigned long)++seq);
    Serial.flush();   // ep day het buffer USB CDC truoc khi task di ngu
    vTaskDelay(LED_BLINK_PERIOD_MS / portTICK_PERIOD_MS);

    digitalWrite(LED_GPIO, LOW);         // tắt LED
    Serial.printf("[BAI2][%lu] LED state: OFF\n", (unsigned long)++seq);
    Serial.flush();
    vTaskDelay(LED_BLINK_PERIOD_MS / portTICK_PERIOD_MS);
  }
}

void bai2_neo_blinky_task(void *pvParameters)
{
  Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
  strip.begin();
  strip.clear();
  strip.show();
  Serial.printf("[BAI2] NeoPixel blinky start on GPIO %d\n", NEO_PIN);
  Serial.flush();

  while (1)
  {
    strip.setPixelColor(0, strip.Color(255, 0, 0));   // đỏ
    strip.show();
    Serial.println("[BAI2] NEO state: RED");
    Serial.flush();
    vTaskDelay(NEO_BLINK_PERIOD_MS / portTICK_PERIOD_MS);

    strip.setPixelColor(0, strip.Color(0, 0, 0));     // tắt
    strip.show();
    Serial.println("[BAI2] NEO state: OFF");
    Serial.flush();
    vTaskDelay(NEO_BLINK_PERIOD_MS / portTICK_PERIOD_MS);
  }
}
