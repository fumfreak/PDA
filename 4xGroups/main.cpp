#include <iostream>
#include <stdio.h>
#include <mpi.h>

#define n 1000;

using namespace std;

int main(int argc, int argv){

    int a[n], rc, rank, ranks[4] = {1,2,3,4};
    int suma, produs, minim, maxim;

    MPI_Group Default, Add, Prod, Min, Max;
    MPI_Comm Add, Produs, Max, Min;

    rc = MPI_Init(&argc, &argv);

    if(rc != MPI_SUCCESS){
        printf("Error!")
        MPI_Abort(MPI_COMM_WORLD, rc);
    }

    MPI_Comm_Rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_group(MPI_COMM_WORLD, &Default);

    if(rank<17){

        if((rank%4 == 0)&&(rank!=0)){

            MPI_Group_incl(Default, 4, ranks, &Add);
        }
        else if(rank%4 == 1){

            MPI_Group_incl(Default, 4, ranks, &Prod);
        }
        else if(rank%4 == 2){

            MPI_Group_incl(Default, 4, ranks, &Min);
        }
        else if(rank%4 == 3){

            MPI_Group_incl(Default, 4, ranks, &Max);
        }
    }

    MPI_Comm_Create(MPI_COMM_WORLD, Add, &MPI_COMM_Add);
    MPI_Comm_Create(MPI_COMM_WORLD, Prod, &MPI_COMM_Produs);
    MPI_Comm_Create(MPI_COMM_WORLD, Min, &MPI_COMM_Min);
    MPI_Comm_Create(MPI_COMM_WORLD, Max, &MPI_COMM_Max);

    if(rank == 0){

        MPI_Reduce(&a, &suma, 1, MPI_int, MPI_SUM, 0, MPI_COMM_Add);
        MPI_Reduce(&a, &produs, 1, MPI_int, MPI_PROD, 0, MPI_COMM_Produs);
        MPI_Reduce(&a, &maxim, 1, MPI_int, MPI_MAX, 0, MPI_COMM_Max);
        MPI_Reduce(&a, &minim, 1, MPI_int, MPI_MIN, 0, MPI_COMM_Min);

        printf("Suma: %d \n Produs: %d \n Min: %d \n Max: %d", suma, produs, minim, maxim);
    }

    MPI_Finalize();

    return 0;
}
