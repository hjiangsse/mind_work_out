import matplotlib.pyplot as plt
import numpy as np
from matplotlib import font_manager

def test_func_plot(font_property):
    plt.figure(figsize=(10, 5))

    #曲线绘制
    start_val = 0
    stop_val = 10
    num_val = 1000
    x = np.linspace(start_val, stop_val, num_val)
    y = np.sin(x)
    plt.plot(x, y, '--g,', lw=2, label='sin(x)')

    #调整坐标轴范围
    x_min = 0
    x_max = 10
    y_min = -1.5
    y_max = 1.5
    plt.xlim(x_min, x_max)
    plt.ylim(y_min, y_max)

    #设置坐标轴标签
    plt.xlabel('x asix', fontsize=15)
    plt.xlabel('y asix', fontsize=15)

    #设置坐标标签
    x_locations = np.arange(0, 10, 2)
    x_labels = ['2021-10-01', '2021-10-02', '2021-10-03', '2021-10-04', '2021-10-05']
    y_locations = np.arange(-1, 1.5, 1)
    y_labels = [u'最小值', u'零值', u'最大值']
    plt.xticks(x_locations, x_labels, rotation=0, fontsize=15)
    plt.yticks(y_locations, y_labels, fontsize=15, fontproperties=font_property)

    #设置网格线
    plt.grid(True, ls=':', color='r', alpha=0.5)

    #设置图形标题
    plt.title("函数式绘图", fontsize=25, fontproperties=font_property)

    #图例显示
    plt.legend(loc='upper right', fontsize=15, prop=font_property)

    #显示图像
    plt.show()

if __name__ == "__main__":
    fontP = font_manager.FontProperties()
    fontP.set_family('SimHei')
    fontP.set_size(15)

    test_func_plot(fontP)