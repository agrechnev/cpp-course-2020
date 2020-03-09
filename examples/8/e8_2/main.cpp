// Example 8_2 : IntBox: Copy/move constructors, assignment
// Created by Oleksiy Grechnyev 2017

#include <iostream>

#include "./IntBox.h"

int main(){
    using namespace std;
        
    {
        cout << "\nIntBox Ctor, Dtor :\n\n" << endl;
        IntBox a, b(17);   // a is empty, b is not
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
    }

    {
        cout << "\nIntBox getValue, setValue, clear :\n\n" << endl;
        IntBox a, b(17), c(18);

        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        cout << "c = " << c << endl;

        a.setValue(21);
        b.setValue(22);
        c.clear();

        cout << "a.getValue() = " << a.getValue() << endl;
        cout << "b.getValue() = " << b.getValue() << endl;
        try {
            cout << "c.getValue() = " << c.getValue() << endl; // throws exception
        } catch (const logic_error & e) {
            cout << "Caught exception : " << e.what() << endl;
        }
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        cout << "c = " << c << endl;
    }
        

    {
        cout << "\nIntBox copy operations :\n\n" << endl;

        IntBox a, b(17);
        IntBox c(a);   // Copy ctor (empty)
        IntBox d(b);   // Copy ctor
        IntBox e(22);

        cout << "a = " << a << ", b = " << b << ", c = " << c << ", d = " << d << ", e = " << e << endl;

        a = e;  // Copy assign e to a, b
        b = e;
        e.setValue(42); // And change e

        e = e; // Check self-assignment

        cout << "a = " << a << ", b = " << b << ", c = " << c << ", d = " << d << ", e = " << e << endl;

        a = c;  // Copy assign empty
        b = c;

        cout << "a = " << a << ", b = " << b << ", c = " << c << ", d = " << d << ", e = " << e << endl;
    }

    {
        cout << "\nIntBox move operations :\n\n" << endl;

        IntBox a(17), b(18);
        IntBox c(move(a)), d(move(b)); // Move Ctor

        cout << "a = " << a << ", b = " << b << ", c = " << c << ", d = " << d << endl;

        a = move(c); // Move assignment, moves c back to a
        b = IntBox(42); // Move assignment of a temp

        // Check the correct self-assignment
        b = move(b);

        cout << "a = " << a << ", b = " << b << ", c = " << c << ", d = " << d << endl;

        // Try swap
        swap(a, b);
        swap(c, d);

        cout << "a = " << a << ", b = " << b << ", c = " << c << ", d = " << d << endl;
    }
    return 0;
}
