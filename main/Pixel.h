#ifndef ESP_IMAGE_PIXEL_H
#define ESP_IMAGE_PIXEL_H
#include "lvgl.h"

class Pixel {
public:
    int16_t x;
    int16_t y;
    uint16_t color;

    Pixel(int16_t x, int16_t y, uint16_t color);

    void draw(lv_obj_t * canvas) const;
};


#endif //ESP_IMAGE_PIXEL_H
