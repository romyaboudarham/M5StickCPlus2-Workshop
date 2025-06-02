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

  // set up sprite
  sprite = new LGFX_Sprite(&StickCP2.Display); // Create a new sprite (invisible drawing layer) This lets us draw things off-screen first --> reduces flicker
  sprite->setColorDepth(16); // Set the color depth for the sprite (16-bit color is common and looks good)
  sprite->createSprite(screenWidth, screenHeight); // Set the sprite size to cover the full screen
  
  sprite->setTextColor(WHITE);
  sprite->setTextSize(3);
  sprite->fillScreen(BLACK);
  sprite->drawString("Press Btn A", 5, 5); 
  sprite->drawString("or Btn B", 5, 30); 

  sprite->pushSprite(0, 0); // Push the finished drawing from the sprite onto the actual screen
}

int rectWidth = 40;
int rectHeight = 8;
int rectX = 100;
int rectY = 120;
int rectSpeed = 5; // # of pixels to move the shape 5 pixels;

void loop() {
  StickCP2.update(); // for inputs (i.e. Button)

   /*** CUSTOMIZE BEGIN ***/
  if (StickCP2.BtnA.isPressed()) {
    rectX = rectX + rectSpeed; // ADDED: Move rect to the right 
    StickCP2.Speaker.tone(2000, 30); // frequency, duration of tone
    sprite->fillScreen(NAVY);
    sprite->drawString("Btn A Pressed", 5, 5);
  }
  if (StickCP2.BtnB.isPressed()) {
    rectX = rectX - rectSpeed; // ADDED: move rect to the left
    StickCP2.Speaker.tone(1200, 30); // frequency, duration of tone
    sprite->fillScreen(PURPLE);
    sprite->drawString("Btn B Pressed", 5, 5);
  }
   /*** CUSTOMIZE END ***/

  sprite->fillRect(rectX, rectY, rectWidth, rectHeight, ORANGE); // Draw rectangle: x (top-left), y (top-left), width, height, color

  sprite->pushSprite(0, 0); // Push the finished drawing from the sprite onto the actual screen
}
