// Example 4_3 : Diamond problem in multiple inheritance
// Created by Oleksiy Grechnyev 2017

#include <iostream>
using namespace std;
//=========================
// This example is shamelessly stolen from Wikipedia

struct Animal {
    Animal(double w) : weight(w) {}
    virtual void eat() {
        cout << "Animal::eat()" << endl;
    }
    double weight;
};

// Two classes virtually inheriting Animal:
// If you change "public virtual" -> "public", it would not work
struct Mammal : public virtual Animal {
    Mammal(double w) : Animal(w*1000) {}
    virtual void breathe() {
        cout << "Mammal::breathe()" << endl;
    }
};

struct WingedAnimal : public virtual Animal {
    WingedAnimal(double w) : Animal(w*100) {}
    virtual void flap(){
        cout << "WingedAnimal::flap()" << endl;
    }
};

// A bat is still a winged mammal
struct Bat : public Mammal, public WingedAnimal {
    // Bat calls the Animal(w) constructor also !!!
    Bat(double w) : Mammal(w), WingedAnimal(w), Animal(w) {}
};
//=========================
int main(){

    cout << "Diamond problem and virtual inheritance demo:  \n\n";

    Bat b(0.05);

    b.eat();
    b.breathe();
    b.flap();

    // Result : 0.05 and not 50 and not 5
    // Only the Animal(w) in Mammal() is used
    // Animal(w*1000) and Animal(w*100) are not used when creating Bat!
    cout << "weight = " << b.weight << endl;

    return 0;
}
