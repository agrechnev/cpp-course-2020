// Example 1_1 : Hello world (sort of)
// Created by Oleksiy Grechnyev 2017

// This is a comment
/* This is also a comment */

// Include the header file iostream (needed for file Input/Output)
// This is NOT called 'import' or 'add library' !!!
#include <iostream>

/*
 The main() function is the program entry point
 it can also be declared as main(int argc, char **argv) 
 returns int value, 0 for correct exit, 1 for error
 */
int main(){
    // cout (standard output stream) and
    // endl (End of line) are members of namespace std
    // They are defined in the header iostream
    std::cout << "Carthago delenda est." << std::endl;
    
    // Return 0 = OK
    return 0;
}