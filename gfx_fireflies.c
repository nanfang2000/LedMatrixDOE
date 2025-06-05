#include "gfx_driver.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "hardware/timer.h"

// 萤火虫数量
#define NUM_FIREFLIES 64
// 信息素挥发率
#define PHEROMONE_EVAPORATION 0.9
// 信息素强度
#define PHEROMONE_INTENSITY 100
// 群体行为参数
#define NEIGHBOR_RADIUS 5  // 邻居检测半径
#define ALIGNMENT_WEIGHT 0.1f  // 对齐权重
#define COHESION_WEIGHT 1.0f   // 凝聚权重
#define SEPARATION_WEIGHT 3.0f // 分离权重

// 信息素地图
float pheromone_map[16][32];

// 萤火虫位置结构体
typedef struct {
    int x;
    int y;
    float vx;  // 改为float以支持更平滑的移动
    float vy;
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

// 计算两个点之间的距离
static float distance(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    return sqrtf(dx * dx + dy * dy);
}

// 更新萤火虫位置
static void firefly_update_fireflies(firefly_t *fireflies) {
    for (int i = 0; i < NUM_FIREFLIES; i++) {
        float align_x = 0, align_y = 0;    // 对齐力
        float cohesion_x = 0, cohesion_y = 0;  // 凝聚力
        float separation_x = 0, separation_y = 0;  // 分离力
        int neighbors = 0;
        
        // 计算群体行为
        for (int j = 0; j < NUM_FIREFLIES; j++) {
            if (i == j) continue;
            
            float dist = distance(fireflies[i].x, fireflies[i].y, 
                                fireflies[j].x, fireflies[j].y);
            
            if (dist < NEIGHBOR_RADIUS) {
                neighbors++;
                
                // 对齐：与邻居保持相同方向
                align_x += fireflies[j].vx;
                align_y += fireflies[j].vy;
                
                // 凝聚：向邻居的平均位置移动
                cohesion_x += fireflies[j].x - fireflies[i].x;
                cohesion_y += fireflies[j].y - fireflies[i].y;
                
                // 分离：避免碰撞
                if (dist > 0) {
                    separation_x -= (fireflies[j].x - fireflies[i].x) / dist;
                    separation_y -= (fireflies[j].y - fireflies[i].y) / dist;
                }
            }
        }
        
        if (neighbors > 0) {
            // 归一化对齐力
            align_x /= neighbors;
            align_y /= neighbors;
            
            // 归一化凝聚力
            cohesion_x /= neighbors;
            cohesion_y /= neighbors;
            
            // 归一化分离力
            separation_x /= neighbors;
            separation_y /= neighbors;
            
            // 应用群体行为
            fireflies[i].vx += ALIGNMENT_WEIGHT * align_x +
                             COHESION_WEIGHT * cohesion_x +
                             SEPARATION_WEIGHT * separation_x;
            fireflies[i].vy += ALIGNMENT_WEIGHT * align_y +
                             COHESION_WEIGHT * cohesion_y +
                             SEPARATION_WEIGHT * separation_y;
        }
        
        // 限制速度
        float speed = sqrtf(fireflies[i].vx * fireflies[i].vx + 
                          fireflies[i].vy * fireflies[i].vy);
        if (speed > 2.0f) {
            fireflies[i].vx = (fireflies[i].vx / speed) * 2.0f;
            fireflies[i].vy = (fireflies[i].vy / speed) * 2.0f;
        }
        
        // 更新位置
        fireflies[i].x += (int)fireflies[i].vx;
        fireflies[i].y += (int)fireflies[i].vy;
        
        // 边界处理
        if (fireflies[i].x < 0) {
            fireflies[i].x = 0;
            fireflies[i].vx = 1;
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
    rgb_t red = {255, 0, 0};
    rgb_t green = {0, 255, 0};
    rgb_t blue = {0, 0, 255};
    firefly_t fireflies[NUM_FIREFLIES];
    memset(fireflies, 0, sizeof(fireflies));
    
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