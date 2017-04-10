#include <iostream>
#include <mpi.h>
#include <stdio>

#define nrproc 1000;
#define nrelem 1000;

using namespace std;

int main(int argc, int argv)
{
    int a[nrelem][nrelem], b[nrelem][nrelem], c[nrelem][nrelem], temp[nrelem], sum[nrelem];
    int rc, rank, x;

    rc = MPI_Init(&argc, &argv);

    if(rc != MPI_SUCCESS){
        printf("Error!")
        MPI_Abort(MPI_COMM_WORLD, rc);
    }

    MPI_Comm_rank (MPI_COMM_WORLD,&rank);

    if(rank == 0){

        for(int i = 0; i < nrproc; i++){

               for(int j = 0; j < nrelem; j++)
                  temp[j] = a[i][j];

               MPI_Send(&temp, nrelem, MPI_int, i, 0, MPI_COMM_WORLD);

               for(j = 0; j < nrelem; j++)
                  temp[j] = b[i][j];

               MPI_Send(&temp, nrelem, MPI_int, i, 0, MPI_COMM_WORLD);
        }

        for(int i = 0; i < nrproc; i++){

               MPI_Recv(&temp, nrelem, MPI_int, i, 0, MPI_COMM_WORLD);
               for(int j = 0; j < nrelem; j++)
                  c[i][j] = temp[j];
        }

        for(i = 0; i < nrelem ; i++){
            for(j = 0; j < nrelem; j++)
                printf("%d", c[i][j]);
            printf("\n");
    }
    else {

        MPI_Recv(&temp, nrelem, MPI_int, 0, 0, MPI_COMM_WORLD);

        for(int i = 0; i < nrelem; i++)
            sum[i] = temp[i];

        MPI_Recv(&temp, nrelem, MPI_int, 0, 0, MPI_COMM_WORLD);

        for(int i = 0; i < nrelem; i++)
            sum[i] += temp[i];

        MPI_Send(&sum, nrelem, MPI_int, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
