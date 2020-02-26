// Example 5.7 : type conversions (casts)
// Created by Oleksiy Grechnyev 2017, 2020

#include <iostream>
#include <iomanip>
#include <string>


using namespace std;

struct Base{
    virtual void print(){
        cout << "Base" << endl;
    }
};

struct Derived : public Base{
    void print() override {
        cout << "Derived" << endl;
    }
};

enum class Num {Zero, One, Two, Three, Four, Five};

//==============================
int main(){
    {
        cout << "\nImplicit conversions:  \n\n";
        // Primitive
        float a = 777;   // Possible loss of accuracy
        int b = 3.5;    // Loss of accuracy
        char c = 1987; // Loss of higher bytes,  Warning !

        // Non-explicit constructor  : const char[8] to string
        string s = "Phoenix";

        // cast operator , ostream to bool
        bool d(cout);  // Cannot use = here as the operator is explicit!

        cout << "a = " << a << ", b = " << b << " , s = " << s << ", d = " << d << endl;

        // Any pointer to void*
        void * vP = &b;

        // Pointer and reference upcasting (Derived* to Base* , Derived & to Base &)
        Derived derived;
        Base & baseR = derived;
        Base * baseP = &derived;
        baseR.print();   // Prints 'Derived' twice, polymorphism works
        baseP->print();
    }

    {
        cout << "\nconst_cast  \n\n";

        int a = 17;
        const int & crA = a;
        int & rA = const_cast<int &>(crA);   // Remove const
        rA = 20;
        cout << "a = " << a << endl;           // Prints 20

        double b = 1.1;
        const double * cpB = &b;
        double * pB = const_cast<double *>(cpB);   // Remove const
        *pB = 2.2;
        cout << "b = " << b << endl;          // Prints 2.2
    }

    {
        cout << "\nstatic_cast  \n\n";

        string s = static_cast<string>("Idiot !");  // Allowed as implicit conversion
        int i = static_cast<int>(Num::Four);
        bool b = static_cast<bool>(cout);  // Works even though the operator is exxplicit

        // void * to any pointer
        void * pV = &i;
        int *pI = static_cast<int *>(pV);
        cout << "s = " << s << ", i = " << i << ", *pI = " << *pI << endl;

        // Reference and Pointer downcast
        Derived d;
        Base & rB = d;
        Base * pB = &d;
        Derived & rD =  static_cast<Derived &>(rB);   // Downcast
        Derived * pD =  static_cast<Derived *>(pB);   // No checks  !
        rD.print();  // Prints "Derived" twice
        pD->print();
    }

    {
        cout << "\ndynamic_cast  \n\n";

        // Reference and Pointer downcast
        // This is a safe version, it checks that the ref/pointer indeed points to a Derived object
        Derived d;
        Base & rB = d;
        Base * pB = &d;
        Derived & rD =  dynamic_cast<Derived &>(rB);   // Downcast
        Derived * pD =  dynamic_cast<Derived *>(pB);   // With checks  !
        rD.print();  // Prints "Derived" twice
        pD->print();

        // Now try a wrong object
        Base b2;
        Base & rB2 = b2;
        Base * pB2 = &b2;
        // rB2 is a ref to wrong type. throws bad_cast
//        Derived & rD2 = dynamic_cast<Derived &>(rB2);   // throws bad_cast
        Derived * pD2 = dynamic_cast<Derived *>(pB2);   // returns nullptr
        if (!pD2)
            cout << "nullptr !!!" << endl;
    }

    {
        cout << "\nreinterpret_cast  \n\n";

        int i = 17;
        int *pI = &i;     // Pointer
        long long j = reinterpret_cast<long long>(pI);
        cout << "j = " << j << endl;
        
        
        // Cast int * to double *:
        double *pD = reinterpret_cast<double *>(pI);
        cout << "*pD = " << *pD << endl;
    }

    return 0;
}
