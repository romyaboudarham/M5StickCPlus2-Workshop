#include "shake.h"

#define SHAKE_THRESHOLD 900.0f  // how hard to shake before we fire

uint32_t durationMs = 700;

// Triangle coordinates
static const int32_t triLeftX   = 20;
static const int32_t triRightX  = 220;
static const int32_t triBaseY   = 10;
static const int32_t triTipY    = 120;
int32_t triCenterX = (triLeftX + triRightX) / 2;
int32_t triCenterY = (triBaseY + triTipY) / 2;

bool detectShaking() {
  // only run when new IMU data arrives
  if (!StickCP2.Imu.update()) return false;
  auto d = StickCP2.Imu.getImuData();
  
  // 1) gyro check (your original) ------------------------------
  if ( fabs(d.gyro.x) > SHAKE_THRESHOLD ||
       fabs(d.gyro.y) > SHAKE_THRESHOLD ||
       fabs(d.gyro.z) > SHAKE_THRESHOLD ) {
    return true;
  }

  // 2) accel-delta check ----------------------------------------
  // on first run, seed the “previous” values without triggering
  static bool   firstRun = true;
  static float  pAx, pAy, pAz;
  float ax = d.accel.x, ay = d.accel.y, az = d.accel.z;

  if (firstRun) {
    pAx = ax; pAy = ay; pAz = az;
    firstRun = false;
    return false;
  }

  // sum of absolute changes across all axes
  float delta = fabs(ax - pAx)
              + fabs(ay - pAy)
              + fabs(az - pAz);

  // store for next frame
  pAx = ax; pAy = ay; pAz = az;

  // tune this to your liking (experiment to see what “vigorous” is)
  const float ACC_DELTA_THRESHOLD = 3.0f;  
  if (delta > ACC_DELTA_THRESHOLD) {
    return true;
  }

  // otherwise, no shake yet
  return false;
}

void drawRectangles(LovyanGFX* gfx) {
    int x      = rand() % gfx->width();
    int y      = rand() % gfx->height();
    int r      = (gfx->width() >> 4) + 2;
    uint16_t c = rand();
    gfx->fillRect(x - r, y - r, r * 2, r * 2, c);
}

/**
 * Runs a  random‐blue‐only animation for durationMs milliseconds,
 * then clears the screen when done.
 */
void shakingEffect(uint32_t durationMs) {
  uint32_t start = millis();

  // clear at start
  StickCP2.Display.fillScreen(TFT_BLACK);

  while (millis() - start < durationMs) {
    // pick a random “blue” color in 16-bit 5-6-5:
    //   red = 0…16, green = 0…32, blue = 128…255
    uint8_t r5 = 0;                                   // no red
    uint8_t g6 = random(0, 33);                       // small green
    uint8_t b5 = random(16, 32);                      // strong blue
    uint16_t blueShade = (r5 << 11) | (g6 << 5) | b5;

    // random circle
    int x = random(0, StickCP2.Display.width());
    int y = random(0, StickCP2.Display.height());
    int radius = (StickCP2.Display.width() >> 4) + 2;
    StickCP2.Display.fillCircle(x, y, radius, blueShade);

    // random rectangle
    drawRectangles(&StickCP2.Display);

    delay(50);  // tweak animation speed
  }

  // when done, clear screen
  StickCP2.Display.fillScreen(TFT_BLACK);
}

// helper to draw our “8-ball” triangle
void drawMagicTriangle(uint32_t outlineColor, uint32_t fillColor) {
  // shaking effect for 700 ms
  shakingEffect(durationMs);

  // big filled triangle (blue)
  StickCP2.Display.fillTriangle(
    triLeftX,  triBaseY,
    triRightX, triBaseY,
    triCenterX,   triTipY,
    fillColor
  );

  // white outline
  StickCP2.Display.drawTriangle(
    triLeftX,  triBaseY,
    triRightX, triBaseY,
    triCenterX,   triTipY,
    outlineColor
  );
}


void drawWrappedText(String text, int xCenter, int yStart, int maxWidth) {
  StickCP2.Display.setTextDatum(MC_DATUM);  // Middle center anchor

  int lineHeight = 16 * 2; // Adjust if needed for your text size
  int cursorY = yStart;

  // Split text into words
  std::vector<String> words;
  int start = 0;
  for (int i = 0; i <= text.length(); i++) {
    if (i == text.length() || text[i] == ' ') {
      words.push_back(text.substring(start, i));
      start = i + 1;
    }
  }

  String line = "";
  for (int i = 0; i < words.size(); i++) {
    String temp = line + (line.length() > 0 ? " " : "") + words[i];
    int width = StickCP2.Display.textWidth(temp);

    if (width > maxWidth && line.length() > 0) {
      // Draw current line and start new one
      StickCP2.Display.drawString(line, xCenter, cursorY);
      cursorY += lineHeight;
      line = words[i]; // Start with current word
    } else {
      line = temp;
    }
  }

  // Draw last line
  if (line.length() > 0) {
    StickCP2.Display.drawString(line, xCenter, cursorY);
  }
}