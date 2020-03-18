#include <iostream>

#include "a.h"
#include "B.h"

using namespace std;

int main(){
    cout << "This is the main program !!!" << endl;
    int c = funA(7, 3);
    cout << "c = " << c << endl;
    
    B b(17);
    b.hello();
}