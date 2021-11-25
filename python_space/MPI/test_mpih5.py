from mpi4py import MPI
import h5py

comm = MPI.COMM_WORLD
rank = comm.rank

f = h5py.File('collective_test.h5', 'w', driver='mpio', comm=comm)

dset = f.create_dataset('x', (100,), 'i')
dset.attrs['title'] = "Hello"

if rank == 0:
    dset[0] = 42

if rank == 1:
    dset[1] = 44

f.close()
