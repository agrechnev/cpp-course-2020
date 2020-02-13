// Example 3_2 : functions, overloading
// Created by Oleksiy Grechnyev 2017

#include <iostream>
#include <string>
#include <vector>
#include <array>

using namespace std;

//=========================
// Block 1 : simple functions

/// No parameters, no return type (void)
void hello(){
    cout << "Take a look to the sky just before you die \n";
    cout << "It is the last time you will" << endl;
}

/// Simple function: adds a and b
/// static means that the function is local to this cpp file and is not exported
static int add1(int a, int b){
    int c = a + b;
    // A side effect! prints something to cout
    cout << "add1() is called: side effect !" << endl;
    // Return value optimization: usually no copy/move when returning a local
    // Even if it is of a fancy class like vector
    return c;
}

/// We can also specify the return type like this (no more static)
auto add2(int a, int b) -> int {
    return a + b;
}

/// Or like this (C++ 14)
auto add3(int a, int b){
    return a + b;
}

/// Or like this (C++ 14)
decltype(auto) add4(int a, int b){
    return a + b;
}

/// This version uses default parameter
int add5(int a, int b = 10){
    return a + b;
}

//=========================
// Block 2 : reference parameters

/// string & s is a reference, we can change it
void changeString(string & s){
    s = "Hello " + s;
}

/// class (non-primitive) parameters which should not be changed
/// are typically passed as const reference, like (const sring &)
/// It helps avoid copying
/// Note: we return string, not string & !!!
/// Return by reference is used by class getters and such
string addStrings(const string & s1, const string & s2){
    return s1 + s2;
}

//=========================
// Block 3 : overloading

/// 3 functions have the same name !
void print(int a) {
    cout << "print(int) called !" << endl;
    cout << a << endl;
}

void print(int a, double b) {
    cout << "print(int, double) called !" << endl;
    cout << a << " " << b << endl;
}

/// We pass const string & as usual
void print(const string & s) {
    cout << "print(const string &) called !" << endl;
    cout << s << endl;
}

//=========================
// Block 4 : Templates

/// Add two numbers : template version
template <typename T>  // OR "template <class T>"
T tmplAdd(T a, T b) {
    return a + b;
}


/// Print a container with templates (will not work with non-containers !)
template <typename T>
void printContainer(const T & c) {
    /// Range for works with any container !
    for (const auto & el : c)
        cout << el << " ";
    cout << endl;
}

//=========================
int main() {
    {
        cout << "Functions 1 : simple functions\n\n";
        
        // Let's call everything
        hello();
        cout << "add1(3, 17) = " << add1(3, 17) << endl;
        cout << "add2(3, 17) = " << add2(3, 17) << endl;
        cout << "add3(3, 17) = " << add3(3, 17) << endl;
        cout << "add4(3, 17) = " << add4(3, 17) << endl;
        cout << "add5(3, 17) = " << add5(3, 17) << endl;
        cout << "add5(3) = " << add5(3) << endl; // Gives 3 + 10 == 13
    }

    {
        cout << "\nFunctions 2 : passing arguments by reference \n\n";

        string s1 = "Medea";
        changeString(s1); // Now we change s1
        cout << "s1 = " << s1 << endl;

        string s2 = "Hello ";
        string s3 = "there !";
        cout << "addStrings(s2, s3) = " << addStrings(s2, s3) << endl;
    }

    {
        cout << "\nFunctions 3 : overloading \n\n";

        // One of the 3 overloads is selected from argument types
        print(17); // print(int)
        print(22.8); // print(int), double is converted to int
        print(4, 5.7); // print(int, double)
        print(13, 23); // print(int, double), int is converted to double
        print(string("Nel Zelpher")); // print(string)
        print("Maria Traydor"); // print(string), const char * is converted to string

        // If there is no possible conversion
        // Or the choice is too ambiguous, you get a compiler error
    }
    
    {
        cout << "\nFunctions 4 : templates \n\n";

        // tmplAdd
        cout << "tmplAdd(3, 4) = " << tmplAdd(3, 4) << endl;
        cout << "tmplAdd(3.1, 4.2) = " << tmplAdd(3.1, 4.2) << endl;
        cout << "tmplAdd(3, 4.2) = ERROR !" << endl;
        cout << "tmplAdd(3., 4.2) = " << tmplAdd(3., 4.2) << endl;
        cout << "tmplAdd<double>(3, 4.2) = " << tmplAdd<double>(3, 4.2) << endl;
        // Note: You need to create string() explicitly, does not work with string literals !
        cout << "tmplAdd(string(\"Hello \"), string(\"World !\")) = " << tmplAdd(string("Hello "), string("World !")) << endl;
        // ... Unless you give the explicit type
        cout << "tmplAdd<string>(\"Hello \", \"World !\") = " << tmplAdd<string>("Hello ", "World !") << endl; // COnverted to string
        
        
        // printContainer
        // Works even with C-arrays ! (But NOT pointers !)
        int a[] = {3, 10, 17};
        cout << "\na = ";
        printContainer(a);
//         printContainer((char *)a);  // ERROR ! Does not work with pointers! No way to determine array size !
        
        vector<char> b{'x', 'y', 'z'};
        cout << "b = ";
        printContainer(b);
        
        array<string, 3> c{"red", "green", "blue"};
        cout << "c = ";
        printContainer(c);
    }

    return 0;
}
