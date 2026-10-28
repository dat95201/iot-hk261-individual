#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

/* Dữ liệu cảm biến dùng chung giữa các task (Bài 3 ghi, Bài 1 & 5 đọc) */
extern float glob_temperature;
extern float glob_humidity;

/* Thông tin Wi-Fi chế độ AP (YoloUNO phát ra) */
extern String ssid;
extern String password;

/* Thông tin Wi-Fi chế độ Station (YoloUNO kết nối vào) */
extern String wifi_ssid;
extern String wifi_password;

/* Thông tin CoreIOT */
extern String CORE_IOT_SERVER;
extern String CORE_IOT_PORT;
extern String CORE_IOT_TOKEN;

/* Cờ + semaphore báo đã có Internet (task Wi-Fi give, task CoreIOT take) */
extern bool isWifiConnected;
extern SemaphoreHandle_t xBinarySemaphoreInternet;

#endif
