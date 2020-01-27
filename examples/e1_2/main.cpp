// Example 1_2 : Introducing classes, vectors.
// This is example demonstrates many C++ features at a glance, I'll explain them in detail later.
// Created by Oleksiy Grechnyev 2017

// Header iostream (file Input/Output)
#include <iostream>
// Header vector (class std::vector)
#include <vector>
// Header string (class std::string)
#include <string>

// This is the global scope. Functions, classes, global data can be declared here.

/** @brief A heroic brave superhero ultra-violent warrior
 *
 * This is a doxygen-style comment. If your code has lots of these,
 * you can generate doxygen docs out of it. You must have doxygen installed, of course.
 *
 * Put some description of the class here.
 * Here we define our class in the file main.cpp which also has the function main().
 * Usually people put every class into a separate pair of files, like Warrior.h, Warrior.cpp
 */
class Warrior {
public:  // Public stuff goes here
    /** @brief Constructor (allways written as Ctor by real C++ people !)
     *
     * Note the construction const std::string &name,
     * It passes the string 'name' by reference to avoid copying
     * But as it is const, it cannot be modified
     * This is common for class types, not needed (but wouldn't hurt) for a primitive 'int age'
     *
     * @param[in] name
     * @param[in] weapon
     * @param[in] age
     */
    Warrior(const std::string &name, const std::string &weapon, int age) :
            name(name),  // Init class field 'name' with argument 'name'
            weapon(weapon),
            age(age) {
        // Note : Declared here, defined also here
        // Calls own method str()
        std::cout << "Constructor : " << str() << std::endl;
    }

    /// A CLass Method: Convert this object to string, declared here, defined below
    std::string str() const;

    /// Getter to get a private field, returns a const reference
    const std::string &getName() const {
        return name;
    }

    /// Another getter
    const std::string &getWeapon() const {
        return weapon;
    }

    /// Another getter
    int getAge() const {
        return age;
    }

private: // Private stuff goes here
    /// A class field: Warrior's name (short doxygen comment with three '/')
    std::string name;

    /// Another class field: Warrior's weapon
    std::string weapon;

    /// Another class field: Warrior's Age
    int age;
}; // Note the semicolon ';' here, in C++ (unlike Java etc) it is important !

// You can define class methods outside of class definition
std::string Warrior::str() const{
    return "name = " + name + ", weapon = " + weapon + ", age = " + std::to_string(age);
}

//=============================================

/** @brief Function main()
 *
 * This is another doxygen-style comment.
 *
 * @param[in] argc  Number of comand-line agruments + program name
 * @param[in] argv  Program name + comand-line agruments
 * @return          0 if successful, 1 if error
 */
int main(int argc, char **argv){
    // Allows to use names from namespace std, such as 'cout' or 'vector', without prefix 'std::'
    using namespace std;
    
    // Print program name and command-line arguments using a for loop. Arrays and vectors always start with 0 in C++ !
    // Note: C++ does NOT check for index out of range !
    // C++ is a FAST language, not some kind of Java !
    // argv[666] will give undefined behavior, usually a segmentation fault !
    cout << "argc = " << argc << endl << endl;
    for (int i = 0; i < argc; ++i)
        cout << "argv[" << i << "] = " << argv[i] << endl;

    cout << endl; // Skip a line
    // Now let's create a vector of warriors, initializing with a list
    vector<Warrior> warriors{
            {"Brianna", "Lightsaber", 17},  // Initialize each warrior with a list (std::initializer_list)
            {"Sita", "Spear", 15},
            {"Jean Grey", "Telekinesis", 25},
            Warrior("Ashe", "Zodiac Spear", 19) // Or an explicit constructor call
    };

    // Add some more warriors
    warriors.emplace_back("Jaheira", "Club+5", 110); // Construct in-place. Best !
    Warrior wz("Zoe Maya Castillo", "Fists", 20);
    warriors.push_back(wz); // OOPS! A copy operation! BAD !
    warriors.push_back(Warrior("Casca", "Sword", 24)); // move operation : a bit better !

    cout << endl;
    cout << "WARRIORS (range for loop):" << endl;
    cout << endl;

    // Print all warriors using a range-for loop.
    // Again, I use a const reference (const Warrior &) to avoid copying objects
    for (const Warrior & w: warriors)
        cout << w.str() << endl;

    // Print them again with a traditional for loop
    cout << endl;
    cout << "WARRIORS (traditional for loop):" << endl;
    cout << endl;

    for (int i = 0; i < warriors.size(); ++i)
        cout << warriors[i].str() << endl;
    
    // Print them again with an iterator loop
    // Ugly, use iterators for container algorithms like std::sort() instead !
    cout << endl;
    cout << "WARRIORS (iterator for loop):" << endl;
    cout << endl;

    for (auto it = cbegin(warriors); it != cend(warriors); ++it)
        // Note : we use ->str() instead of .str(), because iterator is a pointer-like object !
        // It is one development of C pointers, the other being smart pointers
        cout << it->str() << endl; 
    
    return 0;
}
