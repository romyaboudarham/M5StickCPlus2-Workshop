#include <M5StickCPlus2.h>
#include "esp_sleep.h"

#define PWR_BUTTON_PIN 35
#define BACKLIGHT_PIN   27    // TFT backlight on M5StickC Plus 2
#define DOUBLE_TAP_INTERVAL 500

extern int  pressCount     = 0;
extern int lastPressTime = 0;

bool detectShaking();
void drawRectangles(LovyanGFX* gfx);
void shakingEffect(uint32_t durationMs);
void drawMagicTriangle(uint32_t outlineColor, uint32_t fillColor);

#endif