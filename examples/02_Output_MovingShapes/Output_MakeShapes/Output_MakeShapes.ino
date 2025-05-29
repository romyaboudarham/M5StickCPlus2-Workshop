#include <M5StickCPlus2.h> // this 'include' line includes the M5StickCPlus2 library
                           // this allows us to use functions written for this specific device

// and "int" is an "integer" which is a WHOLE number (not a fraction) i.e. 1, 6, 17, 394
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
  screenWidth = StickCP2.Display.width(); // 240
  screenHeight = StickCP2.Display.height(); // 135
}

void loop() {
  StickCP2.update();

  // CUSTOMIZE
  StickCP2.Display.fillRect(0, 0, 100, 50, CYAN); // x (top-left), y (top-left), width, height, color
  // shape options: https://github.com/lovyan03/LovyanGFX/blob/5438181440c71cf30bbdc347b0b1597ae3ebf77d/src/lgfx/v1/LGFXBase.hpp#L192
  StickCP2.Display.fillCircle(180, 50, 30, VIOLET); // x (center), y (center), radius, color
  StickCP2.Display.fillEllipse(70, 75, 50, 30, ORANGE); // x (center), y (center), radius-x, radius-y, color
  StickCP2.Display.fillTriangle(180, 135, 200, 100, 240, 135, YELLOW); // x0, y0, x1, y1, x2, y2, color
}