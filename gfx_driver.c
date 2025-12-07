#include <stdio.h>
#include <string.h>
#include <math.h>
#include "gfx_driver.h"
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/pio.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h"
#include "pico/divider.h"
#include "mbi5252.h"

// Gamma校正查找表 (gamma = 2.2)
// 用于将线性RGB值转换为符合人眼感知的亮度值
static const uint8_t gamma_table[256] = {
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,
    1,   1,   1,   1,   1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   2,
    2,   3,   3,   3,   3,   3,   3,   3,   4,   4,   4,   4,   4,   5,   5,   5,
    5,   6,   6,   6,   6,   7,   7,   7,   7,   8,   8,   8,   9,   9,   9,   10,
    10,  10,  11,  11,  11,  12,  12,  12,  13,  13,  13,  14,  14,  15,  15,  15,
    16,  16,  17,  17,  17,  18,  18,  19,  19,  20,  20,  21,  21,  22,  22,  23,
    23,  24,  24,  25,  25,  26,  26,  27,  27,  28,  28,  29,  29,  30,  31,  31,
    32,  32,  33,  34,  34,  35,  35,  36,  37,  37,  38,  39,  39,  40,  41,  41,
    42,  43,  43,  44,  45,  45,  46,  47,  48,  48,  49,  50,  51,  51,  52,  53,
    54,  54,  55,  56,  57,  58,  58,  59,  60,  61,  62,  63,  63,  64,  65,  66,
    67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,  80,  81,  82,
    83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,  96,  98,  99,
    100, 101, 102, 103, 105, 106, 107, 108, 109, 111, 112, 113, 114, 116, 117, 118,
    120, 121, 122, 124, 125, 126, 128, 129, 130, 132, 133, 135, 136, 137, 139, 140,
    142, 143, 145, 146, 148, 149, 151, 152, 154, 155, 157, 158, 160, 161, 163, 165,
    166, 168, 170, 171, 173, 175, 176, 178, 180, 181, 183, 185, 187, 188, 190, 192,
    194, 196, 197, 199, 201, 203, 205, 207, 209, 211, 213, 215, 217, 219, 221, 223,
    225, 227, 229, 231, 233, 235, 237, 239, 241, 243, 245, 248, 250, 252, 254, 255
};

/**
 * @brief 应用gamma校正
 * 
 * @param value 输入值 (0-255)
 * @return uint8_t 校正后的值 (0-255)
 */
static inline uint8_t apply_gamma(uint8_t value) {
    return gamma_table[value];
}

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
                
                // 应用gamma校正
                uint8_t r_corrected = apply_gamma(color.red);
                uint8_t g_corrected = apply_gamma(color.green);
                uint8_t b_corrected = apply_gamma(color.blue);
                
                chip = 2 - (x * 3 + 0) / 16 + z * 3;
                ch = 15 - (x * 3 + 0) % 16;
                frame[15 - y][ch][chip] = b_corrected << 6;
                chip = 2 - (x * 3 + 1) / 16 + z * 3;
                ch = 15 - (x * 3 + 1) % 16;
                frame[15 - y][ch][chip] = g_corrected << 6;
                chip = 2 - (x * 3 + 2) / 16 + z * 3;
                ch = 15 - (x * 3 + 2) % 16;
                frame[15 - y][ch][chip] = r_corrected << 6;
            }
        }
    }
    mbi5252_send_frame(frame, 256);
}
