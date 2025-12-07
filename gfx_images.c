/**
 * @file gfx_images.c
 * @brief Predefined 16x16 low-resolution images
 */

#include "gfx_images.h"

// 颜色定义 - 使用宏简化代码
#define C_BLACK    ((rgb_t){0, 0, 0})           // 黑色 (头发、阴影)
#define C_WHITE    ((rgb_t){255, 255, 255})     // 白色 (高光)
#define C_SKIN     ((rgb_t){240, 220, 200})     // 肤色 (浅)
#define C_SKIN2    ((rgb_t){200, 180, 160})     // 肤色 (稍深)
#define C_SKIN3    ((rgb_t){180, 160, 140})     // 肤色 (阴影)
#define C_HAIR     ((rgb_t){60, 40, 30})        // 头发 (深棕色)
#define C_HAIR2    ((rgb_t){80, 60, 50})        // 头发 (稍浅)
#define C_BG       ((rgb_t){200, 180, 160})     // 背景 (浅棕色)
#define C_GLASS    ((rgb_t){150, 150, 150})     // 灰色 (眼镜框)

/**
 * @brief 人像头像 (16x16) - 基于模糊人像照片
 * 
 * 这是一个16x16像素化的头像，包含：
 * - 浅色皮肤的脸部
 * - 深色头发区域
 * - 眼镜框架
 * - 浅棕色背景
 */
const image_t image_portrait = {
    .pixels = {
        // 行 0-1: 顶部背景和头发
        {C_BG, C_BG, C_BG, C_BG, C_BG, C_BG, C_BG, C_BG, C_BG, C_BG, C_BG, C_BG, C_BG, C_BG, C_BG, C_BG},
        {C_BG, C_BG, C_BG, C_HAIR, C_HAIR, C_HAIR, C_HAIR, C_HAIR, C_HAIR, C_HAIR, C_HAIR, C_HAIR, C_HAIR, C_BG, C_BG, C_BG},
        
        // 行 2-3: 头发和额头
        {C_BG, C_BG, C_HAIR, C_HAIR, C_HAIR2, C_HAIR2, C_HAIR2, C_HAIR2, C_HAIR2, C_HAIR2, C_HAIR2, C_HAIR, C_HAIR, C_BG, C_BG, C_BG},
        {C_BG, C_HAIR, C_HAIR2, C_HAIR2, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_HAIR2, C_HAIR2, C_HAIR, C_BG, C_BG},
        
        // 行 4-5: 眼镜和眼睛区域
        {C_BG, C_HAIR, C_HAIR2, C_SKIN, C_SKIN, C_GLASS, C_GLASS, C_GLASS, C_GLASS, C_GLASS, C_GLASS, C_SKIN, C_SKIN, C_HAIR2, C_HAIR, C_BG},
        {C_BG, C_HAIR2, C_SKIN, C_SKIN, C_GLASS, C_WHITE, C_WHITE, C_WHITE, C_WHITE, C_WHITE, C_WHITE, C_GLASS, C_SKIN, C_SKIN, C_HAIR2, C_BG},
        
        // 行 6-7: 眼睛和鼻子区域
        {C_BG, C_SKIN, C_SKIN, C_GLASS, C_WHITE, C_BLACK, C_BLACK, C_WHITE, C_WHITE, C_BLACK, C_BLACK, C_WHITE, C_GLASS, C_SKIN, C_SKIN, C_BG},
        {C_BG, C_SKIN, C_SKIN, C_GLASS, C_WHITE, C_BLACK, C_BLACK, C_WHITE, C_WHITE, C_BLACK, C_BLACK, C_WHITE, C_GLASS, C_SKIN, C_SKIN, C_BG},
        
        // 行 8-9: 鼻子和脸颊
        {C_BG, C_SKIN, C_SKIN, C_SKIN, C_GLASS, C_WHITE, C_WHITE, C_WHITE, C_WHITE, C_WHITE, C_WHITE, C_GLASS, C_SKIN, C_SKIN, C_SKIN, C_BG},
        {C_BG, C_SKIN2, C_SKIN, C_SKIN, C_SKIN, C_GLASS, C_GLASS, C_GLASS, C_GLASS, C_GLASS, C_GLASS, C_SKIN, C_SKIN, C_SKIN, C_SKIN2, C_BG},
        
        // 行 10-11: 嘴巴和下巴
        {C_BG, C_SKIN2, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN2, C_BG},
        {C_BG, C_SKIN2, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN3, C_SKIN3, C_SKIN3, C_SKIN3, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN2, C_BG},
        
        // 行 12-13: 下巴和颈部
        {C_BG, C_SKIN2, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN2, C_BG},
        {C_BG, C_BG, C_SKIN2, C_SKIN2, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_SKIN2, C_SKIN2, C_BG, C_BG, C_BG},
        
        // 行 14-15: 颈部和背景
        {C_BG, C_BG, C_BG, C_SKIN2, C_SKIN2, C_SKIN2, C_SKIN2, C_SKIN2, C_SKIN2, C_SKIN2, C_SKIN2, C_SKIN2, C_BG, C_BG, C_BG, C_BG},
        {C_BG, C_BG, C_BG, C_BG, C_BG, C_BG, C_BG, C_BG, C_BG, C_BG, C_BG, C_BG, C_BG, C_BG, C_BG, C_BG}
    }
};

