// Example 5_4 : pair, optional, any
// Created by Oleksiy Grechnyev 2017

#include <string>
#include <iostream>

#include <utility>
#include <optional>
#include <any>
#include <typeinfo>
//=========================
int main() {
    using namespace std;

    // pair
    {
        cout << "\n\nstd::pair : \n\n";
        
        pair<string, int> p1("Maria Traydor", 19); // Create a pair normally (with Ctor)
        
        auto p2 = make_pair(string("Nel Zelpher"), 23); // Auto-instantiation, easy to get types wrong !
        auto p3 = make_pair<string, int>("Nel Zelpher", 23);   // Better !
        auto p4 = pair<string, int>("Nel Zelpher", 23);     // Same result, use Ctor instead of make_pair
        pair<string, int> p5;
        p5 = {"Sophia Esteed", 19};       // Assign with a list
        // Note: pair can be assigned, copied, moved, stored in containers etc.
        
        cout << p1.first << " : " << p1.second << endl;
        cout << p2.first << " : " << p2.second << endl;
        cout << p3.first << " : " << p3.second << endl;
        cout << p4.first << " : " << p4.second << endl;
        cout << p5.first << " : " << p5.second << endl;
    }

    // optional : Container with either object or no object
    {
        cout << "\n\nstd::optional\n\n" << endl;
        
        optional<string> o1; // Empty optional
        optional<string> o2{"Arboga 10.2%"}; // Optional with a string
        
        cout << "o1.has_value() = " << o1.has_value()  << endl;
        if (o1) {   // Check that o1 is not empty
            cout << "o1.value() = " << o1.value() << endl;  // Throws std::bad_optional_access for empty optional
        }
        cout << "o1.value_or(\"Default string\") = " << o1.value_or("Default string") << endl;   // Replace by default if empty
        
        cout << "\no2.has_value() = " << o2.has_value()  << endl;
        if (o2) {   // Check that o2 is not empty
            cout << "o2.value() = " << o2.value() << endl;  // Throws std::bad_optional_access for empty optional
        }
        cout << "o2.value_or(\"Default string\") = " << o2.value_or("Default string") << endl;   // Replace by default if empty
        
        
        o2.reset(); // Make o2 empty
        // NOw o2 is empty
        cout << "AFter reset() : o2.has_value() = " << o2.has_value()  << endl;
        
        // COnstruct string object in place without copy/move
        o2.emplace("Pripps Blå"); 
        cout << "Now o2.value() = " << o2.value() << endl;
        o2 = nullopt; // Same as reset() : nullify o3
        cout << "AFter nullopt: o2.has_value() = " << o2.has_value()  << endl;
        
        // Construct with make_optional (don't copy/move string object)
        o2 = make_optional<string>("Spendrups");
        cout << "Now o2.value() = " << o2.value() << endl;
    }
    
    // any : Container with object of any type (with copy contructor), can also be empty
    {
        cout << "\n\nstd::any\n\n" << endl;
        
        any a;  // Empty
        cout << "type =" << a.type().name() << ", has_value = " << a.has_value() << endl;
        
        // Now let us assign int to a
        a = 17; 
        cout << "type =" << a.type().name() << ", value = " << any_cast<int>(a) << endl;
        // Compare to a known type
        cout << "(a.type() == typeid(int)) = " <<  (a.type() == typeid(int)) << endl; // Note (), == has lower priority than << !

        // any_cast throws bad_any_cast if the type is wrong !
        try {
            cout << "type =" << a.type().name() << ", value = " << any_cast<double>(a) << endl;
        } catch (const exception & e) {
            cout << "Caught exception : " << e.what() << endl;
        }
        
        // Now let us assign string to a
        a = string("Reimi Saionji");
        cout << "type =" << a.type().name() << ", value = " << any_cast<string>(a) << endl;
        
        // Finally, make a empty again
        a.reset();
        cout << "type =" << a.type().name() << ", has_value = " << a.has_value() << endl;
    }

    return 0;
}
