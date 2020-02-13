#pragma once
// By Oleksiy Grechnyev 2017

#include <string>

/// This is a common interface (or abstract class) parent for a number of classes
class Entity{
public:

    /// Constructor
    Entity(const std::string &name) :
        name(name) {}

    /// Abstract (aka pure virtual): print some info on the class
    virtual void printMe() = 0;

    /// Some action
    virtual void action(){
        std::cout << "My name is " << name << " ! " << std::endl;
    }

    /// Getter
    std::string getName() const
    {
        return name;
    }

    /// Setter
    void setName(const std::string &value)
    {
        name = value;
    }

protected:  // Use protected instead of private for inheritance !
    /// Name of the entity
    std::string name;
};
