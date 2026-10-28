#include "global.h"
#include "config.h"

float glob_temperature = 0;
float glob_humidity    = 0;

/* Wi-Fi do YoloUNO phát ra (chế độ AP) */
String ssid     = CFG_AP_SSID;
String password = CFG_AP_PASSWORD;

/* Wi-Fi YoloUNO kết nối vào (chế độ Station) */
String wifi_ssid     = CFG_WIFI_SSID;
String wifi_password = CFG_WIFI_PASSWORD;

/* CoreIOT */
String CORE_IOT_SERVER = CFG_COREIOT_SERVER;
String CORE_IOT_PORT   = CFG_COREIOT_PORT;
String CORE_IOT_TOKEN  = CFG_COREIOT_TOKEN;

bool isWifiConnected = false;
SemaphoreHandle_t xBinarySemaphoreInternet = NULL;  // được tạo trong setup() của main.cpp
