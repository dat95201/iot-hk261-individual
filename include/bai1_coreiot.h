#ifndef __BAI1_COREIOT_H__
#define __BAI1_COREIOT_H__

#include <Arduino.h>
#include <WiFi.h>
#include "global.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>


void bai1_coreiot_task(void *pvParameters);

#endif