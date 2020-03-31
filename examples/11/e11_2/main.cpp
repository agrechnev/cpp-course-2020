// Example 11.1 Template : variadic, metaprogramming
// Created by Oleksiy Grechnyev 2017
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

using namespace std;
//==============================
// Template functions
//==============================
// Variadic

// Size of the variadic pack
template <typename... Args>
size_t packSize(const Args & ... pack){
    return sizeof...(pack);
//    return sizeof...(Args);  // Same result
}

// print: print all args to stdout
// Non-variadic print (to break the recursion)
template <typename T>
void print(const T & t){
    cout << t << endl;
}
// The variadic overload
template <typename T, typename... Args>
void print(const T & t, const Args & ... rest){
    cout << t << endl;
    print(rest...);
}

// print2: print all args to stdout using expansion (UGLY)
template <typename... Args>
void print2(const Args & ... args){
    int temp[] = {(print(args), 0)...};
}

// printSq: print numerical args to stdout, squared
template <typename T>
T square(const T & t){
    return t*t;
}
template <typename... Args>
void printSq(const Args & ... args){
    print(square(args)...);
}

// A simple ostream impementation of printf
template <typename...  Params>
void printfCPP(std::ostream & os, const std::string & fmt, Params... p) {
    constexpr size_t SIZE = 1000;
    static char buffer[SIZE];  // Hidden global buffer = ugly
    std::snprintf(buffer, SIZE, fmt.c_str(), p...);
    os << buffer;
}

//==============================
// Advanced

/// Compile-time factorial from Wikipedia
// Induction
template <int N>
struct Factorial {
  static const int value = N * Factorial<N - 1>::value;
};
// Base case via template specialization:
template <>
struct Factorial<0> {
  static const int value = 1;
};

/// Print value or pointer
template<typename T>
void katanaImpl(const T & val, true_type){   // Pointer
    cout << "Pointer : " << val << " , *val = "<< *val << endl;
}
template<typename T>
void katanaImpl(const T & val, false_type){   // Not Pointer
    cout << "Value : " << val << endl;
}
template<typename T>
void katana(const T & val){
    katanaImpl(val, is_pointer<T>());  // true_type or false_type
}

//==============================
// main() 
//==============================
int main() {
    {
        cout << "\nVariadic templates : \n\n";
        cout << boolalpha;

        cout << "packsize = " << packSize(13, "Carrot", 91, 'A', true, 'Z', 3.14159) << endl;

        cout << "\nprint() :\n";
        print(13, "Carrot", 91, 'A', true, 'Z', 3.14159);

        cout << "\nprint2() :\n";
        print2(13, "Carrot", 91, 'A', true, 'Z', 3.14159);

        cout << "\nprintSq() :\n";
        printSq(1, 2, 3.14159);

        printfCPP(cout, "%s : %d * %d = %d\n", "Hello", 3, 7, 3*7);
    }

    {
        cout << "\nAdvanced templates aka metaprogramming : \n\n";

        cout << "Factorial<5>::value = " << Factorial<5>::value << endl;

        cout << "\nkatana():\n";
        int i = 17;
        katana(19);
        katana(i);
        katana(&i); // Pointer
    }
    return 0;
}
