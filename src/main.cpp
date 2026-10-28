/* ============================================================================
 *  IoT - HK261 - Bài tập thực hành cá nhân
 *  Board: YoloUNO (ESP32-S3) - PlatformIO
 *
 *  CÁCH DÙNG:
 *    Mỗi bài là một khối bên dưới. Muốn chạy bài nào thì BỎ COMMENT khối của
 *    bài đó và COMMENT lại các khối còn lại, rồi build & upload.
 *    Nhớ điền Wi-Fi / CoreIOT token trong include/config.h trước khi chạy
 *    Bài 1 và Bài 5.
 * ========================================================================== */

#include <esp_system.h>

#include "global.h"
#include "config.h"

#include "wifi_sta.h"
#include "bai1_coreiot.h"
#include "bai2_led_blinky.h"
#include "bai3_dht20.h"
#include "bai4_semaphore.h"
#include "bai5_webserver.h"

void setup()
{
  Serial.begin(115200);
  /* YoloUNO (ESP32-S3) dùng USB CDC native cho Serial. Phải chờ host gắn
     monitor xong mới in, nếu không những byte đầu sẽ bị CDC bỏ.
     Timeout 3s để board vẫn chạy khi cắm nguồn rời, không có máy tính. */
  unsigned long t0 = millis();
  while (!Serial && millis() - t0 < 3000) delay(10);
  delay(300);
#if ARDUINO_USB_CDC_ON_BOOT
  /* Mac dinh HWCDC bo byte khi host chua kip nhan. Noi timeout de no
     doi thay vi drop -> bot hien tuong log bi thung giua dong. */
  Serial.setTxTimeoutMs(1000);
#endif

  /* Banner chan doan: neu dong nay lap lai lien tuc -> board dang reboot loop.
     reset_reason: 1=POWERON 3=SW 4=PANIC 5=INT_WDT 6=TASK_WDT 7=WDT 8=DEEPSLEEP 9=BROWNOUT */
  Serial.printf("\n===== BOOT  reset_reason=%d  heap=%u =====\n",
                (int)esp_reset_reason(), (unsigned)ESP.getFreeHeap());
  Serial.flush();

  xBinarySemaphoreInternet = xSemaphoreCreateBinary();

  /* ========================================================================
   * BÀI 1 - GỬI TELEMETRY LÊN COREIOT  (MQTT: v1/devices/me/telemetry)
   *   Cần: Wi-Fi (wifi_sta_task) + nguồn dữ liệu (bai3_dht20_task)
   * ====================================================================== */
  // Serial.println("=== BAI 1: CoreIOT telemetry ===");
  xTaskCreate(wifi_sta_task,      "WiFi STA",   4096, NULL, 3, NULL);
  xTaskCreate(bai3_dht20_task,    "DHT20",      4096, NULL, 2, NULL);
  xTaskCreate(bai1_coreiot_task,  "CoreIOT",    4096, NULL, 2, NULL);

  /* ========================================================================
   * BÀI 2 - LED BLINKY
   * ====================================================================== */
  // Serial.println("=== BAI 2: LED Blinky ===");
  // xTaskCreate(bai2_led_blinky_task, "LED Blinky", 4096, NULL, 2, NULL);
  // xTaskCreate(bai2_neo_blinky_task, "NEO Blinky", 4096, NULL, 2, NULL);

  /* ========================================================================
   * BÀI 3 - ĐỌC DHT20 QUA I2C (có quét địa chỉ I2C lúc khởi động)
   * ====================================================================== */
  // Serial.println("=== BAI 3: DHT20 I2C ===");
  // xTaskCreate(bai3_dht20_task, "DHT20", 4096, NULL, 2, NULL);

  /* ========================================================================
   * BÀI 4 - SEMAPHORE (binary semaphore + mutex, 2 task)
   * ====================================================================== */
  // Serial.println("=== BAI 4: Semaphore ===");
  // bai4_semaphore_init();
  // xTaskCreate(bai4_producer_task, "Producer", 4096, NULL, 2, NULL);
  // xTaskCreate(bai4_consumer_task, "Consumer", 4096, NULL, 3, NULL);

  /* ========================================================================
   * BÀI 5 - WEBSERVER TRÊN YOLOUNO (STA + AP, điều khiển LED, xem cảm biến)
   *   Task webserver tự lo Wi-Fi nên KHÔNG bật wifi_sta_task cùng lúc.
   * ====================================================================== */
  // Serial.println("=== BAI 5: Webserver ===");
  // xTaskCreate(bai3_dht20_task,      "DHT20",     4096, NULL, 2, NULL);
  // xTaskCreate(bai5_webserver_task,  "WebServer", 8192, NULL, 2, NULL);
}

void loop()
{
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}