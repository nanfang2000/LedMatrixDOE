/**
 * @file gfx_image.h
 * @brief Header file for the image display implementation
 */

#ifndef GFX_IMAGE_H
#define GFX_IMAGE_H

#include "gfx_driver.h"

// 图片尺寸
#define IMAGE_WIDTH 16
#define IMAGE_HEIGHT 16

/**
 * @struct image_t
 * @brief Structure representing a 16x16 image
 * 
 * This structure stores a 16x16 pixel image as an array of RGB colors.
 * The image data is stored in row-major order (y, then x).
 */
typedef struct {
    rgb_t pixels[IMAGE_HEIGHT][IMAGE_WIDTH];  /**< Pixel data in [y][x] order */
} image_t;

// 3D点阵尺寸
#define VOXEL_SIZE 16

/**
 * @struct voxel_array_t
 * @brief Structure representing a 16x16x16 3D voxel array
 * 
 * This structure stores a 16x16x16 voxel array.
 * The voxel data is stored in [z][y][x] order.
 * 0 means empty, 1 means filled.
 */
typedef struct {
    int size;                                    /**< Size of the voxel array (should be 16) */
    rgb_t color;                                 /**< Color for filled voxels */
    uint8_t voxels[VOXEL_SIZE][VOXEL_SIZE][VOXEL_SIZE];  /**< Voxel data in [z][y][x] order */
} voxel_array_t;

/**
 * @brief Draw an image at the specified position (2D)
 * 
 * Draws a 16x16 image at the specified (x, y) position on the screen.
 * The image is drawn at the default z layer (middle layer).
 * 
 * @param x The x-coordinate of the top-left corner of the image
 * @param y The y-coordinate of the top-left corner of the image
 * @param image Pointer to the image structure to draw
 */
void gfx_draw_image(int x, int y, const image_t *image);

/**
 * @brief Draw an image at the specified 3D position
 * 
 * Draws a 16x16 image at the specified (x, y, z) position in 3D space.
 * 
 * @param x The x-coordinate of the top-left corner of the image
 * @param y The y-coordinate of the top-left corner of the image
 * @param z The z-coordinate (depth) of the image
 * @param image Pointer to the image structure to draw
 */
void gfx_draw_image_3d(int x, int y, int z, const image_t *image);

/**
 * @brief Draw an image with transparency support (2D)
 * 
 * Draws a 16x16 image at the specified position, skipping transparent pixels.
 * A pixel is considered transparent if its RGB values are all zero (black).
 * 
 * @param x The x-coordinate of the top-left corner of the image
 * @param y The y-coordinate of the top-left corner of the image
 * @param image Pointer to the image structure to draw
 */
void gfx_draw_image_transparent(int x, int y, const image_t *image);

/**
 * @brief Draw an image with transparency support (3D)
 * 
 * Draws a 16x16 image at the specified 3D position, skipping transparent pixels.
 * A pixel is considered transparent if its RGB values are all zero (black).
 * 
 * @param x The x-coordinate of the top-left corner of the image
 * @param y The y-coordinate of the top-left corner of the image
 * @param z The z-coordinate (depth) of the image
 * @param image Pointer to the image structure to draw
 */
void gfx_draw_image_transparent_3d(int x, int y, int z, const image_t *image);

/**
 * @brief Draw a 3D voxel array at the specified position
 * 
 * Draws a 16x16x16 voxel array starting at the specified (x, y, z) position.
 * Only filled voxels (value != 0) are drawn using the color specified in the voxel array.
 * 
 * @param x The x-coordinate of the starting position
 * @param y The y-coordinate of the starting position
 * @param z The z-coordinate (depth) of the starting position
 * @param voxel_array Pointer to the voxel array structure to draw
 */
void gfx_draw_voxel_array(int x, int y, int z, const voxel_array_t *voxel_array);

/**
 * @brief Draw a 3D voxel array with rotation
 * 
 * Draws a 16x16x16 voxel array with rotation around X, Y, and Z axes.
 * Rotation angles are specified in degrees (0-360).
 * 
 * @param x The x-coordinate of the center position
 * @param y The y-coordinate of the center position
 * @param z The z-coordinate (depth) of the center position
 * @param angle_x Rotation angle around X axis in degrees (0-360)
 * @param angle_y Rotation angle around Y axis in degrees (0-360)
 * @param angle_z Rotation angle around Z axis in degrees (0-360)
 * @param voxel_array Pointer to the voxel array structure to draw
 */
void gfx_draw_voxel_array_rotated(int x, int y, int z, 
                                   int angle_x, int angle_y, int angle_z,
                                   const voxel_array_t *voxel_array);

#endif /* GFX_IMAGE_H */

