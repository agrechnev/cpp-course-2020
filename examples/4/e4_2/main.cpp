// Example 4.2 : Inheritance, overriding, polymorphism, virtual methods
// Created by Oleksiy Grechnyev 2017

#include <iostream>
#include <memory>

#include "./Monster.h"
#include "./Vampire.h"

int main(){
    using namespace std;
    
    {
        cout << "\nMonster demo : \n\n";
        Monster g("Grshnak", "Goblin", 9);

        cout << "Calling g.action()\n";
        g.action();
        cout << "Calling g.printMe()\n";
        g.printMe();
    }
    
    {
        cout << "\nVampire demo : \n\n";
        Vampire v("Hans", 789);

        cout << "Calling v.action()\n";
        v.action();
        cout << "Calling v.printMe()\n";
        v.printMe();
        cout << "Calling v.Monster::printMe()\n";
        v.Monster::printMe();
        cout << "Calling v.sayHi()\n";
        v.sayHi();
        cout << "Calling v.sayBye()\n";
        v.sayBye();
    }

    {
        cout << "\nPolymorphism and virtual demo : \n\n";
        Vampire v("Lucius", 1234);

        // Reference polymorphism
        Person & p = v; // Person & ref to v, polymorphism !

        cout << "Calling p.sayHi()\n";
        p.sayHi();  // virtual, Vampire::setHi() is called !

        cout << "Calling p.sayBye() : not virtual !!! \n";
        p.sayBye(); // non-virtual, Person::setHi() is called !

        // Pointer polymorphism
        Monster * m = &v; // Person & pointer to v, polymorphism !

        cout << "Calling m->action()\n"; // virtual, Monster::action() is called !
        m->action();
        cout << "Calling m->printMe()\n"; // virtual, Monster::printMe() is called !
        m->printMe();
    }


    return 0;
}
