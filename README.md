# ESP-IMAGE

Show image on ESP32S3 with ST7735S display

## Usage

1. Prepare environment with esp-idf(6.0+) and uv
2. Clone this repo
3. Configure in `idf.py menuconfig` and wire display
4. Define your screen size also in `main/main.cpp:(10-11)`
5. use `uv run scripts/generate.py apply path/to/image -s $size` to generate image data, size in `[0.96, 1.44, 1.8]` use
   `-r` to rotate
6. build and flash

## Menuconfig options

In Component config:

### LVGL configuration

- horizontal&vertical(160/80)
- Color depth(RGB565)
- Swap the 2 bytes of RGB565 color (try)

### LVGL TFT Display controller

- Select a display controller model. (ST7735S)
- Display Pin Assignments
    - My configure:
    - (36) GPIO for MOSI (Master Out Slave In)
    - \[ ] GPIO for MISO (Master In Slave Out)
    - (35) GPIO for CLK (SCK / Serial Clock)
    - \[*] Use CS signal to control the display
    - (39)    GPIO for CS (Slave Select)
    - \[*] Use DC signal to control the display
    - (38)    GPIO for DC (Data / Command)
    - (37) GPIO for Reset
    - \[ ] Enable control of the display backlight by using an GPIO.

## Wiring

As configured above, wire as:

| ESP32S3 Pin | ST7735S Pin |
|-------------|-------------|
| GND         | GND         |
| 3V3         | VCC         |
| 35          | SCL (CLK)   |
| 36          | SDA (MOSI)  |
| 37          | RST         |
| 38          | DC          |
| 39          | CS          |
| 3V3         | BLK         |

Tips: if you want to use backlight control, wire a GPIO pin to BLK and configure it in menuconfig.
