#ifndef __BAI3_DHT20_H__
#define __BAI3_DHT20_H__

#include <Arduino.h>
#include <Wire.h>
#include "LiquidCrystal_I2C.h"
#include "DHT20.h"
#include "global.h"
#include "config.h"

/* SDA: GPIO 11   SCL: GPIO 12   Địa chỉ I2C của DHT20: 0x38 */
void bai3_i2c_scan(void);                    // quét bus I2C, in các địa chỉ tìm thấy
void bai3_dht20_task(void *pvParameters);    // đọc nhiệt độ / độ ẩm định kỳ

#endif