/**
 * @brief 笑脸图标 (16x16)
 */
const image_t image_smile = {
    .pixels = {
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
    }
};

/**
 * @brief 心形图标 (16x16)
 */
const image_t image_heart = {
    .pixels = {
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK}
    }
};

/**
 * @brief 星星图标 (16x16)
 */
const image_t image_star = {
    .pixels = {
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK}
    }
};

/**
 * @brief 箭头图标 (16x16)
 */
const image_t image_arrow = {
    .pixels = {
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK}
    }
};

/**
 * @brief 房子图标 (16x16)
 */
const image_t image_house = {
    .pixels = {
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK},
        {C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK, C_BLACK}
    }
};

/**
 * @brief image_hemuyang_head (16x16) - 从 hemuyang_head.tiff 转换
 */
const image_t image_hemuyang_head = {
    .pixels = {
        {((rgb_t){154, 147, 138}), ((rgb_t){150, 142, 133}), ((rgb_t){143, 136, 127}), ((rgb_t){148, 140, 131}), ((rgb_t){144, 135, 127}), ((rgb_t){99, 92, 87}), ((rgb_t){11, 2, 8}), ((rgb_t){17, 0, 6}), ((rgb_t){15, 0, 3}), ((rgb_t){0, 0, 0}), ((rgb_t){33, 20, 18}), ((rgb_t){55, 38, 31}), ((rgb_t){51, 35, 29}), ((rgb_t){49, 33, 28}), ((rgb_t){49, 33, 26}), ((rgb_t){49, 32, 24})},
        {((rgb_t){155, 148, 139}), ((rgb_t){150, 143, 134}), ((rgb_t){153, 145, 135}), ((rgb_t){145, 136, 127}), ((rgb_t){84, 75, 71}), ((rgb_t){96, 71, 61}), ((rgb_t){151, 116, 100}), ((rgb_t){160, 122, 104}), ((rgb_t){154, 115, 97}), ((rgb_t){128, 94, 77}), ((rgb_t){67, 42, 33}), ((rgb_t){34, 16, 15}), ((rgb_t){54, 37, 29}), ((rgb_t){48, 33, 24}), ((rgb_t){49, 32, 23}), ((rgb_t){46, 31, 22})},
        {((rgb_t){156, 149, 141}), ((rgb_t){153, 145, 137}), ((rgb_t){156, 148, 138}), ((rgb_t){98, 90, 84}), ((rgb_t){124, 94, 81}), ((rgb_t){189, 150, 130}), ((rgb_t){216, 171, 151}), ((rgb_t){217, 171, 151}), ((rgb_t){210, 163, 142}), ((rgb_t){193, 148, 126}), ((rgb_t){152, 112, 93}), ((rgb_t){85, 54, 41}), ((rgb_t){40, 25, 20}), ((rgb_t){53, 37, 30}), ((rgb_t){48, 32, 25}), ((rgb_t){46, 32, 24})},
        {((rgb_t){156, 150, 142}), ((rgb_t){158, 151, 141}), ((rgb_t){129, 122, 115}), ((rgb_t){82, 65, 60}), ((rgb_t){181, 144, 125}), ((rgb_t){213, 170, 150}), ((rgb_t){228, 185, 167}), ((rgb_t){231, 187, 171}), ((rgb_t){221, 176, 159}), ((rgb_t){202, 157, 139}), ((rgb_t){174, 132, 112}), ((rgb_t){129, 91, 73}), ((rgb_t){44, 18, 14}), ((rgb_t){53, 39, 32}), ((rgb_t){57, 41, 32}), ((rgb_t){51, 36, 28})},
        {((rgb_t){158, 153, 145}), ((rgb_t){156, 149, 140}), ((rgb_t){87, 82, 79}), ((rgb_t){101, 79, 70}), ((rgb_t){192, 154, 133}), ((rgb_t){204, 164, 145}), ((rgb_t){222, 183, 167}), ((rgb_t){234, 193, 178}), ((rgb_t){227, 184, 168}), ((rgb_t){207, 164, 148}), ((rgb_t){172, 132, 116}), ((rgb_t){144, 105, 87}), ((rgb_t){70, 41, 30}), ((rgb_t){42, 31, 28}), ((rgb_t){68, 51, 43}), ((rgb_t){56, 42, 34})},
        {((rgb_t){162, 158, 150}), ((rgb_t){147, 139, 130}), ((rgb_t){46, 46, 49}), ((rgb_t){137, 112, 101}), ((rgb_t){190, 155, 138}), ((rgb_t){191, 159, 148}), ((rgb_t){195, 160, 149}), ((rgb_t){214, 174, 160}), ((rgb_t){221, 179, 164}), ((rgb_t){193, 156, 142}), ((rgb_t){166, 133, 122}), ((rgb_t){143, 107, 95}), ((rgb_t){87, 54, 41}), ((rgb_t){30, 23, 21}), ((rgb_t){71, 55, 47}), ((rgb_t){62, 48, 41})},
        {((rgb_t){165, 160, 152}), ((rgb_t){141, 136, 129}), ((rgb_t){83, 77, 80}), ((rgb_t){175, 150, 139}), ((rgb_t){195, 167, 150}), ((rgb_t){177, 148, 138}), ((rgb_t){177, 143, 131}), ((rgb_t){207, 170, 154}), ((rgb_t){197, 159, 143}), ((rgb_t){179, 144, 131}), ((rgb_t){165, 135, 125}), ((rgb_t){139, 108, 97}), ((rgb_t){107, 77, 67}), ((rgb_t){76, 59, 53}), ((rgb_t){72, 58, 50}), ((rgb_t){68, 54, 48})},
        {((rgb_t){166, 162, 153}), ((rgb_t){151, 144, 137}), ((rgb_t){125, 106, 101}), ((rgb_t){187, 154, 138}), ((rgb_t){213, 174, 160}), ((rgb_t){198, 163, 151}), ((rgb_t){210, 174, 163}), ((rgb_t){213, 174, 159}), ((rgb_t){195, 153, 137}), ((rgb_t){189, 152, 140}), ((rgb_t){180, 146, 137}), ((rgb_t){170, 133, 123}), ((rgb_t){137, 104, 94}), ((rgb_t){78, 60, 51}), ((rgb_t){78, 64, 56}), ((rgb_t){72, 58, 51})},
        {((rgb_t){165, 164, 156}), ((rgb_t){169, 145, 135}), ((rgb_t){171, 132, 119}), ((rgb_t){207, 170, 154}), ((rgb_t){235, 190, 178}), ((rgb_t){249, 204, 192}), ((rgb_t){236, 192, 180}), ((rgb_t){218, 173, 159}), ((rgb_t){213, 165, 150}), ((rgb_t){197, 158, 144}), ((rgb_t){226, 182, 169}), ((rgb_t){210, 164, 151}), ((rgb_t){153, 116, 104}), ((rgb_t){100, 62, 54}), ((rgb_t){88, 69, 62}), ((rgb_t){72, 61, 54})},
        {((rgb_t){165, 165, 158}), ((rgb_t){180, 158, 149}), ((rgb_t){201, 154, 142}), ((rgb_t){213, 175, 160}), ((rgb_t){239, 193, 181}), ((rgb_t){242, 195, 186}), ((rgb_t){230, 179, 167}), ((rgb_t){220, 173, 159}), ((rgb_t){199, 159, 146}), ((rgb_t){193, 149, 136}), ((rgb_t){228, 181, 170}), ((rgb_t){206, 159, 148}), ((rgb_t){148, 109, 99}), ((rgb_t){120, 80, 73}), ((rgb_t){92, 74, 66}), ((rgb_t){73, 64, 57})},
        {((rgb_t){168, 167, 161}), ((rgb_t){175, 162, 154}), ((rgb_t){210, 167, 153}), ((rgb_t){213, 174, 159}), ((rgb_t){242, 198, 185}), ((rgb_t){250, 204, 192}), ((rgb_t){237, 189, 174}), ((rgb_t){222, 176, 162}), ((rgb_t){210, 162, 150}), ((rgb_t){200, 154, 140}), ((rgb_t){225, 176, 164}), ((rgb_t){209, 162, 151}), ((rgb_t){148, 109, 100}), ((rgb_t){105, 80, 71}), ((rgb_t){89, 80, 73}), ((rgb_t){78, 67, 61})},
        {((rgb_t){173, 170, 165}), ((rgb_t){168, 164, 157}), ((rgb_t){181, 160, 152}), ((rgb_t){202, 166, 155}), ((rgb_t){233, 188, 175}), ((rgb_t){243, 198, 182}), ((rgb_t){215, 173, 160}), ((rgb_t){209, 159, 151}), ((rgb_t){203, 144, 138}), ((rgb_t){178, 134, 124}), ((rgb_t){203, 161, 147}), ((rgb_t){188, 145, 132}), ((rgb_t){139, 109, 105}), ((rgb_t){110, 97, 93}), ((rgb_t){89, 80, 74}), ((rgb_t){79, 69, 65})},
        {((rgb_t){175, 172, 167}), ((rgb_t){171, 166, 159}), ((rgb_t){166, 164, 158}), ((rgb_t){183, 161, 152}), ((rgb_t){218, 176, 163}), ((rgb_t){230, 188, 172}), ((rgb_t){238, 196, 180}), ((rgb_t){239, 196, 182}), ((rgb_t){223, 176, 162}), ((rgb_t){202, 159, 143}), ((rgb_t){197, 156, 142}), ((rgb_t){161, 121, 112}), ((rgb_t){137, 121, 122}), ((rgb_t){122, 118, 116}), ((rgb_t){86, 78, 70}), ((rgb_t){83, 74, 69})},
        {((rgb_t){178, 175, 170}), ((rgb_t){172, 168, 162}), ((rgb_t){173, 167, 161}), ((rgb_t){170, 160, 154}), ((rgb_t){178, 150, 141}), ((rgb_t){197, 162, 149}), ((rgb_t){223, 182, 167}), ((rgb_t){236, 192, 179}), ((rgb_t){223, 176, 165}), ((rgb_t){189, 148, 135}), ((rgb_t){158, 123, 114}), ((rgb_t){139, 117, 114}), ((rgb_t){158, 155, 160}), ((rgb_t){117, 115, 116}), ((rgb_t){87, 80, 74}), ((rgb_t){67, 61, 63})},
        {((rgb_t){178, 176, 172}), ((rgb_t){173, 170, 165}), ((rgb_t){173, 168, 164}), ((rgb_t){172, 166, 160}), ((rgb_t){166, 145, 135}), ((rgb_t){157, 130, 120}), ((rgb_t){172, 143, 134}), ((rgb_t){179, 144, 136}), ((rgb_t){168, 135, 127}), ((rgb_t){143, 114, 109}), ((rgb_t){111, 86, 83}), ((rgb_t){137, 132, 134}), ((rgb_t){143, 142, 148}), ((rgb_t){96, 92, 95}), ((rgb_t){84, 78, 78}), ((rgb_t){35, 32, 42})},
        {((rgb_t){180, 177, 173}), ((rgb_t){175, 171, 167}), ((rgb_t){175, 171, 166}), ((rgb_t){173, 167, 162}), ((rgb_t){186, 160, 148}), ((rgb_t){184, 153, 138}), ((rgb_t){163, 135, 124}), ((rgb_t){147, 120, 110}), ((rgb_t){130, 105, 99}), ((rgb_t){115, 89, 85}), ((rgb_t){104, 75, 71}), ((rgb_t){91, 79, 79}), ((rgb_t){91, 86, 86}), ((rgb_t){97, 91, 88}), ((rgb_t){82, 77, 77}), ((rgb_t){16, 16, 33})},
    }
};

