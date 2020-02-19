// Example 5_6 : Eigen
// Created by Oleksiy Grechnyev 2020

#include <iostream>
#include <Eigen/Dense>


//=========================
int main() {
    using namespace std;
    
    Eigen::MatrixXd m(2, 3); // Double matrix : 2 rows, 3 cols
    m << 1 , 2, 3, 4, 5, 6; // Provide values (overloaded operators << and ,)
    
    Eigen::VectorXd v(3);  // Column double 3-vector
    v << 1, 0, -1;
    
    cout << "m = " << m << endl;
    cout << "v = " << v << endl;
    cout << "m*v = " << m*v << endl;

    return 0;
}
