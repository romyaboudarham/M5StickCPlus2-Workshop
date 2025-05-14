#include "taskFetcher.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>

extern const char* serverURL = "https://script.google.com/macros/s/AKfycbw2Hr2BnaoYhFCzlYHDQkSW6F1BHWnJ-UnDmXtt7cul2avT-uBP4KBnzdb7DS4sb-57yA/exec";

std::vector<String> tasks;

unsigned long lastFetch      = 0;
const unsigned long interval = 120000UL;  // 2 minutes

void autoFetchEvery(unsigned long  intervalMs) {
  unsigned long now = millis();
  if (now - lastFetch >= intervalMs) {
    lastFetch = now;
    fetchTasks(serverURL);
    Serial.println("Auto-refreshed");
  }
}

void fetchTasks(const char* serverURL) {
  HTTPClient http;
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  http.begin(serverURL);

  int code = http.GET();
  if (code != 200) {
    Serial.printf("HTTP error: %d\n", code);
    http.end();
    return;
  }

  String payload = http.getString();
  DynamicJsonDocument doc(4096);
  if (deserializeJson(doc, payload)) {
    Serial.println("JSON parse error");
    http.end();
    return;
  }

  tasks.clear();
  for (JsonObject row : doc.as<JsonArray>()) {
    if (row.containsKey("Task")) {
      tasks.push_back(String((const char*)row["Task"]));
      Serial.print("Loaded: ");
      Serial.println(row["Task"].as<const char*>());
    }
  }

  http.end();
}
