// Example 2_1 : Built-in types, numeric limits.
// Created by Oleksiy Grechnyev 2017

#include <iostream>
#include <limits>
// <iomanip> has std::setw(), std::setfill()  for formatting output
#include <iomanip>

int main(int argc, char **argv){
    using namespace std;
    
    // Demonstrate the danger of mixing signed and unsigned numbers
    // I use the block, so that names a, b do not leak
    {
        cout << "Adding int and unsigned :" << endl;
        int a = -10;
        unsigned int b = 1;
        cout << " int a = -10; unsigned int b = 1;" << endl;
        cout << "a + b = " << a + b << endl << endl;
    }
    
    {
        // Numeric limits
        cout << "Numeric limits :" << endl;
        cout << "long long :" << endl;
        // Or the old, pre-C++ 11 syntax : 
        // typedef long long MyType;
        using MyType = long long;  // You can try different types here
        cout << boolalpha; // Write bool as true/false
        cout << "sizeof(MyType) = " << sizeof(MyType) << endl;
        cout << "is_signed = " << numeric_limits<MyType>::is_signed << endl;
        cout << "is_integer = " << numeric_limits<MyType>::is_integer << endl;
        cout << "is_exact = " << numeric_limits<MyType>::is_exact << endl;
        cout << "has_infinity = " << numeric_limits<MyType>::has_infinity << endl;
        cout << "has_quiet_NaN = " << numeric_limits<MyType>::has_quiet_NaN << endl;
        cout << "digits = " << numeric_limits<MyType>::digits << endl;
        cout << "digits10 = " << numeric_limits<MyType>::digits10 << endl;
        cout << "lowest() = " << numeric_limits<MyType>::lowest() << endl;
        cout << "min() = " << numeric_limits<MyType>::min() << endl;
        cout << "max() = " << numeric_limits<MyType>::max() << endl;
    }
    
    {
        // Let's try the same for long double
        cout << endl << "long double :" << endl;
        // I can re-use MyTtype because of blocks
        using MyType = long double;
        cout << "sizeof(MyType) = " << sizeof(MyType) << endl;
        cout << "is_signed = " << numeric_limits<MyType>::is_signed << endl;
        cout << "is_integer = " << numeric_limits<MyType>::is_integer << endl;
        cout << "is_exact = " << numeric_limits<MyType>::is_exact << endl;
        cout << "has_infinity = " << numeric_limits<MyType>::has_infinity << endl;
        cout << "has_quiet_NaN = " << numeric_limits<MyType>::has_quiet_NaN << endl;
        cout << "digits = " << numeric_limits<MyType>::digits << endl;
        cout << "digits10 = " << numeric_limits<MyType>::digits10 << endl;
        cout << "min_exponent = " << numeric_limits<MyType>::min_exponent << endl;
        cout << "max_exponent = " << numeric_limits<MyType>::max_exponent << endl;
        cout << "min_exponent10 = " << numeric_limits<MyType>::min_exponent10 << endl;
        cout << "max_exponent10 = " << numeric_limits<MyType>::max_exponent10 << endl;
        cout << "lowest() = " << numeric_limits<MyType>::lowest() << endl;
        cout << "min() = " << numeric_limits<MyType>::min() << endl;
        cout << "max() = " << numeric_limits<MyType>::max() << endl;
    
        cout << "epsilon() = " << numeric_limits<MyType>::epsilon() << endl;
        cout << "infinity() = " << numeric_limits<MyType>::infinity() << endl;
        cout << "quiet_NaN() = " << numeric_limits<MyType>::quiet_NaN() << endl;
    }
    
    // Other types, literals
    cout << endl << "Other types, literals :" << endl;
    // bool
    {
        cout << "bool :" << endl;
        cout << endl << "sizeof(bool) = " << sizeof(bool) << endl;
        bool b = 12;  // 12 is considered true and changed to 1
        cout << boolalpha << "b = " << b << endl;    // Prints true
        cout << noboolalpha << "b = " << b << endl;  // Prints 1, not 12
        cout << "(int)b = " << (int)b << endl;  // Prints 1, not 12
    }
    
    // A small difference between 2 big doubles
    {
        cout << "Small difference between 2 big doubles :" << endl;
        double a = 1.0e15;
        double b = 1.0e15 + 0.1234;
        cout << endl << "b - a = " << b-a << endl;
    }
    
    // Literals
    {
        cout << "Literals :" << endl;
        cout << "1234 = " << 1234 << endl; // int
        cout << "4000000000u = " << 4000000000u << endl; // unsigned
        // Note the quotes to separate digits !
        cout << "8'000'000'000ll = " << 8'000'000'000ll << endl; // long long
        cout << "8000000000ull = " << 8000000000ull << endl; // unsigned long long
        cout << "1.23e-4 = " << 1.23e-4 << endl; // double
        cout << "1.23e-4f = " << 1.23e-4f << endl; // float
        cout << "1.23e-4l = " << 1.23e-4l << endl; // long double
        cout << "'A' = " << 'A' << endl; // char
        cout << "\"Dina Meyer\" = " << "Dina Meyer" << endl; // const char [11]
        
        cout << "0xFF = " << 0xFF << endl; // int (HEX)
        cout << "0xFF = 0x" << hex << 0xFF << dec << endl; // hex print, dec to switch back to decimal !!!
        cout << "0xFF = 0x" << hex << setw(4) << setfill('0') << 0xFF << dec << endl; 
        cout << dec;
        
        cout << "0100 = " << 0100 << endl; // int (OCTAL)
        cout << "0100 = 0" << oct << 0100 << dec << endl; // int (OCTAL)
        
        cout << "0b100 = " << 0b100 << endl; // int (BIN)
    }

    return 0;
}