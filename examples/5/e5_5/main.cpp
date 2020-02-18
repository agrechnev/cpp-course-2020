// Example 5.5 : enum, enum class 
// Created by Oleksiy Grechnyev 2017, 2020

#include <iostream>
#include <iomanip>
#include <string>

//==============================
int main(){
    using namespace std;
    {
        cout << "\nEnum 1 : simple enum \n\n";

        enum Color {red, green, blue, cyan, magenta, yellow, orange};  // Uscoped

        Color a = magenta;                    // Used without any scope ! BAD !
        Color b = a;
        cout << "b = " << b << endl;      // Can print, prints 4
        int i = a;                        // Can assign Color to int
        cout << "i = " << i << endl;      // Prints 4
    }

    {
        cout << "\nEnum 2 : enum class \n\n";

        enum class Color {red, green, blue, cyan, magenta, yellow, orange};  // Scoped

        Color a = Color::magenta;                    // magenta is in scope Color:: ! GOOD!
        Color b = a;
        cout << "b = " << (int)b << endl;      // Explicit cast, prints 4
        int i = (int) a;                        // Explicit cast
        cout << "i = " << i << endl;      // Prints 4
    }

    {
        cout << "\nEnum 3 : initial values : start with 17 \n\n";

        enum Color {red = 17, green, blue, cyan, magenta, yellow, orange};  // Uscoped, sttarts with 17

        cout << red << " " << green << " " << blue << " " << cyan << " " << magenta << " " << yellow << " " << orange << endl;

        // Using an anonymus enum for constants
        enum {OK = 0, FILE_NOT_FOUND = 1234, BAD_DATA = 1235, IO_ERRROR = 1236};
    }
    {
        cout << "\nEnum 4 : initial values : Danger ! \n\n";

        enum Color {red, green, blue, cyan = 1, magenta, yellow, orange};  // Uscoped, sttarts with 17

        cout << red << " " << green << " " << blue << " " << cyan << " " << magenta << " " << yellow << " " << orange << endl;
    }


    {
        cout  << "\nEnum 5 :enum underlying types. \n\n";
        enum Color1 : int {red, green, blue, cyan, magenta, yellow, orange};
        enum class Color2 : unsigned char {red, green, blue, cyan, magenta, yellow, orange};
        enum class Color3 : long long {red, green, blue, cyan, magenta, yellow, orange};

        cout << "sizeof(Color1) = " << sizeof(Color1) << endl;
        cout << "sizeof(Color2) = " << sizeof(Color2) << endl;
        cout << "sizeof(Color3) = " << sizeof(Color3) << endl;
    }

    return 0;
}
