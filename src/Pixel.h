#ifndef ESP_IMAGE_PIXEL_H
#define ESP_IMAGE_PIXEL_H
#include <TFT_eSPI.h>

class Pixel {
public:
    int16_t x;
    int16_t y;
    uint16_t color;

    Pixel(int16_t x, int16_t y, uint16_t color);

    void draw(TFT_eSPI &tft) const;
};


#endif //ESP_IMAGE_PIXEL_H
