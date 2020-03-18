#include <iostream>

#include "./a.h"

int funA(int x, int y){
    std::cout << "funA(" << x << ", " << y << ")" << std::endl;
    return x*y;
}