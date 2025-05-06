#include <M5StickCPlus2.h>
#include "wifiUtils.h"
#include "taskFetcher.h"
#include "shake.h"

// Wifi
const char* ssid      = "CCA";
const char* password  = "";

bool wasShaking = false;

void setup() {
  //  init StickCP2
  auto cfg = M5.config();
  StickCP2.begin(cfg);

  Serial.begin(115200);
  randomSeed(analogRead(0));
  connectWiFi(ssid, password);

  // initial data load
  fetchTasks(serverURL);

  StickCP2.Display.clear();

  /*** CUSTOMIZE BEGIN ***/
  StickCP2.Display.setTextSize(2);
  StickCP2.Display.setRotation(1);
  // color options: https://github.com/lovyan03/LovyanGFX/blob/55a0f66d9278faa596c8d51a8e8a3e537dd8f44f/src/lgfx/v1/misc/enum.hpp#L56
  StickCP2.Display.setTextColor(GREEN);
  // text placement options: https://github.com/lovyan03/LovyanGFX/blob/55a0f66d9278faa596c8d51a8e8a3e537dd8f44f/src/lgfx/v1/misc/enum.hpp#L135
  StickCP2.Display.setTextDatum(baseline_center);
  // font options: https://github.com/lovyan03/LovyanGFX/blob/55a0f66d9278faa596c8d51a8e8a3e537dd8f44f/src/lgfx/v1/lgfx_fonts.cpp#L1154
  StickCP2.Display.setTextFont(&fonts::Orbitron_Light_24);
  StickCP2.Display.setTextSize(1);
  //StickCP2.Display.drawString("Shake me!", StickCP2.Display.width() / 2, StickCP2.Display.height() / 2);
  StickCP2.Display.println("Button B: refresh");
  StickCP2.Display.println("SHAKE ME");
  /*** CUSTOMIZE END ***/
}

void loop() {
  StickCP2.update();

  // auto-refresh every 2 minutes (120000 ms)
  autoFetchEvery(120000UL);

  // Shake detection: on falling edge, print a new task
  bool isShaking = detectShaking();
  if (!isShaking && wasShaking) {
    showTaskInTriangle();
  }
  wasShaking = isShaking;

  // BtnA → show random task
  if (StickCP2.BtnA.wasPressed()) {
  }

  // BtnB → manual refresh
  if (StickCP2.BtnB.wasPressed()) {
    StickCP2.Display.clear();
    StickCP2.Display.setCursor(0, 30);
    StickCP2.Display.println("Refreshing...");
    fetchTasks(serverURL);
    StickCP2.Display.clear();
    StickCP2.Display.println("Shake me!");
  }
}

// displays task in the triangle
void showTaskInTriangle() {
  if (tasks.empty()) {
    StickCP2.Display.drawString("No Tasks!", triCenterX, triCenterY, 2);
    return;
  }
  /*** CUSTOMIZE BEGIN ***/
  // color options: https://github.com/lovyan03/LovyanGFX/blob/55a0f66d9278faa596c8d51a8e8a3e537dd8f44f/src/lgfx/v1/misc/enum.hpp#L56
  // create custom RGB color: uint32_t myBlue = StickCP2.Display.color565(0, 0, 255); // Pure blue
  drawMagicTriangle(TFT_WHITE, TFT_BLUE); // 1st value: triangle outline color, 2nd value: triangle fill color 
  StickCP2.Display.setTextDatum(MC_DATUM);
  StickCP2.Display.setTextColor(TFT_WHITE, TFT_ORANGE);
  StickCP2.Display.setTextSize(2);
  /*** CUSTOMIZE END ***/
  
  int i = random(tasks.size());
  StickCP2.Display.drawString(tasks[i].c_str(), triCenterX, triCenterY, 2);
}