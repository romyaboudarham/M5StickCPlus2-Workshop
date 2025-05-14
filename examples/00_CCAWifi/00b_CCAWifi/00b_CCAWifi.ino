#include <M5StickCPlus2.h>
#include <WiFi.h>

const char* ssid     = "CCA";
const char* password = "";

void setup() {
  M5.begin();
  Serial.begin(115200);
  M5.Lcd.clear();
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("Connecting to");
  M5.Lcd.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    M5.Lcd.print(".");
  }

  IPAddress ip = WiFi.localIP();
  Serial.printf("\nConnected! IP: %s\n", ip.toString().c_str());
  M5.Lcd.clear();
  M5.Lcd.println("IP:");
  M5.Lcd.println(ip);
}

void loop() {
  // nothing here
}
