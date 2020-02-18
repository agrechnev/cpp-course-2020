// Example 5.1 : scope, memory management unique_ptr
// Created by Oleksiy Grechnyev 2017, 2020
// Class Tjej is used a lot here, it logs Ctors and Dtors


#include <iostream>
#include <string>
#include <memory>

#include "Tjej.h"

using namespace std;

// Global variable
Tjej glob("Globula Statika");


//==============================
// Factory (source) function example 1
unique_ptr<Tjej> factory1(const string & name){
    return make_unique<Tjej>(name); // No need for explicit move here
}

//==============================
// Factory (source) function example 2 : the same
unique_ptr<Tjej> factory2(const string & name){
    unique_ptr<Tjej> upT = make_unique<Tjej>(name);
    return upT;  // Will work without move also
}
//==============================
// Sink (consumer) example which destroys a unique_ptr<Tjej> object
// Note the parameter BY VALUE unique_uupTr<Tjej> uupT
void sink(unique_ptr<Tjej> upT){  // By value !!! NO ref ! MOVED here !
    cout << "Sink: name = " << upT->getName() << endl;
    // Now upT and the managed object are destroyed as they go out of scope !
}
//==============================
int main(){
    {
        cout << "\nLocal and temp objects :  \n\n";
        Tjej *pT = new Tjej("Heap Tjej");
        Tjej t1("Local Tjej");
        Tjej("Temp Tjej");
        delete pT;
    }

    {
        cout << "\nunique_ptr example 1:  \n\n";
        unique_ptr<Tjej> upT1 = make_unique<Tjej>("Maria Traydor");  // Create a new heap object owned by a unique upTR
        unique_ptr<Tjej> upT2(new Tjej("Tynave")); // This is also OK


        cout << "sizeof(unique_ptr<Tjej>) = " << sizeof(unique_ptr<Tjej>) << endl;

        cout << "name1 = " << upT1->getName() << endl;  // You can access members like this
        cout << "name2 = " << (*upT2).getName() << endl;  // Or like this

        // Let's create some more
        unique_ptr<Tjej> upT3 = move(upT1); // Move is OK, copy is not
        unique_ptr<Tjej> upT4 = make_unique<Tjej>("Sophia Esteed");
        auto upT5 = make_unique<Tjej>("Nel Zelpher");  // We can use auto like this !
        auto upT6 = make_unique<Tjej>("Clair Lasbard");
        auto upT7 = make_unique<Tjej>("Mirage Koas");
        auto upT8 = make_unique<Tjej>("Blair Lansfeld");

        cout << "Deleting some objects by hand :" << endl;

        upT4.reset(); // Force delete
        upT5 = nullptr; // Same effect !
        Tjej * pT6 = upT6.get(); // Get raw pointer. OK, but don't delete it !
        Tjej * pT7 = upT7.release(); // Release ownership and get the raw pointer
        delete pT7; // Now we have to delete it by hand !!!!


        // Release ownership and give a regular pointer

        cout << "About to clean up automatically :" << endl;
        // Here all managed objects get destroyed by the unique_ptr destructor
    }

    {
        cout << "\nunique_ptr example 2: Source (factory) and sink (consumer).  \n\n";
        // Create a new heap object owned by a unique_ptr
        unique_ptr<Tjej> upT = factory2("Souce of all magic");
        // We can use the managed object
        cout << "name = " << upT->getName() << endl;
        // Now we move upT to sink(), where it is destroyed
        sink(move(upT));
        cout << "After sink" << endl;
    }

    return 0;
}
