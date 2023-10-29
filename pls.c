#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define NUMSTEPS 1000000

int main(int argc, char** argv) {
    int i, rank, size;
    double x, pi, sum = 0.0;
    double step = 1.0 / (double) NUMSTEPS;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int local_steps = NUMSTEPS / size;
    int local_start = rank * local_steps;
    int local_end = local_start + local_steps;
    x = (local_start + 0.5) * step;

    for (i = local_start; i < local_end; i++) {
        x += step;
        sum += 4.0 / (1.0 + x * x);
    }

    MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        pi *= step;
        printf("PI is %.20f\n", pi);
    }

    MPI_Finalize();

    return 0;
}
