#!/usr/bin/env python3
"""
将STL文件转换为16x16x16点阵（体素化）并生成C数组

依赖:
    pip install numpy-stl
"""

import sys
import struct
import numpy as np

try:
    from stl import mesh
except ImportError:
    print("错误: 缺少必要的Python库", file=sys.stderr)
    print("请运行以下命令安装:", file=sys.stderr)
    print("  pip install numpy-stl", file=sys.stderr)
    sys.exit(1)

def read_binary_stl(filename):
    """读取二进制STL文件"""
    with open(filename, 'rb') as f:
        # 读取80字节的头部
        header = f.read(80)
        
        # 读取三角形数量
        num_triangles = struct.unpack('<I', f.read(4))[0]
        
        # 读取所有三角形
        triangles = []
        for i in range(num_triangles):
            # 读取法向量（12字节，3个float）
            normal = struct.unpack('<3f', f.read(12))
            # 读取三个顶点（每个12字节，3个float）
            v1 = struct.unpack('<3f', f.read(12))
            v2 = struct.unpack('<3f', f.read(12))
            v3 = struct.unpack('<3f', f.read(12))
            # 读取属性字节计数（2字节，通常为0）
            attr = f.read(2)
            
            triangles.append([v1, v2, v3])
        
        return np.array(triangles), header.decode('ascii', errors='ignore').strip()

def point_in_triangle_2d(p, v1, v2, v3):
    """使用重心坐标判断点是否在三角形内（2D投影）"""
    def sign(p1, p2, p3):
        return (p1[0] - p3[0]) * (p2[1] - p3[1]) - (p2[0] - p3[0]) * (p1[1] - p3[1])
    
    d1 = sign(p, v1, v2)
    d2 = sign(p, v2, v3)
    d3 = sign(p, v3, v1)
    
    has_neg = (d1 < 0) or (d2 < 0) or (d3 < 0)
    has_pos = (d1 > 0) or (d2 > 0) or (d3 > 0)
    
    return not (has_neg and has_pos)

def voxelize_stl(stl_file, size=16):
    """
    将STL文件体素化为指定大小的点阵
    
    Args:
        stl_file: STL文件路径
        size: 点阵大小（默认16）
    
    Returns:
        voxel_array: 3D布尔数组，True表示有体素 [z][y][x]
        bounds: 边界框 (min_bounds, max_bounds)
    """
    # 使用numpy-stl库读取STL文件
    try:
        stl_mesh = mesh.Mesh.from_file(stl_file)
    except Exception as e:
        print(f"错误: 无法读取STL文件: {e}", file=sys.stderr)
        sys.exit(1)
    
    # 获取所有顶点
    vertices = stl_mesh.vectors.reshape(-1, 3)
    
    # 计算边界框
    min_bounds = vertices.min(axis=0)
    max_bounds = vertices.max(axis=0)
    
    # 计算缩放和平移，使模型适合16x16x16空间（留一点边距）
    size_range = max_bounds - min_bounds
    max_range = max(size_range)
    scale = (size - 2) / max_range  # 留2个体素的边距
    center = (min_bounds + max_bounds) / 2
    target_center = size / 2
    
    # 转换所有三角形到体素空间
    triangles_voxel = []
    for triangle in stl_mesh.vectors:
        v1 = (triangle[0] - center) * scale + target_center
        v2 = (triangle[1] - center) * scale + target_center
        v3 = (triangle[2] - center) * scale + target_center
        triangles_voxel.append((v1, v2, v3))
    
    # 创建体素数组
    voxel_array = np.zeros((size, size, size), dtype=bool)
    
    # 对每个三角形，标记其覆盖的体素
    print("正在进行体素化...", file=sys.stderr)
    triangle_count = len(triangles_voxel)
    
    for tri_idx, triangle in enumerate(triangles_voxel):
        if tri_idx % 100 == 0:
            print(f"  处理进度: {tri_idx}/{triangle_count} 三角形", file=sys.stderr)
        
        v1, v2, v3 = triangle
        
        # 计算三角形的边界框
        tri_min = np.minimum(np.minimum(v1, v2), v3)
        tri_max = np.maximum(np.maximum(v1, v2), v3)
        
        # 在边界框内检查每个体素
        x_min = max(0, int(np.floor(tri_min[0])))
        x_max = min(size, int(np.ceil(tri_max[0])) + 1)
        y_min = max(0, int(np.floor(tri_min[1])))
        y_max = min(size, int(np.ceil(tri_max[1])) + 1)
        z_min = max(0, int(np.floor(tri_min[2])))
        z_max = min(size, int(np.ceil(tri_max[2])) + 1)
        
        for x in range(x_min, x_max):
            for y in range(y_min, y_max):
                for z in range(z_min, z_max):
                    # 体素中心点
                    voxel_center = np.array([x + 0.5, y + 0.5, z + 0.5])
                    
                    # 检查体素中心是否接近三角形（在三角形附近）
                    # 计算体素中心到三角形平面的距离
                    edge1 = v2 - v1
                    edge2 = v3 - v1
                    normal = np.cross(edge1, edge2)
                    if np.linalg.norm(normal) < 1e-6:
                        continue  # 退化三角形
                    
                    normal = normal / np.linalg.norm(normal)
                    d = np.dot(normal, v1)
                    dist = abs(np.dot(normal, voxel_center) - d)
                    
                    # 如果距离足够近，检查是否在三角形投影内
                    if dist < 0.8:  # 阈值
                        # 投影到XY平面检查
                        if point_in_triangle_2d(voxel_center[:2], v1[:2], v2[:2], v3[:2]):
                            voxel_array[z, y, x] = True
                        # 投影到XZ平面检查
                        elif point_in_triangle_2d([voxel_center[0], voxel_center[2]], 
                                                  [v1[0], v1[2]], [v2[0], v2[2]], [v3[0], v3[2]]):
                            voxel_array[z, y, x] = True
                        # 投影到YZ平面检查
                        elif point_in_triangle_2d([voxel_center[1], voxel_center[2]], 
                                                  [v1[1], v1[2]], [v2[1], v2[2]], [v3[1], v3[2]]):
                            voxel_array[z, y, x] = True
    
    # 使用简单的填充算法填充内部
    print("正在填充内部体素...", file=sys.stderr)
    filled_voxels = fill_interior(voxel_array, size)
    
    return filled_voxels, (min_bounds, max_bounds)

