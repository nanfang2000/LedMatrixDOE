# 3D点阵旋转显示功能

## 概述

现在支持对16x16x16的3D点阵进行三个方向的旋转显示：
- **绕X轴旋转** (Pitch - 前后翻转)
- **绕Y轴旋转** (Yaw - 水平旋转)
- **绕Z轴旋转** (Roll - 左右翻转)

## API说明

### `gfx_draw_voxel_array_rotated()`

```c
void gfx_draw_voxel_array_rotated(int x, int y, int z, 
                                   int angle_x, int angle_y, int angle_z,
                                   const voxel_array_t *voxel_array);
```

在指定位置绘制带旋转的3D点阵。

**参数：**
- `x, y, z`: 点阵中心在屏幕上的坐标位置
- `angle_x`: 绕X轴旋转角度（0-360度）
- `angle_y`: 绕Y轴旋转角度（0-360度）
- `angle_z`: 绕Z轴旋转角度（0-360度）
- `voxel_array`: 指向点阵数据结构的指针

**说明：**
- 旋转是围绕点阵的中心进行的
- 角度范围是0-360度，会自动归一化
- 支持同时绕多个轴旋转

## 使用示例

### 示例1: 绕Y轴旋转（水平旋转）

```c
#include "gfx_image.h"

extern const voxel_array_t voxel_head;

int angle = 0;

while(1) {
    gfx_clear();
    
    // 绕Y轴旋转（水平旋转）
    gfx_draw_voxel_array_rotated(8, 8, 8, 0, angle, 0, &voxel_head);
    
    gfx_sync_frame();
    
    angle = (angle + 5) % 360;  // 每次旋转5度
    sleep_ms(50);  // 延迟50ms
}
```

### 示例2: 绕X轴旋转（前后翻转）

```c
// 绕X轴旋转
gfx_draw_voxel_array_rotated(8, 8, 8, angle, 0, 0, &voxel_head);
```

### 示例3: 绕Z轴旋转（左右翻转）

```c
// 绕Z轴旋转
gfx_draw_voxel_array_rotated(8, 8, 8, 0, 0, angle, &voxel_head);
```

### 示例4: 组合旋转

```c
// 同时绕X和Y轴旋转
gfx_draw_voxel_array_rotated(8, 8, 8, angle, angle, 0, &voxel_head);

// 同时绕三个轴旋转
gfx_draw_voxel_array_rotated(8, 8, 8, angle_x, angle_y, angle_z, &voxel_head);
```

### 示例5: 固定角度显示

```c
// 显示旋转45度的点阵
gfx_draw_voxel_array_rotated(8, 8, 8, 0, 45, 0, &voxel_head);
```

## 旋转方向说明

### 绕X轴旋转 (angle_x)
- **正角度**: 点阵向前翻转（俯视时顺时针）
- **负角度**: 点阵向后翻转（俯视时逆时针）
- **视觉效果**: 像点头一样前后翻转

### 绕Y轴旋转 (angle_y)
- **正角度**: 点阵水平顺时针旋转（从上方看）
- **负角度**: 点阵水平逆时针旋转（从上方看）
- **视觉效果**: 像转盘一样水平旋转

### 绕Z轴旋转 (angle_z)
- **正角度**: 点阵左右翻转（从前方看顺时针）
- **负角度**: 点阵左右翻转（从前方看逆时针）
- **视觉效果**: 像侧翻一样左右翻转

## 性能优化建议

1. **预计算角度**: 如果只使用固定角度（如90度、180度、270度），可以预先计算并存储结果

2. **使用查找表**: 对于频繁使用的角度，可以使用查找表替代sin/cos计算

3. **减少旋转计算**: 如果不需要旋转，使用`gfx_draw_voxel_array()`函数，它更高效

4. **控制帧率**: 旋转动画时适当控制帧率，避免过度计算

## 注意事项

1. **坐标系统**: 旋转是围绕点阵中心进行的，确保传入的x, y, z是中心位置

2. **边界检查**: 旋转后的点可能超出屏幕范围，函数会自动处理边界

3. **精度**: 使用整数运算和固定点数学，精度为0.001（1000倍缩放）

4. **数学库**: 需要链接数学库（在CMakeLists.txt中已添加 `-lm`）

## 完整示例代码

```c
#include <stdio.h>
#include "pico/stdlib.h"
#include "gfx_driver.h"
#include "gfx_image.h"

extern const voxel_array_t voxel_head;

int main() {
    stdio_init_all();
    gfx_init();
    
    int angle_x = 0;
    int angle_y = 0;
    int angle_z = 0;
    
    while(1) {
        gfx_clear();
        
        // 绕Y轴旋转（水平旋转）
        gfx_draw_voxel_array_rotated(8, 8, 8, angle_x, angle_y, angle_z, &voxel_head);
        
        gfx_sync_frame();
        
        // 更新角度
        angle_y = (angle_y + 5) % 360;  // Y轴每次旋转5度
        
        sleep_ms(50);  // 控制旋转速度
    }
}
```

## 技术实现

旋转使用标准的3D旋转矩阵：
1. 先绕Z轴旋转
2. 再绕Y轴旋转
3. 最后绕X轴旋转

使用固定点数学（1000倍缩放）进行整数运算，避免浮点数计算，提高性能。
