import mmap
import timeit

def regular_io(filename):
    with open(filename, mode="r", encoding="utf8") as file_obj:
        text = file_obj.read()

def mmap_io(filename):
    with open(filename, mode="r", encoding="utf8") as file_obj:
        with mmap.mmap(file_obj.fileno(), length=0, access=mmap.ACCESS_READ) as mmap_obj:
            text = mmap_obj.read()

def mmap_io_readsub(filename):
    with open(filename, mode="r", encoding="utf8") as file_obj:
        with mmap.mmap(file_obj.fileno(), length=0, access=mmap.ACCESS_READ) as mmap_obj:
            print(mmap_obj[:20])

def regular_io_find(filename):
    with open(filename, mode="r", encoding="utf-8") as file_obj:
        text = file_obj.read()
        print(text.find(" the "))

def mmap_io_find(filename):
    with open(filename, mode="r", encoding="utf-8") as file_obj:
        with mmap.mmap(file_obj.fileno(), length=0, access=mmap.ACCESS_READ) as mmap_obj:
            print(mmap_obj.find(b" the "))

if __name__ == "__main__":
    filename = "test.txt"
    #mmap_io_readsub(filename)

    res1 = timeit.repeat(
     "regular_io_find(filename)",
     repeat=3,
     number=1,
     setup="from __main__ import regular_io_find, filename")

    res2 = timeit.repeat(
        "mmap_io_find(filename)",
        repeat=3,
        number=1,
        setup="from __main__ import mmap_io_find, filename")
    print(res1)
    print(res2)
    '''
    res_regular = timeit.repeat(
        "regular_io(filename)",
        repeat=3,
        number=1,
        setup="from __main__ import regular_io, filename"
    )
    
    res_mmap = timeit.repeat(
        "mmap_io(filename)",
        repeat=3,
        number=1,
        setup="from __main__ import mmap_io, filename"
    )
    print(res_regular)
    print(res_mmap)
    '''