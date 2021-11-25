import numpy as np
from multiprocessing import Pool
import h5py

def distance(arr):
    return np.sqrt(np.sum(arr ** 2))

def main():
    with h5py.File('coords.h5', 'w') as f:
        dset = f.create_dataset('coords', (1000, 2), dtype='f4')
        dset[...] = np.random.random((1000,2))

    with h5py.File('coords.h5', 'r') as f:
        data = f['coords'][...]
    
    p = Pool(4)
    result = np.array(p.map(distance, data))

    with h5py.File('coords.h5', 'w') as f:
        f['distances'] = result

if __name__ == "__main__":
    main()