#include "freertos/FreeRTOS.h"
#include "lvgl.h"
#include "lvgl_helpers.h"

#include "Pixel.h"
#include "image_data.h"

#ifdef IMAGE_ANIMATED
#include "esp_timer.h"
#define LV_TICK_PERIOD_MS 1
#endif

#define height 160
#define width 80

void draw_picture();

#ifdef IMAGE_ANIMATED
static void lv_tick_task(void *arg) {
    (void) arg;

    lv_tick_inc(LV_TICK_PERIOD_MS);
}

#endif

extern "C" void app_main() {
    assert(image_height==height);
    assert(image_width==width);

    lv_init();
    lvgl_driver_init();

    const auto buf1 = static_cast<lv_color_t *>(heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA));
    assert(buf1 != nullptr);
    const auto buf2 = static_cast<lv_color_t *>(heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA));
    assert(buf2 != nullptr);
    static lv_disp_buf_t disp_buf;

    lv_disp_buf_init(&disp_buf, buf1, buf2, DISP_BUF_SIZE);

    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.flush_cb = disp_driver_flush;

    disp_drv.rotated = 1;

    disp_drv.buffer = &disp_buf;
    lv_disp_drv_register(&disp_drv);

#ifdef IMAGE_ANIMATED
    constexpr esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_task,
        .arg = nullptr,
        .dispatch_method = ESP_TIMER_TASK,
        .name = "periodic_gui",
        .skip_unhandled_events = false
    };
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));
#endif

    draw_picture();

    vTaskDelete(nullptr);
}


void draw_picture() {
    lv_obj_t *canvas = lv_canvas_create(lv_scr_act(), nullptr);
    static lv_color_t canvasBuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(80, 160)];
    lv_canvas_set_buffer(canvas, canvasBuf, 80, 160, LV_IMG_CF_TRUE_COLOR);
#if defined IMAGE_ANIMATED
    while (true) {
        for (auto &frame_data: image_data) {
#else
            const auto &frame_data = image_data;
#endif
            for (int16_t i = 0; i < image_height; i++) {
                for (int16_t j = 0; j < image_width; j++) {
                    Pixel(j, i, frame_data[i * image_width + j]).draw(canvas);
                }
            }
            lv_task_handler();
#if defined IMAGE_ANIMATED
            vTaskDelay(pdMS_TO_TICKS(image_frame_delay));
        }
    }
#endif
}
