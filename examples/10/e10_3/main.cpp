// Example 10.3 : CTPL thread pool.
// Note: You must load git modules, see the root README.md !
// Created by Oleksiy Grechnyev, IT-JIM 2020

#include <iostream>
#include <sstream>
#include <vector>

#include "ctpl_stl.h"

using namespace std;

//==============================
int main() {
    cout << "Example 10.3 : CTPL thread pool" << endl;

    // Numbers from 1 to 100000
    // Their sum is 5000050000
    constexpr int nData = 100000;
    vector<long> data(nData);
    for (int i = 0; i < nData; ++i) {
        data[i] = i + 1;
    }

    // Now we want to calculate the sum with the thread pool

    // First, create the pool
    int nThread = 7; // Number of threads to use in the pool
    ctpl::thread_pool pool(nThread);
    cout << "nThread = " << pool.size() << endl;

    // Calculate block size : number of elements per thread
    int bSize = nData / nThread;
    if (nData % nThread)
        ++bSize;

    // Launch the threads
    vector<future<long>> partialSums;
    for (int j = 0; j < nThread; ++j) {
        // Calculate first:last range
        int i1 = j * bSize;
        int i2 = min((j + 1) * bSize, nData);
        partialSums.push_back(pool.push([i1, i2, &data](int threadID) -> long {
            ostringstream oss;
            oss << "Thread " << threadID << " :  [" << i1 << ": " << i2 << "]" << endl;
            cerr << oss.str();
            // Calculate a partial sum
            long s = 0;
            for (int i = i1; i < i2; ++i) {
                s += data[i];
            }
            return s;
        }));
    }

    // Wait for the threads to finish and get the total sum
    long sum = 0;
    for (future<long> & f : partialSums)
        sum += f.get();

    cout << "sum = " << sum << " = 5000050000" << endl; // Must be 5000050000

    return 0;
}
