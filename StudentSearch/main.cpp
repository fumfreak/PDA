#include <iostream>
#include <stdio>
#include <mpi.h>

#define nrstud 1000;

using namespace std;

int main(int argc, char* argv[])
{
    int rank, numtasks;

    char search[20] = NULL;
    int search_age = 0;
    float search_mark = 0;

    typedef struct{

        char name[20], surname[20];
        char sex;
        int age;
        float mark;
    } Student;

    Student lista[nrstud], recvbuf[count], rezultat[50];

    MPI_Datatype oldtypes[3], MPI_studentype;
    MPI_Aint offsets[3], extent;

    int blockcounts[3];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    offsets[0] = 0;
    oldtypes[0] = MPI_CHAR;
    blockcounts[0] = 3;

    MPI_Type_extent(MPI_CHAR, &extent);
    offsets[1] = 41* extent;
    oldtypes[1] = MPI_INT;
    blockcounts[1] = 1;

    MPI_Type_extent(MPI_INT, &extent);
    offsets[2] = extent;
    oldtypes[2] = MPI_FLOAT;
    blockcounts[2] = 1;

    MPI_Type_struct(3, blockcounts, offsets, oldtypes, &MPI_studentype);
    MPI_Type_commit(&MPI_studentype);

    if(rank == 0){

        int count = nrstud/numtasks;
        MPI_IScatter(&lista, count, MPI_studentype, &recvbuf, count, MPI_studentype, 0, MPI_COMM_WORLD);
        MPI_IRecv(&rezultat, 50, MPI_studentype, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    else{

    LOOP:for(int i = 0; i < count; i++){

            bool OK = false;

            if(search!=NULL)

                if(!(recvbuf[i].name == search)||(recvbuf[i].surname == search)){

                    i++;
                    goto LOOP;
                }

            if(search_age)

                if(recvbuf[i].age != search_age){

                    i++;
                    goto LOOP;
                }

            if(search_mark)

                if(recvbuf[i].mark < search_mark){

                    i++;
                    goto LOOP;
                }


            MPI_Send(&recvbuf+i, 1, MPI_studentype, 0, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();

    return 0;
}
