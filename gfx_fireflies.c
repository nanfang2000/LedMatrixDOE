#include "gfx_driver.h"
#include <stdlib.h>
#include <math.h>
#include "hardware/timer.h"

// 萤火虫数量
#define NUM_FIREFLIES 32
// 信息素挥发率
#define PHEROMONE_EVAPORATION 0.9
// 信息素强度
#define PHEROMONE_INTENSITY 100
// 信息素地图
float pheromone_map[16][32];

// 萤火虫位置结构体
typedef struct {
    int x;
    int y;
    int vx;
    int vy;
    rgb_t color;
} firefly_t;

// 初始化信息素地图
static void firefly_init_pheromone_map() {
    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 32; x++) {
            pheromone_map[y][x] = 0.0;
        }
    }
}

// 初始化萤火虫群
static void firefly_init_fireflies(firefly_t *fireflies) {
    for (int i = 0; i < NUM_FIREFLIES; i++) {
        fireflies[i].x = rand() % 32;
        fireflies[i].y = rand() % 16;
        fireflies[i].vx = (rand() % 3) - 1; // -1, 0, 1
        fireflies[i].vy = (rand() % 3) - 1;
        // 随机颜色
        fireflies[i].color.red = rand() % 256;
        fireflies[i].color.green = rand() % 256;
        fireflies[i].color.blue = rand() % 256;
    }
}

// 更新信息素地图
static void firefly_update_pheromone_map(firefly_t *fireflies) {
    // 信息素挥发
    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 32; x++) {
            pheromone_map[y][x] *= PHEROMONE_EVAPORATION;
        }
    }
    
    // 释放信息素
    for (int i = 0; i < NUM_FIREFLIES; i++) {
        pheromone_map[fireflies[i].y][fireflies[i].x] += PHEROMONE_INTENSITY;
    }
}

// 选择下一个移动方向（基于蚁群算法）
static void firefly_select_next_direction(firefly_t *firefly) {
    int possible_directions[8][2] = {
        {-1, -1}, {0, -1}, {1, -1},
        {-1,  0},          {1,  0},
        {-1,  1}, {0,  1}, {1,  1}
    };
    
    float total_pheromone = 0.0;
    float probabilities[8];
    
    // 计算每个方向的信息素总和
    for (int i = 0; i < 8; i++) {
        int new_x = firefly->x + possible_directions[i][0];
        int new_y = firefly->y + possible_directions[i][1];
        
        if (new_x >= 0 && new_x < 32 && new_y >= 0 && new_y < 16) {
            probabilities[i] = pheromone_map[new_y][new_x] + 0.1f; // 添加基础概率
            total_pheromone += probabilities[i];
        } else {
            probabilities[i] = 0.0;
        }
    }
    
    // 如果没有有效方向，随机选择一个
    if (total_pheromone <= 0.0) {
        int random_dir = rand() % 8;
        firefly->vx = possible_directions[random_dir][0];
        firefly->vy = possible_directions[random_dir][1];
        return;
    }
    
    // 归一化概率
    for (int i = 0; i < 8; i++) {
        probabilities[i] /= total_pheromone;
    }
    
    // 轮盘赌选择
    float random_value = (float)rand() / RAND_MAX;
    float cumulative_probability = 0.0;
    for (int i = 0; i < 8; i++) {
        cumulative_probability += probabilities[i];
        if (random_value <= cumulative_probability) {
            firefly->vx = possible_directions[i][0];
            firefly->vy = possible_directions[i][1];
            break;
        }
    }
}

// 更新萤火虫位置
static void firefly_update_fireflies(firefly_t *fireflies) {
    for (int i = 0; i < NUM_FIREFLIES; i++) {
        // 如果当前速度为0，强制选择一个方向
        if (fireflies[i].vx == 0 && fireflies[i].vy == 0) {
            int dir = rand() % 8;
            int directions[8][2] = {
                {-1, -1}, {0, -1}, {1, -1},
                {-1,  0},          {1,  0},
                {-1,  1}, {0,  1}, {1,  1}
            };
            fireflies[i].vx = directions[dir][0];
            fireflies[i].vy = directions[dir][1];
        }
        
        // 更新位置
        fireflies[i].x += fireflies[i].vx;
        fireflies[i].y += fireflies[i].vy;
        
        // 边界处理
        if (fireflies[i].x < 0) {
            fireflies[i].x = 0;
            fireflies[i].vx = 1;  // 碰到边界时改变方向
        }
        if (fireflies[i].x >= 32) {
            fireflies[i].x = 31;
            fireflies[i].vx = -1;
        }
        if (fireflies[i].y < 0) {
            fireflies[i].y = 0;
            fireflies[i].vy = 1;
        }
        if (fireflies[i].y >= 16) {
            fireflies[i].y = 15;
            fireflies[i].vy = -1;
        }
    }
}

// 绘制所有萤火虫
static void gfx_draw_fireflies(firefly_t *fireflies) {
    for (int i = 0; i < NUM_FIREFLIES; i++) {
        gfx_draw_pixel(fireflies[i].x, fireflies[i].y, fireflies[i].color);
    }
}

// 主萤火虫效果循环
void gfx_firefly_effect(void) {
    firefly_t fireflies[NUM_FIREFLIES];
    
    // 初始化信息素地图和萤火虫
    firefly_init_pheromone_map();
    firefly_init_fireflies(fireflies);
    
    while (1) {
        // 清屏（通过绘制黑色像素）
        gfx_clear();
        
        // 更新信息素地图和萤火虫
        firefly_update_pheromone_map(fireflies);
        firefly_update_fireflies(fireflies);
        gfx_draw_fireflies(fireflies);
        
        // 显示更新
        gfx_sync_frame();
        
        // 简单延迟
        busy_wait_us(100000);  // 10ms = 10000us
    }
}