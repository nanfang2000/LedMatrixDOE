#!/usr/bin/env python3
"""
将图像文件转换为C语言的image_t结构
支持将图像缩放到16x16并生成C代码

依赖:
    pip install Pillow numpy
"""

import sys

try:
    from PIL import Image
    import numpy as np
except ImportError as e:
    print("错误: 缺少必要的Python库", file=sys.stderr)
    print("请运行以下命令安装:", file=sys.stderr)
    print("  pip install Pillow numpy", file=sys.stderr)
    sys.exit(1)

def rgb_to_c_color(r, g, b):
    """将RGB值转换为C结构体格式"""
    return f"((rgb_t){{{r}, {g}, {b}}})"

def convert_image_to_c(image_path, output_var_name="image_portrait", output_file=None, 
                       use_transparent=False, threshold=10):
    """
    将图像文件转换为C语言的image_t结构
    
    Args:
        image_path: 输入图像文件路径
        output_var_name: 输出的变量名
        output_file: 输出文件路径（如果为None，则输出到stdout）
        use_transparent: 是否将接近黑色的像素转换为透明（黑色）
        threshold: 透明度阈值，RGB值都小于此值的像素将被设为黑色
    """
    try:
        # 打开图像
        img = Image.open(image_path)
        
        # 转换为RGB模式（如果不是的话）
        if img.mode == 'RGBA':
            # 如果有alpha通道，先合成到白色背景上
            background = Image.new('RGB', img.size, (255, 255, 255))
            background.paste(img, mask=img.split()[3])  # 使用alpha通道作为mask
            img = background
        elif img.mode != 'RGB':
            img = img.convert('RGB')
        
        # 缩放到16x16，使用高质量重采样
        img = img.resize((16, 16), Image.Resampling.LANCZOS)
        
        # 转换为numpy数组
        img_array = np.array(img)
        
        # 生成C代码
        lines = []
        lines.append(f"/**")
        lines.append(f" * @brief {output_var_name} (16x16) - 从 {image_path} 转换")
        lines.append(f" */")
        lines.append(f"const image_t {output_var_name} = {{")
        lines.append("    .pixels = {")
        
        for y in range(16):
            row = []
            for x in range(16):
                r, g, b = img_array[y, x]
                
                # 如果启用透明模式，将接近黑色的像素设为黑色
                if use_transparent and r < threshold and g < threshold and b < threshold:
                    r, g, b = 0, 0, 0
                
                row.append(rgb_to_c_color(r, g, b))
            lines.append("        {" + ", ".join(row) + "},")
        
        lines.append("    }")
        lines.append("};")
        
        # 输出结果
        output = "\n".join(lines)
        
        if output_file:
            with open(output_file, 'w', encoding='utf-8') as f:
                f.write(output)
            print(f"已成功转换图像并保存到: {output_file}")
            print(f"图像尺寸: {img.size[0]}x{img.size[1]} -> 16x16")
        else:
            print(output)
            
    except FileNotFoundError:
        print(f"错误: 找不到文件 {image_path}", file=sys.stderr)
        sys.exit(1)
    except Exception as e:
        print(f"错误: {e}", file=sys.stderr)
        import traceback
        traceback.print_exc()
        sys.exit(1)

def main():
    if len(sys.argv) < 2:
        print("用法: python convert_image_to_c.py <图像文件> [变量名] [输出文件] [--transparent]")
        print("")
        print("参数:")
        print("  图像文件      - 输入的图像文件路径（支持TIFF, PNG, JPEG等）")
        print("  变量名        - C变量名（默认: image_portrait）")
        print("  输出文件      - 输出C代码文件路径（可选，默认输出到stdout）")
        print("  --transparent - 将接近黑色的像素转换为黑色（用于透明效果）")
        print("")
        print("示例:")
        print("  python convert_image_to_c.py hemuyang_head.tiff")
        print("  python convert_image_to_c.py hemuyang_head.tiff image_portrait")
        print("  python convert_image_to_c.py hemuyang_head.tiff image_portrait output.c")
        print("  python convert_image_to_c.py hemuyang_head.tiff image_portrait output.c --transparent")
        sys.exit(1)
    
    image_path = sys.argv[1]
    var_name = "image_portrait"
    output_file = None
    use_transparent = False
    
    # 解析参数
    for i, arg in enumerate(sys.argv[2:], start=2):
        if arg == "--transparent":
            use_transparent = True
        elif not arg.startswith("--"):
            if var_name == "image_portrait" and i == 2:
                var_name = arg
            elif output_file is None:
                output_file = arg
    
    convert_image_to_c(image_path, var_name, output_file, use_transparent)

if __name__ == "__main__":
    main()

