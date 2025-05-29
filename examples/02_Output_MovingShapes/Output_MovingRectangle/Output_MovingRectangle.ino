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

  StickCP2.Display.setRotation(1); // this function sets the rotation of the display
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

void loop() {
  sprite->fillScreen(BLACK); // Clear the sprite by filling it with black

  /*** MOVE RECTANGLE - BEGIN ***/
  rectX = rectX + rectSpeedX; // Adds a value to X
  if (rectX + rectWidth > screenWidth || rectX < 0) { // screen boundary check
    rectSpeedX = -rectSpeedX; // if boundary hit, change the direction of movement
  }

  // draw updated rectangle
  sprite->fillRect(rectX, rectY, rectWidth, rectHeight, CYAN); // x (top-left), y (top-left), width, height, color
  /*** MOVE RECTANGLE - END ***/

  // shape options: https://github.com/lovyan03/LovyanGFX/blob/5438181440c71cf30bbdc347b0b1597ae3ebf77d/src/lgfx/v1/LGFXBase.hpp#L192
  sprite->fillCircle(180, 50, 30, VIOLET); // x (center), y (center), radius, color
  sprite->fillEllipse(70, 75, 50, 30, ORANGE); // x (center), y (center), radius-x, radius-y, color
  sprite->fillTriangle(180, 135, 200, 100, 240, 135, YELLOW); // x0, y0, x1, y1, x2, y2, color

  sprite->pushSprite(0, 0); // Push the finished drawing from the sprite onto the actual screen
}
