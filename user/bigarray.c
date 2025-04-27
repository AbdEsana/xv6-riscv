#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


#define SIZE (65536)
int *arr;

int
main(int argc, char *argv[])
{
    int n = 4; // number of children
    int pids[n];
    int statuses[n];
    int finished = 0;
    int total_sum = 0;

    arr = (int *)malloc(SIZE * sizeof(int));
    if (arr == 0) {
        printf("malloc failed\n");
        exit(-1, "");
    }

    // Initialize the array
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i;
    }

    int child_num = forkn(n, pids);
    if (child_num == -1) {
        printf("forkn(%d) failed\n", n);
        free(arr);
        exit(-1, "");
    }

    if (child_num >= 1) {
        int part = SIZE / n;
        int start = (child_num - 1) * part;
        int end = start + part;
        int part_sum = 0;
    
        for (int i = start; i < end; i++) {
            part_sum += arr[i];
        }
    
        free(arr);
        exit(part_sum, "");
    }

    // Parent process
    if (waitall(&finished, statuses) < 0) {
        printf("waitall failed\n");
        free(arr);
        exit(-1, "");
    }

    for (int i = 0; i < finished; i++) {
        total_sum += statuses[i];
    }

    printf("final sum: %d\n", total_sum);

    free(arr);
    exit(0, "");
}
