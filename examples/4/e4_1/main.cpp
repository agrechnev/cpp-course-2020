// Example 4.1 : Class Ctors, Dtors, copy/move ctors and assignments using class Tjej
// Created by Oleksiy Grechnyev 2017
#include <iostream>
#include <memory>

#include "./Warrior.h"  // ./ is optional, but nice
#include "Tjej.h"  // No ./ here
#include "./Box.h"

// GLobal variable example: Dtor should fire at program exit!
Tjej glob("Globula Statika");

int main(){
    using namespace std;
    using namespace MyNS;
    // The blocks here limit the scope, so that destructors kick in at the end of each block
    // Everything is destroyed by the end of each block
    {
        cout << "\nWarrior : \n\n";

        // Create a warrior
        Warrior w0;  // Default constructor, rather stupid, does not increase the count
        Warrior w1("Maria Traydor", "Gun", 19);
        Warrior w2{"Sophia Esteed", "Staff", 19};
        Warrior w3 = Warrior("Nel Zelpher", "Knives", 23);
        Warrior w4("Clair Lasbard", "Knives", 25);

        w1.within(2300);  // Call a class method
    }

    {
        cout << "\nWarrior : Static demo \n\n";

        Warrior::printWarriorCount();
    }


    {
        cout << "\nTjej: Initialization : \n\n";
        Tjej t1; //Default ctor: Lilith
        
        // These 5 forms of initialization are more or less equivalent (unless we use std::initializer_list)
        Tjej t2("Kajsa");
        Tjej t3 = Tjej("Anna");  // No copy/move here ! And no assignment !
        Tjej t4{"Maria"};
        Tjej t5 = {"Eva"}; // Again, no assignment ! This is impossible with explicit ctor.
        Tjej t6 = string("Hedvig"); // Again, not possible with explicit ctor

        // Setter + Getter
        t5.setName("Eva Nordström");
        cout << "t5.getName() = " << t5.getName() << endl;

        // Note: destructors work in the reverse order for local vars
    }

    {
        cout << "\nTjej: Copy & Move constructors: \n\n";

        Tjej t1("Anna Nilsson");
        Tjej t2(t1); // Copy constructor
        Tjej t3("Mikaela Blomqvist");
        Tjej t4(move(t3)); // Move constructor, t3 is left with an empty string
    }

    {
        cout << "\nTjej: Copy & Move assignments: \n\n";

        Tjej t1("Kajsa Lindahl");
        Tjej t2; // Default ctor
        t2 = t1; // Copy assignment
        Tjej t3("Yvonne Vennnström");
        Tjej t4; // Default ctor
        t4 = move(t3); // Move assignment
        t4 = Tjej("Marie Lind"); // Move assignment, temp object is moved by default
    }

    {
        cout << "\nTjej: Using heap memory: \n\n";

        Tjej *pT = new Tjej("Lisbeth Salander");  // Pointer: the Old Way

        // Smart pointers are the right way in C++ 11+.
        unique_ptr<Tjej> upT = make_unique<Tjej>("Maja Lundgren");

        delete pT;  // Always delete objects created by new
    }
    
    {
        cout << "\nUsing class templates : \n\n";
        
        // Create box of int type : Note type must always be specified (unlike for function templates) !
        Box<int> a(13);
        a.setVal(17);
        cout << "a.getVal() = " << a.getVal() << endl;
        
        // And a box of string : Same template can be used to create boxes of any type !
        Box<string> b("Rutabaga");
        cout << "b.getVal() = " << b.getVal() << endl;
        b.setVal("Turnip");
        cout << "b.getVal() = " << b.getVal() << endl;
    }

    return 0;
}
