// Created by Oleksiy Grechnyev 2017

#pragma once

#include <string>

// ctor = Constructor, dtor = Destructor
// A Demo Class with ctor, dtor, copy/move ctor, copy/move assignment
// with a single std::string field name
// Note: after moving a std::string the original object has empty string,
// Which is show by the dtor
// 
// Note: if you don't include any dtor or copy/move stuff, the 
// Default copy/move ctors and assignments will be similar to mine
class Tjej{
public:
    Tjej() noexcept{
        std::cout << "Default ctor " << name << std::endl;
    }

    // No explicit here. But usually we make it explicit.
    Tjej(const std::string & s) noexcept : name(s){
        std::cout << "Ctor " << name << std::endl;
    }

    Tjej(const Tjej & rhs) noexcept : name(rhs.name)  {
        std::cout << "Copy Ctor " << name << std::endl;
    }

    // Uses rvalue ref (Tjej &&) and std::move
    // Note : without noexcept vector would prefer copy Ctor !
    Tjej(Tjej && rhs) noexcept : name(std::move(rhs.name)){
        std::cout << "Move Ctor " << name << std::endl;
    }

    ~Tjej(){
        std::cout << "Dtor " << name << std::endl;
    }
    
    Tjej & operator= (const Tjej & rhs) noexcept {
        // Check for self-assignment
        if (this != &rhs) 
            name = rhs.name;
        std::cout << "Copy Assignment " << name << std::endl;
        return *this;
    }
        
    Tjej & operator= (Tjej && rhs) noexcept {
        // Check for self-assignment
        if (this != &rhs)
            name = std::move(rhs.name);
        std::cout << "Move Assignment " << name << std::endl;
        return *this;
    }

    /// Getter
    const std::string &getName() const noexcept {
        return name;
    }

    /// Setter
    void setName(const std::string &name) noexcept {
        Tjej::name = name;
    }

private:
    /// Field wiith a default value
    std::string name = "Lilith";
};

