# IoT HK261 - Bài tập thực hành cá nhân

Board: **YoloUNO (ESP32-S3)** · Framework: **Arduino** · Build: **PlatformIO**

Source code lấy từ project mẫu `YoloUNO_PlatformIO`, tổ chức lại theo từng bài
để bật/tắt nhanh khi cần demo.

## 1. Chuẩn bị

Điền thông tin thật vào `include/config.h`:

```c
#define CFG_WIFI_SSID       "..."   // Wi-Fi YoloUNO kết nối vào
#define CFG_WIFI_PASSWORD   "..."
#define CFG_COREIOT_TOKEN   "..."   // access token device trên CoreIOT
```

> Khi nộp báo cáo / chụp màn hình nhớ che mật khẩu Wi-Fi và access token.

## 2. Chạy từng bài

Mở `src/main.cpp`, trong `setup()` mỗi bài là một khối. **Bỏ comment khối của
bài cần chạy, comment lại các khối còn lại**, rồi build & upload:

```bash
pio run -t upload && pio device monitor
```

Mặc định repo đang bật **Bài 2**.

## 3. Bản đồ bài tập → source

| Bài | Nội dung | File | Task trong `main.cpp` |
|-----|----------|------|------------------------|
| 1 | Gửi telemetry lên CoreIOT (MQTT) | `src/bai1_coreiot.cpp` | `wifi_sta_task` + `bai3_dht20_task` + `bai1_coreiot_task` |
| 2 | LED Blinky + log Serial | `src/bai2_led_blinky.cpp` | `bai2_led_blinky_task` / `bai2_neo_blinky_task` |
| 3 | I2C DHT20 (có quét địa chỉ I2C) | `src/bai3_dht20.cpp` | `bai3_dht20_task` |
| 4 | Semaphore FreeRTOS (binary + mutex) | `src/bai4_semaphore.cpp` | `bai4_producer_task` + `bai4_consumer_task` |
| 5 | Webserver (STA + AP, điều khiển LED) | `src/bai5_webserver.cpp` | `bai3_dht20_task` + `bai5_webserver_task` |

File dùng chung: `src/global.cpp`, `include/global.h`, `include/config.h`,
`src/wifi_sta.cpp`.

## 4. Ghi chú theo từng bài

**Bài 1 - CoreIOT.** Publish MQTT lên topic `v1/devices/me/telemetry` với payload
`{"temperature":..,"humidity":..}`, subscribe `v1/devices/me/rpc/request/+`.
Username MQTT = access token, password rỗng. Task chờ `xBinarySemaphoreInternet`
do `wifi_sta_task` give trước khi kết nối broker.

**Bài 2 - LED Blinky.** LED đơn GPIO 48, chu kỳ 1000 ms; NeoPixel GPIO 45, chu kỳ
500 ms. In trạng thái ra Serial mỗi lần đổi. Dùng `vTaskDelay()` chứ không dùng
`delay()` nên không block các task khác.

**Bài 3 - DHT20.** `Wire.begin(11, 12)`, địa chỉ DHT20 mặc định `0x38`.
`bai3_i2c_scan()` quét bus một lần lúc khởi động và in địa chỉ tìm được.
Đọc mỗi 5 giây, ghi vào `glob_temperature` / `glob_humidity`.

**Bài 4 - Semaphore.** Binary semaphore `xBinarySemaphoreData` đồng bộ
Producer → Consumer; mutex `xMutexSerial` bảo vệ Serial và biến dùng chung.
Log in rõ thứ tự TAKE / GIVE.

**Bài 5 - Webserver.** `WebServer` (đồng bộ) cổng 80. Khởi động vào STA nếu đã có
SSID, không thì phát AP để cấu hình; nhấn nút BOOT để quay lại AP.
Routes: `/`, `/toggle?led=1|2`, `/sensors`, `/settings`, `/connect`.
Trang chủ dùng `fetch()` gọi `/sensors` định kỳ để cập nhật số liệu.

## 5. Cấu trúc thư mục

```
├── platformio.ini
├── boards/yolo_uno.json
├── include/        config.h, global.h, bai1..bai5 headers, wifi_sta.h
├── lib/            DHT20, LCD, PubSubClient, ArduinoJson (copy từ project mẫu)
└── src/            main.cpp, global.cpp, wifi_sta.cpp, bai1..bai5
```
