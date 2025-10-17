#include "Pixel.h"

Pixel::Pixel(const int16_t x, const int16_t y, const uint16_t color) : x(x), y(y), color(color) {
}

void Pixel::draw(TFT_eSPI &tft) const {
    tft.drawPixel(x, y, color);
}
