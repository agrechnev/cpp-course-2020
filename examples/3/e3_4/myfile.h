// Or you can start with
// #pragrma once

// Classic include guard
#ifndef _MYFILE_H_
#define _MYFILE_H_

#include <iostream>

// Using namespaces is a good practice, especially in libraries
namespace MyNS {
    /// Functions declared here, defined in myfile.cpp
    int add(int a, int b);

    /// Global variable = evil !!! Declared here, defined in myfile.cpp .
    extern int x;

    /// This is OK with constexpr, but not const ! No need to put anything to myfile.cpp .
    constexpr int GLOBAL_CONST = 666;

    /// If we really really want to define (implement) a function in myfile.h, what do we do ?

    // Error ! Multiple definitions at link stage !
    /* void hello0(){
        std::cout << "hello0()" << std::endl;
    } */

    /// Make it inline
    inline void hello1(){
        std::cout << "hello1()" << std::endl;
    }

    /// static will also work
    static void hello2(){
        std::cout << "hello2()" << std::endl;
    }

    // Or how about anonymous namespace ?
    namespace {
        void hello3(){
            std::cout << "hello3()" << std::endl;
        }
    }
}

#endif