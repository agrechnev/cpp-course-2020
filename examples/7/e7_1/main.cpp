// Example 7.1 Functors. Lambda expressions.
// Created by Oleksiy Grechnyev 2017

#include <iostream>
#include <functional>
#include <memory>

using namespace std;

//==============================
/// PrintOp that uses std::function
static void printOp(function<int(int, int)> op) {
    cout << "printOp: op(7, 3) = " << op(7, 3) << endl;
}

//==============================
/// PrintOp version that uses function pointer (C syntax, not good idea in C++ !)
static void printOp2(int (*op)(int, int)) {
    cout << "printOp2: op(7, 3) = " << op(7, 3) << endl;
}

//==============================
/// PrintOp version that uses templates
template <typename T>
void printOp3(T op) {
    cout << "printOp3: op(7, 3) = " << op(7, 3) << endl;
}

//==============================
// various operations we can try
static int add(int x, int y) {
    return x + y;
}

// Different signature !
static int addRef(const int &x, const int &y) {
    return x + y;
}

static int mul(int x, int y) {
    return x * y;
}

/// Add 3 numbers, not a binary OP ! p is in the middle for fun !
static int add3(int x, int p, int y) {
    return x + p + y;
}
//==============================
int main() {
    {
        cout << "\nFunction pointers, functors: binary operation :\n\n";

        // Pass a function to printOp()
        cout << "add:\n";
        // Pointer to add and add is basically the same thing
        // Just like for arrays
        // Both printOp and printOp2 work in this case
        printOp(add);
        printOp(&add);
        printOp2(add);
        printOp2(&add);

        // printOp3 is fine too
        printOp3(add);
        printOp3(&add);

        // Now let's try variables
        cout << "mul (variables):\n";
        int (*mulPtr)(int, int) =  mul;     // Function pointer var
        function<int(int, int)> mulFun = mul;  // std::function var
        printOp(mulFun);    // printOp works with both pointer and std::function
        printOp(mulPtr);
        printOp2(mulPtr);    // printOp2 only works with the pointer

        // Now we use addRef with a different signature
        cout << "adddRef:\n";
        printOp(addRef);   // std::function does implicit conversions ...
//        printOp2(addRef);   // ... while function pointers don't

        // No let's try a functor to add x+y+p (p = parameter)
        // Remember, struct is same as class but with default public
        struct FunctorAdd {
            int p = 0; // Parameter
            int operator()(int x, int y) {
                return x + y + p;
            }
        };

        FunctorAdd fa{17};  // Sets p
        cout << "FunctorAdd fa{17};\n";
        printOp(fa);   // std::function works fine with functors ...
//        printOp2(fa);   // while function pointers don't !!!

        // What about operators ?
        cout << "plus<int>()\n";
//        printOp(operator+);  // Does not work
        printOp(plus<int>());  // plus is a functor template which wraps operator+
        printOp(plus<>());  // or even like this (C++ 14)
    }

    {
        cout << "\nLambdas: binary operation :\n\n";
        // Lambdas are anonymous functors, sort of
        // Captured variables are class fields

        cout << "Lambda add : \n";
        // No capture, return type is optional, but better to specify it
        printOp([](int x, int y)->int{
            return x + y;
        });

        cout << "Lambda auto add (C++ 14) : \n";
        printOp([](auto x, auto y){
            return x + y;
        });

        cout << "Capture by value: add + 17 :\n";
        // Lambdas are stored in auto, since capture class has no name
        int p = 17;
        // Capture by value :
        auto lamAdd = [p](int x, int y)->int{
            return x + y + p;
        };
        function<int(int, int)> lamAdd2 = lamAdd; // Lambdas can be also kept in std::function

        // Now we change p, the value captured by the lambda does not change !
        p = 0;
        printOp(lamAdd);
        printOp(lamAdd2);

        // Now let's capture by ref:
        cout << "Capture by ref: mul* 3 :\n";
        // At present, p = 0
        auto lamMul = [&p] (int x, int y)->int{
            return x * y * p;
        };
        // Now we change p !
        p = 3;
        printOp(lamMul);  // Value p=3 is used because of the ref capture !

        cout << "Emulate lambda with a functor (add + 3) :\n";
        struct {
            int pCap; // Parameter
            int operator()(int x, int y) {
                return x + y + pCap;
            }
        } functor{p};  // pCap captures p by value
        printOp(functor);

        // Now the init capture !
        // I wanted to show unique_ptr, but it doesn't work with std::function !!!
        // std::function needs lambda to be copyable, and unique_ptr is not !
        cout << "Init capture mul* 2 :\n";
        printOp([z = p - 1](int x, int y)->int{
            return x * y * z;
        });
        // By ref also work !
        printOp([&z = p](int x, int y)->int{
            return x * y * z;
        });

        // Let's try unique_ptr anyway, works only with printOp3 (template version)
        auto uI = make_unique<int>(3);
        printOp3([u = move(uI)](int x, int y)->int{
            return x * y * *u;
        });
    }

    {
        cout << "\nstd::bind, lambdas, class members :\n\n";

        // std::bind example
        cout << "add3() with std::bind : p = 10 :\n";
        // Make a binary op out of add3 with bind
        printOp(bind(add3, placeholders::_1, 10, placeholders::_2));

        // Most programmers prefer lambdas to bind, same effect with a lambda
        cout << "add3() with lambdas : p = 10 :\n";
        printOp([](int x, int y)->int{
            return add3(x, 10, y);
        });

        // How to pass a non-static class member as a function ?
        cout << "Non-static class member : p = 20 :\n";
        struct Z{
            int p = 0;
            int op(int x, int y) {
                return x + y + p;
            }
        };

        Z z{20};  // Create an object with  p = 20
//        printOp(z.op);   // This does not work !

        // Class methods have invisible first argument this :
        function<int(Z*, int, int)> funny = Z::op; // This works !

        // You have to use bind or lambda wrapper (preferred !)
        // Note the hidden 1st argument, which is this (&z) !
        printOp(bind(Z::op, &z, placeholders::_1, placeholders::_2));
        printOp([&z](int x, int y)->int{
            return z.op(x,y);
        });

        cout << "Fun with mutable lambda : \n";
        int n = 10;
        auto lam = [n]() mutable -> void{
            n += 10;
            cout << "n = " << n << endl;
        };
        lam();
    }
    return 0;
}
