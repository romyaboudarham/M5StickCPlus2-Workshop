#include <M5StickCPlus2.h>
#include "wifiUtils.h"
#include "taskFetcher.h"
#include "shake.h"

// Wifi
const char* ssid      = "CCA"; // REPLACE WITH YOUR WIFI NAME
const char* password  = ""; // REPLACE WITH YOUR WIFI PASSWORD

bool wasShaking = false;

int screenWidth = 0;  // this variable is used to set the screen width
int screenHeight = 0; // this variable is used to set the screen height

int numTasks;

void setup() {
  //  init StickCP2
  auto cfg = M5.config();
  StickCP2.begin(cfg);
  StickCP2.Display.setRotation(1);
  StickCP2.Display.setTextSize(1);

  Serial.begin(115200);
  randomSeed(analogRead(0));
  connectWiFi(ssid, password);

  // initial data load
  fetchTasks(serverURL);

  screenWidth = StickCP2.Display.width();
  screenHeight = StickCP2.Display.height();

  loadStartUpScreen();

  numTasks = 0;
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

  // BtnA → complete task
  if (StickCP2.BtnA.wasPressed()) {
    StickCP2.Speaker.tone(3500, 40);
    delay(50);
    StickCP2.Speaker.tone(4000, 40);
    delay(50);
    StickCP2.Speaker.tone(4700, 100);  // Longer last tone for completion
    numTasks++;
  }

  showNumTasks();

  // BtnB → manual refresh
  if (StickCP2.BtnB.wasPressed()) {
    StickCP2.Display.clear();
    StickCP2.Display.setTextFont(&fonts::Orbitron_Light_24);  // Vector font — don't setTextSize()
    StickCP2.Display.drawString("Loading Tasks", StickCP2.Display.width() / 2, 30);
    fetchTasks(serverURL);
    showTaskInTriangle();
  }
}

// displays task in the triangle
void showTaskInTriangle() {
  /*** CUSTOMIZE BEGIN ***/
  StickCP2.Display.setTextFont(&fonts::Orbitron_Light_24);  // Vector font — don't setTextSize()
  // color options: https://github.com/lovyan03/LovyanGFX/blob/55a0f66d9278faa596c8d51a8e8a3e537dd8f44f/src/lgfx/v1/misc/enum.hpp#L56
  // create custom RGB color: uint32_t myBlue = StickCP2.Display.color565(0, 0, 255); // Pure blue
  drawMagicTriangle(TFT_WHITE, TFT_BLUE); // 1st value: triangle outline color, 2nd value: triangle fill color 
  StickCP2.Display.setTextDatum(MC_DATUM);
  StickCP2.Display.setTextColor(TFT_WHITE, TFT_ORANGE);
  /*** CUSTOMIZE END ***/

  String msg = tasks.empty() ? "No Tasks!" : tasks[random(tasks.size())].c_str();
  drawWrappedText(msg, StickCP2.Display.width() / 2, 30, StickCP2.Display.width() - 20);
}

void loadStartUpScreen() {
  StickCP2.Display.clear();
  StickCP2.Display.setTextFont(&fonts::Orbitron_Light_24);  // Vector font — don't setTextSize()
  StickCP2.Display.setTextDatum(MC_DATUM);
  drawMagicTriangle(TFT_WHITE, TFT_BLUE);
  StickCP2.Display.setTextColor(TFT_WHITE, TFT_ORANGE);
  StickCP2.Display.drawString("SHAKE ME", StickCP2.Display.width() / 2, StickCP2.Display.height() / 2);
}

void showNumTasks() {
  StickCP2.Display.setTextFont(&fonts::lgfxJapanGothic_16); 
  StickCP2.Display.setTextColor(TFT_WHITE, TFT_BLACK);  // Background will auto-clear
  StickCP2.Display.setCursor(5, StickCP2.Display.height()-15);
  StickCP2.Display.printf("completed: %d", numTasks);
}
