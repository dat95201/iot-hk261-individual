#ifndef __CONFIG_H__
#define __CONFIG_H__

/* ============================================================
 *  CẤU HÌNH DÙNG CHUNG CHO 5 BÀI THỰC HÀNH
 *  >>> ĐIỀN THÔNG TIN THẬT VÀO ĐÂY TRƯỚC KHI NẠP <<<
 *  Lưu ý: báo cáo yêu cầu KHÔNG để lộ mật khẩu Wi-Fi và
 *  access token, nên khi chụp màn hình / nộp bài hãy che lại.
 * ============================================================ */

// ---- Wi-Fi mà YoloUNO sẽ kết nối vào (chế độ Station) ----
#define CFG_WIFI_SSID       "YOUR_WIFI_SSID"
#define CFG_WIFI_PASSWORD   "YOUR_WIFI_PASSWORD"

// ---- Wi-Fi do YoloUNO tự phát ra (chế độ Access Point - Bài 5) ----
#define CFG_AP_SSID         "ESP32-HK261"
#define CFG_AP_PASSWORD     "12345678"

// ---- CoreIOT (Bài 1) ----
#define CFG_COREIOT_SERVER  "app.coreiot.io"
#define CFG_COREIOT_PORT    "1883"
#define CFG_COREIOT_TOKEN   "ACCESS_TOKEN"   // access token của device trên CoreIOT

// ---- Chân GPIO (theo board YoloUNO / ESP32-S3) ----
#define CFG_LED_GPIO        48    // LED đơn trên board
#define CFG_NEO_PIN         45    // NeoPixel RGB
#define CFG_NEO_COUNT       1
#define CFG_BOOT_PIN        0     // nút BOOT, dùng để quay lại chế độ AP

// ---- I2C cho DHT20 (Bài 3) ----
#define CFG_I2C_SDA         11
#define CFG_I2C_SCL         12
#define CFG_DHT20_ADDR      0x38

#endif
