import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure(figsize=(10, 6))
ax = fig.add_subplot(111)

#gen data
start_val = 0
stop_val = 10
num_val = 1000
x = np.linspace(start_val, stop_val, num_val)
y = np.sin(x)

ax.plot(x, y, ':g', lw=2, label='sin(x)')

x_min = 0
x_max = 10
y_min = -1.5
y_max = 1.5
ax.set_xlim(x_min, x_max)
ax.set_ylim(y_min, y_max)

x_location = np.arange(0, 10, 2)
x_labels = ['hjiang', 'zhangjiang', 'sichuan', 'chendu', 'shanghai']
y_location = np.arange(-1, 1.5, 1)
y_labels = ['min', 'zero', 'max']
ax.set_xticks(x_location)
ax.set_yticks(y_location)
ax.set_xticklabels(x_labels, fontsize=15)
ax.set_yticklabels(y_labels, fontsize=15)

ax.set_xlabel('x asix', fontsize=15)
ax.set_ylabel('y asix', fontsize=15)

ax.grid(True, ls=':', color='r', alpha=0.5)
ax.set_title('object-oritend plot', fontsize=20)
plt.show()