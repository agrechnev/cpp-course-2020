// Cuda example add2 by Oleksiy Grechnyev
// This one uses classical memory management

#include <iostream>
#include <cmath>
#include <vector>

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
    int nF = n*sizeof(float);
    
    // Create data in the CPU memory (host)
    std::vector<float> x(n), y(n);
    
    // Initialize host
    for (int i=0; i<n; ++i) {
        x[i] = 2.0f;
        y[i] = 1.0f;
    }
    
    // Allocate GPU (device) memory
    float *dX, *dY;
    cudaMalloc(&dX, nF);
    cudaMalloc(&dY, nF);
    
    // Copy Device->Host
    cudaMemcpy(dX, x.data(), nF, cudaMemcpyHostToDevice);
    cudaMemcpy(dY, y.data(), nF, cudaMemcpyHostToDevice);
    
    // Automatic block size and number of blocks for max speed
//     int blockSize = 256;
//     int numBlocks = (n+ blockSize -1) / blockSize;

    // Smaller values for the demo
    int blockSize = 4;
    int numBlocks = 3;
    
    // Add
    add<<<numBlocks, blockSize>>>(n, dX, dY);
    
    // Not needed in this example
//     cudaDeviceSynchronize();
    
    // Copy Host->Device
    cudaMemcpy(y.data(), dY, nF, cudaMemcpyDeviceToHost);
    
    // Check the result: should be 0
    double maxE=0;
    for (int i = 0; i< n ; ++i)
        maxE = std::fmax(maxE, std::fabs(y[i] - 3.0f));
    std::cout << "maxE = " << maxE << std::endl;
    
    // Free memory
    cudaFree(dX);
    cudaFree(dY);
    
    return 0;
}
