// Example 5_4 : pair, optional, any
// Created by Oleksiy Grechnyev 2017

#include <string>
#include <iostream>

#include <utility>
#include <optional>
#include <any>
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

    // optional
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
        
    }
    
    // any
    {
        
    }

    return 0;
}
