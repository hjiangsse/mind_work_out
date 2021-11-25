from mpi4py import MPI

comm = MPI.COMM_WORLD

print("Hello World(from process %d)" % comm.rank)