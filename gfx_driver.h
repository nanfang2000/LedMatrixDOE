/**
 * @file gfx_driver.h
 * @brief Header file for the graphics driver module, defining graphics operation interfaces and data types.
 * 
 * This header file provides basic functions of the graphics driver, including initialization, screen clearing, 
 * pixel drawing, area filling, and frame synchronization operations.
 */

#ifndef _GFX_DRIVER_H
#define _GFX_DRIVER_H
#include <stdint.h>

/**
 * @struct rgb_t
 * @brief Structure representing an RGB color.
 * 
 * This structure uses 8-bit unsigned integers to represent the red, green, and blue color channels respectively.
 */
typedef struct {
    uint8_t red;   /**< Value of the red channel, ranging from 0 to 255. */
    uint8_t green; /**< Value of the green channel, ranging from 0 to 255. */
    uint8_t blue;  /**< Value of the blue channel, ranging from 0 to 255. */
} rgb_t;

/**
 * @brief Initialize the graphics driver.
 * 
 * This function is used to perform necessary initialization operations for the graphics driver, 
 * such as hardware initialization.
 */
void gfx_init(void);

/**
 * @brief Clear the screen.
 * 
 * This function clears all pixels on the screen, usually setting the screen to the default background color.
 */
void gfx_clear(void);

/**
 * @brief Draw a pixel at the specified position.
 * 
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color of the pixel, represented by the rgb_t structure.
 */
void gfx_draw_pixel(int x, int y, rgb_t color);

/**
 * @brief Fill a specified area with a color.
 * 
 * @param x0 The x-coordinate of the top-left corner of the filling area.
 * @param y0 The y-coordinate of the top-left corner of the filling area.
 * @param w The width of the filling area.
 * @param h The height of the filling area.
 * @param color The filling color, represented by the rgb_t structure.
 */
void gfx_fill(int x0, int y0, int w, int h, rgb_t color);

/**
 * @brief Synchronize the frame buffer.
 * 
 * This function updates the contents of the frame buffer to the actual display device.
 */
void gfx_sync_frame(void);

#endif // _GFX_DRIVER_H
