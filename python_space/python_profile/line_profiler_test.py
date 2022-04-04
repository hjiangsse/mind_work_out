def acc_square_add(n):
    """acc square sum"""
    res = 0
    for i in range(n):
        res += (i+1) * (i+1)
    return res

@profile
def slow_function():
    print("slow function begin")
    acc_square_add(10000000)
    print("slow function end")

if __name__ == "__main__":
    slow_function()
