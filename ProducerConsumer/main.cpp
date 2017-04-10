#include <iostream>
#include <stdio.h>
#include <mpi.h>
#include <cstdlib.h>

#define X 100;


using namespace std;

void refill(int* b){

    for(int j = 0; j < X; j++)
        if(&(b + j) == 0)
            &(b + j) = 1;
        else &(b + j) = 0;
}

int main(int argc, char* argv)
{
    int a[X], rank, numtasks, c[X];

    MPI_Datatype MPI_produse;
    MPI_Type_contiguous(X, MPI_int, &MPI_produse);
    MPI_Type_commit(&MPI_produse);
    MPI_produse b[numtasks];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    MPI_Bcast(&a, X, MPI_produse, 0, MPI_COMM_WORLD);

    while(1){

        if(rank){

            for(int i = 0; i < X; i++){

                int OK = rand()%2;
                if(OK)
                    a[i] = 0;
            }
        }

        MPI_Barrier(MPI_COMM_WORLD);

        if(rank==0){

            MPI_Gather(&a, 1, MPI_produse, &b, 1, MPI_produse, 0, MPI_COMM_WORLD);

            for(int i = 0; i < numtasks; i++){

                refill(&b[i]);
                MPI_Send(&b[i], 1, MPI_produse, i, 0, MPI_COMM_WORLD);
            }
        }

        if(rank){

            MPI_Recv(&c, 1, MPI_produse, 0, 0, MPI_COMM_WORLD);
            for(int i = 0; i < X; i++){

                a[i] = a[i] + c[i];
                if(a[i] > 1)
                    printf("Error 404! Processor no.%d", rank);
            }
        }
    }

    MPI_Finalize();

    return 0;
}
