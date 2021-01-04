#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
#include <time.h>
#include <string.h>

#define ARR_SIZE 10

int main(int argc, char *argv[]) {

	int rank, code, tag = 100;
	int arr[ARR_SIZE];
    unsigned long long ans[] = { [0 ... 9] = 1 }; //init all elements to 1 to calc factorial
    double etime;
	MPI_Status status; 

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if (rank == 0){
		for (int i = 0; i < ARR_SIZE; i++) arr[i] = i+1;
        etime = MPI_Wtime();
        code = MPI_Send(arr, ARR_SIZE, MPI_INTEGER, 1, tag, MPI_COMM_WORLD);
        code = MPI_Recv(ans, ARR_SIZE, MPI_LONG, 1, tag, MPI_COMM_WORLD, &status);
        etime = MPI_Wtime() - etime;
        printf("Elapsed time is %fs\n", etime);
        for (int i = 0; i < ARR_SIZE ; i++)
            printf("%d! = %llu\n", arr[i], ans[i]);
	}
	else if (rank == 1) {
        code = MPI_Recv(arr, ARR_SIZE, MPI_INTEGER, 0, tag, MPI_COMM_WORLD, &status);
        for (int i = 0; i < ARR_SIZE; i++) {
            for (int j = 1; j <= arr[i]; ++j) {
                ans[i] *= j;
            }
        }
        code = MPI_Send(ans, ARR_SIZE, MPI_LONG, 0, tag, MPI_COMM_WORLD);
	}
	
	MPI_Finalize();
	return 0;
}