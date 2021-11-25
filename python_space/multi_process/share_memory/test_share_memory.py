from multiprocessing import shared_memory
import array

def test_low_level_share_memory():
    shm_a = shared_memory.SharedMemory(create=True, size=10)
    print(type(shm_a))
    buffer = shm_a.buf
    print("the length of the buffer: ", len(buffer))
    buffer[:4] = bytearray([22,33,44,55])
    buffer[4] = 100

    shm_b = shared_memory.SharedMemory(shm_a.name)
    print(array.array('b', shm_b.buf[0:5]))
    shm_b.buf[:5] = b'hello'
    print(bytes(shm_a.buf))

    shm_a.close()
    shm_b.close()
    shm_a.unlink()

if __name__ == "__main__":
    test_low_level_share_memory()