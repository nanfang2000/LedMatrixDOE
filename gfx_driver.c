#include <stdio.h>
#include <string.h>
#include "gfx_driver.h"
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/pio.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h"
#include "pico/divider.h"
#include "mbi5252.h"

typedef struct {
    int width;
    int height;
    rgb_t buf[16][32];
}frame_buffer_t;

frame_buffer_t frame_buffer = {0};

void gfx_init(void) {
    frame_buffer.width = 32;
    frame_buffer.height = 16;
    gfx_clear();
    mbi5252_init(6, 16, 16);
}

void gfx_draw_pixel(int x, int y, rgb_t color) {
    frame_buffer.buf[y][x] = color;
}

void gfx_fill(int x0, int y0, int w, int h, rgb_t color) {
    for (int y = y0; y < h + y0; y++) {
        for (int x = x0; x < w + x0; x++) {
            frame_buffer.buf[y][x] = color;
        }
    }
}

void gfx_clear(void) {
    rgb_t rgb = {0, 0, 0};
    gfx_fill(0, 0, frame_buffer.width, frame_buffer.height, rgb);
}

void gfx_sync_frame(void) {
    uint16_t frame[16][16][48];
    memset(frame, 0, sizeof(frame));
    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 32; x++) {
            int ch = 0;
            int chip = 0;
            rgb_t color = frame_buffer.buf[y][x];
            chip = 5 - (x * 3 + 0) / 16;
            ch = 15 - (x * 3 + 0) % 16;
            frame[y][ch][chip] = color.red << 6;
            chip = 5 - (x * 3 + 1) / 16;
            ch = 15 - (x * 3 + 1) % 16;
            frame[y][ch][chip] = color.green << 6;
            chip = 5 - (x * 3 + 2) / 16;
            ch = 15 - (x * 3 + 2) % 16;
            frame[y][ch][chip] = color.blue << 6;
        }
    }
    mbi5252_send_frame(frame, 256);
}
