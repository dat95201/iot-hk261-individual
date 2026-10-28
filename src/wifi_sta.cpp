#include "wifi_sta.h"

/* Lấy từ task_wifi.cpp của project mẫu (phần đang bị comment),
 * đổi sang dùng wifi_ssid / wifi_password trong global.cpp. */
void wifi_sta_task(void *pvParameters)
{
  if (wifi_ssid.isEmpty())
  {
    Serial.println("[WIFI] wifi_ssid rong - kiem tra include/config.h");
    vTaskDelete(NULL);
  }

  WiFi.mode(WIFI_STA);

  if (wifi_password.isEmpty())
    WiFi.begin(wifi_ssid.c_str());
  else
    WiFi.begin(wifi_ssid.c_str(), wifi_password.c_str());

  Serial.print("[WIFI] Connecting to ");
  Serial.print(wifi_ssid);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }

  Serial.println();
  Serial.print("[WIFI] Connected, STA IP address: ");
  Serial.println(WiFi.localIP());
  isWifiConnected = true;

  /* Give semaphore -> task CoreIOT (Bài 1) đang chờ sẽ chạy tiếp */
  xSemaphoreGive(xBinarySemaphoreInternet);

  vTaskDelete(NULL);
}
