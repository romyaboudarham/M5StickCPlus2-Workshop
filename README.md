# SF Design Week - Interactive Wearables Workshop

By Romy Aboudarham with support from Sudhu Tewari

The workshop will introduce you to the basics of physical prototyping using the Arduino software and fundamental coding concepts like variables, functions, and loops to transform design ideas into an interactive experience with M5Stack's M5StickC Plus2 watch. 

M5StickCPlus2 watch & USB cables will be provided for you to use and keep during the workshop.

If you have questions prior to or after the workshop please contact Romy: romyaboudarham@gmail.com

## Before the Workshop
#### 1. Install Arduino Software
Arduino software (IDE) runs on Windows, Mac OSX, and Linux. Please download and install the (free) [Arduino software here](http://arduino.cc/en/Main/Software).  <!-- We prefer to use an older version of the Arduino IDE: Version 1.8.19. Feel free to download the newer version as well and run them both for comparison. -->
Please bring your laptop, with the software installed, to the workshop. **Laptops with the Arduino IDE installed will be provided for those without one**

Additional instructions [here](https://docs.m5stack.com/en/arduino/arduino_ide) and [here](https://learn.adafruit.com/ladyadas-learn-arduino-lesson-number-0/download-software)

#### 2. Install M5StickC Plus2 Board Management to Arduino IDE
The Board Manager URL is like a link that tells the Arduino software where to find the information it needs to work with your M5StickC Plus2 device.

1. Open Arduino IDE to a new blank sketch
2. Click _Arduino -> Settings -> Add Aditional Board Manager URLS_
   - Copy this URL: ```https://static-cdn.m5stack.com/resource/arduino/package_m5stack_index.json```
   - Paste the URL into "Additional Board Manager URLs" text field

![Alt text](https://github.com/romyaboudarham/M5StickCPlus2-Workshop/blob/main/media/add-board-url-tutorial.png)

3. In left sidebar, click "Boards Manager" icon
   - Search for "M5Stack" and **Install**
   
![Alt text](https://github.com/romyaboudarham/M5StickCPlus2-Workshop/blob/main/media/install-library-tutorial.png)


## At the Workshop
 - Please interrupt any time with questions.

### First steps: Verifying correct installation

1. Connect M5Stick via USB cable
   - Windows? Might see “New Hardware Discovered” and later might see “New Hardware Ready for Use”.
   - Mac OS X? Might see “New Network Interface Found”. Click “Network Preferences…”,  click “Apply”, and when it finishes, click “Close”. It doesn’t matter if the configuration fails.
   - Linux? Nothing to do here

2. Open Arduino software (IDE)

3. Select _Tools -> Board -> M5Stack -> M5StickCPlus2_

4. Select _Tools -> Port_ 
   - Windows? Chose the largest COM number
     - No COMs? Raise your hand for help
   - Mac OS X? Chose either usbmodem - you should also see _(LilyGo T-Display)_
     - No usbmodem? Raise your hand for help
   - Linux? There is only one choice

5. Open _File->Examples->Basics->Blink_
   - Click “Upload”
   - Look for errors in the bottom window of the program
     - Errors? Raise your hand for help
   - Look for the amber LED on your Arduino to be blinking
     - No blinking? Raise your hand for help

*******************************************************************************
### Is this thing on?
Copy the code below and paste it into a new Arduino sketch _OR_ download and open this example sketch: [HelloWorld.ino](/examples/HelloWorld/HelloWorld.ino)

```cpp
/*
  Hello World
  A "Hello, World!" program generally is a computer program that
	outputs or displays the message "Hello, World!".
	Such a program is very simple in most programming languages,
	and is often used to illustrate the basic syntax of a programming language.
	It is often the first program written by people learning to code
*/

void setup() {
//initialize serial communications at 9600 baud rate
Serial.begin(9600);
}

void loop(){
//send 'Hello, world!' over the serial port
Serial.println("Hello, world!");
//wait 100 milliseconds so we don't drive ourselves crazy
delay(1000);
}
```
The _Serial_ commands allow Arduino to send a message to your laptop. In order to see this message you need to open the _Serial Monitor_ by clicking on the magnifying glass near the top right corner.
- If you are using Arduino IDE 1.8._ the serial monitor will open in another window.
- If you are using Arduino IDE 2._._ the serial monitor will display at the bottom of the IDE window.

a little code anatomy:
- The [setup()](https://www.arduino.cc/reference/en/language/structure/sketch/setup/) function is called when a sketch starts.
  - Use it to initialize variables, pin modes, start using libraries, etc.
  - The setup() function will only run once, after each power-up or reset of the Arduino board.
- The [loop()](https://www.arduino.cc/reference/en/language/structure/sketch/loop/) the loop() function does precisely what its name suggests, and _loops_ consecutively through your list of instructions to control the Arduino.
  - The loop() functions runs continuously as long as the Arduino is powered on.
  - Each instruction is executed in order from top to bottom.
  - Arduino only executes one instruction at a time.

More on the specific functions and variables soon! Let's make something happen in the real world first.

*******************************************************************************
### How to use Arduino to turn something ON and OFF
