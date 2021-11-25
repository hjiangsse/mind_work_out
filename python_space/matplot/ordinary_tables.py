import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure(figsize=(12, 8))
ax = fig.add_subplot(111)
x = np.arange(10,20)
y = np.around(np.log(x), 2)
ax.plot(x, y, marker='o')

ax.annotate('style1', xy=(x[1], y[1]), xytext=(80, 10), textcoords='offset points', 
arrowprops = dict(arrowstyle='->', connectionstyle="angle3,angleA=80,angleB=50"))

ax.annotate('style2', xy=(x[2], y[2])) 

plt.show()