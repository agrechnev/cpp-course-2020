// Example 6.1 : Buil-in arrays, std::array, simple algorithms
// Created by Oleksiy Grechnyev 2017
// Class Tjej is used here, it logs Ctors and Dtors


#include <iostream>
#include <string>
#include <array>
#include <experimental/array>
#include <algorithm>
#include <memory>

//#include "Tjej.h"

using namespace std;

//=======================================
/// Print a container. Works also with built-in arrays.
/// pair from maps cannot be printed like this
template <typename C>
void print(const C & c){
    for (const auto & e : c)
        cout << e << " ";
    cout << endl;
}
//==============================
/// Print a container. This version uses iterators
template <typename C>
void print2(const C & c){
    for (auto it = begin(c); it != end(c); ++it)
        cout << *it << " ";
    cout << endl;
}
//==============================
// Get array size, template magic !
// Works only with arrays, not pointers !!!
// Uses const ref to array
template <typename T, size_t SIZE>
size_t getArraySize(const T (&) [SIZE]){
    return SIZE;
}
//==============================
int main(){
    {
        cout << "-----------------------------";
        cout << "\nBuilt-in arrays :  \n\n";
        
        // Array definition
        int a[12];
        double b[3] = {0.1, 1.2, 2.3};
        string weapons[] = {"Sword", "Axe", "Bow"};
        constexpr int SIZE = 1024*16;    // SIZE must be constexpr
        char buffer[SIZE];
        // C-string is a char array or char *, terminated with \0
        char cString[] = "This is a null-terminated C-string";   // Automatically ended with \0
        double matrix[10][10];      // Multidimensional

        // Using indices : starts with 0 !!!
        for (int i=0; i<12; ++i)
            a[i] = i*i;

        // Print using our template print
        cout << "a = ";
        print(a);  // Note that print receives a as a ref to array
        cout << "\nweapons = ";
        print(weapons);
        cout << "\nweapons = ";
        print2(weapons);   // print2 also works !

        // Implicitly convert array to pointer
        char * message = cString;
        cout << "message = " << message << endl;

        cout << "\nArrays and sizeof() : \n";
        cout << "Size in bytes : sizeof a = " << sizeof a << endl;
        cout << "Number of elements = " << sizeof a/sizeof(int) << endl;

        // References and pointers to arrays
        // This is stupid stuff, but funny
        // Size must be always fixed in array refs and pointers !
        // This template receives a by reference
        cout << "\ngetArraySize(a) = " << getArraySize(a) << endl;
        int (& aRef1) [12] = a; // Weird syntax, is't it?
        int (* aPtr1) [12] = &a;
        // It gets simpler if we create a type alias
        using ArrayType = int [12];
        ArrayType & aRef2 = a;
        ArrayType * aPtr2 = &a;

        // Iterator and range for
        const string names[] = {"Karen", "Lucia", "Anastasia", "Margaret", "Alice"};
        cout << "\nPrinting with range for:\n";
        for (const string & s : names)  // It actually uses begin(), end()
            cout << s << " ";

        cout << "\n\nPrinting with pointers :\n";
        const string * eit = names + 5;   // Position just after the last element
        for (const string * it = names; it != eit; ++it)
            cout << *it << " ";

        cout << "\n\nPrinting with iterators (pointers actually) :\n";
        for (const auto *it = begin(names); it != end(names); ++it)
            cout << *it << " ";
        cout << endl;

        // Dynamic memory in heap
        // Pointers are not real arrays!
        // You cannot use range for, begin(), end() for pointers !
        // Absolutely no way to tell the size !
        // sizeof(data) returns pointer size (8 bytes) and not array size !
        int size = 17;                  // Not constexpr
        int * data = new int[size];
        for (int i=0; i<size; ++i)
            data[i] = i*i; // We can use operator[] with pointers

        cout << "\nDynamic array : data = ";
        for (int i=0; i<size; ++i)
            cout << data[i]<< " ";
        cout << endl;
        cout << "sizeof(data) = " << sizeof(data) << endl;

        delete [] data;                    // Array delete

        // We can use unique_ptr (But not shared_ptr !)
        unique_ptr<int[]> data2(new int[size]);
        for (int i=0; i<size; ++i)
            data2[i] = i*i;
        cout << "\nDynamic array with unique_ptr : data2 = ";
        for (int i=0; i<size; ++i)
            cout << data2[i]<< " ";
        cout << endl;
    }

    {
        cout << "\n-----------------------------";
        cout << "\nstd::array basics :  \n\n";

        // Must always specify size, part of the template !
        array<string, 5> aS1{"Karen", "Lucia", "Anastasia", "Margaret", "Alice"};
        cout << "aS1 = ";
        print(aS1);  // Our function print(), see above

        constexpr int SIZE = 1024*16;
        array<double, SIZE> aD; // Must be constexpr

        auto aStr = std::experimental::make_array("Red", "Green", "Blue");
        cout << "aStr = ";  print(aStr);

        // First and last elements
        cout << "aS1.front() = " << aS1.front() << endl;
        cout << "aS1.back() = " << aS1.back() << endl;

        // get: compile-time index
        cout << "get<2>(aS1) = " << get<2>(aS1) << endl;

        // Declare a type alias to avoid repeated declaration
        using SArray = array<string, 5>;

        // Arrays can be copied
        SArray aS2 = aS1;
        // Let us create another array of 5 strings
        SArray aS3 = {"One", "Two", "Three", "Four", "Five"};
        aS2.swap(aS3);  // Swap aS2 and aS3
        //        swap(aS2, aS3);   // The same
        cout << "\nAfter swap :\naS2 = "; print(aS2);
        cout << "aS3 = ";  print(aS3);

        // Create an std::array object out of a built-in array
        cout << "\nCreating std::array object out of built-in array :\n";
        string a[] = {"Maria", "Nel", "Sophia", "Clair", "Mirage"};
        auto aS4 = std::experimental::to_array(a);
        cout << "aS4 = ";  print(aS4);

        // Get raw pointer
        string * s = aS1.data();

        // Fill with repeating value
        cout << "\nFill:\n";
        array <int, 10> aI;
        aI.fill(17);
        cout << "aI = ";  print(aI);

        // std::array of funny types
        // Pointers
        int i1 = 13, i2 = 17, i3 = 666;
        array <int *, 3> aPtr{&i1, &i2, &i3};       // Pointers
        array <const int *, 3> aCPtr{&i1, &i2, &i3}; // Pointers to const

        // Constants
        array<const string, 5> cNames{"Maria", "Nel", "Sophia", "Clair", "Mirage"};
        cout << "cNames = ";  print(cNames);

        // unique_ptr
        array<unique_ptr<int>, 2> uAr {
            make_unique<int>(17),
            make_unique<int>(666)
        };

        // Built-in array
        array<int[17], 3> aa;
    }

    {
        cout << "\n-----------------------------";
        cout << "\nstd::array iterators + algorithms:  \n\n";


        // Access with operator[] or at()
        // operator[] does not check boundaries
        // at() does and throws std::out_of_range if wrong index
        array<int, 12> aI1;
        for (int i = 0; i < aI1.size(); ++i)
            aI1[i] = i*i;

        array<int, 12> aI2;
        // This is the proper index type, usually I just use int,
        for (array<int, 12>::size_type i = 0; i < aI2.size(); ++i)
            aI2.at(i) = i*i;

        // Print an array with index
        cout << "\nPrint with index : aI1 = ";
        for (int i = 0; i < aI2.size(); ++i)
            cout << aI2.at(i) << " ";
        cout << endl;

        // Print an array with iterator
        cout << "\nPrint with const iterator : aI1 = ";
        for (auto it = aI1.cbegin(); it != aI1.cend(); ++it)
            cout << *it << " ";
        cout << endl;

        cout << "\nPrint with const iterator (no auto) : aI1 = ";
        for (array<int, 12>::const_iterator it = aI1.cbegin(); it != aI1.cend(); ++it)
            cout << *it << " ";
        cout << endl;

        cout << "\nPrint with reverse const iterator : aI1 = ";
        for (auto it = aI1.crbegin(); it != aI1.crend(); ++it)
            cout << *it << " ";
        cout << endl;

        // Print an array with iterator + index
        // This is stupid, demonstrates obtaining index from iterator
        cout << "\nPrint with iterator + index : aI1 = ";
        for (auto it = aI1.cbegin(); it != aI1.cend(); ++it) {
            int index = it - aI1.cbegin();  // Iterator arithmetics !
            cout << aI1.at(index) << " ";
        }
        cout << endl;

        // Print with range for, it also uses begin(), end()
        cout << "\nPrint with range for : aI1 = ";
        for (int i : aI1)
            cout << i << " ";
        cout << endl;


        // Find min and max elements with algorithms:
        auto itMax = max_element(aI1.cbegin(), aI1.cend());
        cout << "\nMAX = " << *itMax << endl;
        cout << "MIN = " << *min_element(aI1.cbegin(), aI1.cend()) << endl;


        // Reversing with algorithm reverse(), 2 iterators to algorithm !
        reverse(aI1.begin(), aI1.end());
        cout << "\nAfter reverse() : aI1 = "; print(aI1);


        // Now let us change our array with non-const iterator
        cout << "\nChanging aI1 with iterators ( %= 20) :\n";
        for (auto it = aI1.begin(); it != aI1.end(); ++it)
            *it %= 20;
        cout << "aI1 = "; print(aI1);

        // Sort with algorithm sort(), 2 iterators to algorithm !
        sort(aI1.begin(), aI1.end());
        cout << "\nAfter sort() : aI1 = "; print(aI1);

    }

    {
        cout << "\n-----------------------------";
        cout << "\nstd::array find + reverse :  \n\n";

        array<int, 12> aI1;   // Same array of squares as before
        for (int i = 0; i < aI1.size(); ++i)
            aI1[i] = i*i;
        cout << "aI1 = "; print(aI1);

        // Lets try std::find()
        // We use non-const iterators to reverse later
        auto found16 = find(aI1.begin(), aI1.end(), 16);  // Returns iterator
        if (found16 == aI1.end() )
            cout << "16 not found !\n";
        else
            cout << "Found 16 at index " << found16 - aI1.begin() << endl;

        auto found17 = find(aI1.begin(), aI1.end(), 17);
        if (found17 == aI1.end() )
            cout << "17 not found !\n";
        else
            cout << "Found 17 at index " << found17 - aI1.begin() << endl;

        auto found64 = find(aI1.begin(), aI1.end(), 64);
        if (found64 == aI1.end() )
            cout << "64 not found !\n";
        else
            cout << "Found 64 at index " << found64 - aI1.begin() << endl;


        // Suppose we don't know A Priori that 16 goes before 64.
        // What can we do ? For arrays we can compare:
        array<int, 12>::iterator it1 = found16, it2 = found64;
        if (it1 > it2)         // Check the order !
                swap(it1, it2);
            
        // Now it1 < it2
        // Reverse the part from 16  to 64 inclusive
        // We need it2+1 to include 64 in the reverse !
        reverse(it1, it2+1);

        cout << "\nAfter find reverse:\n";
        cout << "aI1 = "; print(aI1);
    }

    {
        cout << "\n-----------------------------";
        cout << "\nstd::array fill, copy, generate, for_each :  \n\n";
        
        array<int, 12> aI1;
        fill(aI1.begin(), aI1.end(), 19); // Fill with the value 19
        cout << "aI1 = "; print(aI1);
        
        array<int, 12> aI2 = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
        array<int, 12> aI3;
        
        copy(aI2.begin(), aI2.end(), aI3.begin());   // Copy aI2 to aI3
        cout << "aI3 = "; print(aI3);
        
        array<int, 12> aI4;
        // Generate aI4
        int n = 0;
        generate(aI4.begin(), aI4.end(), [&n](){return n++;});
        cout << "aI4 = "; print(aI4);
        
        for_each(aI4.begin(), aI4.end(), [](int &n){n*=3;});   // Multiply each element by 3
        cout << "aI4 = "; print(aI4);
    }
    
    return 0;
}
