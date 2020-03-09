// Example 8.1 Operator overloading : class Vec2

#include <iostream>
#include <string>

#include "./Vec2.h"

using namespace std;

//==============================
int main() {
    {
        cout << "\nVec2 constructor, ==, !=, output :\n\n";

        Vec2 a(1.0, 2.0), b(1.0, 2.0), c(2.0, 1.0);

        //        cout << "Enter vector b :" << endl;
        //        cin >> b;

        // Assignment
        Vec2 d;
        d = c;

        // overloaded <<
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        cout << "c = " << c << endl;
        cout << "d = " << d << endl;

        // getters
        cout << "a.getX() = " << a.getX() << endl;
        cout << "a.getY() = " << a.getY() << endl;

        // overloaded ==, !=
        cout << boolalpha;
        cout << "(a == a) is " << (a == a) << endl;
        cout << "(a != a) is " << (a != a) << endl;
        cout << "(a == b) is " << (a == b) << endl;
        cout << "(a != b) is " << (a != b) << endl;
        cout << "(a == c) is " << (a == c) << endl;
        cout << "(a != c) is " << (a != c) << endl;
    }

    {
        cout << "\nVec2 comparison operators (compare x, then y) :\n\n";

        Vec2 a(1.0, 2.0), b(1.0, 1.0), c(2.0, 0.0);

        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        cout << "c = " << c << endl;

        cout << "a < b :" << (a < b) << endl;
        cout << "a > b :" << (a > b) << endl;
        cout << "a <= b :" << (a <= b) << endl;
        cout << "a >= b :" << (a >= b) << endl;

        cout << "a <= a :" << (a <= a) << endl;
        cout << "a >= a :" << (a >= a) << endl;
        cout << "a < a :" << (a < a) << endl;
        cout << "a > a :" << (a > a) << endl;

        cout << "a < c :" << (a < c) << endl;
        cout << "a > c :" << (a > c) << endl;
        cout << "a <= c :" << (a <= c) << endl;
        cout << "a >= c :" << (a >= c) << endl;
    }

    {
        cout << "\nVec2 arithmetics :\n\n";

        Vec2 a(-1, 2), b(2, -1);
        a += b;   // 1 1
        cout << "a = " << a << endl;
        a -= b;    // Back to  -1 2
        cout << "a = " << a << endl;
        a *= 3.0;  // a = -3 6
        cout << "a = " << a << endl;
        a /= 3.0;   // Back to  -1 2
        cout << "a = " << a << endl;

        // More arithmetics
        Vec2 c = 2.0*a + b*3.0;    // 4 1
        cout << "c = " << c << endl;
        c = a*3.0 - b/0.5 + 2*Vec2{3, -5}; // -1 -2
        cout << "c = " << c << endl;

        // Finally, the unary minus
        c = -c;   // 1  2
        cout << "c = " << c << endl;
    }

    {
        cout << "\nVec2 exotics :\n\n";
        Vec2 a(-13, -666), b(0,0);

        a("A Terrible Evil Vector :");  // Function call (string arg)

        // operator[] non-const
        a[0] = -4;
        a[1] = 3;
//        a[2] = 3;  // throws out_of_range

        // operator[] const
        const Vec2 & cA = a;
        cout << "cA[0] = " << cA[0] << ", cA[1] = " << cA[1] << endl;

        // Length, operator double
        // operator double is explicit, explicit casts only !
        cout << "a.len() = " << a.len() << endl;   // As method
        cout << "(double)a = " << (double)a << endl;   // As explicit cast
        cout << "static_cast<double>(a) = " << static_cast<double>(a) << endl;
        // double d = a; // Does not work, as operator double is explicit

        // operator bool
        // Works in if and ?: even though it's explicit
        if (a)
            cout << "a is not zero" << endl;
        else
            cout << "a is zero" << endl;

        cout << (b ? "b is not zero" : "b is zero") << endl;
        // bool myBool = a;  // Error, operator bool is explicit
        bool myBool = (bool)a;  // OK
    }
    return 0;
}
