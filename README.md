# SF Design Week - Interactive Wearables Workshop

By Romy Aboudarham with support from Sudhu Tewari

The workshop will introduce you to the basics of physical prototyping using the Arduino software and fundamental coding concepts like variables, functions, and loops to transform design ideas into an interactive experience with M5Stack's M5StickC Plus2 watch. 

M5StickCPlus2 watch & USB cables will be provided for you to use and keep during the workshop.

If you have questions prior to or after the workshop please contact Romy: romyaboudarham@gmail.com

## Section 0 - Before the Workshop
### 0.1 Install Arduino Software
Arduino software (IDE) runs on Windows, Mac OSX, and Linux. Please download and install the (free) [Arduino software here](http://arduino.cc/en/Main/Software).  <!-- We prefer to use an older version of the Arduino IDE: Version 1.8.19. Feel free to download the newer version as well and run them both for comparison. -->
Please bring your laptop, with the software installed, to the workshop. **Laptops with the Arduino IDE installed will be provided for those without one**

Additional instructions [on M5Stack's Arduino instructions here](https://docs.m5stack.com/en/arduino/arduino_ide) and [Adafruit's Arduino lessons here](https://learn.adafruit.com/ladyadas-learn-arduino-lesson-number-0/download-software)

### 0.2 Install M5StickC Plus2 Board Management to Arduino IDE
The Board Manager URL is a link that tells the Arduino software where to find the information it needs to work with your M5StickC Plus2 device.

**0.2.1** Open Arduino Software (IDE) &nbsp;&nbsp;&nbsp;&nbsp;

**0.2.2** Click _Arduino->Settings->Add Aditional Board Manager URLS_ &nbsp;&nbsp;&nbsp;&nbsp;
<img src="https://github.com/romyaboudarham/M5StickCPlus2-Workshop/blob/main/media/0.2.2a-arudino_settings.png" style="width: 700px; height: auto;">

<img src="https://github.com/romyaboudarham/M5StickCPlus2-Workshop/blob/main/media/0.2.2b-open_urls.png" style="width: 700px; height: auto;">
   
   - Copy this URL: ```https://static-cdn.m5stack.com/resource/arduino/package_m5stack_index.json```
   - Paste the URL into "Additional Board Manager URLs" text field

<img src="https://github.com/romyaboudarham/M5StickCPlus2-Workshop/blob/main/media/0.2.2c-paste_url.png" style="width: 700px; height: auto;">

**0.2.3** In left sidebar, click "Boards Manager" icon &nbsp;&nbsp;&nbsp;&nbsp;
   - Search for "M5Stack" and **Install**
   
<img src="https://github.com/romyaboudarham/M5StickCPlus2-Workshop/blob/main/media/install-library-tutorial.png" style="width: 700px; height: auto;">

### 0.3 Install M5StickCPlus2 Library to Arduino IDE

**0.3.1** In left sidebar, click "Library Manager" icon &nbsp;&nbsp;&nbsp;&nbsp;
   - Search for "M5StickCPlus2" and **Install**
   - You will then be asked about installing dependencies. **Click "INSTALL ALL"**
<img src="https://github.com/romyaboudarham/M5StickCPlus2-Workshop/blob/main/media/0.3.1a-open_library_manager.png" style="width: 700px; height: auto;">

   - ALTERNATE: You can also access the Library Manager like this:
<img src="https://github.com/romyaboudarham/M5StickCPlus2-Workshop/blob/main/media/0.3.1b-alt_open_library_manager.png" style="width: 700px; height: auto;">

## Section 1 - WELCOME to the WORKSHOP!!
 - Please interrupt any time with questions.

### 1.1 First steps: Verifying correct installation

**1.1.1** Connect M5Stick via USB cable &nbsp;&nbsp;&nbsp;&nbsp;
   - Windows? Might see “New Hardware Discovered” and later might see “New Hardware Ready for Use”.
   - Mac OS X? Might see “New Network Interface Found”. Click “Network Preferences…”,  click “Apply”, and when it finishes, click “Close”. It doesn’t matter if the configuration fails.
   - Linux? Nothing to do here

**1.1.2** Open Arduino software (IDE) &nbsp;&nbsp;&nbsp;&nbsp;

**1.1.3** Select _Tools->Board-> M5Stack->M5StickCPlus2_ (If you don't see "M5StickCPlus2" you may not have correctly installed the board manager URL in the previous step) &nbsp;&nbsp;&nbsp;&nbsp;

**1.1.4** Select _Tools -> Port_ &nbsp;&nbsp;&nbsp;&nbsp;
   - Windows? Chose the largest COM number
     - No COMs? Raise your hand for help
   - Mac OS X? Chose either usbserial - you should also see _(LilyGo T-Display)_
     - No usbserial? Raise your hand for help
   - Linux? There is only one choice

**1.1.5** Should look something like this &nbsp;&nbsp;&nbsp;&nbsp;

   <img src="https://github.com/romyaboudarham/M5StickCPlus2-Workshop/blob/main/media/successful-install.png" style="width: 700px; height: auto;">



*******************************************************************************
### 1.2 Is this thing on?
**1.2.1**  Copy the code below and paste it into a new, empty Arduino sketch _OR_ download and open this example sketch: [HelloWorld.ino](/examples/01_HelloWorld/HelloWorld/HelloWorld.ino) &nbsp;&nbsp;&nbsp;&nbsp;

```cpp
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
```
**1.2.2** "Compile" & "Upload" the code to the device by clicking the Arrow in the top left corner &nbsp;&nbsp;&nbsp;&nbsp;
   - Compile = translate this code (C++) into machine-readable language. This step also checks for correct syntax in your code.
   - Upload = sending the code to the device, where the code is now stored on the device, so when you disconnect it form your computer the code still lives on the device.

**1.2.3** Open up the "Serial Monitor" by clicking on the magnifying glass near the top right corner (the monitor will either open in a new window or at the bottom of your screen depending on your computer). &nbsp;&nbsp;&nbsp;&nbsp;
   - This is where we will see any text within "Serial.println(...)".
   - The _Serial_ commands allow Arduino IDE to send a message to your laptop.
   - Baud rate = the rate at which information is transferred in a communication channel. "115200 baud" means that the serial port is capable of transferring a maximum of 115200 bits per second.

<img src="https://github.com/romyaboudarham/M5StickCPlus2-Workshop/blob/main/media/HelloWorld.png" style="width: 720px; height: auto;">  

Success!
   
<img src="https://github.com/romyaboudarham/M5StickCPlus2-Workshop/blob/main/media/HelloWorldM5Stick.jpeg" style="width: 500px; height: auto;"> 

#### How is this working??
- The [setup()](https://www.arduino.cc/reference/en/language/structure/sketch/setup/) function is called when a sketch starts.
  - Use it to initialize variables, pin modes, start using libraries, etc. In our case, this is where we set up the screen display features (text color, font, orientation, default text etc.) 
  - The setup() function will only run once, after each power-up or reset of the Arduino board.
- The [loop()](https://www.arduino.cc/reference/en/language/structure/sketch/loop/) the loop() function does precisely what its name suggests, and _loops_ consecutively through your list of instructions to control the Arduino.
  - The loop() functions runs continuously as long as the Arduino is powered on.
  - Each instruction is executed in order from top to bottom.
  - Arduino only executes one instruction at a time.
 
#### YOUR TURN
- Change the code to display "Hello YOUR-NAME" on the watch and in the Serial Monitor
- Change the color, font, size, placement of the text
- CHALLENGE: center the text (hint: will need to use screenWidth and screenHeight from lines 16 and 17)
*******************************************************************************
## Section 2 - Let's make and move shapes oOOooOo pretty!
### 2.1 Making the Shapes
Screens use a coordinate system where (0,0) starts at the top-left corner. The x-axis goes right and is the first number in the pair. The y-axis goes down and is the second number in the pair (x,y). Each pixel’s position is marked by how far it is from the top-left. This is how most LED and digital screens work when placing or lighting up pixels.  

<img src="https://github.com/romyaboudarham/M5StickCPlus2-Workshop/blob/main/media/axis.png" style="width: 550px; height: auto;"> 

**2.1.1** Within the **"loop()"** function, add this line. Compile & Upload. (Right arrow in upper left) &nbsp;&nbsp;&nbsp;&nbsp;
```cpp
StickCP2.Display.fillRect(0, 0, 100, 50, CYAN); // x (top-left), y (top-left), width, height, color
```
&ensp; **YOUR TURN:** Change the x, y, width, height, and color values  

**2.1.2** Now add these lines. Compile & Upload. &nbsp;&nbsp;&nbsp;&nbsp;
```cpp
// shape options: https://github.com/lovyan03/LovyanGFX/blob/5438181440c71cf30bbdc347b0b1597ae3ebf77d/src/lgfx/v1/LGFXBase.hpp#L192
StickCP2.Display.fillCircle(180, 50, 30, VIOLET); // x (center), y (center), radius, color
StickCP2.Display.fillEllipse(70, 75, 50, 30, ORANGE); // x (center), y (center), radius-x, radius-y, color
StickCP2.Display.fillTriangle(180, 135, 200, 100, 240, 135, YELLOW); // x0, y0, x1, y1, x2, y2, color
```

&ensp; **YOUR TURN:** Change the values of the shapes and make some art!
### 2.2 Moving the Shapes
**2.2.1** VARIABLES! Make the following additions and changes in your code. &nbsp;&nbsp;&nbsp;&nbsp;
- The 2 lines above loop() create **variables** (rectX, rectY) that hold **integers** (int) that represent the x and y coordinate of your rectangle. 1. If you have multiple rectangles, you will want multiple variables with distinct names. For example, rect1_X, rect2_X, etc.
- The numbers for the x and y coordinates are now replaced with these variables.
```
int rectX = 0; // <-- ADD
int rectY = 0; // <-- ADD 

void loop() {
   StickCP2.update();

   StickCP2.Display.fillRect(rectX, rectY, 100, 50, CYAN); // <-- CHANGE the X & Y values
  ...
```
Compile to check for errors (checkmark in upper left)

**2.2.2** IF STATEMENTS! &nbsp;&nbsp;&nbsp;&nbsp;
- **QUESTION** Since we know that loop() is endlessing looping and drawing the rectangle at position (0,0), what do we need to do to the rectangle's X value to move it across the screen to the right?
- **QUESTION** The rectangle is going to move infinitely across and off the screen, how do we account for boundaries of the screen and have the shape move back and forth?  

Final code for moving rectangle back and forth here: [Output_MovingRectangle.ino](examples/02_Output_MovingShapes/Output_MovingRectangle/Output_MovingRectangle.ino)
- **CHALLENGE** move the rectangle up and down (hint: similar to moving rectX, but with rectY, a new variable for rectSpeedY, and using screenHeight)
- **CHALLENGE** make all the shapes move!  

Final code for moving all shapes here: [Output_MovingShapes.ino](examples/02_Output_MovingShapes/Output_MovingAllShapes/Output_MovingAllShapes.ino)

## Section 3 - Let's move a shape when we press a button!
