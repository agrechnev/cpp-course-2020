// Example 3_4 : headers
// Created by Oleksiy Grechnyev 2017

#include <iostream>
#include <string>
#include <vector>

#include "myfile.h"   // Header from this project
// Or, probably better style:
// #include "./myfile.h"

int main() {
    using namespace std;
    using namespace MyNS;

    cout << "Headers example \n\n";
    cout << "add(3, 17) = " << add(3, 17) << endl;
    cout << "x = " << x << endl; // Global var from myfile
    cout << "GLOBAL_CONST = " << GLOBAL_CONST << endl; // Global const from myfile

    hello1();
    hello2();
    hello3();

    return 0;
}

