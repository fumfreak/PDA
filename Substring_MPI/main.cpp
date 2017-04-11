#include <iostream>
#include <mpi.h>

#define N = 1000;
#define M = 100;
#define P = 100;

using namespace std;

bool Look_For(int flag){

    if((strlen(querry) - flag) < (N/numtasks))
        for(int i = flag, i < strlen(querry); i++){

            if(text[(i - flag)+ gg] != (querry + flag))
                return 0;
            else if(i == strlen(querry))
                return 1;
        }
        else {

            int OK = 1;

            for(int i = flag, i < strlen(querry); i++){

                if(text[(i - flag)+ gg] != (querry + flag))
                    OK = 0;

            if(OK)
                return Look_For(i);
        }
}


int compute(char* text, int gap, char* querry){

    for(int i = gap; i <= gap + N/numtasks; i++){

        int success = 0;
        if( test(&text + i) ){

            success++;
            if (success == strlen(querry)){

                return i - success;
            }
            else
                if((i == (gap + N/numtasks))&&(rank!=numtasks)){

                        MPI_Send(&success, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);

                }
        }
        else success = 0;


        MPI_Recv(&flag, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);

        if(flag)
            if (Look_For(flag))
                return i - success;

    }

    return -1;
}

int main(int argc, char* argv)
{
    char text[N], querry[M];
    int rank, numtasks, result[P], incr = 0;
    int OK[numtasks];
    int flag = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    if(rank == 0){

        for(int i = 0; i < N/numtasks; i++){

            MPI_Send(&text, N, MPI_CHAR, i, 0, MPI_COMM_WORLD);
            MPI_Send(&querry, M, MPI_CHAR, i, 0, MPI_COMM_WORLD);
            MPI_Recv(&OK[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);

            if(OK[i] != -1){

                result[incr] = OK[i];
                incr++;
            }
        }
    }

    if(rank){

        MPI_Recv(&text, N, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        MPI_Recv(&querry, M, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        int gap = rank*(N/numtasks);
        OK = compute(&text, gap, &querry);
        MPI_Send(&OK, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

    }

    MPI_Finalize();
    
    return 0;
}

