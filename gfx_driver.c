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
    int depth;
    rgb_t buf[16][16][16];  // 3D buffer: [z][y][x]
}frame_buffer_t;

frame_buffer_t frame_buffer = {0};

void gfx_init(void) {
    frame_buffer.width = 16;
    frame_buffer.height = 16;
    frame_buffer.depth = 16;
    gfx_clear();
    mbi5252_init(16*3, 16, 16);
}

// 3D绘制函数
void gfx_draw_pixel_3d(int x, int y, int z, rgb_t color) {
    if (x >= 0 && x < frame_buffer.width &&
        y >= 0 && y < frame_buffer.height &&
        z >= 0 && z < frame_buffer.depth) {
        frame_buffer.buf[z][y][x] = color;
    }
}

// 2D绘制函数（向后兼容，默认使用中间层z=8）
void gfx_draw_pixel(int x, int y, rgb_t color) {
    gfx_draw_pixel_3d(x, y, frame_buffer.depth / 2, color);
}

// 3D填充函数
void gfx_fill_3d(int x0, int y0, int z0, int w, int h, int d, rgb_t color) {
    for (int z = z0; z < d + z0 && z < frame_buffer.depth; z++) {
        if (z < 0) continue;
        for (int y = y0; y < h + y0 && y < frame_buffer.height; y++) {
            if (y < 0) continue;
            for (int x = x0; x < w + x0 && x < frame_buffer.width; x++) {
                if (x >= 0) {
                    frame_buffer.buf[z][y][x] = color;
                }
            }
        }
    }
}

// 2D填充函数（向后兼容，默认填充所有z层）
void gfx_fill(int x0, int y0, int w, int h, rgb_t color) {
    gfx_fill_3d(x0, y0, 0, w, h, frame_buffer.depth, color);
}

void gfx_clear(void) {
    rgb_t rgb = {0, 0, 0};
    gfx_fill_3d(0, 0, 0, frame_buffer.width, frame_buffer.height, frame_buffer.depth, rgb);
}

void gfx_sync_frame(void) {
    uint16_t frame[16][16][48];
    memset(frame, 0, sizeof(frame));
    
    // 将3D frame_buffer投影到2D显示
    // 使用"最前面像素"策略：从后往前遍历z轴，后面的像素会被前面的覆盖
    for (int y = 0; y < frame_buffer.height; y++) {
        for (int z = 0; z < frame_buffer.depth; z++) {
            for (int x = 0; x < frame_buffer.width; x++) {
                // 将颜色写入显示帧缓冲区
                int ch = 0;
                int chip = 0;
                rgb_t color = frame_buffer.buf[z][y][x];
                chip = 2 - (x * 3 + 0) / 16 + z * 3;
                ch = 15 - (x * 3 + 0) % 16;
                frame[y][ch][chip] = color.blue << 6;
                chip = 2 - (x * 3 + 1) / 16 + z * 3;
                ch = 15 - (x * 3 + 1) % 16;
                frame[y][ch][chip] = color.green << 6;
                chip = 2 - (x * 3 + 2) / 16 + z * 3;
                ch = 15 - (x * 3 + 2) % 16;
                frame[y][ch][chip] = color.red << 6;
            }
        }
    }
    mbi5252_send_frame(frame, 256);
}
