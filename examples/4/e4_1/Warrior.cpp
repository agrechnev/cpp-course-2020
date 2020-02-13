//
// Created by  Oleksiy Grechnyev on 9/8/2017.
//

#include <iostream>
#include "Warrior.h"

namespace MyNS {

    Warrior::Warrior(const std::string &name, const std::string &weapon, int age) :
            name(name),   // Initialize the fields, overriding defaults
            weapon(weapon),
            age(age) {
        // Constructor body (often empty)
        std::cout << "Warrior Ctor : ";
        printWarrior(*this); // Now the object is fully created we can print it
        // this == pointer to the current object
        // *this == current object
        ++warriorCount; // Increase the static var by 1
    }

    const std::string &Warrior::getName() const {
        return name;
    }

    void Warrior::setName(const std::string &name) {
        Warrior::name = name;
    }

    // This is a static method !!!
    void Warrior::printWarriorCount()
    {
        // We can use static var warriorCount in a static method
        std::cout << "warriorCount = " << warriorCount << std::endl;
    }

    void printWarrior(const Warrior &w) {
        std::cout << "Warrior{ name : " << w.name << ", weapon : " << w.weapon << " , age : " << w.age << "}" << std::endl;
    }

    // Static fields and methods must be implemented in CPP (without static keyword)
    int Warrior::warriorCount = 0;

}

// No we are outside any namespaces
// We can also work with namespaces like this, but I don't like it
void MyNS::Warrior::within(int year) const{
    using namespace std;;

    cout << "The year was  " << year << endl;
    cout << "The brave " << age << "-year old warrior named " << name << endl;
    cout << "embarked on a quest armed with " << weapon << endl;
}

