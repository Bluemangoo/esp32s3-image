#include "Pixel.h"

Pixel::Pixel(const int16_t x, const int16_t y, const uint16_t color) : x(x), y(y), color(color) {
}

void Pixel::draw(lv_obj_t *canvas) const {
    lv_canvas_set_px(canvas, x, y, lv_color_make((color >> 11) << 3, ((color >> 5) & 0x3F) << 2, (color & 0x1F) << 3));
}
