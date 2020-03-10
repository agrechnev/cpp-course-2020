// Example 8_3 : numerics
// Created by Oleksiy Grechnyev 2020

#include <numeric>
#include <iostream>
#include <vector>


int main(){
    using namespace std;
        
    {
        // sum
        vector<double> v{1., 2., 4., 7., 10.};
        
        // Sum all elements
        cout << "sum = " << accumulate(cbegin(v), cend(v), 0.) << endl;
        
        // Sum all elements starting with 1. (adds 1).
        cout << "sum (starting 1) = " << accumulate(cbegin(v), cend(v), 1.) << endl;
        
        // Product of all elements, with lambda
        auto bop = [](double x, double y)->double{
            return x*y;
        };
        cout << "prod1 = " << accumulate(cbegin(v), cend(v), 1., bop) << endl;
        
        // Product of all elements, with standard function multiplies
        cout << "prod2 = " << accumulate(cbegin(v), cend(v), 1., multiplies<int>()) << endl;
    }
    
    

    return 0;
}
