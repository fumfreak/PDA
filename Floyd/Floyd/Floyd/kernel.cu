
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <cstdlib>

#define dim 10;
#define RAND_MAX = 500;

cudaError_t addWithCuda(int *c, const int *a, const int *b, unsigned int size);

__global__ void addKernel(int *A, int *B)
{
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	int j = blockIdx.y * blockDim.y + threadIdx.y;

	for(int k = 0; k < dim; k++){
		_syncthreads();
		if(A[i+dim] + A[j+dim] < A[i+j])
			B[i+j] = A[i+dim] + A[j+dim];
	}
		
    
}

void init(int A){
	
	for(int i = 0; i < dim; i++)
		for(int j = 0; j < dim; j++)
			A[i][j] = rand();
}

void write(int A){

	for (int i = 0; i < dim; i++){
		for (int j = 0; j < dim; j++)
			printf("%d", A[i][j]);
		printf("/n");
	}
}


int main()
{
	int *d_A, *h_A, *d_B;
	int size = dim*dim;

	cudaMalloc(&d_A, size);	
	cudaMalloc(&d_B, size);
	
	cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);

	dim3 threadBlocks (n, n);

	addKernel <<<1, threadBlocks>>> (d_A);

	cudaMemcpy(h_A, d_B, size, cudaMemcpyDeviceToHost);
	
	write(h_A);

	cudaFree(d_A);
	cudaFree(d_B);
	
	return cudaStatus;
}

