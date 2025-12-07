/**
 * @file gfx_images.h
 * @brief Predefined 16x16 low-resolution images
 */

#ifndef GFX_IMAGES_H
#define GFX_IMAGES_H

#include "gfx_image.h"

// 颜色定义
#define RGB_BLACK   {0, 0, 0}
#define RGB_WHITE   {255, 255, 255}
#define RGB_RED     {255, 0, 0}
#define RGB_GREEN   {0, 255, 0}
#define RGB_BLUE    {0, 0, 255}
#define RGB_YELLOW  {255, 255, 0}
#define RGB_CYAN    {0, 255, 255}
#define RGB_MAGENTA {255, 0, 255}
#define RGB_ORANGE  {255, 165, 0}

/**
 * @brief 笑脸图标 (16x16)
 */
extern const image_t image_smile;

/**
 * @brief 心形图标 (16x16)
 */
extern const image_t image_heart;

/**
 * @brief 星星图标 (16x16)
 */
extern const image_t image_star;

/**
 * @brief 箭头图标 (16x16)
 */
extern const image_t image_arrow;

/**
 * @brief 房子图标 (16x16)
 */
extern const image_t image_house;

/**
 * @brief 人像头像 (16x16)
 */
extern const image_t image_portrait;

/**
 * @brief 赫墨阳头像 (16x16)
 */
extern const image_t image_hemuyang_head;

/**
 * @brief chrome图标 (16x16)
 */
extern const image_t image_chrome;

/**
 * @brief 赫墨阳头像2 (16x16)
 */
extern const image_t image_hemuyang_head2;

extern const voxel_array_t voxel_head;
  
#endif /* GFX_IMAGES_H */

