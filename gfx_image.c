/**
 * @file gfx_image.c
 * @brief Implementation of image display functions
 */

#include "gfx_image.h"
#include <string.h>
#include <math.h>

/**
 * @brief Check if a pixel is transparent (black)
 * 
 * @param color The color to check
 * @return 1 if transparent, 0 otherwise
 */
static int is_transparent(const rgb_t *color) {
    return (color->red == 0 && color->green == 0 && color->blue == 0);
}

void gfx_draw_image(int x, int y, const image_t *image) {
    if (image == NULL) {
        return;
    }
    
    for (int py = 0; py < IMAGE_HEIGHT; py++) {
        for (int px = 0; px < IMAGE_WIDTH; px++) {
            int screen_x = x + px;
            int screen_y = y + py;
            
            // 检查是否在屏幕范围内
            if (screen_x >= 0 && screen_x < 32 && screen_y >= 0 && screen_y < 16) {
                gfx_draw_pixel(screen_x, screen_y, image->pixels[py][px]);
            }
        }
    }
}

void gfx_draw_image_3d(int x, int y, int z, const image_t *image) {
    if (image == NULL) {
        return;
    }
    
    for (int py = 0; py < IMAGE_HEIGHT; py++) {
        for (int px = 0; px < IMAGE_WIDTH; px++) {
            int screen_x = x + px;
            int screen_y = y + py;
            
            // 检查是否在屏幕范围内
            if (screen_x >= 0 && screen_x < 32 && screen_y >= 0 && screen_y < 16) {
                gfx_draw_pixel_3d(screen_x, screen_y, z, image->pixels[py][px]);
            }
        }
    }
}

void gfx_draw_image_transparent(int x, int y, const image_t *image) {
    if (image == NULL) {
        return;
    }
    
    for (int py = 0; py < IMAGE_HEIGHT; py++) {
        for (int px = 0; px < IMAGE_WIDTH; px++) {
            const rgb_t *pixel = &image->pixels[py][px];
            
            // 跳过透明像素（黑色）
            if (is_transparent(pixel)) {
                continue;
            }
            
            int screen_x = x + px;
            int screen_y = y + py;
            
            // 检查是否在屏幕范围内
            if (screen_x >= 0 && screen_x < 32 && screen_y >= 0 && screen_y < 16) {
                gfx_draw_pixel(screen_x, screen_y, *pixel);
            }
        }
    }
}

void gfx_draw_image_transparent_3d(int x, int y, int z, const image_t *image) {
    if (image == NULL) {
        return;
    }
    
    for (int py = 0; py < IMAGE_HEIGHT; py++) {
        for (int px = 0; px < IMAGE_WIDTH; px++) {
            const rgb_t *pixel = &image->pixels[py][px];
            
            // 跳过透明像素（黑色）
            if (is_transparent(pixel)) {
                continue;
            }
            
            int screen_x = x + px;
            int screen_y = y + py;
            
            // 检查是否在屏幕范围内
            if (screen_x >= 0 && screen_x < 32 && screen_y >= 0 && screen_y < 16) {
                gfx_draw_pixel_3d(screen_x, screen_y, z, *pixel);
            }
        }
    }
}

/**
 * @brief Get sin value for angle in degrees (using lookup table)
 * 
 * @param angle Angle in degrees (0-360)
 * @return sin value scaled by 1000 (fixed point)
 */
static int sin_lookup(int angle) {
    // Normalize angle to 0-360
    angle = angle % 360;
    if (angle < 0) angle += 360;
    
    // Use math library for now (can be optimized with lookup table)
    double rad = angle * M_PI / 180.0;
    return (int)(sin(rad) * 1000.0);
}

/**
 * @brief Get cos value for angle in degrees (using lookup table)
 * 
 * @param angle Angle in degrees (0-360)
 * @return cos value scaled by 1000 (fixed point)
 */
static int cos_lookup(int angle) {
    // Normalize angle to 0-360
    angle = angle % 360;
    if (angle < 0) angle += 360;
    
    // Use math library for now (can be optimized with lookup table)
    double rad = angle * M_PI / 180.0;
    return (int)(cos(rad) * 1000.0);
}

