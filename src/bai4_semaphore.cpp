#include "bai4_semaphore.h"

/* ============================================================
 * BÀI 4 - LẬP TRÌNH SEMAPHORE TRÊN YOLOUNO
 *
 * Loại semaphore sử dụng:
 *   - Binary semaphore (xBinarySemaphoreData): đồng bộ Producer -> Consumer
 *   - Mutex (xMutexSerial): bảo vệ tài nguyên dùng chung là cổng Serial
 *     và biến toàn cục shared_value
 *
 * Các task:
 *   - Producer : priority 2 - mỗi 2 giây tăng shared_value rồi GIVE semaphore
 *   - Consumer : priority 3 - block chờ TAKE semaphore, nhận được thì đọc và in
 * ============================================================ */

SemaphoreHandle_t xBinarySemaphoreData = NULL;
SemaphoreHandle_t xMutexSerial         = NULL;

static volatile int shared_value = 0;   // tài nguyên dùng chung

void bai4_semaphore_init(void)
{
  xBinarySemaphoreData = xSemaphoreCreateBinary();
  xMutexSerial         = xSemaphoreCreateMutex();
}

void bai4_producer_task(void *pvParameters)
{
  while (1)
  {
    /* Giu mutex suot ca viec ghi bien dung chung lan viec in ra Serial */
    xSemaphoreTake(xMutexSerial, portMAX_DELAY);
    shared_value++;
    Serial.printf("[BAI4][Producer] ghi shared_value = %d  -> GIVE semaphore\n", shared_value);
    Serial.flush();
    xSemaphoreGive(xMutexSerial);

    /* Danh thuc Consumer */
    xSemaphoreGive(xBinarySemaphoreData);

    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void bai4_consumer_task(void *pvParameters)
{
  while (1)
  {
    /* Block vo han cho toi khi Producer give */
    if (xSemaphoreTake(xBinarySemaphoreData, portMAX_DELAY) == pdTRUE)
    {
      xSemaphoreTake(xMutexSerial, portMAX_DELAY);
      Serial.printf("[BAI4][Consumer] TAKE semaphore       -> doc shared_value = %d\n", shared_value);
      Serial.flush();
      xSemaphoreGive(xMutexSerial);
    }
  }
}
