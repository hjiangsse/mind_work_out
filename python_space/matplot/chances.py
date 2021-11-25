import numpy as np

def test_binomial():
    print(np.random.binomial(5, 0.5, 10))

#--------------------------------------------
# n: test numbers
# k: the number something happen
# p: the probility something happen in one test
#--------------------------------------------
def cal_binomial_val(n, k, p):
    return (sum(np.random.binomial(n, p, size=100000 * n) == k) / float(100000 * n))

if __name__ == "__main__":
    #test_binomial()
    print(cal_binomial_val(5, 5, 0.5))