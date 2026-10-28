#ifndef __BAI5_WEBSERVER_H__
#define __BAI5_WEBSERVER_H__
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "global.h"
#include "bai2_led_blinky.h"

#define LED1_PIN 48
#define LED2_PIN 41
#define BOOT_PIN 0
//extern WebServer server;

//extern bool isAPMode;




String mainPage();
String settingsPage();

void startAP();
void setupServer();
void connectToWiFi();

void bai5_webserver_task(void *pvParameters);

#endif