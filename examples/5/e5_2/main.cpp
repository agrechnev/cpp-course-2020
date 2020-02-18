// Example 5.2 : shared_ptr
// Created by Oleksiy Grechnyev 2017, 2020
// Class Tjej is used a lot here, it logs Ctors and Dtors


#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "Tjej.h"

using namespace std;

//==============================
// Classes for inheritance
class Animal{
public:
    Animal(const string & name) : name(name) {}  // Ctor
    virtual ~Animal() { // virtual Dtor never hurts
        cout << "Animal Dtor : " << name << endl;
    }
    virtual void talk(){
        cout << "Animal : " << name << endl;
    }
protected:
    string name;
};

class Bear: public Animal{
public:
    Bear(const string & name) : Animal(name) {}  // Ctor
    void talk() override {
        cout << " ANGRY BEAR " << name << " : GRRRRRR !!! AWWWWRRRR !!!" << endl;
    }
};

//==============================

// This can be a node for a double linked list
struct Node{

    Node(const string & data) : data(data) {}

    ~Node(){
        cout << "Dtor Node : " << data << endl;
    }

    string data;
    shared_ptr<Node> next;  // shared_ptr in one direction
    weak_ptr<Node> prev;  // and weak_ptr in the other one
};


//==============================
int main(){
   
    {
        cout << "\nshared_ptr demo : \n" << endl;

        shared_ptr<Tjej> s1 = make_shared<Tjej>("Maria Traydor");  // Create like this
        auto s2 = make_shared<Tjej>("Nel Zelpher");  // Or like this
        shared_ptr<Tjej> s3(new Tjej("Sophia Esteed")); // Or like this (ugly)

        // You can also convert unique_ptr to shared_ptr (don't forget move !)
        auto u = make_unique<Tjej>("Mirage Koas");
        shared_ptr<Tjej> s4(move(u));  // u is destroyed, s4 takes over the object

        // We can put them into a container (copy operations)
        vector<shared_ptr<Tjej>> v;
        v.push_back(s1);
        v.push_back(s2);
        v.push_back(s3);
        v.push_back(s4);
        // And create another one directly in the vector
        v.emplace_back(make_shared<Tjej>("Clair Lasbard"));

        // Make some copies
        auto s5 = s1;
        auto s6 = s2;
        // Move is OK as well
        auto s7 = move(s3);
        s2.reset(); // This is OK, only one copy is destroyed
        Tjej * rawPtr = s1.get(); // Get Raw pointer (don't delete it !!!)

        // Print the vector
        for (const auto & s : v)
            cout << "Vector : " << s->getName() << endl;
    }


    {
        cout << "\nshared_ptr polymorhism demo : \n" << endl;

        auto sB = make_shared<Bear>("Teddy");  // Create a shared_ptr<Bear> object

        cout << "Ref upcast :" << endl;
        Animal & rA = *sB;
        rA.talk();

        cout << "Raw ptr upcast :" << endl;
        Animal *pA = sB.get(); // Get the raw Bear * ptr
        pA->talk();

        cout << "shared_ptr upcast :" << endl;
        shared_ptr<Animal> sA = sB;  // Implicit upcast
        sA->talk();

        cout << "shared_ptr downcast :" << endl;
        shared_ptr<Bear> sB1 = static_pointer_cast<Bear>(sA);    // No checks ! Unsafe.
        shared_ptr<Bear> sB2 = dynamic_pointer_cast<Bear>(sA);   // Checks. Safe.
        sB1->talk();
        sB2->talk();
    }  // The managed object is deleted here


    {
        cout << "\nweak_ptr demo : \n" << endl;

        // Create 2 nodes pointing at each other
        auto s1 = make_shared<Node>("Nel Zelpher");
        auto s2 = make_shared<Node>("Maria Traydor");

        s1->next = s2;
        s2->prev = s1;  // A weak_ptr

        weak_ptr<Node> w = s2->prev;  // weak_ptr can be copied
        // We can create a shared_ptr out of a weak_ptr for a temporary ownership
        if (! w.expired()){
            shared_ptr<Node> s = w.lock();  // s is actually a copy of s1
            cout << "s->data = " << s->data << endl;
        } // s is destroyed here, s1, s2 are still alive

    }  // s1, s2 die here and delete the managed objects

    return 0;
}
