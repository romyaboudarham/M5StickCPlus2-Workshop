#include <M5StickCPlus2.h> // library

void setup() {

  // initiatlize the device using the M5StickCPlus2 library
  auto cfg = M5.config();
  StickCP2.begin(cfg);

  /*** CUSTOMIZE BEGIN ***/
  // 0: portrait, 1: landscape, 2: portrait-flipped, 3: landscape-flipped
  StickCP2.Display.setRotation(1);
  // font options: https://github.com/lovyan03/LovyanGFX/blob/55a0f66d9278faa596c8d51a8e8a3e537dd8f44f/src/lgfx/v1/lgfx_fonts.hpp#L329
  StickCP2.Display.setTextFont(&fonts::Orbitron_Light_24);
  // color options: https://github.com/m5stack/M5GFX/blob/b1a0e54e79a1c50d1d0d628524bbde7275423b5f/src/M5GFX.h#L143
  StickCP2.Display.setTextColor(GREEN);
  StickCP2.Display.setTextSize(1); // try 2!
  // text reference point options: https://github.com/lovyan03/LovyanGFX/blob/55a0f66d9278faa596c8d51a8e8a3e537dd8f44f/src/lgfx/v1/misc/enum.hpp#L135
  StickCP2.Display.setTextDatum(top_left);
  StickCP2.Display.drawString("Hello Romy!", 0, 0);
  /*** CUSTOMIZE END ***/
}

// initialize circle coordinates
int radius = 50;
int x = 0;
int y = 0;

void loop() {
  StickCP2.update();

  if (x < StickCP2.Display.width()-radius) {
    x = x + 5; // x = 0 + 1 = 1
    StickCP2.Display.clear();
    StickCP2.Display.fillCircle(x, y, radius, GREEN); // x, y, radius, color
  } 


  //StickCP2.Display.fillCircle(x, y, 20, ORANGE); // x, y, radius, color

  //StickCP2.Display.fillRect(x, y, 50, 25, VIOLET); // top-left x, top-left y, width, height, color
  delay(500);
}
