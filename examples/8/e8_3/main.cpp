// Example 8_3 : numerics
// Created by Oleksiy Grechnyev 2020

#include <numeric>
#include <iostream>
#include <vector>


int main(){
    using namespace std;
        
    {
        vector<double> v{1., 2., 4., 7., 10.};
        // Sum all the elements
        cout << "sum = " << accumulate(cbegin(v), cend(v), 0.) << endl;
    }

    return 0;
}
