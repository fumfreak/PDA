
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>


#define width = 10000;
#define height = 10000;



cudaError_t addWithCuda(int *c, const int *a, const int *b, unsigned int size);

__global__ void Reduce_noise(int *devPtr, int *pitch )
{
    int i = blockIdx.x*blockDim.x + threadIdx.x;
	int j = blockIdx.y*blockDim.y + threadIdx.y;
	
	float x = ((devPtr + (j * pitch + i - 1) + (devPtr + (j * pitch + i + 1))/2;
	//devPtr + (j * pitch + i) = x;
	
	if (i == 0) {
		
	}

	if (i == width - 1) {

	}
	
	if (j == 0) {

	}

	if (j == height - 1) {

	}

	


    
}

int main()
{
    
	
	float *h_A[width][height];
	
	size_t pitch;
	float *devPtr;

	cudaMallocPitch (&devPtr, &pitch, width * sizeof(float), height * sizeof(float));
	cudaMemcpy2D(devPtr, pitch, h_A, pitch, width* sizeof(float), height* sizeof(float), cudaMemcpyHostToDevice);

	dim3 threadsPerBlock = (width, height);
	dim3 blocksPerGrid = 1;

	Reduce_noise<<<blocksPerGrid, threadsPerBlock>>>(devPtr, pitch);

	cudaMemcpy2D(h_A, pitch, devPtr, width* sizeof(float), height* sizeof(float), cudaMemcpyDeviceToHost);

	cudaFree(devPtr);


/*
	cudaError_t cudaMemcpy2D	(	void * 	dst, 
size_t 	dpitch,
const void * 	src,
size_t 	spitch,
size_t 	width,
size_t 	height,
enum cudaMemcpyKind 	kind	 
)	

dst 	- Destination memory address
dpitch 	- Pitch of destination memory
src 	- Source memory address
spitch 	- Pitch of source memory
width 	- Width of matrix transfer (columns in bytes)
height 	- Height of matrix transfer (rows)
kind 	- Type of transfer



cudaError_t cudaMallocPitch	(	void ** 	devPtr,
size_t * 	pitch,
size_t 	width,
size_t 	height
)

devPtr 	- Pointer to allocated pitched device memory
pitch 	- Pitch for allocation
width 	- Requested pitched allocation width (in bytes)
height 	- Requested pitched allocation height


*/
 
