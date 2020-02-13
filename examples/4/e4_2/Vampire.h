#pragma once
// By Oleksiy Grechnyev 2017

#include "./Monster.h"
#include "./Person.h"

/// Vampire is both a Person and a Monster. Multiple inheritance !
class Vampire : public Monster, public Person {
public:
    /// Constructor
    Vampire(const std::string & name, int age) :
        Monster(name + " the Bloodthirsty", "Vampire", age/10), // Monster constructor
        Person(name, age) // Person constructor
    {}

    /// Overrides Monster::printMe()
    virtual void printMe() override {
        // Note : parent is not called
        // We can access all protected fields !
        // Note : Both Monster and Person have a field 'name' !!!
        std::cout << "Vampire{\nMonster::name : " << Monster::name << " , \n";
        std::cout << "Monster::type : " << type << " , \n";
        std::cout << "Monster::level : " << level << " , \n";
        std::cout << "Person::name : " << Person::name << " , \n";
        std::cout << "Person::age : " << age << "\n}" << std::endl;
    }

    // action() is inherited from Monster as public

    /// Overrides Person::sayHi()
    virtual void sayHi() override {
        std::cout << "sayHi() Vampire version : \n";
        Person::sayHi(); // Call parent
    }

    /// Overrides non-virtual Person::sayHi(), cannot use override keyword
    void sayBye() {
        std::cout << "sayBye() Vampire version : \n";
        Person::sayBye(); // Call parent
    }
};
