import pstats
from pstats import SortKey

if __name__ == "__main__":
    p = pstats.Stats('cumsum.stat')
    p.strip_dirs().sort_stats(-1).print_stats()
    p.sort_stats(SortKey.NAME).print_stats()
    p.sort_stats(SortKey.CUMULATIVE).print_stats()
    p.sort_stats(SortKey.TIME).print_stats()
