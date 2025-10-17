#include <SPI.h>
#include <TFT_eSPI.h>

#include "Pixel.h"
#include "image_data.h"

auto tft = TFT_eSPI();

void draw_picture();

void setup() {
    tft.init();
    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);
    draw_picture();
}

void loop() {
}

void draw_picture() {
#if defined IMAGE_ANIMATED
    while (true) {
        for (auto &frame_data: image_data) {
#else
    const auto &frame_data = image_data;
#endif
    for (int16_t i = 0; i < image_height; i++) {
        for (int16_t j = 0; j < image_width; j++) {
            Pixel(j, i, frame_data[i * image_width + j]).draw(tft);
        }
    }
#if defined IMAGE_ANIMATED
    delay(image_frame_delay);
}
    }
#endif
}
