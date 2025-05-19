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
  StickCP2.Display.setRotation(1);
    
  screenWidth = StickCP2.Display.width(); // 240
  screenHeight = StickCP2.Display.height(); // 135
}

// rectangle variables
int rectX = 0;
int rectY = 0;
int rectWidth = 100;
int rectHeight = 50;
int rectSpeedX = 1;
int rectSpeedY = 2;

// circle variables
int circleX = 180;
int circleY = 50;
int circleRadius = 30;
int circleSpeedY = 1;

void loop() {
  StickCP2.update();

  /*** MOVE RECTANGLE -BEGIN ***/
  // Erase previous rectangle area
  StickCP2.Display.fillRect(rectX, rectY, rectWidth, rectHeight, BLACK); // or background color

  // Update X position & speed direction
  rectX = rectX + rectSpeedX;
  if (rectX + rectWidth > screenWidth || rectX < 0) {
    rectSpeedX = -rectSpeedX;
  }

  // Update Y position & speed direction
  rectY = rectY + rectSpeedY;
  if (rectY + rectHeight > screenHeight || rectY < 0) {
    rectSpeedY = -rectSpeedY;
  }

  // draw updated rectangle
  StickCP2.Display.fillRect(rectX, rectY, rectWidth, rectHeight, CYAN); // x (top-left), y (top-left), width, height, color
  /*** MOVE RECTANGLE - END ***/

  /*** MOVE CIRCLE - BEGIN ***/
  StickCP2.Display.fillCircle(circleX, circleY, circleRadius, BLACK);

  circleY = circleY + circleSpeedY;
  if (circleY + circleRadius > screenHeight || circleY < 0) {
    circleSpeedY = -circleSpeedY;
  }

  StickCP2.Display.fillCircle(circleX, circleY, circleRadius, VIOLET);
  /*** MOVE CIRCLE - END ***/

  /*** MOVE ELLIPSE ***/
  StickCP2.Display.fillEllipse(70, 75, 50, 30, ORANGE); // x (center), y (center), radius-x, radius-y, color

  /*** MOVE TRIANGLE ***/
  StickCP2.Display.fillTriangle(180, 135, 200, 100, 240, 135, YELLOW); // x0, y0, x1, y1, x2, y2, color

  delay(30);
}
