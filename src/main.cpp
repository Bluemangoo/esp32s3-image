#include <SPI.h>
#include <TFT_eSPI.h>

#include "Pixel.h"
#include "image_data.h"

auto tft = TFT_eSPI();

void setup() {
    tft.init();
    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);
    for (int16_t i = 0; i < image_height; i++) {
        for (int16_t j = 0; j < image_width; j++) {
            Pixel(j, i, image_data[i * image_width + j]).draw(tft);
        }
    }
}

void loop() {
}
