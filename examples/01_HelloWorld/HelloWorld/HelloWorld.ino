#include <M5StickCPlus2.h> // this 'include' line includes the M5StickCPlus2 library
						               // this allows us to use functions written for this specific device

// define global variables here
// an "int" is an "integer" which is a WHOLE number (not a fraction or number with a decimal point) i.e. 1, 6, 17, 394
int screenWidth = 0;  // this variable is used to set the screen width
int screenHeight = 0; // this variable is used to set the screen height

void setup() {
  // initialize Serial Monitor to use baud rate 115200
  Serial.begin(115200);
  // initiatlize the device using the M5StickCPlus2 library
  auto cfg = M5.config();
  StickCP2.begin(cfg);

  StickCP2.Display.setRotation(1); // this function sets the rotation of the display
  								                 // 0: portrait, 1: landscape, 2: portrait-flipped, 3: landscape-flipped
  
  screenWidth = StickCP2.Display.width();
  screenHeight = StickCP2.Display.height();
}

void loop() {
  StickCP2.update();

  /*** CUSTOMIZE BEGIN ***/
  // font options: https://github.com/lovyan03/LovyanGFX/blob/55a0f66d9278faa596c8d51a8e8a3e537dd8f44f/src/lgfx/v1/lgfx_fonts.hpp#L329
  StickCP2.Display.setTextFont(&fonts::Orbitron_Light_24);
  // color options: https://github.com/m5stack/M5GFX/blob/b1a0e54e79a1c50d1d0d628524bbde7275423b5f/src/M5GFX.h#L143
  StickCP2.Display.setTextColor(GREEN);
  StickCP2.Display.setTextSize(1); // try 2!
  // text reference point options: https://github.com/lovyan03/LovyanGFX/blob/55a0f66d9278faa596c8d51a8e8a3e537dd8f44f/src/lgfx/v1/misc/enum.hpp#L135
  StickCP2.Display.setTextDatum(top_left);
  StickCP2.Display.drawString("Hello World!", 0, 0); // prints to the device screen
  
  Serial.println("Hello World!"); // prints to the serial monitor
  /*** CUSTOMIZE END ***/
}
