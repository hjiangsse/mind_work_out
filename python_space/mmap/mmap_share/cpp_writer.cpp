#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

using namespace std;

int main(int argc, char **argv) {
    if(argc != 2) {
        printf("usage: program filepath\n");
        return -1;
    }

    int fd = -1;
    if((fd = open(argv[1], O_RDWR, 0)) == -1) {
        printf("unable to open file %s.\n", argv[1]);
        return -1;
    }

    //open the file in mmap memory
    char* shared = (char *)mmap(NULL, 8, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shared == NULL) {
        printf("share memory map failed!\n");
        return -1;
    }

    while(true) {
        printf("0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\n", shared[0], shared[1], shared[2], shared[3], shared[4], shared[5], shared[6], shared[7]);
        sleep(1);
    }
    return 0;
}