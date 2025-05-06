#include <M5StickCPlus2.h>
#include "esp_sleep.h"

#define PWR_BUTTON_PIN 35
#define BACKLIGHT_PIN   27    // TFT backlight on M5StickC Plus 2
#define DOUBLE_TAP_INTERVAL 500
#define SHAKE_THRESHOLD 500.0f  // how hard to shake before we fire

volatile int  pressCount     = 0;
volatile uint64_t lastPressTime = 0;

// track last known state
//bool wasShaking = false;

void IRAM_ATTR powerButtonISR() {
  uint64_t now = esp_timer_get_time() / 1000;
  if (now - lastPressTime < DOUBLE_TAP_INTERVAL) {
    pressCount++;
  } else {
    pressCount = 1;
  }
  lastPressTime = now;
}

// void setup() {
//   M5.begin();
//   Serial.begin(115200);
//   delay(100);

//   // init StickCP2
//   auto cfg = M5.config();
//   StickCP2.begin(cfg);

//   // make sure backlight is ON to start
//   pinMode((gpio_num_t)BACKLIGHT_PIN, OUTPUT);
//   digitalWrite(BACKLIGHT_PIN, HIGH);

//   // prepare power-button interrupt
//   pinMode((gpio_num_t)PWR_BUTTON_PIN, INPUT_PULLUP);
//   attachInterrupt(
//     digitalPinToInterrupt(PWR_BUTTON_PIN),
//     powerButtonISR,
//     FALLING
//   );

//   showShakeState(false);  // draw “Not Shaking!” once at start
  
//   /*** CUSTOMIZE BEGIN ***/
//   StickCP2.Display.setRotation(1);
//   // color options: https://github.com/lovyan03/LovyanGFX/blob/55a0f66d9278faa596c8d51a8e8a3e537dd8f44f/src/lgfx/v1/misc/enum.hpp#L56
//   StickCP2.Display.setTextColor(GREEN);
//   // text placement options: https://github.com/lovyan03/LovyanGFX/blob/55a0f66d9278faa596c8d51a8e8a3e537dd8f44f/src/lgfx/v1/misc/enum.hpp#L135
//   StickCP2.Display.setTextDatum(baseline_center);
//   // font options: https://github.com/lovyan03/LovyanGFX/blob/55a0f66d9278faa596c8d51a8e8a3e537dd8f44f/src/lgfx/v1/lgfx_fonts.cpp#L1154
//   StickCP2.Display.setTextFont(&fonts::Orbitron_Light_24);
//   StickCP2.Display.setTextSize(1);
//   StickCP2.Display.drawString("Shake me!", StickCP2.Display.width() / 2, StickCP2.Display.height() / 2);
//   /*** CUSTOMIZE END ***/
// }

// void loop() {
//   StickCP2.update();
//   detectPWRDoubleTap();
//   detectABtnTap();

//   bool isShaking = detectShaking();

//   // only update when state changes
//   if (isShaking != wasShaking) {
//     wasShaking = isShaking;
//     showShakeState(isShaking);
//   }

//   delay(50);  // slow the loop a bit to reduce noise
// }

// void detectABtnTap() {
//   if (StickCP2.BtnA.wasPressed()) {
//         StickCP2.Speaker.tone(8000, 20);
//         Serial.println("A Btn Pressed");
//   }
//   if (StickCP2.BtnA.wasReleased()) {
//       StickCP2.Speaker.tone(8000, 20);
//       Serial.println("A Btn Released");
//   }
// }

// void detectPWRDoubleTap() {
//   if (pressCount >= 2) {
//     pressCount = 0;
//     Serial.println("Double-tap → light sleep in 50 ms…");
//     delay(50);

//     // 1) wait for button release
//     while (digitalRead(PWR_BUTTON_PIN) == LOW) {
//       delay(10);
//     }

//     // 2) turn the backlight OFF (panel retains its last image)
//     digitalWrite(BACKLIGHT_PIN, LOW);

//     // 3) arm wake on next press, then light-sleep
//     esp_sleep_enable_ext0_wakeup((gpio_num_t)PWR_BUTTON_PIN, 0);
//     esp_light_sleep_start();

//     // === resumes here on wake ===

//     // 4) turn the backlight back ON
//     digitalWrite(BACKLIGHT_PIN, HIGH);
//     Serial.println("Woke up—backlight restored!");
//     delay(100);
//   }
//   delay(10);
// }

// void showShakeState(bool shaking) {
//   StickCP2.Display.clear();
//   if (shaking) {
//     Serial.println("Shaking!");
//     StickCP2.Display.setTextColor(RED);
//     StickCP2.Display.drawString(
//       "Shaking!",
//       StickCP2.Display.width()  / 2,
//       StickCP2.Display.height() / 2
//     );
//   } else {
//     Serial.println("Not Shaking");
//     StickCP2.Display.setTextColor(GREEN);
//     StickCP2.Display.drawString(
//       "Not Shaking!",
//       StickCP2.Display.width()  / 2,
//       StickCP2.Display.height() / 2
//     );
//   }
// }

// bool detectShaking() {
//   // only run when new IMU data arrives
//   if (!StickCP2.Imu.update()) return false;
//   auto d = StickCP2.Imu.getImuData();
  
//   // 1) gyro check (your original) ------------------------------
//   if ( fabs(d.gyro.x) > SHAKE_THRESHOLD ||
//        fabs(d.gyro.y) > SHAKE_THRESHOLD ||
//        fabs(d.gyro.z) > SHAKE_THRESHOLD ) {
//     return true;
//   }

//   // 2) accel-delta check ----------------------------------------
//   // on first run, seed the “previous” values without triggering
//   static bool   firstRun = true;
//   static float  pAx, pAy, pAz;
//   float ax = d.accel.x, ay = d.accel.y, az = d.accel.z;

//   if (firstRun) {
//     pAx = ax; pAy = ay; pAz = az;
//     firstRun = false;
//     return false;
//   }

//   // sum of absolute changes across all axes
//   float delta = fabs(ax - pAx)
//               + fabs(ay - pAy)
//               + fabs(az - pAz);

//   // store for next frame
//   pAx = ax; pAy = ay; pAz = az;

//   // tune this to your liking (experiment to see what “vigorous” is)
//   const float ACC_DELTA_THRESHOLD = 3.0f;  
//   if (delta > ACC_DELTA_THRESHOLD) {
//     return true;
//   }

//   // otherwise, no shake yet
//   return false;
// }
