// Example 6.3 : std::set, std::map
// Created by Oleksiy Grechnyev 2017

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

//=======================================
/// Print a container. Works also with built-in arrays.
/// pair from maps cannot be printed like this
template <typename C>
void print(const C & c){
    for (const auto & e : c)
        cout << e << " ";
    cout << endl;
}
//=======================================
/// Prints a map with range for
template <typename M>
void printMap(const M & m){
    for (const auto & e : m)
        cout << e.first << " : " << e.second << endl;
}
//=======================================
/// Prints a map with iterators
template <typename M>
void printMap2(const M & m){
    for (auto it = m.begin(); it != m.end(); ++it)
        cout << it->first << " : " << it->second << endl;
}

//==============================
int main(){
    {
        cout << "-----------------------------";
        cout << "\nstd::set operations :  \n\n";
        
        set<int> s{1, 22, 2, 3, 19, 1, 3, 8, 12, 19, 22};  // Repeated, unsorted
        // Contains : 1 2 3 8 12 19 22
        cout << "s = "; print(s);

        cout << "s.count(22) = " << s.count(22) << endl;    // Returns 0, 1
        auto pos = s.find(22); // Returns iterator or s.end() if not found
        
        // Insert elements
        s.insert(5);
        s.emplace(7);
        s.insert({11, 13, 17, 19, 23});
        cout << "s = "; print(s);
        // 1 2 3 5 7 8 11 12 13 17 19 22

        // Delete elements
        s.erase(8);
        s.erase(12);
        s.erase(22);
        cout << "s = "; print(s);
        // 1 2 3 5 7 11 13 17 19 23
    }
    {
        cout << "-----------------------------";
        cout << "\nstd::pair :  \n\n";

        pair<string, int> p1("Maria Traydor", 19);
        auto p2 = make_pair("Nel Zelpher", 23);   // Note the implicit conversion const char [] -> string
        pair<string, int> p3;
        p3 = {"Sophia Esteed", 19};           // const char [] -> string

        cout << p1.first << " : " << p1.second << endl;
        cout << p2.first << " : " << p2.second << endl;
        cout << p3.first << " : " << p3.second << endl;
    }

    {
        cout << "-----------------------------";
        cout << "\nstd::map :  \n\n";

        map<string, int> m1{
                {"Maria Traydor", 19},
                {"Nel Zelpher", 23}
        };

        m1.insert({"Mirage Koas", 27});  // Create a new entry
        m1.insert(make_pair("Sophia Esteed", 19));
        m1.emplace("Peppita Rossetti", 14);
        m1["Clair Lasbard"] = 25;  // Create OR change

        m1["Mirage Koas"] -= 1;
        m1.at("Nel Zelpher") -= 1;

        // Increase all values by 1
        for (auto & p : m1)
            p.second += 1;

        cout << "\n m1 = \n"; printMap(m1);

        // Check for an element
        cout << "m1.count(\"Nel Zelpher\") = " << m1.count("Nel Zelpher") << endl;

        auto pos = m1.find("Peppita Rossetti");
        m1.erase(pos);
        m1.erase("Mirage Koas");
        cout << "\n m1 = \n"; printMap(m1);

        cout << "m1.size() = " << m1.size() << endl;
    }


    return 0;
}
