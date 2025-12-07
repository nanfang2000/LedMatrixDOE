# STL转3D点阵使用说明

## 概述

这个工具可以将STL 3D模型文件转换为16x16x16的点阵，并生成C数组代码，可以在LED点阵模块上显示。

## 安装依赖

首先需要安装Python依赖库：

```bash
pip install numpy-stl numpy
```

## 使用方法

### 基本用法

```bash
python3 convert_stl_to_voxel.py head_3d.stl
```

这将读取`head_3d.stl`文件，生成C代码并输出到标准输出。

### 指定变量名

```bash
python3 convert_stl_to_voxel.py head_3d.stl voxel_head
```

### 保存到文件

```bash
python3 convert_stl_to_voxel.py head_3d.stl voxel_head head_voxel.c
```

### 指定颜色

默认颜色是白色(255, 255, 255)，可以自定义：

```bash
python3 convert_stl_to_voxel.py head_3d.stl voxel_head head_voxel.c --color 255 200 150
```

## 在C代码中使用

### 1. 生成点阵数据

运行脚本生成C代码：

```bash
python3 convert_stl_to_voxel.py head_3d.stl voxel_head head_voxel.c
```

### 2. 在代码中包含头文件

```c
#include "gfx_image.h"
```

### 3. 声明点阵数据

将生成的C代码添加到你的源文件中，或者创建一个单独的文件（如`head_voxel.c`）并在头文件中声明：

```c
// 在头文件中
extern const voxel_array_t voxel_head;
```

### 4. 显示点阵

```c
// 在(0, 0, 0)位置显示点阵
gfx_draw_voxel_array(0, 0, 0, &voxel_head);

// 同步帧缓冲区
gfx_sync_frame();
```

### 完整示例

```c
#include "gfx_driver.h"
#include "gfx_image.h"

// 假设点阵数据已经在head_voxel.c中定义
extern const voxel_array_t voxel_head;

int main() {
    gfx_init();
    
    // 清屏
    gfx_clear();
    
    // 在原点显示3D点阵
    gfx_draw_voxel_array(0, 0, 0, &voxel_head);
    
    // 同步到显示
    gfx_sync_frame();
    
    while(1) {
        // 主循环
    }
}
```

## 数据结构说明

生成的`voxel_array_t`结构包含：

- `size`: 点阵大小（16）
- `color`: RGB颜色，用于绘制填充的体素
- `voxels[16][16][16]`: 体素数据，按[z][y][x]顺序存储
  - 0表示空体素
  - 1表示填充的体素

## 注意事项

1. STL文件应该是二进制格式
2. 体素化过程可能需要一些时间，特别是对于复杂的模型
3. 生成的16x16x16点阵是低分辨率的，细节可能会丢失
4. 点阵会自动缩放以适应16x16x16空间

## API参考

### `gfx_draw_voxel_array(int x, int y, int z, const voxel_array_t *voxel_array)`

在指定位置绘制3D点阵。

**参数：**
- `x`: X坐标起始位置
- `y`: Y坐标起始位置  
- `z`: Z坐标（深度）起始位置
- `voxel_array`: 指向点阵数据结构的指针

**说明：**
- 只绘制填充的体素（值不为0）
- 自动检查边界，超出屏幕范围的体素不会被绘制
- 使用点阵数据中指定的颜色绘制
