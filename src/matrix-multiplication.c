#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

const int MAIN_PID = 0;

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int pid;
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);

    int numberOfProcesses;
    MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcesses);

    int n;
    int m = numberOfProcesses;

    int *v;

    int *matrix;
    int *result;

    int *myMatrix;
    int myResult;

    v = malloc(n * sizeof(int));

    if (pid == MAIN_PID) {
        scanf("%d", &n);

        int numberOfIntsToRead = m * n;
        matrix = malloc(numberOfIntsToRead * sizeof(int));

        int i;
        for (i = 0; i < numberOfIntsToRead; i++) {
            scanf("%d", &matrix[i]);
        }

        for (i = 0; i < n; i++) {
            scanf("%d", &v[i]);
        }
    }

    MPI_Bcast(&n, 1, MPI_INT, MAIN_PID, MPI_COMM_WORLD);
    MPI_Bcast(v, n, MPI_INT, MAIN_PID, MPI_COMM_WORLD);

    myMatrix = malloc(n * sizeof(int));

    MPI_Scatter(matrix, n, MPI_INT, myMatrix, n, MPI_INT, MAIN_PID, MPI_COMM_WORLD);

    int i;
    for (i = 0; i < n; i++) {
        myResult += myMatrix[i] * v[i];
    }

    if (pid == MAIN_PID) {
        result = malloc(m * sizeof(int));
    }

    MPI_Gather(&myResult, 1, MPI_INT, result, 1, MPI_INT, MAIN_PID, MPI_COMM_WORLD);

    if (pid == MAIN_PID) {
        for (i = 0; i < m; i++) {
            printf("%d\n", result[i]);
        }
        free(result);
        free(matrix);
    }

    free(myMatrix);
    free(v);

    MPI_Finalize();
}