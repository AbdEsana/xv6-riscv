#include "kernel/types.h"
#include "user/user.h"

int main(void){
    printf("Initial memory size: %d bytes\n", memsize());

    char *arr = malloc(20 * 1024); //Allocate 20k more bytes of memory
    //failed malloc
    if (arr == 0){
        printf("malloc failed\n");
        exit(1,"");
    }

    printf("after malloc: %d bytes\n", memsize());

    free(arr);

    printf("after free: %d bytes\n", memsize());

    exit(0,"");
}