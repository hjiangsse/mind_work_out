import numpy as np
import time

if __name__ == "__main__":
    np.random.seed(int(time.time()))
    print(np.random.binomial(1000, 0.5, 20))

    #计算连续抛10次硬币，每次都正面向上的概率
    print(sum(np.random.binomial(5, 0.5, 100000) == 5) / 100000.)

    #假设5次有三次以上为正，表示这次为胜利, 计算胜利的概率
    print(sum(np.random.binomial(5, 0.5, 100000) > 3) / 100000.)
    print(6/32.0)

    for i in range(1, 10):
        print(i)
