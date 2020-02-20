// Example 6.5 : strings
// Created by Oleksiy Grechnyev 2017, 2020

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <set>

#include <codecvt>   // for codecvt_utf8
#include <locale>    // for wstring_convert
//==============================
int main(){
    using namespace std;
    {
        cout << "\nConstructors :\n\n";

        // Literals and C-strings are 0-terminated
        // LIteral is a const char [] and NOT a string object !!!

        string s1("Bastard Sword");  // From a literal (const char [])
        cout << "s1 = " << s1 << endl;

        const char * cS = "Heavy Crossbow";   // From a C-string
        string s2(cS);
        cout << "s2 = " << s2 << endl;

        string s3(18, 'Z');  // 18 copies of char Z
        cout << "s3 = " << s3 << endl;

        string s4("Mary Had a Little Lamb", 8); // First 8 chars of a literal
        cout << "s4 = " << s4 << endl;

        string s5("Mary Had a Little Lamb" + 5, 12); // Adding int to literal moves position !
        cout << "s5 = " << s5 << endl;

        string s6(s1, 8);  // Take chars STARTING from position 8 in s1
        cout << "s6 = " << s6 << endl;

        string s7(s2, 6, 5);   // String, start, length
        cout << "s7 = " << s7 << endl;

        string s8; // Empty string

        string s9 = "Baron of Hell";   // Assignment, also works for implicit conversion
        cout << "s9 = " << s9 << endl;

        // assing() sets an existing string constructor-like (many forms)
        s3.assign(s2, 6, 5);  // String, start, length
        cout << "s3 = " << s3 << endl;
    }


    {
        cout << "\nString operation :\n\n";

        string s1 = "Take a look to the sky just before you die";
        cout << "s1 = " << s1 << endl;

        cout << "s1.size() = " << s1.size() << endl;
        cout << "s1.length() = " << s1.length() << endl;

        // substr
        cout << "s1.substr() = " << s1.substr() << endl;
        cout << "s1.substr(7) = " << s1.substr(7) << endl;
        cout << "s1.substr(7, 11) = " << s1.substr(7, 11) << endl;

        //c_str() ; Returns a 0-terminated C string
        // C-string return lives only as long as the string object alive and not modified !!!
        cout << "s1.c_str() = " << s1.c_str() << endl;

        // Get the raw data (might be not 0-terminated !!!)
        const char * raw = s1.data();
    }


    {
        cout << "\nContainer operations :\n\n";

        string s = "Who's to say where the wind will take you";

        // Print with a range for
        for (char c : s)
            cout << c;
        cout << endl;

        // Modify with a range for
        for (char & c : s)
            c = toupper(c);

        // Print with an iterator
        for (auto it = s.cbegin(); it != s.cend(); ++it)
            cout << *it;
        cout << endl;

        // All algorithms can be used on strings
        // Sort
        sort(s.begin(), s.end());
        cout << s << endl;
    }

    {
        cout << "\ncapacity, push_back(), reserve :\n\n";

        string s;
        for (int i = 0; i<65; ++i){
            cout << "size = " << s.size() << " , capacity = " << s.capacity() << endl;
            s.push_back('Z');
        }

        // We get 15, 30, 60, 120 ...
        // 15 is the local capacity (stored in-place)
        // If more than 15 chars, we'll need HEAP

        s.reserve(100); // Reserve space

        s.shrink_to_fit(); // Shrink
        cout << "\nAfter shrink :\n";
        cout << "s = " << s << endl;
        cout << "size = " << s.size() << " , capacity = " << s.capacity() << endl;

        s.resize(27);   // Resize
        cout << "\nAfter resize :\n";
        cout << "s = " << s << endl;
        cout << "size = " << s.size() << " , capacity = " << s.capacity() << endl;

        s.clear();
        cout << "\nAfter clear :\n";
        cout << "s = " << s << endl;
        cout << "size = " << s.size() << " , capacity = " << s.capacity() << endl;


        s.clear();   // Remove everything, capacity=65 still !
        cout << "\nAfter clear :\n";
        cout << "s = " << s << endl;
        cout << "size = " << s.size() << " , capacity = " << s.capacity() << endl;

        s.shrink_to_fit(); // Shrink again, we get back to size = 0, capacity=15 !
        cout << "\nAfter shrink :\n";
        cout << "s = " << s << endl;
        cout << "size = " << s.size() << " , capacity = " << s.capacity() << endl;
    }

    {
        cout << "\ninsert, erase :\n\n";

        // string has index-based insert, same syntax as ctor and assign
        string s1 = "Lucy Liu";
        cout << "s1 = " << s1 << endl;

        s1.insert(5, "Alexis ");    // Insert substring before position 5
        cout << "s1 = " << s1 << endl;

        s1.insert(0, string("One Gorgeous Two"), 4, 9);    // Insert in the beginning (before 0)
        cout << "s1 = " << s1 << endl;

        s1.insert(s1.size(), 3, '!');    // Insert in the end, 3 times '!'
        cout << "s1 = " << s1 << endl;

        // Of course, iterator-based insert can be used as well
        // It only works with char, lists and iterators, no strings!
        auto pos = s1.begin() + 9;
        pos = s1.insert(pos, '?') + 1;
        cout << "s1 = " << s1 << endl;

        string s2(" Deadly ");
        s1.insert(pos, s2.cbegin(), s2.cend());
        cout << "s1 = " << s1 << endl;

        s1.erase(0, 18);   // pos, length to delete
        cout << "s1 = " << s1 << endl;

        pos = s1.begin() + 5;
        s1.erase(pos, pos + 7);  // Erase with iterators
        cout << "s1 = " << s1 << endl;

        s1.erase(8);
        cout << "s1 = " << s1 << endl;
    }

    {
        cout << "\n+, +=, append(), replace() :\n\n";

        string s1 = string("One ") + "Two " + "Three";      // OK
        cout << "s1 = " << s1 << endl;
        string s2 = "One " + string("Two ") + "Three";      // OK
        cout << "s2 = " << s2 << endl;
        string s3 = "One " + ("Two " + string("Three"));    // OK
        cout << "s3 = " << s3 << endl;
//        string s4 = "One " + "Two " + string("Three");      // Error
//        string s4 = "One " + "Two " + "Three";              // Error


        string s = "Alpha ";
        cout << "s = " << s << endl;

        // Append in the end
        s.append("Beta ");
        cout << "s = " << s << endl;
        // Append a substring of a C-string
        s.append("Gamma Delta ", 6);
        cout << "s = " << s << endl;

        // += works like append
        s += "Epsilon ";
        cout << "s = " << s << endl;

        // Replace works like erase, then insert
        s.replace(6, 4, "OMEGA");
        cout << "s = " << s << endl;
    }

    {
        cout << "\nfind() :\n\n";

        string s("Gorgeous ? Deadly Lucy Alexis Liu!!!");
        cout << "s = " << s << endl;
        cout << "s.size() = " << s.size() << endl;


        auto result = s.find("Alex");  // string::size_type actually
        cout << "s.find(\"Alex\") = " << result << endl;

        // Find a substring
        result = s.find("Alexander", 5);
        cout << "s.find(\"Alexander\", 5) = " << result << endl;  // npos
        if (string::npos == result)
            cout << "Not found !!!" << endl;

        cout << "s.find(\" L\") = " << s.find(" L") << endl;   // Find first
        cout << "s.rfind(\" L\") = " << s.rfind(" L") << endl; // Find last

        // Find first of characters
        cout << "s.find_first_of(\".,?!;;\") = " << s.find_first_of(".,?!;;") << endl;
        // Or last
        cout << "s.find_last_of(\".,?!;;\") = " << s.find_last_of(".,?!;;") << endl;

        // Find first not of characters
        cout << "s.find_first_not_of(\".,?!;;\") = " << s.find_first_not_of(".,?!;;") << endl;
        // Or last
        cout << "s.find_last_not_of(\".,?!;;\") = " << s.find_last_not_of(".,?!;;") << endl;


        cout << "\nALgorithm std::find() :\n";
        // Algorithm searches work for string but are less convenient
        auto it = find(s.cbegin(), s.cend(), 'L');  // Function, not method !
        cout << it - s.cbegin() << endl;

        it = find_if(s.cbegin(), s.cend(), [](char c)->bool{
            return set<char>{'?','!', '.', ',', ':', ';'}.count(c);
        });
        cout << it - s.cbegin() << endl;

        const string s2("Alex");  // Search for Alex with algorithms
        it = search(s.cbegin(), s.cend(), s2.cbegin(), s2.cend());
        cout << it - s.cbegin() << endl;

        const string s3(".,?!;;");  // Search for any of the ".,?!;;" with algorithms
        it = find_first_of(s.cbegin(), s.cend(), s3.cbegin(), s3.cend());
        cout << it - s.cbegin() << endl;
    }

    {
         cout << "\nComparing strings :\n\n";

         cout << boolalpha;
         cout << (string("Mary Ann") == string("Mary Ann")) << endl;      // OK
         cout << ("Mary Ann" == string("Mary Ann")) << endl;              // OK
         cout << (string("Mary Ann") == "Mary Ann") << endl;              // OK
         cout << ("Mary Ann" == "Mary Ann") << endl;       // Compares pointers, not strings !!!

         cout << string("abcd").compare("abce") << endl;   // -1
         cout << string("abcd").compare("abc") << endl;    // 1
         // Compare two substrings
         cout << string("Alpha Two Three Tango")
                 .compare(6, 9, string("One Two Three Four"), 4, 9) << endl;    // 0

    }

    {
         cout << "\nNumber-string conversion :\n\n";

         cout << to_string(-17) << endl;
         cout << to_string(0.123456789) << endl;

         // stoi etc throw invalid_argument or out_of_range
         cout << stoi("101") << endl;

         size_t st;  // Number of characters read
         cout << stoi("101", &st) << endl;
         cout << "st = " << st << endl;

         cout << stoi("101", nullptr, 2) << endl;  // 5, base 2
         cout << stoi("101", nullptr, 5) << endl;  // 26. base 5
         cout << stoi("101", nullptr, 8) << endl;  // 65. base 8
         cout << stoi("101", nullptr, 16) << endl;  // 257. base 16

         // base =0, auto base
         cout << stoi("101", nullptr, 0) << endl;  // 101, decimal
         cout << stoi("0101", nullptr, 0) << endl;  // 65, base 8
         cout << stoi("0x101", nullptr, 0) << endl;  // 257, base 16
    }

    {
        cout << "\nUTF-8 and UTF-16 :\n\n";

        cout << "If it doesn't work on windows, try typing 'chcp 65001' in the windows console." << endl;
        cout << "Or redirect into a file." << endl;

        // Strings can hold UTF-8 and read from/write to streams
        // Your literals must be UTF-8 !
        string s1 = "Український текст!";
        cout << "s1 = " << s1 << endl;

        // UTF-16 to UTF-8 converter object. Ugly, isn't it?
        wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t> cvt;

        // char16_t :  UTF-16 character
        // u16string is the type to hold UTF-16 characetrs
        u16string us1 = cvt.from_bytes(s1);   // Convert UTF-8 to UTF-16 !
        u16string us2 = u"ЇїЄєҐґÅåÖöÄä";    // UTF-8 string literal converted to UTF-16
        u16string us3{0x414, 0x456, 0x432, 0x43a, 0x430};   // Numerical UTF-16 values
        u16string us4{u'Ї', u'ж' , u'а', u' ', u'å', u'ö', u'ä'};   // List of UTF-16 chars

        // You cannot print u16string to cout, first convert to UTF-8 !
        cout << "us1 = " << cvt.to_bytes(us1) << endl;
        cout << "us2 = " << cvt.to_bytes(us2) << endl;
        cout << "us3 = " << cvt.to_bytes(us3) << endl;
        cout << "us4 = " << cvt.to_bytes(us4) << endl;

        cout << "\nNow iterate over individual characters of us2 :\n";

        for (char16_t c : us2)
            cout << cvt.to_bytes(c) << "  " << hex <<(int)c << dec << endl;


    }
    return 0;
}
