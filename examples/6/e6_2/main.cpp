// Example 6.2 : std::vector
// Created by Oleksiy Grechnyev 2017
// Class Tjej is used here, it logs Ctors and Dtors

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

#include "Tjej.h"

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
int main(){
    {
        cout << "-----------------------------";
        cout << "\nstd::vector creation :  \n\n";
        
        vector<int> vI1;            // Empty vector
        vI1.push_back(11);          // Add elements to an empty vector
        vI1.push_back(12);
        vI1.push_back(13);
        cout << "vI1 = "; print(vI1);
        
        vector<int> vI2(10);        // vector of 10 elements
        cout << "vI2 = "; print(vI2);
        
        vector<int> vI3(10, 13);    // vector of 10 elements equal to 13
        cout << "vI3 = "; print(vI3);
        
        vector<int> vI4{10, 13};    // vector of two elements : 10, 13
        cout << "vI4 = "; print(vI4);
        
        vector<int> vI5 = {2, 3, 7, 11, 13, 17, 19, 23};    // List assignment constructor
        cout << "vI5 = "; print(vI5);
        
        vector<string> vS{"Maria", "Nel", "Sophia", "Clair", "Mirage"};    // List constructor
        cout << "vS = "; print(vS);

        vector<int> vI6;            // Empty vector
        vI6 = {1, 2, 7, 13};        // assign a list
        cout << "vI6 = "; print(vI6);

        vI3.swap(vI6);    // swap is very efficient
    }

    {
        cout << "-----------------------------";
        cout << "\nstd::vector logging copy/move operations with Tjej:  \n\n";
        
        {
            cout << "\ncreate 5 elements, then fill with at(): \n" << endl;
            vector<Tjej> vT(5);   // Note: that calls default constructor of Tjej 5 times !!!
            for (int i=0; i < 5; ++i)
                vT.at(i) = Tjej("Tjej #" + to_string(i));
        }
        
        {
            cout << "\nfill with push_back() : move : \n" << endl;
            vector<Tjej> vT;   // Empty vector
            for (int i=0; i < 5; ++i)
                // push_back with a temp is a move
                vT.push_back(Tjej("Tjej #" + to_string(i)));
        }

        {
            cout << "\nfill with emplace_back() \n" << endl;
            vector<Tjej> vT;   // Empty vector
            for (int i=0; i < 5; ++i)
                // push_back with a temp is a move
                vT.emplace_back("Tjej #" + to_string(i));
        }

        {
            cout << "\nfill with reserve(5) + emplace_back() \n" << endl;
            vector<Tjej> vT;   // Empty vector
            vT.reserve(5);
            for (int i=0; i < 5; ++i)
                // push_back with a temp is a move
                vT.emplace_back("Tjej #" + to_string(i));
        }
    }
    
    {
        cout << "-----------------------------";
        cout << "\nstd::vector capacity growth : \n\n";

        vector<int> v;
        for (int i = 0; i <= 40; ++i) {
            cout << "size = " << v.size() << ", capacity = " << v.capacity() << endl;
            v.push_back(i);
        }

    }

    {
        cout << "-----------------------------";
        cout << "\nstd::vector insert example : \n\n";

        vector<int> v{1, 2, 3, 4, 5};
        cout << "v = "; print(v);

        auto pos = find(v.cbegin(), v.cend(), 3);  // Find position of 3
        pos = v.insert(pos, 17);             // Insert BEFORE 3, returns iterator to 17
        pos = v.insert(pos, {21, 22});      // Insert list before 17
        pos = v.emplace(pos, 33);           // Emplace BEFORE 21, returns iterator to 33
        cout << "v = "; print(v);

        // How to insert in a loop. You cannot use range for !!!
        for (auto it = v.cbegin(); it != v.cend(); ++it)
            if (*it > 20 && *it < 30)
                it = v.insert(it, 49) + 1;   // Insert 49 BEFORE 21, 22

        // You need +1 here to avoid repeating the insert before 21 until program crashes
        // it -> 21
        // insert 17 before 21, it -> 17
        // +1 : it -> 21
        // ++it : iy -> 22

        cout << "v = "; print(v);
    }

    {
        cout << "-----------------------------";
        cout << "\nstd::vector erase example : \n\n";

        vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto pos = find(v.cbegin(), v.cend(), 2);  // Find 2
        pos = v.erase(pos);    // Erase 2, pos -> 3
        pos = v.erase(pos, pos+3);    // Erase 3, 5, 6
        cout << "v = "; print(v);

        v.assign({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});   // Just like Ctor

        // Delete all even numbers in a for loop
        for (auto it = v.cbegin(); it != v.cend(); ++it)
            if (*it % 2 == 0)
                it = v.erase(it) - 1;  // -1 to negate ++it

        cout << "v = "; print(v);
    }

    return 0;
}