/**
 * @brief chrome (16x16) - 从 icons8-chrome-48.png 转换
 */
const image_t image_chrome = {
    .pixels = {
        {((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 255}), ((rgb_t){254, 253, 253}), ((rgb_t){255, 254, 254}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 254, 254}), ((rgb_t){255, 253, 253}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 255})},
        {((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 255}), ((rgb_t){254, 252, 252}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 255}), ((rgb_t){241, 214, 203}), ((rgb_t){233, 156, 138}), ((rgb_t){242, 132, 121}), ((rgb_t){248, 133, 118}), ((rgb_t){242, 157, 126}), ((rgb_t){247, 214, 194}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 253, 252}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 255})},
        {((rgb_t){255, 255, 255}), ((rgb_t){254, 253, 252}), ((rgb_t){255, 255, 255}), ((rgb_t){244, 242, 237}), ((rgb_t){232, 127, 107}), ((rgb_t){252, 75, 57}), ((rgb_t){255, 72, 57}), ((rgb_t){255, 76, 62}), ((rgb_t){255, 77, 62}), ((rgb_t){255, 73, 57}), ((rgb_t){255, 79, 55}), ((rgb_t){240, 131, 95}), ((rgb_t){250, 243, 230}), ((rgb_t){255, 255, 255}), ((rgb_t){254, 253, 252}), ((rgb_t){255, 255, 255})},
        {((rgb_t){254, 253, 253}), ((rgb_t){255, 255, 255}), ((rgb_t){250, 237, 236}), ((rgb_t){232, 98, 77}), ((rgb_t){255, 70, 57}), ((rgb_t){246, 71, 60}), ((rgb_t){244, 78, 68}), ((rgb_t){242, 53, 45}), ((rgb_t){242, 48, 46}), ((rgb_t){243, 70, 67}), ((rgb_t){245, 67, 61}), ((rgb_t){255, 65, 57}), ((rgb_t){241, 98, 69}), ((rgb_t){250, 240, 231}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 253, 253})},
        {((rgb_t){255, 253, 253}), ((rgb_t){255, 255, 255}), ((rgb_t){204, 153, 112}), ((rgb_t){255, 68, 57}), ((rgb_t){246, 77, 64}), ((rgb_t){243, 63, 50}), ((rgb_t){244, 0, 0}), ((rgb_t){252, 100, 75}), ((rgb_t){252, 107, 73}), ((rgb_t){245, 59, 0}), ((rgb_t){244, 72, 51}), ((rgb_t){244, 81, 63}), ((rgb_t){255, 77, 57}), ((rgb_t){240, 138, 95}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 254, 254})},
        {((rgb_t){255, 255, 255}), ((rgb_t){208, 237, 214}), ((rgb_t){88, 174, 77}), ((rgb_t){212, 84, 47}), ((rgb_t){246, 59, 51}), ((rgb_t){247, 73, 51}), ((rgb_t){248, 193, 191}), ((rgb_t){216, 216, 238}), ((rgb_t){216, 220, 237}), ((rgb_t){250, 216, 188}), ((rgb_t){252, 172, 20}), ((rgb_t){251, 174, 25}), ((rgb_t){253, 183, 31}), ((rgb_t){255, 194, 19}), ((rgb_t){246, 236, 190}), ((rgb_t){255, 255, 255})},
        {((rgb_t){255, 255, 255}), ((rgb_t){159, 208, 155}), ((rgb_t){56, 193, 89}), ((rgb_t){145, 144, 71}), ((rgb_t){227, 0, 0}), ((rgb_t){246, 194, 191}), ((rgb_t){145, 206, 255}), ((rgb_t){0, 144, 245}), ((rgb_t){0, 143, 245}), ((rgb_t){143, 200, 255}), ((rgb_t){253, 230, 184}), ((rgb_t){255, 192, 0}), ((rgb_t){255, 197, 38}), ((rgb_t){255, 209, 3}), ((rgb_t){240, 215, 110}), ((rgb_t){255, 255, 255})},
        {((rgb_t){255, 255, 255}), ((rgb_t){136, 202, 138}), ((rgb_t){85, 188, 89}), ((rgb_t){52, 172, 76}), ((rgb_t){205, 117, 60}), ((rgb_t){216, 213, 236}), ((rgb_t){0, 145, 245}), ((rgb_t){54, 148, 240}), ((rgb_t){55, 150, 240}), ((rgb_t){0, 139, 245}), ((rgb_t){216, 224, 236}), ((rgb_t){255, 202, 48}), ((rgb_t){253, 190, 4}), ((rgb_t){255, 206, 25}), ((rgb_t){250, 213, 91}), ((rgb_t){255, 255, 255})},
        {((rgb_t){255, 255, 255}), ((rgb_t){135, 202, 138}), ((rgb_t){88, 187, 88}), ((rgb_t){39, 176, 79}), ((rgb_t){142, 169, 84}), ((rgb_t){215, 212, 235}), ((rgb_t){0, 145, 245}), ((rgb_t){41, 150, 240}), ((rgb_t){46, 150, 240}), ((rgb_t){0, 140, 245}), ((rgb_t){219, 225, 235}), ((rgb_t){255, 203, 47}), ((rgb_t){253, 191, 4}), ((rgb_t){255, 207, 24}), ((rgb_t){250, 213, 91}), ((rgb_t){255, 255, 255})},
        {((rgb_t){255, 255, 255}), ((rgb_t){154, 210, 156}), ((rgb_t){81, 187, 85}), ((rgb_t){85, 178, 90}), ((rgb_t){40, 168, 39}), ((rgb_t){194, 219, 193}), ((rgb_t){165, 200, 255}), ((rgb_t){0, 141, 245}), ((rgb_t){0, 142, 245}), ((rgb_t){152, 200, 255}), ((rgb_t){240, 225, 186}), ((rgb_t){255, 189, 0}), ((rgb_t){255, 195, 41}), ((rgb_t){255, 206, 7}), ((rgb_t){241, 216, 111}), ((rgb_t){255, 255, 255})},
        {((rgb_t){255, 255, 255}), ((rgb_t){211, 235, 212}), ((rgb_t){79, 182, 83}), ((rgb_t){81, 176, 84}), ((rgb_t){71, 174, 78}), ((rgb_t){82, 178, 79}), ((rgb_t){191, 222, 195}), ((rgb_t){201, 223, 239}), ((rgb_t){201, 222, 238}), ((rgb_t){194, 212, 189}), ((rgb_t){239, 189, 0}), ((rgb_t){255, 194, 0}), ((rgb_t){255, 194, 20}), ((rgb_t){255, 203, 9}), ((rgb_t){245, 236, 190}), ((rgb_t){255, 255, 255})},
        {((rgb_t){254, 254, 254}), ((rgb_t){255, 255, 255}), ((rgb_t){127, 197, 130}), ((rgb_t){82, 189, 86}), ((rgb_t){85, 179, 88}), ((rgb_t){71, 174, 78}), ((rgb_t){36, 168, 41}), ((rgb_t){118, 189, 96}), ((rgb_t){92, 168, 84}), ((rgb_t){175, 157, 0}), ((rgb_t){255, 196, 0}), ((rgb_t){253, 195, 25}), ((rgb_t){255, 208, 4}), ((rgb_t){242, 206, 74}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 254})},
        {((rgb_t){253, 254, 253}), ((rgb_t){255, 255, 255}), ((rgb_t){240, 248, 240}), ((rgb_t){98, 185, 102}), ((rgb_t){82, 189, 86}), ((rgb_t){80, 177, 84}), ((rgb_t){89, 178, 89}), ((rgb_t){39, 172, 77}), ((rgb_t){89, 152, 50}), ((rgb_t){248, 192, 38}), ((rgb_t){255, 196, 20}), ((rgb_t){255, 207, 4}), ((rgb_t){244, 198, 37}), ((rgb_t){247, 248, 231}), ((rgb_t){255, 255, 255}), ((rgb_t){254, 254, 252})},
        {((rgb_t){255, 255, 255}), ((rgb_t){253, 254, 253}), ((rgb_t){255, 255, 255}), ((rgb_t){240, 248, 240}), ((rgb_t){128, 198, 131}), ((rgb_t){79, 182, 83}), ((rgb_t){87, 188, 86}), ((rgb_t){54, 182, 87}), ((rgb_t){219, 190, 44}), ((rgb_t){255, 209, 0}), ((rgb_t){255, 202, 12}), ((rgb_t){243, 207, 74}), ((rgb_t){247, 248, 231}), ((rgb_t){255, 255, 255}), ((rgb_t){254, 254, 251}), ((rgb_t){255, 255, 255})},
        {((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 255}), ((rgb_t){253, 254, 253}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 255}), ((rgb_t){214, 236, 213}), ((rgb_t){146, 210, 158}), ((rgb_t){159, 201, 133}), ((rgb_t){247, 212, 88}), ((rgb_t){242, 216, 111}), ((rgb_t){245, 237, 191}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 255}), ((rgb_t){254, 254, 251}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 255})},
        {((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 255}), ((rgb_t){253, 254, 253}), ((rgb_t){254, 254, 254}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 254}), ((rgb_t){254, 254, 252}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 255}), ((rgb_t){255, 255, 255})},
    }
};

