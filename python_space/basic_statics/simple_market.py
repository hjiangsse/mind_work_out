import numpy as np
import random
import matplotlib.pyplot as plt

def simple_market(win_rate, play_time = 1000, stock_num = 9, position = 0.01, commision = 0.01, lever = False):
    money_steps = np.zeros(play_time)
    money_steps[0] = 1000 #初始本金数量
    lose_count = 1
    binomial = np.random.binomial(stock_num, win_rate, play_time)

    for i in range(1, play_time):
        if money_steps[i-1] * position * lose_count <= money_steps[i-1]: #资金充足
            once_chip = money_steps[i-1] * position * lose_count
        else:
            print(money_steps[i-1])
            break

        if binomial[i] > stock_num // 2: #持有的一半股票都在上涨
            money_steps[i] = (money_steps[i-1] + once_chip) if lever == False else money_steps[i-1] + once_chip * lose_count
            lose_count = 1
        else:
            money_steps[i] = (money_steps[i-1] - once_chip) if lever == False else money_steps[i-1] - once_chip * lose_count
            lose_count += 1

        money_steps[i] -= commision
        if money_steps[i] <= 0:
            break
    return money_steps

#一条道走到黑
def dark_market(win_rate, play_time = 1000, stock_num = 9, position = 0.01, commision = 0.01, lever = False):
    money_steps = np.zeros(play_time)
    money_steps[0] = 1000 #初始本金数量
    lose_count = 1
    binomial = np.random.binomial(stock_num, win_rate, play_time)

    #初始赌注
    old_chip = money_steps[0] * position * lose_count 
    for i in range(1, play_time):
        if lose_count > 1:
            #当前处于连续输钱状态，加倍赌注
            cur_chip = old_chip * 2
        else:
            #上一笔交易赢钱了，见好就收，这一次加正常的赌注
            cur_chip = money_steps[i-1] * position * lose_count

        #资金不足了，退出赌局
        if cur_chip > money_steps[i-1]:    
            break

        if binomial[i] > stock_num // 2: #持有的一半股票都在上涨
            money_steps[i] = (money_steps[i-1] + cur_chip) if lever == False else money_steps[i-1] + cur_chip * lose_count
            lose_count = 1
        else:
            money_steps[i] = (money_steps[i-1] - cur_chip) if lever == False else money_steps[i-1] - cur_chip * lose_count
            lose_count += 1

        money_steps[i] -= commision
        if money_steps[i] <= 0:
            break
        old_chip = cur_chip
    return money_steps

#加入仓位管理因子的市场模型
def position_manage_market(play_time = 1000, stock_num = 9, commision = 0.01):
    money_steps = np.zeros(play_time)
    money_steps[0] = 1000
    win_rate = random.uniform(0.5, 1)
    binomial = np.random.binomial(stock_num, win_rate, play_time)

    for i in range(1, play_time):
        once_chip = money_steps[i-1] * ((win_rate * 1 - (1 - win_rate)) / 1) #kaili公式1赔1的概率下注
        if binomial[i] > stock_num // 2:
            money_steps[i] = money_steps[i-1] + once_chip
        else:
            money_steps[i] = money_steps[i-1] - once_chip
        money_steps[i] -= commision
        if money_steps[i] <= 0:
            break
        
    return money_steps

if __name__ == "__main__":
    trader = 50
    _ = [plt.plot(np.arange(1000), simple_market(0.5, play_time = 1000, stock_num = 9, commision = 0))
         for _ in np.arange(0, trader)]
    pass
