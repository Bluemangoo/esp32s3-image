# ESP-IMAGE

Show image on ESP32S3 with ST7735S display

## Usage

1. Prepare environment with platform-io and uv
2. Clone this repo
3. Configure in `platformio.ini` and wire display
4. use `uv run scripts/generate.py apply path/to/image -s $size` to generate image data, size in `[0.96, 1.44, 1.8]` use
   `-r` to rotate
5. build and flash

## Wiring

As configured above, wire as:

| ESP32S3 Pin | ST7735S Pin |
|-------------|-------------|
| GND         | GND         |
| 3V3         | VCC         |
| 14          | SCL (CLK)   |
| 13          | SDA (MOSI)  |
| RST         | RST         |
| 17          | DC          |
| 7           | CS          |
| 3V3         | BLK         |
