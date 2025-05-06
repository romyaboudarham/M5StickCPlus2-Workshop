#include <Arduino.h>
#include <M5StickCPlus2.h>

#ifndef SHAKE_H
#define SHAKE_H

extern int32_t triCenterX;
extern int32_t triCenterY; 

bool detectShaking();
void drawRectangles(LovyanGFX* gfx);
void shakingEffect(uint32_t durationMs);
void drawMagicTriangle(uint32_t outlineColor, uint32_t fillColor);

#endif