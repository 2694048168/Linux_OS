import cv2
import numpy as np

# 创建黑色背景图像
width, height = 1000, 1000
image = np.zeros((height, width), dtype=np.uint8)

# 定义圆心和半径
center = (width // 2, height // 2)
radii = [350, 250, 150, 80]  # 从外到内的四个半径

# 绘制四个嵌套圆环
for i, radius in enumerate(radii):
    # 绘制白色圆
    cv2.circle(image, center, radius, 255, -1)  # -1 表示填充
    
    # 在内部绘制一个黑色圆，形成圆环
    if i < len(radii) - 1:  # 最后一个圆不需要内部黑色圆
        inner_radius = radii[i+1] + 15  # 稍微大于下一个圆，确保形成圆环
        cv2.circle(image, center, inner_radius, 0, -1)

# 保存图像
cv2.imwrite("nested_circles.png", image)

# 显示图像
cv2.imshow("Nested Circles", image)
cv2.waitKey(0)
cv2.destroyAllWindows()

# 测试 findContours() 函数
# 读取刚创建的图像
img = cv2.imread("nested_circles.png")
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# 应用二值化
_, thresh = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)

# 查找轮廓
contours, hierarchy = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

# 绘制轮廓
contour_img = img.copy()
cv2.drawContours(contour_img, contours, -1, (0, 255, 0), 2)

# 显示轮廓结果
cv2.imshow("Contours", contour_img)
cv2.waitKey(0)
cv2.destroyAllWindows()

# 打印轮廓和层级信息
print(f"找到 {len(contours)} 个轮廓")
print("层级关系:", hierarchy)
