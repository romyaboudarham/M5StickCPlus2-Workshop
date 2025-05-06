#include "M5StickCPlus2.h"
#include <WiFi.h>

void setup() {
  // Init M5 hardware (screen, buttons, etc.)
  M5.begin();

  // Start serial for debugging
  Serial.begin(115200);
  delay(100);

  // Prepare the LCD
  M5.Lcd.clear();
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("Station MAC:");

  // Ensure WiFi is in station mode (default)
  WiFi.mode(WIFI_STA);

  // Read the MAC address
  String mac = WiFi.macAddress();

  // Output to Serial
  Serial.print("M5StickC PLUS 2 MAC: ");
  Serial.println(mac);

  // Display on LCD
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.println(mac);
}

void loop() {
  // Nothing else to do
}
