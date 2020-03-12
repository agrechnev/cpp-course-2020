// Example 8_3 : numerics
// Created by Oleksiy Grechnyev 2020

#include <numeric>
#include <iostream>
#include <vector>


int main(){
    using namespace std;
        
    {
        // sum
        cout << "\naccumulate : " << endl;
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
    
    {
        // iota
        cout << "\niota : " << endl;
        vector<double> v(10);
        // FIll array with 2 .. 11
        iota(v.begin(), v.end(), 2.);  
        for (double d : v )
            cout << d << " ";
        cout << endl;
    }
    
    {
        //Scalar product of v1, v2
        vector<double> v1{0.5, -2, 1};
        vector<double> v2{1, 1.5, 1};
        cout << "\ninner_product :" << endl;
        cout << "v1*v2 = " << inner_product(cbegin(v1), cend(v1), cbegin(v2), 0.) << endl;
    }
    
    

    return 0;
}
