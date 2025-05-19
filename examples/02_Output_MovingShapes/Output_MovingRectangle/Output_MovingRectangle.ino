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
  screenWidth = StickCP2.Display.width(); // 240
  screenHeight = StickCP2.Display.height(); // 135

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

// rectangle variables
int rectX = 0;
int rectY = 0;
int rectWidth = 100;
int rectHeight = 50;
int rectSpeedX = 1;

void loop() {
  StickCP2.update();

  /*** MOVE RECTANGLE - BEGIN ***/
  // Erase previous rectangle area
  StickCP2.Display.fillRect(rectX, rectY, rectWidth, rectHeight, BLACK); // or background color

  // Update X position & speed direction
  rectX = rectX + rectSpeedX;
  if (rectX + rectWidth > screenWidth || rectX < 0) {
    rectSpeed = -rectSpeedX;
  }

  // draw updated rectangle
  StickCP2.Display.fillRect(rectX, rectY, rectWidth, rectHeight, CYAN); // x (top-left), y (top-left), width, height, color
  /*** MOVE RECTANGLE - END ***/

  // shape options: https://github.com/lovyan03/LovyanGFX/blob/5438181440c71cf30bbdc347b0b1597ae3ebf77d/src/lgfx/v1/LGFXBase.hpp#L192
  StickCP2.Display.fillCircle(180, 50, 30, VIOLET); // x (center), y (center), radius, color
  StickCP2.Display.fillEllipse(70, 75, 50, 30, ORANGE); // x (center), y (center), radius-x, radius-y, color
  StickCP2.Display.fillTriangle(180, 135, 200, 100, 240, 135, YELLOW); // x0, y0, x1, y1, x2, y2, color

  delay(30);
}
