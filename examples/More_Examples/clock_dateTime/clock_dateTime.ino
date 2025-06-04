#include <M5StickCPlus2.h>

LGFX_Sprite* sprite;

int screenWidth;
int screenHeight;

void setup() {
  Serial.begin(115200);

  auto cfg = M5.config();
  StickCP2.begin(cfg);

  StickCP2.Display.setRotation(1);  // 1 = landscape
  screenWidth = StickCP2.Display.width();   // 240
  screenHeight = StickCP2.Display.height(); // 135

  sprite = new LGFX_Sprite(&StickCP2.Display);
  sprite->setColorDepth(16);
  sprite->createSprite(screenWidth, screenHeight);
}

void loop() {
  sprite->fillScreen(BLACK);
  drawDateTime();
  sprite->pushSprite(0, 0);
}

void manuallySetDateTime(bool setDateTime) {
  if (setDateTime) {
                               // YYYY  MM  DD    hh  mm  ss
    StickCP2.Rtc.setDateTime( { { 2025, 6, 4 }, { 12, 11, 0 } } );
  }
}

void drawDateTime() {
  // to manually set time:
  // 1. flip to true
  // 2. manually change time in "manuallySetDateTime" function ^^
  // 3. Upload
  // 4. flip false & Upload
  manuallySetDateTime(false);
   
  auto now = StickCP2.Rtc.getDateTime();

  // Format time: HH:MM:SS
  char timeStr[9];
  snprintf(timeStr, sizeof(timeStr), "%02d:%02d:%02d",
           now.time.hours, now.time.minutes, now.time.seconds);

  // Format date: Month DD
  const char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                          "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  char dateStr[10];
  snprintf(dateStr, sizeof(dateStr), "%s %02d",
           months[now.date.month - 1], now.date.date);

  // CUSTOMIZE BORDER - BEGIN
  sprite->drawRect(3, 3, screenWidth-8, screenHeight-7, SKYBLUE);
  // CUSTOMIZE BORDER - END

  // CUSTOMIZE DATE - BEGIN
  sprite->setTextFont(&fonts::Roboto_Thin_24);  // Small font
  sprite->setTextColor(WHITE);
  sprite->setTextDatum(middle_center);
  sprite->drawString(dateStr, screenWidth / 2, 35);
  // CUSTOMIZE DATE - END

  // CUSTOMIZE TIME - BEGIN
  sprite->setTextFont(&fonts::lgfxJapanGothic_40);  // Large font
  sprite->setTextColor(ORANGE);
  sprite->drawString(timeStr, screenWidth / 2, screenHeight / 2 + 5); // Centered
  // CUSTOMIZE TIME - END

  delay(1000);
}
