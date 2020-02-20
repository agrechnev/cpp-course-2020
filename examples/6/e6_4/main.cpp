// Example 6.4 : std::string, std::string_view
// Created by Oleksiy Grechnyev 2020

#include <iostream>
#include <string>
#include <string_view>

//==============================
int main(){
    using namespace std;
    
    {
        cout << "std::string :\n\n";
        
        // Create string from C-string literal
        string s1("Big [REDACTED]");
        // Concatenate
        s1 += " Gun";
        cout << "s1 = " << s1 << endl;
        cout << "s1.size() = " << s1.size() << endl;
        // Create a 0-terminated C-string (const char *) from it
        const char * c1 = s1.c_str();
        cout << "c1 = " << c1 << endl;
        
        // Find a substring, then remove it
        string s2 = "[REDACTED] ";
        int pos = s1.find(s2);
        cout << "pos = " << pos << endl;
        if (pos != string::npos){
            // Remove the substring
            s1.erase(pos, s2.size());
        }
        
        cout << "s1 = " << s1 << endl;
        
        // iteral with suffix s is std::string, not const char * !
        cout << "std::string literal"s << endl;
    }
    
    {
        cout << "std::string_view :\n\n";
        
        // From C-string
        const char * c1 = "Take a look to the sky just before you die";
        string_view sv1(c1);   // Whole 0-terminated string
        string_view sv2(c1 + 12, 10);  // Substring
        
        // From std::string
        string s3{"It is the last time you will"};
        string_view sv3(s3);   // Whole string
        string_view sv4 = string_view(s3).substr(10, 9);  // Substring
        
        // WRONG !!! Dangling pointer, as string temporary dies !!!
        // string_view sv(string("Error !!!"));
        
        cout << "sv1 = " << sv1 << endl;
        cout << "sv2 = " << sv2 << endl;
        cout << "sv3 = " << sv3 << endl;
        cout << "sv4 = " << sv4 << endl;
        
    }
        
    return 0;
}
