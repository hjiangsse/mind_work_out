#from memory_profiler import profile

@profile
def my_func():
    a = [1] * (10 ** 6)
    b = [2] * (2 * 10 ** 7)
    del b
    return a

@profile
def your_func():
    c = [1] * (10 ** 6)
    d = [2] * (2 * 10 ** 7)
    del d
    return c

if __name__ == '__main__':
    my_func()
    your_func()
