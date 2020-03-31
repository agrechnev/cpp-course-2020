// Example 11.1 Template basics
// Created by Oleksiy Grechnyev 2017
#include <iostream>
#include <string>
#include <vector>
#include <array>

#include "./MyArray.h"

using namespace std;
//==============================
// Simple template functions
//==============================
/// Compare function based on <
template <typename T>
int compare(const T & a, const T & b) {
    if (a < b)
        return -1;
    else if (b < a)
        return 1;
    else
        return 0;
}

// Specialization for float
template <>
int compare(const float & a, const float & b) {
    if (a < b)
        return -7;
    else if (b < a)
        return 7;
    else
        return 0;
}


/// Multiply anything by a compiler-specified int parameter N
template <int N, typename T>  // N is first, T can be deduced
T mul(const T & t) {
    return t*N;
}

//==============================
// Containers

/// Print a container with range for + auto
template <typename C>
void print1(const C & c){
    for (const auto & e : c)
        cout << e << " ";
    cout << endl;
}

/// Print a container with range for + and auto (requires value_type)
template <typename C>
void print2(const C & c){
    for (const typename C::value_type & e : c)
        cout << e << " ";
    cout << endl;
}

/// Print a container with iterators
template <typename C>
void print3(const C & c){
    for (auto it = cbegin(c); it != cend(c); ++it)
        cout << *it << " ";
    cout << endl;
}


/// My own version of std::find, iterator-based
template <typename I, typename T>
I myFind(const I & begin, const I & end, const T & val){
    for (I it = begin; it != end; ++it) {
        if (val == *it)
            return it;
    }
    return end;
}

/// Find first negative number in container given by 2 iterators, stupid version
/// Return the element as const ref
template <typename R, typename I>
const R & findNeg1(const I & begin, const I & end){
    for (I it = begin; it != end; ++it)
        if (*it < 0)
            return *it;
    throw runtime_error("NOT FOUND !");
}

/// Clever version with decltype
template <typename I>
auto findNeg2(const I & begin, const I & end) -> const decltype(*end) & {
    for (I it = begin; it != end; ++it)
        if (*it < 0)
            return *it;
    throw runtime_error("NOT FOUND !");
}

//==============================
// Built-in arrays, do not work with pointers !

/// constexpr array size
template <typename T, size_t N>
constexpr size_t arraySize(T (&a)[N]){
    return N;
}

/// My own begin(), end() implementation for an array (iterators are pointers)
template <typename T, size_t N>
T * myBegin(T (&a)[N]){
    return & a[0];
}

template <typename T, size_t N>
T * myEnd(T (&a)[N]){
    return & a[N];
}

//==============================
// main() 
//==============================
int main() {
    {
        cout << "\nSimple template functions : \n\n";
        cout << "compare() : \n";
        cout << "compare(3, 4) = " << compare(3, 4) << endl; // int
        cout << "compare(3, 3) = " << compare(3, 3) << endl; // int
        cout << "compare(3, 2) = " << compare(3, 2) << endl; // int

        cout << "compare(3.0, 2.5) = " << compare(3.0, 2.5) << endl; // double

        cout << "compare(3.0f, 2.5f) = " << compare(3.0f, 2.5f) << endl; // float (specialization !)

        //        cout << compare(3, 2.5);   // Error ! Cannot resolve type !
        cout << "compare<double>(3, 2.5) = " << compare<double>(3, 2.5) << endl; // OK, double

        cout << "compare(false, true) = " << compare(false, true) << endl; // bool

        // string (lexicographical compare)
        cout << "compare(string(\"ABC\"), string(\"AB\")) = " << compare(string("ABC"), string("AB")) << endl;
        cout << "compare<string>(\"ABC\", \"ABC\") = " << compare<string>("ABC", "ABC") << endl;
        cout << "compare<string>(\"ABC\", \"ABCD\") = " << compare<string>("ABC", "ABCD") << endl;
        cout << "compare<string>(\"ABC\", \"AC\") = " << compare<string>("ABC", "AC") << endl;

//        cout << compare(cerr, cout); // Error, no operator< !

        cout << "mul<3>(2.1) = " << mul<3>(2.1) << endl; // The type is deduced (double)
        cout << "mul<3, float>(2.1) = " << mul<3, float>(2.1) << endl; // The type is specified

//        int i = 17;
//        cout << mul<i, int>(2) << endl;   // Error, i is not constexpr !
    }

    {
        cout << "\nContainer template functions : \n\n";
        vector<string> names{"Maria", "Nel", "Sophia", "Mirage", "Peppita", "Clair"};
        cout << "print1(names) : \n";
        print1(names);
        cout << "print2(names) : \n";
        print2(names);
        cout << "print3(names) : \n";
        print3(names);

        // This is an array, not container
        const string undead[] = {"Skeleton", "Zombie", "Vampire", "Wight", "Wraith", "Dreadknight", "Lich"};
        cout << "print1(undead) : \n";
        print1(undead);
//        print2(undead);  // Error : No value_type
        cout << "print3(undead) : \n";
        print3(undead);

        cout << "myFind() : \n";
        cout << myFind(names.cbegin(), names.cend(), "Clair") - names.cbegin() << endl;

        cout << "findNeg() : \n";
        vector<int> vi{3, 4, 0, 5, -17, 12 -2, 4};
        cout << findNeg1<int>(vi.cbegin(), vi.cend()) << endl;
        cout << findNeg2(vi.cbegin(), vi.cend()) << endl;

    }

    {
        cout << "\nMyArray : \n\n";
        MyArray<string, 6> names{"Maria", "Nel", "Sophia", "Mirage", "Peppita", "Clair"};
        // Check that it works with range for and iterators
        cout << "print1(names) :";
        print1(names);
        cout << "print2(names) :";
        print2(names);
        cout << "print3(names) :";
        print3(names);

        // Overwrite it with some more data
        for (int i = 0; i < 6; ++i) {
            // Both versions work
            names.at(i) = "value # " + to_string(i);
//            names[i] = "value # " + to_string(i);
        }

        // Now print it
        cout << "names = " << endl;
        for (int i = 0; i < 6; ++i) {
//            cout << names.at(i) << endl;
            cout << names[i] << endl;
        }

        // Now let's test assign from an terator
        cout << "\nassign() from an iterator\n";
        vector<string> v{"Mouse", "Rat", "Guinea_Pig", "Vole", "Chinchilla", "Hamster"};
        names.assign(v.begin(), v.end());
        cout << "print1(names) :";
        print1(names);

        // Check == and !=
        cout << "\n == and != \n";
        cout << boolalpha;
        MyArray<string, 6> names2 = names; // Default copy ctor
//        names2[1] = "RAT"; // Change if needed
        cout << "names2 == names : " << (names2 == names) << endl;
        cout << "names2 != names : " << (names2 != names) << endl;
    }
    return 0;
}
