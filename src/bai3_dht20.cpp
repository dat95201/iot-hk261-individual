#include "bai3_dht20.h"

/* ============================================================
 * BÀI 3 - KẾT NỐI I2C VỚI CẢM BIẾN DHT20
 *   SDA: GPIO 11   SCL: GPIO 12   Địa chỉ I2C: 0x38
 *   Giá trị đọc được ghi vào glob_temperature / glob_humidity
 *   để Bài 1 (CoreIOT) và Bài 5 (webserver) dùng lại.
 * ============================================================ */

DHT20 dht20;
LiquidCrystal_I2C lcd(33, 16, 2);   // giữ theo code mẫu (không dùng tới)

/* Quét bus I2C - dựa trên ví dụ i2c_scanner chuẩn của Arduino */
void bai3_i2c_scan(void)
{
  uint8_t count = 0;
  Serial.println("[BAI3] Scanning I2C bus...");

  for (uint8_t address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0)
    {
      Serial.printf("[BAI3] I2C device found at 0x%02X%s\n", address,
                    (address == CFG_DHT20_ADDR) ? "  <-- DHT20" : "");
      count++;
    }
    delay(2);
  }

  if (count == 0) Serial.println("[BAI3] No I2C device found - kiem tra day SDA/SCL va nguon");
  else            Serial.printf("[BAI3] Done, %d device(s) found\n", count);
}

void bai3_dht20_task(void *pvParameters)
{
  Wire.begin(CFG_I2C_SDA, CFG_I2C_SCL);   // khởi tạo bus I2C
  dht20.begin();                          // khởi tạo cảm biến

  bai3_i2c_scan();                        // quét bus 1 lần lúc khởi động

  while (1)
  {
    dht20.read();
    float temperature = dht20.getTemperature();   // nhiệt độ (°C)
    float humidity    = dht20.getHumidity();      // độ ẩm (%)

    /* Xử lý lỗi khi đọc thất bại */
    if (isnan(temperature) || isnan(humidity))
    {
      Serial.println("[BAI3] Failed to read from DHT sensor!");
      temperature = humidity = -1;
    }

    /* Cập nhật biến toàn cục cho các bài khác dùng */
    glob_temperature = temperature;
    glob_humidity    = humidity;

    /* Gop thanh 1 lan ghi: moi Serial.print la 1 transfer USB CDC rieng,
       cang nhieu transfer cang de thung giua dong. */
    Serial.printf("[BAI3] Humidity: %.2f%%  Temperature: %.2f C\n",
                  humidity, temperature);
    Serial.flush();

    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}
