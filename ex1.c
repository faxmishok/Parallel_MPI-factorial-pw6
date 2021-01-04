#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

    unsigned long long int ans = 1;
    int n, rank, code, tag = 100;
    double etime;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,  &rank);

    if (rank == 0){
        printf("n  = "); fflush(stdout);
        scanf("%d", &n);
        code = MPI_Send(&n, 1, MPI_INTEGER, 1, tag, MPI_COMM_WORLD);
        code = MPI_Recv(&ans, 1, MPI_LONG, 1, tag, MPI_COMM_WORLD, &status);
        printf("n! = %llu\n", ans);
    }
    else if (rank == 1){
        code = MPI_Recv(&n, 1, MPI_INTEGER, 0, tag, MPI_COMM_WORLD, &status);
        for (int i = 1; i <= n; ++i) ans *= i;
        code = MPI_Send(&ans, 1, MPI_LONG, 0, tag, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}