// Example 3_3 : namespaces
// Created by Oleksiy Grechnyev 2017

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/// The tag() function prints the namespace it's in
void tag() { cout << "::" << endl; }
//---------
namespace B {
    void tag() { cout << "::B" << endl; }

    const string bStr = "::B";
    const string str = "::B";

} // ::B
//---------
namespace C {
    void tag() { cout << "::C" << endl; }

    const string cStr = "::C";
    const string str = "::C";

} // ::C
//---------
namespace A {

    const string aStr = "::A";
    const string str = "::A";
    namespace Z {
        void tag() { cout << "::A::Z" << endl; }
    } // A::Z

    void tag() { cout << "::A" << endl; }

    namespace A {
        void tag() { cout << "::A::A" << endl; }

        namespace X {
            void tag() { cout << "::A::A::X" << endl; }

            namespace A {
                void tag() { cout << "::A::A::X::A" << endl; }
            } // A::A::X::A
            namespace B {
                void tag() { cout << "::A::A::X::B" << endl; }
            } // A::A::X::B

            // We are in ::A::A::X, calling stuff from a position deep in namespaces
            void fun() {
                tag();  //::A::A::X
                A::tag();  // ::A::A::X::A
                ::tag();  // ::
                ::A::tag();  // ::A
                ::A::A::tag();  // ::A::A

                B::tag(); //::A::A::X::B
                ::B::tag(); //::B

                Z::tag(); // ::A::Z
            }

        } // ::A::A::X
    } // ::A::A
} // ::A

// Anonymous namespace
namespace {
    void anon() {
        cout << "Anonymous namespace" << endl;
    }
}


//===============================
/// Note: The function main() must not be in a namespace !!!
int main() {
    cout << "namespaces example \n\n";

    // We can call function tag() of different namespaces
    tag();  //::
    A::tag();  // ::A
    A::A::X::A::tag();  // ::A::A::X::A
    A::A::X::B::tag();  // ::A::A::X::B
    B::tag();  // ::B
    C::tag();  // ::C

    anon(); // It works !


    cout << "\n using example \n\n";
    using B::bStr; // A single variable, function or class from a NS

    cout << "bStr = " << bStr << endl;

    using namespace A;  // The entire namespace
    using namespace B;
    using namespace C;

//    tag();  // Error ! Ambiguous !
    // Root scope :: helps after using too much 'using'
    ::tag(); // ::  // OK !
//    A::tag();  // Error ! Ambiguous ! Can be either ::A or ::A:: !
    ::A::tag(); // ::A // OK !


//    cout << "str = " << str << endl; // Error ! Ambiguous !
    cout << "aStr = " << aStr << endl; // OK: names differ
    cout << "bStr = " << bStr << endl;
    cout << "cStr = " << cStr << endl;

    cout << "\nCalling function fun() : \n\n";
    ::A::A::X::fun();

    return 0;
}

