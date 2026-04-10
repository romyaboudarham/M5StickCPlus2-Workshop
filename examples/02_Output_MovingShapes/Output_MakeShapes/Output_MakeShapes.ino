#include <M5StickCPlus2.h> // this 'include' line includes the M5StickCPlus2 library
                           // this allows us to use functions written for this specific device

// and "int" is an "integer" which is a WHOLE number (not a fraction) i.e. 1, 6, 17, 394
int screenWidth = 0;  // this variable is used to set the screen width
int screenHeight = 0; // this variable is used to set the screen height

// A "sprite" is an invisible drawing layer we can use to prepare each frame
// before showing it on the screen. This helps prevent flickering.
LGFX_Sprite *sprite;

void setup()
{
  // initialize Serial Monitor to use baud rate 115200
  Serial.begin(115200);
  // initiatlize the device using the M5StickCPlus2 library
  auto cfg = M5.config();
  StickCP2.begin(cfg);

  StickCP2.Display.setRotation(1);          // this function sets the rotation of the display
                                            // 0: portrait, 1: landscape, 2: portrait-flipped, 3: landscape-flipped
  screenWidth = StickCP2.Display.width();   // 240
  screenHeight = StickCP2.Display.height(); // 135

  sprite = new LGFX_Sprite(&StickCP2.Display);     // Create a new sprite (invisible drawing layer) This lets us draw things off-screen first --> reduces flicker
  sprite->setColorDepth(16);                       // Set the color depth for the sprite (16-bit color is common and looks good)
  sprite->createSprite(screenWidth, screenHeight); // Set the sprite size to cover the full screen
}

int rectX = 0;
int rectY = 0;
int rectSpeed = 1;
int rectWidth = 50;

void loop()
{
  sprite->fillScreen(BLACK); // Clear the sprite by filling it with black

  /*** CUSTOMIZE - BEGIN ***/
  sprite->fillRect(0, 0, 100, 50, CYAN); // Draw rectangle: x (top-left), y (top-left), width, height, color
  /*** CUSTOMIZE - END ***/

  sprite->pushSprite(0, 0); // Push the finished drawing from the sprite onto the actual screen
}