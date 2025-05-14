#include "wifiUtils.h"
#include <WiFi.h>
#include <M5StickCPlus2.h>

void connectWiFi(const char* ssid, const char* password) {
  StickCP2.Display.clear();
  StickCP2.Display.println("Connecting to");
  StickCP2.Display.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    StickCP2.Display.print(".");
  }

  StickCP2.Display.clear();
  StickCP2.Display.printf("IP: %s\n", WiFi.localIP().toString().c_str());
  delay(1000);
}