/**
 * @brief image_hemuyang_head2 (16x16) - 从 hemuyang_head2.png 转换
 */
const image_t image_hemuyang_head2 = {
    .pixels = {
        {((rgb_t){160, 159, 154}), ((rgb_t){148, 145, 138}), ((rgb_t){140, 133, 123}), ((rgb_t){148, 136, 124}), ((rgb_t){161, 144, 128}), ((rgb_t){96, 73, 55}), ((rgb_t){22, 0, 0}), ((rgb_t){37, 6, 0}), ((rgb_t){40, 8, 0}), ((rgb_t){24, 0, 0}), ((rgb_t){35, 6, 0}), ((rgb_t){54, 28, 15}), ((rgb_t){56, 36, 27}), ((rgb_t){54, 37, 30}), ((rgb_t){44, 30, 27}), ((rgb_t){46, 35, 33})},
        {((rgb_t){140, 140, 132}), ((rgb_t){143, 140, 131}), ((rgb_t){173, 164, 155}), ((rgb_t){133, 119, 106}), ((rgb_t){77, 58, 43}), ((rgb_t){78, 52, 35}), ((rgb_t){130, 99, 79}), ((rgb_t){158, 126, 105}), ((rgb_t){141, 106, 86}), ((rgb_t){122, 89, 70}), ((rgb_t){79, 47, 32}), ((rgb_t){50, 24, 11}), ((rgb_t){46, 24, 13}), ((rgb_t){56, 39, 32}), ((rgb_t){40, 27, 21}), ((rgb_t){39, 28, 24})},
        {((rgb_t){168, 165, 158}), ((rgb_t){155, 148, 140}), ((rgb_t){142, 132, 122}), ((rgb_t){93, 77, 64}), ((rgb_t){103, 82, 65}), ((rgb_t){168, 141, 122}), ((rgb_t){236, 204, 183}), ((rgb_t){210, 174, 152}), ((rgb_t){210, 174, 152}), ((rgb_t){205, 170, 150}), ((rgb_t){133, 100, 83}), ((rgb_t){71, 43, 29}), ((rgb_t){36, 12, 2}), ((rgb_t){55, 36, 29}), ((rgb_t){46, 31, 26}), ((rgb_t){45, 31, 28})},
        {((rgb_t){155, 148, 140}), ((rgb_t){166, 157, 148}), ((rgb_t){98, 85, 76}), ((rgb_t){61, 42, 28}), ((rgb_t){169, 143, 128}), ((rgb_t){223, 192, 174}), ((rgb_t){245, 208, 189}), ((rgb_t){230, 189, 169}), ((rgb_t){223, 182, 162}), ((rgb_t){227, 189, 170}), ((rgb_t){181, 145, 129}), ((rgb_t){126, 94, 81}), ((rgb_t){41, 14, 3}), ((rgb_t){45, 25, 18}), ((rgb_t){59, 42, 35}), ((rgb_t){54, 39, 34})},
        {((rgb_t){160, 151, 144}), ((rgb_t){171, 158, 150}), ((rgb_t){69, 52, 42}), ((rgb_t){71, 49, 36}), ((rgb_t){207, 178, 162}), ((rgb_t){221, 186, 167}), ((rgb_t){229, 188, 168}), ((rgb_t){255, 213, 192}), ((rgb_t){235, 190, 169}), ((rgb_t){214, 171, 152}), ((rgb_t){195, 156, 139}), ((rgb_t){164, 131, 116}), ((rgb_t){51, 23, 12}), ((rgb_t){33, 10, 2}), ((rgb_t){72, 53, 47}), ((rgb_t){57, 39, 35})},
        {((rgb_t){191, 178, 170}), ((rgb_t){158, 144, 135}), ((rgb_t){60, 40, 29}), ((rgb_t){125, 99, 86}), ((rgb_t){214, 181, 166}), ((rgb_t){197, 159, 140}), ((rgb_t){213, 168, 149}), ((rgb_t){237, 189, 169}), ((rgb_t){242, 194, 174}), ((rgb_t){187, 140, 122}), ((rgb_t){167, 124, 107}), ((rgb_t){155, 117, 104}), ((rgb_t){66, 36, 25}), ((rgb_t){30, 6, 0}), ((rgb_t){83, 63, 56}), ((rgb_t){61, 44, 37})},
        {((rgb_t){168, 153, 146}), ((rgb_t){151, 134, 126}), ((rgb_t){84, 62, 51}), ((rgb_t){182, 152, 141}), ((rgb_t){199, 162, 146}), ((rgb_t){153, 110, 93}), ((rgb_t){184, 136, 116}), ((rgb_t){224, 172, 151}), ((rgb_t){225, 173, 152}), ((rgb_t){171, 123, 103}), ((rgb_t){144, 98, 82}), ((rgb_t){133, 94, 79}), ((rgb_t){97, 65, 54}), ((rgb_t){37, 13, 3}), ((rgb_t){84, 64, 57}), ((rgb_t){71, 54, 47})},
        {((rgb_t){175, 160, 153}), ((rgb_t){173, 154, 147}), ((rgb_t){90, 66, 56}), ((rgb_t){202, 170, 159}), ((rgb_t){223, 184, 169}), ((rgb_t){181, 135, 119}), ((rgb_t){199, 148, 129}), ((rgb_t){243, 188, 168}), ((rgb_t){207, 152, 132}), ((rgb_t){180, 129, 110}), ((rgb_t){152, 105, 89}), ((rgb_t){131, 92, 77}), ((rgb_t){130, 98, 87}), ((rgb_t){45, 21, 11}), ((rgb_t){76, 57, 50}), ((rgb_t){75, 58, 51})},
        {((rgb_t){169, 154, 147}), ((rgb_t){159, 140, 133}), ((rgb_t){168, 144, 134}), ((rgb_t){208, 176, 165}), ((rgb_t){250, 210, 198}), ((rgb_t){255, 218, 202}), ((rgb_t){253, 200, 184}), ((rgb_t){237, 180, 163}), ((rgb_t){214, 158, 141}), ((rgb_t){190, 137, 121}), ((rgb_t){218, 171, 155}), ((rgb_t){208, 168, 156}), ((rgb_t){139, 109, 98}), ((rgb_t){65, 43, 32}), ((rgb_t){75, 58, 50}), ((rgb_t){82, 67, 60})},
        {((rgb_t){185, 170, 165}), ((rgb_t){185, 168, 161}), ((rgb_t){188, 165, 157}), ((rgb_t){204, 171, 162}), ((rgb_t){230, 190, 178}), ((rgb_t){251, 203, 189}), ((rgb_t){249, 196, 180}), ((rgb_t){236, 179, 162}), ((rgb_t){201, 145, 128}), ((rgb_t){199, 146, 130}), ((rgb_t){248, 202, 187}), ((rgb_t){209, 171, 158}), ((rgb_t){122, 94, 83}), ((rgb_t){78, 58, 49}), ((rgb_t){90, 75, 68}), ((rgb_t){67, 56, 50})},
        {((rgb_t){171, 160, 156}), ((rgb_t){186, 171, 166}), ((rgb_t){198, 178, 171}), ((rgb_t){213, 183, 175}), ((rgb_t){239, 201, 190}), ((rgb_t){255, 215, 202}), ((rgb_t){253, 201, 187}), ((rgb_t){229, 173, 158}), ((rgb_t){224, 168, 153}), ((rgb_t){206, 154, 140}), ((rgb_t){251, 207, 194}), ((rgb_t){194, 158, 146}), ((rgb_t){105, 78, 69}), ((rgb_t){76, 59, 51}), ((rgb_t){90, 79, 73}), ((rgb_t){77, 70, 64})},
        {((rgb_t){173, 163, 161}), ((rgb_t){179, 165, 162}), ((rgb_t){186, 167, 161}), ((rgb_t){202, 175, 168}), ((rgb_t){229, 192, 183}), ((rgb_t){245, 201, 190}), ((rgb_t){230, 181, 167}), ((rgb_t){204, 151, 137}), ((rgb_t){188, 135, 121}), ((rgb_t){177, 129, 115}), ((rgb_t){212, 170, 158}), ((rgb_t){160, 128, 117}), ((rgb_t){119, 96, 88}), ((rgb_t){103, 90, 82}), ((rgb_t){88, 83, 77}), ((rgb_t){73, 72, 67})},
        {((rgb_t){185, 180, 177}), ((rgb_t){175, 165, 163}), ((rgb_t){170, 155, 150}), ((rgb_t){183, 158, 153}), ((rgb_t){206, 172, 163}), ((rgb_t){227, 184, 175}), ((rgb_t){240, 192, 180}), ((rgb_t){247, 195, 182}), ((rgb_t){216, 167, 153}), ((rgb_t){204, 158, 145}), ((rgb_t){184, 146, 135}), ((rgb_t){128, 100, 89}), ((rgb_t){141, 122, 115}), ((rgb_t){133, 124, 117}), ((rgb_t){94, 93, 88}), ((rgb_t){75, 77, 72})},
        {((rgb_t){179, 178, 176}), ((rgb_t){174, 169, 166}), ((rgb_t){174, 160, 157}), ((rgb_t){181, 157, 153}), ((rgb_t){186, 156, 148}), ((rgb_t){201, 161, 153}), ((rgb_t){228, 181, 171}), ((rgb_t){254, 204, 193}), ((rgb_t){244, 196, 184}), ((rgb_t){191, 147, 136}), ((rgb_t){142, 105, 96}), ((rgb_t){137, 113, 103}), ((rgb_t){173, 158, 151}), ((rgb_t){120, 115, 109}), ((rgb_t){74, 76, 71}), ((rgb_t){68, 74, 70})},
        {((rgb_t){177, 177, 175}), ((rgb_t){181, 177, 174}), ((rgb_t){182, 171, 169}), ((rgb_t){179, 160, 154}), ((rgb_t){174, 145, 139}), ((rgb_t){172, 133, 126}), ((rgb_t){171, 127, 118}), ((rgb_t){171, 123, 113}), ((rgb_t){153, 106, 96}), ((rgb_t){106, 63, 54}), ((rgb_t){87, 54, 45}), ((rgb_t){140, 117, 109}), ((rgb_t){168, 158, 149}), ((rgb_t){97, 96, 91}), ((rgb_t){66, 73, 66}), ((rgb_t){24, 35, 29})},
        {((rgb_t){179, 179, 179}), ((rgb_t){184, 180, 179}), ((rgb_t){182, 172, 170}), ((rgb_t){182, 163, 159}), ((rgb_t){196, 167, 161}), ((rgb_t){205, 168, 160}), ((rgb_t){188, 144, 135}), ((rgb_t){158, 111, 101}), ((rgb_t){136, 89, 79}), ((rgb_t){121, 81, 71}), ((rgb_t){94, 61, 52}), ((rgb_t){91, 71, 62}), ((rgb_t){89, 78, 72}), ((rgb_t){85, 86, 80}), ((rgb_t){105, 114, 109}), ((rgb_t){0, 12, 8})},
    }
};

/**
 * @brief voxel_head - 16x16x16 3D voxel array
 * Generated from STL file
 */
const voxel_array_t voxel_head = {
    .size = 16,
    .color = { 255, 255, 255 },
    .voxels = {
        // z = 0
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        },
        // z = 1
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        },
        // z = 2
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        },
        // z = 3
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        },
        // z = 4
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        },
        // z = 5
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
            {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
            {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        },
        // z = 6
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
            {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
            {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0},
            {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0},
            {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        },
        // z = 7
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
            {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0},
            {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0},
            {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0},
            {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
            {0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        },
        // z = 8
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
            {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0},
            {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0},
            {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
            {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
            {0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0},
            {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        },
        // z = 9
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
            {0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0},
            {0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
            {0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
            {0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
            {0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0},
            {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        },
        // z = 10
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0},
            {0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0},
            {0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0},
            {0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0},
            {0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        },
        // z = 11
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0},
            {0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0},
            {0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0},
            {0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0},
            {0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        },
        // z = 12
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0},
            {0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0},
            {0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
            {0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        },
        // z = 13
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
            {0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0},
            {0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0},
            {0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        },
        // z = 14
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        },
        // z = 15
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        },
    }
};
