#ifndef __WIFI_STA_H__
#define __WIFI_STA_H__

#include <Arduino.h>
#include <WiFi.h>
#include "global.h"

/* Kết nối Wi-Fi chế độ Station rồi give xBinarySemaphoreInternet.
 * Dùng cho Bài 1 (CoreIOT) khi không chạy webserver của Bài 5. */
void wifi_sta_task(void *pvParameters);

#endif
