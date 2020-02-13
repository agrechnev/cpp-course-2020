// Example 3_1 : References, pointers, C-style memory management
// Created by Oleksiy Grechnyev 2017

#include <iostream>
#include <string>
#include <vector>
#include <array>

/*
  C language headers in C++ start with 'c'. For example
  cstdlib is the C++ version of the C header stdlib.h
  which puts all stuff into the namespace std
*/
#include <cstring>
#include <cstdlib>

using namespace std;

//=========================
int main() {
    {
        cout << "const, constexpr modifiers : \n\n\n";

        const int a = 17;
        // a = 19; // Error
        // const int b; // Error : no initialization

        auto c = a; // c is int, auto ignores const
        c = 12; // OK
        decltype(auto) d = a; // d is const int
//        d = 13; // Error

        using CULL = const unsigned long long; // const in a type declaration
        CULL e = 1001; // e is const unsigned long long

        cout << "a = " << a << ", e = " << e << endl;

        array<const int, 4> cia{4, 3, 2, 1};   // const in a template argument

        // constexpr is a compile-time const, literal types only
        constexpr int SIZE = 18;
        static_assert(SIZE == 18, "Error ! Wrong size !!!");  // Compile-time check
        constexpr const char * NAME = "Lucifer";  // Type const char *
        int cArray[SIZE];  // C Array
        array<int, SIZE> cppArray; // C++ ARray class
    }


    {
        cout << "References 1 : \n\n" << endl;

        int a = 17;
        int b = a;   // Normal variable, not a ref
        int &c = a;  // Ref to a
        const int &d = a; // Const ref to a

        cout << "c is ref to a, d is const ref to a \n";
        cout << "a = " << a << ", b = " << b << ", c = " << c << ", d = " << d << endl;

        cout << "Now we change a to 13 \n";
        a = 13; // This also changes c, d
        // Note that d is also changed.
        // const int & d means that we cannot change d directly,
        // But it does change if we change the value of a
        cout << "a = " << a << ", b = " << b << ", c = " << c << ", d = " << d << endl;

        cout << "Now we change c to 19 \n";
        c = 19; // This also changes a, d
        cout << "a = " << a << ", b = " << b << ", c = " << c << ", d = " << d << endl;

        //d = 17;  // We cannot do that, d is a const int &

        // Difference between auto and decltype(auto)
        auto x = d;  // x is int, auto ignores both ref and const
        x = 11; // OK, and a, c, d are not changed
        decltype(auto) y = c; // y is ref to a

        cout << "Now we change y to 100 \n";
        y = 100; // Changes a, c, d
        decltype(auto) z = d; // y is const ref to a
        // z = 200; // Error

        cout << "a = " << a << ", b = " << b << ", c = " << c << ", d = " << d << endl;
    }

    {
        cout << "\n\nReferences 2 :\n\n" << endl;

        cout << "We can use refs to point to some element of a container, class field, etc\n";

        vector<string> vs{"Zero", "One", "Two", "Three", "Four"};
        string &r2 = vs[2];
        const string &cr2 = vs[2];

        // We can use string & r2 to modify
        r2 = "TWO";
        // We can use const string & r2 to get valuue, but not to modify
        cout << "cr2 = " << cr2 << endl;

        // Now we add another element to the vector
        vs.emplace_back("Five");
        // Now the vector's elements has likely moved and using r2, cr2 is no longer valid !!!
//        cout << "cr2 = " << cr2 << endl;  // Dangerous !!!

        cout << "range for loops with and without reference : \n";

        cout << "Printing vector by  range for with string  : \n";
        // Here s is a copy, copying is ineffficient
        for (string s : vs) {
            cout << s << " ";
            s = "Idiot"; // Copy is modified, container is not affected
        }
        cout << endl;

        cout << "Printing vector by  range for with auto  : \n";
        for (auto s : vs)
            cout << s << " ";
        cout << endl;

        // We can use range for with string & to change the vector eelements
        cout << "Changing vector by range for with string & : \n";
        for (string &s : vs)
            s += s;

        cout << "Printing vector by range for with const string &  : \n";
        // const string & is the optimal way to do it, no copying and wouldn't be modified by mistake
        for (const string &s : vs)
            cout << s << " ";
        cout << endl;

        cout << "Printing vector by range for with const auto &  : \n";
        // const auto & is equally good of course
        for (const auto &s : vs)
            cout << s << " ";
        cout << endl;
    }

    {
        cout << "\n\nPointers 1 :\n\n" << endl;

        int a = 13;
        int *p = &a;  // B is a pointer, points to a at the moment. &a = address of a

        const int *p1 = p; // Pointer to const int,  p1 is NOT a const, we can change p1, but not *p1 !
        int *const p2 = p; // Pointer to int,  p2 is a const,  we can change *p2, but not p2 !
        const int *const p3 = p; // Pointer to const int,  p3 is a const,  we cannot change *p3 or p3 !

        cout << "a = " << a << ", p = " << p << ", *p = " << *p
             << endl;  // Note: p prints as a hex memory address, equal to &a
        // Now we change *p, this means also changing a
        *p = 14;
        cout << "a = " << a << ", p = " << p << ", *p = " << *p << endl;

        int c = 19;  // A new var
        // Now point p to c, you can do this to pointers, put not to refs !
        p = &c;
        // Note that the memory address p has changed, as it now equal to &c
        cout << "a = " << a << ", p = " << p << ", *p = " << *p << ", c = " << c << endl;
    }

    {
        cout << "\n\nPointers 2 :\n\n" << endl;
        cout << "sizeof(string) = " << sizeof(string) << endl;

        const string names[] = {"Karen", "Lucia", "Anastasia", "Margaret", "Alice"};

        cout << "We can use pointers to iterate over an array : \n";
        // Printing array with pointers, iterator-like
        // Note that ++it increases the pointer by sizeof(string) bytes, not by 1 byte !
        // And names + 5 moves by 5 positions !
        const string *eit = names + 5;
        for (const string *it = names; it != eit; ++it)
            cout << *it << " ";
        cout << endl;

        cout << "And even more iterator-like syntax : \n";
        // Note: exactly the same loop will print a container like std::vector
        // C++ iterators arouse out practice of using pointers to iterate over an array
        for (const auto *it = begin(names); it != end(names); ++it)
            cout << *it << " ";
        cout << endl;
    }

    {
        cout << "\n\nPointers 3 : new and delete :\n\n" << endl;

        // new operator creates an object in the heap
        string *pS = new string("new example !");
        cout << "pS = " << pS << ", *pS = " << *pS << endl;
        // Everything created by new must be deleted !!!
        // Otherwise a MEMORY LEAK !
        delete pS;

        cout << "Dynamic array : \n";
        int size;
//        cout << "Enter size :";
//        cin >> size;
        size = 13;
        // Create an array of ints
        // Don't do this in real life, use std::vector instead
        int *pI = new int[size];

        // Note that we can't use range for or iterators here
        for (int i = 0; i < size; ++i)
            pI[i] = i;

        for (int i = 0; i < size; ++i)
            cout << i << " ";
        cout << endl;

        // Use array form of delete: important !!!
        delete[] pI;
    }

    {
        cout << "\n\nC-style memory management, memset, memcpy :\n\n" << endl;

        char s[100]; // Buffer for c strings
        memset(s, 0, 100); // Set the buffer to 0
        // memmcpy is fastest, no checks
        memcpy(s, "Jessica", 4); // Copy 4 bytes only from a literal
        cout << "s = " << s << endl;

        strcpy(s, "Michelle"); // Copies a 0-terminated C-string
        strncpy(s, "Michelle", 100); // Same with taking buffer size into account, does not overflow
        cout << "s = " << s << endl;

        // Memmove is just like memcpy, but it handles overlap correctly
        memmove(s + 3, s, 9);
        cout << "s = " << s << endl;

        // Now let's allocate 2 buffers with malloc and calloc
        // Requires explicit cast from void * to char *
        char *buf1 = (char *) malloc(10);  // 10 bytes
        char *buf2 = (char *) calloc(5, 2); // Also 10 = 5*2 bytes, sets the block to 0

        const char *sLit = "abCdeFghI";
        memcpy(buf2, sLit, 9); // We only copy 9 chars, we know that buf2[9] = 0.
        memcpy(buf1, buf2, 10); // Copy all 10 chars

        cout << "buf1 = " << buf1 << endl;
        cout << "buf2 = " << buf2 << endl;

        // We must free what we allocated in the heap!
        free(buf1);
        free(buf2);

        // Now the crazy stuff: we create object at a specified memory location !!!
        cout << "Crazy stuff : new (ptr) string" << endl;

        string *ptr = (string *) malloc(sizeof(string));
        new (ptr) string("Dark Cindy"); // Create a new string object at memory address ptr
        *ptr = "Lady Yunalesca"; // We can work with this string object
        cout << "*ptr = " << *ptr << endl;
        // After new (ptr) we must call the destructor explicitly, it wouldn't be called otherwise
        // delete ptr;  MIGHT work, but not guaranteed
        ptr->~string();
        free(ptr); // Free the heap memory
    }

    return 0;
}
