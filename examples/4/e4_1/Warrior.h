//
// Created by  Oleksiy Grechnyev on 9/8/2017.
//
#pragma once

#include <string>
#include <iostream>

/// We put it all into a namespace
namespace MyNS {
    /// A demo class with 3 fields, here I use both h and cpp
    /// Every method is declared here, defined in Warrior.cpp
    class Warrior {
    public: //====== Consts
        static constexpr int WARRIOR_CONST = 1001;

    public: //====== Methods
        /// Ctor
        explicit Warrior(const std::string &name, const std::string &weapon, int age);

        /// Default Ctor, we need this because we have other Ctor
        Warrior() = default;

        /// A class method
        void within(int year) const;

        /// Getters and Setters
        const std::string &getName() const;  // Implemented in CPP
        void setName(const std::string &name);

        // Inline getters + setters
        const std::string &getWeapon() const {
            return weapon;
        }

        void setWeapon(const std::string &weapon) {
            Warrior::weapon = weapon;
        }

        int getAge() const {
            return age;
        }

        void setAge(int age) {
            Warrior::age = age;
        }

        /// A static function
        static void printWarriorCount();

        /// A friend function: print the warrior
        friend void printWarrior(const Warrior & w);

    private: //===== Fields
        std::string name{"noname"};  // Cannot use ("noname") , but {} work just fine
        std::string weapon = "noweapon"; // Or like this
        int age = -1;

        /// A static field, must be defined in Warrior.cpp !!!
        static int warriorCount;
    };  // Warrior class

    /// Compilers often don't care, but friend declaration inside a class is not a real declaration
    void printWarrior(const Warrior & w);
}


