#ifndef _GFX_DRIVER_H
#define _GFX_DRIVER_H
#include <stdint.h>

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} rgb_t;

void gfx_init(void);
void gfx_clear(void);
void gfx_draw_pixel(int x, int y, rgb_t color);
void gfx_fill(int x0, int y0, int w, int h, rgb_t color);
void gfx_sync_frame(void);

#endif // _GFX_DRIVER_H
