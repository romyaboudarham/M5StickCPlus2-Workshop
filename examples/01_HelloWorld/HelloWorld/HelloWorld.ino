#include <M5StickCPlus2.h> // this 'include' line includes the M5StickCPlus2 library
                           // this allows us to use functions written for this specific device

// and "int" is an "integer" which is a WHOLE number (not a fraction) i.e. 1, 6, 17, 394
int screenWidth = 0;  // this variable is used to set the screen width
int screenHeight = 0; // this variable is used to set the screen height

// A "sprite" is an invisible drawing layer we can use to prepare each frame
// before showing it on the screen. This helps prevent flickering.
LGFX_Sprite* sprite;

void setup() {
  // initialize Serial Monitor to use baud rate 115200
  Serial.begin(115200);
  // initiatlize the device using the M5StickCPlus2 library
  auto cfg = M5.config();
  StickCP2.begin(cfg);

  StickCP2.Display.setRotation(3); // this function sets the rotation of the display
  								           // 0: portrait, 1: landscape, 2: portrait-flipped, 3: landscape-flipped
  screenWidth = StickCP2.Display.width(); // 240
  screenHeight = StickCP2.Display.height(); // 135

  sprite = new LGFX_Sprite(&StickCP2.Display); // Create a new sprite (invisible drawing layer) This lets us draw things off-screen first --> reduces flicker
  sprite->setColorDepth(16); // Set the color depth for the sprite (16-bit color is common and looks good)
  sprite->createSprite(screenWidth, screenHeight); // Set the sprite size to cover the full screen
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

// triangle variables
float triangle_X0 = 180; // use "float" for fractions (i.e 1.5, 3.4, etc.)
float triangle_X1 = 200;
float triangle_X2 = 240;
float triangleSpeedX = 1.5;

// ellipse variables
int ellipse_X = 70;
int ellipse_Y = 75;
int ellipse_RadiusX = 50;
int ellipse_RadiusY = 30;
int ellipse_SpeedX = 1;
int ellipse_SpeedY = 1;

void loop() {
  sprite->fillScreen(BLACK); // Clear the sprite by filling it with black

  /*** MOVE RECTANGLE - BEGIN ***/
  rectX = rectX + rectSpeedX; // Adds a value to X
  if (rectX + rectWidth > screenWidth || rectX < 0) { // left or right boundary check
    rectSpeedX = -rectSpeedX; // if boundary hit, change the direction of X movement
  }

  rectY = rectY + rectSpeedY;  // Adds a value to Y
  if (rectY + rectHeight > screenHeight || rectY < 0) { // top or bottom boundary check
    rectSpeedY = -rectSpeedY; // if boundary hit, change the direction of Y movement
  }

  // draw updated rectangle
  sprite->fillRect(rectX, rectY, rectWidth, rectHeight, YELLOW); // x (top-left), y (top-left), width, height, color
  /*** MOVE RECTANGLE - END ***/

  /*** MOVE CIRCLE - BEGIN ***/
  circleY = circleY + circleSpeedY;
  if (circleY + circleRadius > screenHeight || circleY < 0) {
    circleSpeedY = -circleSpeedY;
  }

  sprite->fillCircle(circleX, circleY, circleRadius, OLIVE);
  /*** MOVE CIRCLE - END ***/

  /*** MOVE TRIANGLE - BEGIN ***/
  triangle_X0 = triangle_X0 + triangleSpeedX;
  triangle_X1 = triangle_X1 + triangleSpeedX;
  triangle_X2 = triangle_X2 + triangleSpeedX;
  if (triangle_X0 + 60 > screenWidth || triangle_X0 < 0) {
    triangleSpeedX = -triangleSpeedX;
  }
  sprite->fillTriangle(triangle_X0, 135, triangle_X1, 100, triangle_X2, 135, GREENYELLOW); // x0, y0, x1, y1, x2, y2, color
  /*** MOVE TRIANGLE - BEGIN ***/

  /*** MOVE ELLIPSE - BEGIN ***/
  ellipse_X = ellipse_X + ellipse_SpeedX; // Adds a value to X
  if (ellipse_X + ellipse_RadiusX > screenWidth || ellipse_X < 0) { // left or right boundary check
    ellipse_SpeedX = -ellipse_SpeedX; // if boundary hit, change the direction of X movement
  }

  ellipse_Y = ellipse_Y + ellipse_SpeedY; // Adds a value to X
  if (ellipse_Y + ellipse_RadiusY > screenHeight|| ellipse_Y < 0) { // left or right boundary check
    ellipse_SpeedY = -ellipse_SpeedY; // if boundary hit, change the direction of X movement
  }

  sprite->fillEllipse(ellipse_X, ellipse_Y, ellipse_RadiusX, ellipse_RadiusY, GREEN); // x (center), y (center), radius-x, radius-y, color
  /*** MOVE ELLIPSE - END ***/

  sprite->pushSprite(0, 0); // Push the finished drawing from the sprite onto the actual screen
}