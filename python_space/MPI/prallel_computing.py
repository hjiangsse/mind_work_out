import time
from mpi4py import MPI
import numpy as np

def my_function(param1, param2, param3):
    result = param1 ** 2 * param2 + param3
    time.sleep(2)
    return result

#get number of processors and processor rank
comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()

params = np.random.random((15, 3)) * 100.0
n = params.shape[0]

count = n // size #each process slice size
remainder = n % size #extra slice size

if rank < remainder:
    start = rank * (count + 1)
    stop = start + count + 1
else:
    start = rank * count + remainder
    stop = start + count

print("-------------------------------------------------------------------")
local_params = params[start:stop, :]
print(local_params)
local_results = np.empty((local_params.shape[0], local_params.shape[1] + 1))
print(local_results)
local_results[:, :local_params.shape[1]] = local_params
print(local_results)
local_results[:, -1] = my_function(local_results[:, 0], local_results[:, 1], local_results[:, 2])
print(local_results)
print("-------------------------------------------------------------------")

#send result to rank 0
if rank > 0:
    comm.Send(local_results, dest=0, tag=14)
else:
    final_results = np.copy(local_results)
    for i in range(1, size):
        if i < remainder:
            rank_size = count + 1
        else:
            rank_size = count
        
        tmp = np.empty((rank_size, final_results.shape[1]), dtype=float)
        comm.Recv(tmp, source=i, tag=14)
        final_results = np.vstack((final_results, tmp))
    print("result: ")
    print(final_results)