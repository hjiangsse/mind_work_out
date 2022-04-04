import cProfile

def acc_sum(n):
    """acc sum"""
    res = 0
    for i in range(n):
        res += (i+1)
    return res

def acc_square_sum(n):
    """acc square sum"""
    res = 0
    for i in range(n):
        res += (i+1) * (i+1)
    return res

if __name__ == "__main__":
    acc_sum(1000000)
    acc_square_sum(1000000)
