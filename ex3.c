#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARR_SIZE 10

int main(int argc, char *argv[]){

    int block_length, rank, size;
    int arr[ARR_SIZE];
    unsigned long long int ans[] = { [0 ... 9] = 1 };
    double etime;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    block_length = ARR_SIZE / size;
    int data[block_length];

    if (rank == 0) {
        printf("Root process (P0) sending the array values: ");fflush(stdout);
        for (int i = 0; i < ARR_SIZE; i++) {
            arr[i] = i+1;
            printf("%d,", arr[i]);fflush(stdout);
        }
        puts("");fflush(stdout);
    }
    MPI_Scatter(arr, block_length, MPI_INTEGER, data, block_length, MPI_INTEGER, 0, MPI_COMM_WORLD);
   
    printf("\nP%d is calculating...\n", rank);fflush(stdout);
    for (int i = 0; i < block_length; i++) {
        for (int j = 1; j <= data[i]; ++j) {
            ans[i] *= j;
        }
        printf("%d! = %llu\n", data[i], ans[i]);fflush(stdout);
    }

    MPI_Finalize();
    return 0;
}