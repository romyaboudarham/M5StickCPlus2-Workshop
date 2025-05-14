#include <M5StickCPlus2.h> // library

/* 
The setup() function is called when a sketch starts.
The setup() function will only run ONCE, after each power-up
Use it to initialize variables, start using libraries, etc.
*/
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
  StickCP2.Display.drawString("Hello World!", 0, 0);
  /*** CUSTOMIZE END ***/
}

/*
 * The loop() function does precisely what its name suggests: loops consecutively through your lines of instructions
 * The loop() functions runs continuously as long as the device is powered on.
 * Each instruction is executed in order from top to bottom, one at a time
 */
void loop() {
  StickCP2.update();

}