def fill_interior(voxel_array, size):
    """使用扫描线算法填充内部体素"""
    filled = voxel_array.copy()
    
    # 对每个z层进行填充
    for z in range(size):
        layer = filled[z, :, :]
        
        # 对每一行进行扫描线填充
        for y in range(size):
            inside = False
            start_x = 0
            for x in range(size):
                if layer[y, x]:
                    if not inside:
                        inside = True
                        start_x = x
                else:
                    if inside:
                        # 检查是否应该填充（简单启发式：如果左右都有边界）
                        if start_x > 0 and x < size - 1:
                            layer[y, start_x:x] = True
                        inside = False
    
    return filled


def generate_c_array(voxel_array, var_name="voxel_head_3d", color=(255, 255, 255)):
    """
    生成C数组代码
    
    Args:
        voxel_array: 3D布尔数组 [z][y][x]
        var_name: 变量名
        color: RGB颜色值
    """
    size = voxel_array.shape[0]
    lines = []
    
    lines.append(f"/**")
    lines.append(f" * @brief {var_name} - 16x16x16 3D voxel array")
    lines.append(f" * Generated from STL file")
    lines.append(f" */")
    lines.append(f"const voxel_array_t {var_name} = {{")
    lines.append(f"    .size = {size},")
    lines.append(f"    .color = {{ {color[0]}, {color[1]}, {color[2]} }},")
    lines.append(f"    .voxels = {{")
    
    # 按照 [z][y][x] 的顺序生成
    for z in range(size):
        lines.append(f"        // z = {z}")
        lines.append("        {")
        for y in range(size):
            row = []
            for x in range(size):
                if voxel_array[z, y, x]:
                    row.append("1")
                else:
                    row.append("0")
            # 每行最多16个元素，格式化为一行
            lines.append("            {" + ", ".join(row) + "},")
        lines.append("        },")
    
    lines.append("    }")
    lines.append("};")
    
    return "\n".join(lines)

def main():
    if len(sys.argv) < 2:
        print("用法: python convert_stl_to_voxel.py <STL文件> [变量名] [输出文件] [--color R G B]")
        print("")
        print("参数:")
        print("  STL文件      - 输入的STL文件路径")
        print("  变量名        - C变量名（默认: voxel_head_3d）")
        print("  输出文件      - 输出C代码文件路径（可选，默认输出到stdout）")
        print("  --color R G B - RGB颜色值（默认: 255 255 255 白色）")
        print("")
        print("示例:")
        print("  python convert_stl_to_voxel.py head_3d.stl")
        print("  python convert_stl_to_voxel.py head_3d.stl voxel_head")
        print("  python convert_stl_to_voxel.py head_3d.stl voxel_head output.c")
        print("  python convert_stl_to_voxel.py head_3d.stl voxel_head output.c --color 255 200 150")
        sys.exit(1)
    
    stl_file = sys.argv[1]
    var_name = "voxel_head_3d"
    output_file = None
    color = (255, 255, 255)
    
    # 解析参数
    i = 2
    while i < len(sys.argv):
        arg = sys.argv[i]
        if arg == "--color" and i + 3 < len(sys.argv):
            color = (int(sys.argv[i+1]), int(sys.argv[i+2]), int(sys.argv[i+3]))
            i += 4
        elif not arg.startswith("--"):
            if var_name == "voxel_head_3d" and i == 2:
                var_name = arg
            elif output_file is None:
                output_file = arg
            i += 1
        else:
            i += 1
    
    print(f"正在读取STL文件: {stl_file}...", file=sys.stderr)
    voxel_array, bounds = voxelize_stl(stl_file, size=16)
    
    print(f"体素化完成，共有 {voxel_array.sum()} 个体素", file=sys.stderr)
    
    c_code = generate_c_array(voxel_array, var_name, color)
    
    if output_file:
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(c_code)
        print(f"已成功生成C代码并保存到: {output_file}", file=sys.stderr)
    else:
        print(c_code)

if __name__ == "__main__":
    main()
