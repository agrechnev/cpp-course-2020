// Cuda example add1 by Oleksiy Grechnyev
// This one uses cudaMallocManaged() : unified CPU/GPU memory

#include <iostream>
#include <cmath>

// Kernel: This runs on the GPU (device) !
__global__
void add(int n, float *x, float *y){
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    int stride = blockDim.x * gridDim.x;
    printf("thread = %d/%d, block = %d/%d, index = %d/%d \n", threadIdx.x, blockDim.x, blockIdx.x, gridDim.x, index, stride);
    for (int i = index; i< n ; i += stride)
        y[i] += x[i];
}

// This runs on the CPU (host)
int main(){
    int n = 1 << 20; // 1024**2
    
    // Alloc unified CPU/GPU memory
    float *x, *y;
    cudaMallocManaged(&x, n*sizeof(float));
    cudaMallocManaged(&y, n*sizeof(float));
    
    // Initialize data
    for (int i = 0; i< n ; ++i) {
        x[i] = 1.0f;
        y[i] = 2.0f;
    }
   
   
    // Automatic block size and number of blocks for max speed
//     int blockSize = 256;
//     int numBlocks = (n+ blockSize -1) / blockSize;

    // Smaller values for the demo
    int blockSize = 4;
    int numBlocks = 3;
    
    // Add
    add<<<numBlocks, blockSize>>>(n, x, y);
    
    // Wait for GPU, needed here because of cudaMallocManaged()
    cudaDeviceSynchronize();
    
    // Check the result: should be 0
    float maxE=0;
    for (int i = 0; i< n ; ++i)
        maxE = std::fmax(maxE, std::fabs(y[i] - 3.0f));
    std::cout << "maxE = " << maxE << std::endl;
    
    // Free memory
    cudaFree(x);
    cudaFree(y);
    
    return 0;
}
