#pragma once
// By Oleksiy Grechnyev 2017

#include <iostream>

#include "./Entity.h"

class Monster : public Entity{
public:
    /// Constructor
    Monster(const std::string & name, const std::string & type, int level) :
        Entity(name),   // Calling parent constructor
        type(type),    // Initializing local fields
        level(level)
    {}

    /// Implement Entity::printMe()
    virtual void printMe() override {
        // Field 'name' comes from Entity
        std::cout << "Monster{ name : " << name << " , type : " << type <<
                     " , level : " << level << " }" << std::endl;
    }

    /// Override Entity::action()
    virtual void action() override {
        std::cout << "I am a level " << level << " " << type << " ! " << std::endl;
        Entity::action();  // Call the parent !
    }

protected:
    std::string type;
    int level;
};
