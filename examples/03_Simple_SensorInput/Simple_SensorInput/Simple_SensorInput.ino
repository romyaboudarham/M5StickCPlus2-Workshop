#include <M5StickCPlus2.h> // library

void setup() {
  // initiatlize the device using the M5StickCPlus2 library
  auto cfg = M5.config();
  StickCP2.begin(cfg);

  Serial.begin(115200);

  /*** CUSTOMIZE BEGIN ***/
  // 0: portrait, 1: landscape, 2: portrait-flipped, 3: landscape-flipped
  StickCP2.Display.setRotation(1);
  // font options: https://github.com/lovyan03/LovyanGFX/blob/55a0f66d9278faa596c8d51a8e8a3e537dd8f44f/src/lgfx/v1/lgfx_fonts.hpp#L329
  StickCP2.Display.setTextFont(&fonts::Orbitron_Light_24);
  // color options: https://github.com/m5stack/M5GFX/blob/b1a0e54e79a1c50d1d0d628524bbde7275423b5f/src/M5GFX.h#L143
  // uint16_t customColor = color565(0, 255, 0); // RGB for Green
  StickCP2.Display.fillScreen(BLACK);
  StickCP2.Display.setTextColor(GREEN);
  StickCP2.Display.setTextSize(1); // try 2!
  // text reference point options: https://github.com/lovyan03/LovyanGFX/blob/55a0f66d9278faa596c8d51a8e8a3e537dd8f44f/src/lgfx/v1/misc/enum.hpp#L135
  StickCP2.Display.setTextDatum(top_left);
  StickCP2.Display.drawString("Press a Button!", 0, 0); // text, x, y
  /*** CUSTOMIZE END ***/

  delay(500);
}

void loop() {
  StickCP2.update();

  if (StickCP2.BtnA.wasPressed()) {
    StickCP2.Speaker.tone(8000, 20); // frequency, duration
    StickCP2.Display.fillScreen(NAVY);
    delay(200);
    StickCP2.Display.drawString("Btn A Pressed", 0, 0);
  }
  if (StickCP2.BtnB.wasPressed()) { 
    StickCP2.Speaker.tone(8000, 20);
    StickCP2.Display.fillScreen(PURPLE);
    delay(200);
    StickCP2.Display.drawString("Btn B Pressed", 0, 0);
  }
}
