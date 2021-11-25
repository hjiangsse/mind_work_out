import numpy as np
import pandas as pd

# what a burden when use numpy process multi type data
deftype = ([('date', np.str_, 10), ('closeprc', np.float32), ('vol', np.uint32)])
stock = np.array([('2019-01-11', 11.01, 1300000),
                  ('2019-01-12', 12.11, 1200000),
                  ('2019-01-13', 15.01, 1300000),
                  ('2019-01-14', 13.01, 1600000)], dtype=deftype)
print(stock)

# use pandas instead
print(pd.__version__)

# 1.1 generate series
print(np.arange(10))