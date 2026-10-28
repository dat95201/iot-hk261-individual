#ifndef __BAI4_SEMAPHORE_H__
#define __BAI4_SEMAPHORE_H__

#include <Arduino.h>
#include "global.h"

/* Binary semaphore: task Producer báo cho task Consumer là đã có dữ liệu mới */
extern SemaphoreHandle_t xBinarySemaphoreData;
/* Mutex: bảo vệ tài nguyên dùng chung (Serial + biến toàn cục) */
extern SemaphoreHandle_t xMutexSerial;

void bai4_semaphore_init(void);                 // tạo semaphore, gọi trong setup()
void bai4_producer_task(void *pvParameters);    // task đọc/sinh dữ liệu
void bai4_consumer_task(void *pvParameters);    // task hiển thị dữ liệu

#endif
