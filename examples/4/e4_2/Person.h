#pragma once
// By Oleksiy Grechnyev

#include <string>
#include <iostream>

/// A very simple class
class Person {
public:
    /// Constructor
    Person(const std::string & name, int age) :
        name(name),
        age(age) {}

    /// A virtual function
    virtual void sayHi(){
        std::cout << "Hello, I am " << name << " and " <<
         "I am " << age << " years old !" << std::endl;
    }

    /// And here we forgot to put virtual, OUCH ! What's gonna happen now?
    void sayBye(){
        std::cout << "Bye Bye from " << name << " : " << age << std::endl;
    }

protected:
     std::string name;
     int age;
};