/**
 * @brief Rotate a 3D point around X, Y, Z axes
 * 
 * @param x Input x coordinate (relative to center)
 * @param y Input y coordinate (relative to center)
 * @param z Input z coordinate (relative to center)
 * @param angle_x Rotation angle around X axis in degrees
 * @param angle_y Rotation angle around Y axis in degrees
 * @param angle_z Rotation angle around Z axis in degrees
 * @param out_x Output x coordinate
 * @param out_y Output y coordinate
 * @param out_z Output z coordinate
 */
static void rotate_point(int x, int y, int z,
                         int angle_x, int angle_y, int angle_z,
                         int *out_x, int *out_y, int *out_z) {
    // Get sin/cos values (scaled by 1000)
    int sx = sin_lookup(angle_x), cx = cos_lookup(angle_x);
    int sy = sin_lookup(angle_y), cy = cos_lookup(angle_y);
    int sz = sin_lookup(angle_z), cz = cos_lookup(angle_z);
    
    // Rotate around Z axis first
    int x1 = (x * cz - y * sz) / 1000;
    int y1 = (x * sz + y * cz) / 1000;
    int z1 = z;
    
    // Then rotate around Y axis
    int x2 = (x1 * cy + z1 * sy) / 1000;
    int y2 = y1;
    int z2 = (-x1 * sy + z1 * cy) / 1000;
    
    // Finally rotate around X axis
    *out_x = x2;
    *out_y = (y2 * cx - z2 * sx) / 1000;
    *out_z = (y2 * sx + z2 * cx) / 1000;
}

void gfx_draw_voxel_array(int x, int y, int z, const voxel_array_t *voxel_array) {
    if (voxel_array == NULL) {
        return;
    }
    
    int size = voxel_array->size;
    if (size > VOXEL_SIZE) {
        size = VOXEL_SIZE;
    }
    
    for (int vz = 0; vz < size; vz++) {
        for (int vy = 0; vy < size; vy++) {
            for (int vx = 0; vx < size; vx++) {
                // 只绘制填充的体素（值不为0）
                if (voxel_array->voxels[vz][vy][vx] != 0) {
                    int screen_x = x + vx;
                    int screen_y = y + vy;
                    int screen_z = z + vz;
                    
                    // 检查是否在屏幕范围内
                    if (screen_x >= 0 && screen_x < 32 && 
                        screen_y >= 0 && screen_y < 16 &&
                        screen_z >= 0 && screen_z < 16) {
                        gfx_draw_pixel_3d(screen_x, screen_y, screen_z, voxel_array->color);
                    }
                }
            }
        }
    }
}

void gfx_draw_voxel_array_rotated(int x, int y, int z, 
                                   int angle_x, int angle_y, int angle_z,
                                   const voxel_array_t *voxel_array) {
    if (voxel_array == NULL) {
        return;
    }
    
    int size = voxel_array->size;
    if (size > VOXEL_SIZE) {
        size = VOXEL_SIZE;
    }
    
    // Calculate center of voxel array (for rotation)
    int center_offset = size / 2;
    
    // If no rotation, use the simpler function
    if (angle_x == 0 && angle_y == 0 && angle_z == 0) {
        gfx_draw_voxel_array(x - center_offset, y - center_offset, z - center_offset, voxel_array);
        return;
    }
    
    // Draw each voxel with rotation
    for (int vz = 0; vz < size; vz++) {
        for (int vy = 0; vy < size; vy++) {
            for (int vx = 0; vx < size; vx++) {
                // 只绘制填充的体素（值不为0）
                if (voxel_array->voxels[vz][vy][vx] != 0) {
                    // Convert to coordinates relative to center
                    int rel_x = vx - center_offset;
                    int rel_y = vy - center_offset;
                    int rel_z = vz - center_offset;
                    
                    // Apply rotation
                    int rot_x, rot_y, rot_z;
                    rotate_point(rel_x, rel_y, rel_z, angle_x, angle_y, angle_z, 
                                &rot_x, &rot_y, &rot_z);
                    
                    // Convert back to screen coordinates
                    int screen_x = x + rot_x;
                    int screen_y = y + rot_y;
                    int screen_z = z + rot_z;
                    
                    // 检查是否在屏幕范围内
                    if (screen_x >= 0 && screen_x < 32 && 
                        screen_y >= 0 && screen_y < 16 &&
                        screen_z >= 0 && screen_z < 16) {
                        gfx_draw_pixel_3d(screen_x, screen_y, screen_z, voxel_array->color);
                    }
                }
            }
        }
    }
}

