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
//        printf("Hello! %d\n", n);

        scanf("%d", &n);

        int numberOfIntsToRead = m * n;
        matrix = malloc(numberOfIntsToRead * sizeof(int));

//        printf("Reading in %d, %d\n", numberOfIntsToRead, numberOfProcesses);

        int i;
        for (i = 0; i < numberOfIntsToRead; i++) {
            scanf("%d", &matrix[i]);
//            printf("1\n");
        }

        for (i = 0; i < n; i++) {
            scanf("%d", &v[i]);
//            printf("2\n");
        }

//        printf("Matrix\n");
//        for (i = 0; i < numberOfIntsToRead; i++) {
//            printf("%d\n", matrix[i]);
//        }
//
//        printf("Vector\n");
//        for (i = 0; i < n; i++) {
//            printf("%d\n", v[i]);
//        }
    }

//    printf("Done reading\n");

//    printf("About to broadcast pid %d\n", pid);
    MPI_Bcast(&n, 1, MPI_INT, MAIN_PID, MPI_COMM_WORLD);
    MPI_Bcast(v, n, MPI_INT, MAIN_PID, MPI_COMM_WORLD);

//    printf("Printing values for pid %d\n", pid);

//    int j;
//    for (j = 0; j < n; j++) {
//        printf("pid %d  v %d\n", pid, v[j]);
//    }

//    printf("Second broadcasting pid %d\n", pid);
//    printf("Done broadcasting pid %d\n", pid);

    myMatrix = malloc(n * sizeof(int));

    MPI_Scatter(matrix, n, MPI_INT, myMatrix, n, MPI_INT, MAIN_PID, MPI_COMM_WORLD);

//    printf("Scatter done for pid %d\n", pid);

//    printf("Matrix index 0, pid %d\n", pid);
//    printf("%d %d\n", pid, myMatrix[0]);

//    printf("My matrix pid %d   %d %d %d\n", pid, myMatrix[0], myMatrix[1], myMatrix[2]);

    int i;
    for (i = 0; i < n; i++) {
        myResult += myMatrix[i] * v[i];
//        printf("pid %d  i %d  myMatrix %d  v %d  myResult %d\n", pid, i, myMatrix[i], v[i], myResult);
    }

//    printf("result pid %d %d\n", pid, myResult);


//    printf("Starting gather\n");

    if (pid == MAIN_PID) {
        result = malloc(m * sizeof(int));
    }

    MPI_Gather(&myResult, 1, MPI_INT, result, 1, MPI_INT, MAIN_PID, MPI_COMM_WORLD);

//    printf("Gather done\n");

    if (pid == MAIN_PID) {
        for (i = 0; i < m; i++) {
            printf("%d\n", result[i]);
        }
//        free(result);
//        free(matrix);
    }

//    free(myMatrix);
//    free(myResult);
//    free(v);

    MPI_Finalize();
}