// Example 5_4 : pair, optional, any
// Created by Oleksiy Grechnyev 2017

#include <utility>
#include <string>
#include <iostream>
//=========================
int main() {
    using namespace std;
    
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


    return 0;
}
