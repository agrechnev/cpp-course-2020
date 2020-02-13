//
// Created by  Oleksiy Grechnyev on 9/8/2017.
//

// Include the "own" header
#include "myfile.h"

// Don't forget the namespace !
namespace MyNS {
    /// Functions declared in myfile.h, defined here
    int add(int a, int b) {
        return a+b;
    }

    /// Global variable = evil !!!
    int x = 17; // Initialize here if needed
}