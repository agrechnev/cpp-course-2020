// Example 2_2 : Initialization, move, swap, auto, decltype
// Created by Oleksiy Grechnyev 2017

#include <iostream>
#include <string>

int main(){
    using namespace std;
    
    {
        cout << "5 forms of initialization" << endl;
        // No copy/move/assignment here, only 1 object created by ctor each time
        int i1 = 17;  // Does not work with explicit ctor
        int i2(17);  // Cannot be used for class fields
        int i3 = int(17);  // No copy/move here !
        int i4{17};  
        int i5 = {17};   // Does not work with explicit ctor
        cout << i1 << " " << i2 << " " << i3 << " " << i4 << " " << i5 << endl << endl;
    }
    
    {
        cout << "move and swap operations" << endl;
        string s1("Brianna");
        string s2 = move(s1);
        string s3("Mira");
        string s4("Visas");
        swap(s3, s4);
        
        cout << "s1 = " << s1 << endl;
        cout << "s2 = " << s2 << endl;
        cout << "s3 = " << s3 << endl;
        cout << "s4 = " << s4 << endl << endl;
    }

    {
        cout << "auto, decltype, decltype(auto)" << endl;
        int a = 13;
        auto b = a;  // b is int = 13
        decltype(a) c = 14; // c is int = 14
        int &d = a; // d is a reference to a
        // auto gives int even though d is a ref
        auto e = d; // e is int = 13
        // decltype(auto) gives ref
        decltype(auto) f = d; // f is a reference to a
        a = 22; // Change a, d, f
        
        cout << "a = " << a << endl;  // 22
        cout << "b = " << b << endl;  // 13 
        cout << "c = " << c << endl;  // 14
        cout << "d = " << d << endl;  // 22
        cout << "e = " << e << endl;  // 13
        cout << "f = " << f << endl << endl;  // 22
    }
    
    return 0;
}