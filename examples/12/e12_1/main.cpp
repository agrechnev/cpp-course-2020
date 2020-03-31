// Example 12.1 Move, Rvalue References
// Created by Oleksiy Grechnyev 2017
#include <iostream>
#include <string>
#include <vector>

#include "./Tjej.h"

using namespace std;
//==============================
// Sources and sinks
//==============================
/// Create a Tjej object, returns by value
Tjej source1(const string & s){
    // Return by value, no MOVE !
    // Return Value Optimization takes care of it
    Tjej t(s);
    return t;
}

/// 2-step source
Tjej source2(const string & s){
    // Still return by value, no MOVE !
    return source1(s);
}

/// Sink, takes a Tjej object to die
void sink1(Tjej t) {  // By value (move), local that dies !
    cout << "sink1 : " << t.getName() << endl;
} // t dies here

/// 2-step sink
void sink2(Tjej t) {  // By value (move), local that dies !
    sink1(move(t));  // The correct way, move to die !
} // t dies here


//==============================
// Perfect forwarding
//==============================
/// Forward 1 argument to push_back()
template <typename V, typename T>
void addToVec(V & v, T && t){
    v.push_back(forward<T>(t));
}

/// Forward variadic argument to emplace_back()
template <typename V, typename ... Args>
void addToVec2(V & v, Args && ... args){
    v.emplace_back(forward<Args>(args)...);
}

//==============================
// main() 
//==============================
int main() {
    {
        cout << "\nMove basics : \n\n";

        Tjej t1("Maria Traydor");  // Normal Ctor
        Tjej t2(t1);  // Copy Ctor
        Tjej t3(move(t2)); // Move ctor, now t2 is empty

        t1 =  string("Nel Zelpher"); // Move assign of an RVALUE
        t2 = t1; // Copy assign
        t3 = move(t2); // Move assign
        t2 = static_cast<Tjej &&>(t3);  // Move back to t2, this is equivalent to move()
    }

    {
        cout << "\nLvalue vs Rvalue refs : \n\n";
        string s("Mickey Mouse");

        // Non-const LVALUE ref
        string & lr1 = s; // OK
//        string & lr2 = string("Donald Duck"); // ERROR, lvalue ref to rvalue !
        cout << lr1 << endl;

        // Const LVALUE ref
        const string & clr1 = s; // OK
        const string & clr2 = string("Donald Duck"); // ERROR, lvalue ref to rvalue !
        // NOTE: the lifetime of the temporary is extended to the lifetime of clr2 !
        cout << clr1 << endl;
        cout << clr2 << endl;

        // RVALUE ref
        string && rr1 = string("Pluto");
//        string && rr2 = s; // ERROR, rvalue ref to lavlue
        string && rr3 = static_cast<string&&>(s); // OK, cast to rvalue
        string && rr4 = move(s); // OK, the same, move() does not move anything !
        cout << rr1 << endl;
        cout << rr3 << endl;
        cout << rr4 << endl;
    }

    {
        cout << "\nSources and sinks : \n\n";
        Tjej t1 = source1("Karen Koenig"); // 1-step source : no moves or copies !
        cout << "t1.getName() = " << t1.getName() << endl;

        Tjej t2 = source2("Alice Elliot"); // 2-step source : no moves or copies !
        cout << "t2.getName() = " << t2.getName() << endl;

        Tjej t3("Lucia");
        sink1(move(t3));  // 1 move, 0 copy

        Tjej t4("Margarete Gertrude Zelle");
        sink2(move(t4));  // 2 move, 0 copy
    }

    {
        cout << "\nPerfect forwarding : \n\n";

        vector<Tjej> v;
        v.reserve(10);
        addToVec(v, Tjej("Nel Zelpher")); // Add a RVALUE, 1 move
        Tjej t1("Clair Lasbard");
        addToVec(v, t1); // Add a LVALUE, 1 copy

        addToVec2(v, string("Maria Traydor")); // Construct in-place
    }

    return 0;
}
