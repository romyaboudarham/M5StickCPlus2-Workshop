#include <M5StickCPlus2.h> // library

// and "int" is an "integer" which is a WHOLE number (not a fraction) i.e. 1, 6, 17, 394
int screenWidth = 0;
int screenHeight = 0;

void setup() {
  // initialize Serial Monitor to use baud rate 115200
  Serial.begin(115200);
  // initiatlize the device using the M5StickCPlus2 library
  auto cfg = M5.config();
  StickCP2.begin(cfg);

  // 0: portrait, 1: landscape, 2: portrait-flipped, 3: landscape-flipped
  StickCP2.Display.setRotation(1);
  screenWidth = StickCP2.Display.width();
  screenHeight = StickCP2.Display.height();

  /*** CUSTOMIZE BEGIN ***/
  // font options: https://github.com/lovyan03/LovyanGFX/blob/55a0f66d9278faa596c8d51a8e8a3e537dd8f44f/src/lgfx/v1/lgfx_fonts.hpp#L329
  StickCP2.Display.setTextFont(&fonts::Orbitron_Light_24);
  // color options: https://github.com/m5stack/M5GFX/blob/b1a0e54e79a1c50d1d0d628524bbde7275423b5f/src/M5GFX.h#L143
  StickCP2.Display.setTextColor(GREEN);
  StickCP2.Display.setTextSize(1); // try 2!
  // text reference point options: https://github.com/lovyan03/LovyanGFX/blob/55a0f66d9278faa596c8d51a8e8a3e537dd8f44f/src/lgfx/v1/misc/enum.hpp#L135
  StickCP2.Display.setTextDatum(middle_center);
  StickCP2.Display.drawString("Hello World!", screenWidth/2, screenHeight/2);
  /*** CUSTOMIZE END ***/
}

void loop() {
  StickCP2.update();

  Serial.println("Printing in Serial Monitor!");
}