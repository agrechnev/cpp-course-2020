// Example 7.3 : istream, ostream 
// Created by Oleksiy Grechnyev 2017

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

//==============================
// This is a simple ostream impementation of printf
// This one uses a fixed-size static buffer and
// does not support e.g. C++ strings without .c_str()
// Making a better one like Boost format() is much harder
template <typename...  Params>
void print(std::ostream & os, const std::string & fmt, Params... p) {
    constexpr size_t SIZE = 1000;
    static char buffer[SIZE];  // Hidden global buffer = ugly
    std::snprintf(buffer, SIZE, fmt.c_str(), p...);
    os << buffer;
}
//==============================
int main(){
    using namespace std;
    {
        cout << "\nElementary use of cin, cout, cerr :\n\n";

        int a = 3;
        int b = 7;

        cout << "a = " << a << " , b = " << b << " , a*b = " << a*b << endl;

        string fileName("idiot.cfg");
        cerr << "[cerr example]Fatal error : file " << fileName << " not found ! \n";

        double c, d;
        cout << "Enter c, d :" << endl;
        cin >> c >> d;

        cout << "c = " << c << " , d = " << d << " , c*d = " << c*d << endl;

        // cin with string reads only one word (up to a whitespace)
        cout << "Enter your full name (e.g. Mary Ann Carter)\n";
        string name;
        cin >> name;
        cout << "You entered " << name << endl;
        getline(cin, name); // Read the rest of the line

        cout << "OOPS ! It didn't work as expected !\n\n";
        cout << boolalpha << cin.eof() << endl;
        cout << "Let's try again with getline() \n";
        cout << "Enter your full name (e.g. Mary Ann Carter)\n";
        getline(cin, name); // Read full line
        cout << "You entered " << name << endl;

        cout << "It's a good idea to read input streams with getline() !" << endl;

    }

    {
        puts("\nC I/O : using printf(), scanf(), puts(), fgets() :\n");

        puts("Enter a, b :"); // Print a string to stdout
        double a, b;
        scanf("%lf %lf", &a, &b); // Read a, b. Pointers !
        getchar(); // Skip newline
        printf(" %lf * %lf = %15.10lf\n", a, b, a*b); // Print stuff

        constexpr size_t SIZE = 100;
        char s[SIZE]; // Buffer for a C-string
        puts("Your full name ?");
        fgets(s, SIZE, stdin);
        printf("Hello %s !!!\n", s);
    }

    {
        cout << "\nManipulators 1 : \n\n";

        cout << "Flags : " << endl;
        // (no)boolalpha
        cout << "boolalpha: "
             << true << " " << boolalpha << true << noboolalpha << " "
             << false << " " << boolalpha << false << noboolalpha << endl;
        // (no)showbase -- see below
        // (no)showpoint
        cout << "showpoint: " << 3.0 << " " << showpoint << 3.0 << noshowpoint << endl;
        // (no)showpos
        cout << "showpos: " << 13 << " " << showpos << 13 << noshowpos << endl;
        // unitbuf = flush buffer after each write
        // uppercase (does NOT affect char/string !)
        cout << "uppercase: "<< 1.e30  << " "<< uppercase << 1.e30 << nouppercase << endl;

        cout.precision(20);      // Set double precision
        cout << setw(1) << 1 << setw(2) << 2 << setw(3) << 3 << setw(4) << 4
             << setw(5) << 5 << setw(6) << 6 << endl;
        cout << left << setfill('A') << setw(10) << 1
             << setfill('B') << right << setw(10) << 2 << endl;
        cout << scientific << uppercase << setfill('&') << setw(30) << 1.0/3 << endl;
        cout << nouppercase  << defaultfloat;
    }

    {
        cout << "\nManipulators 2 : \n\n";

        int i = 45;
        cout << "Dec : " << i << " " << showbase << i  << noshowbase << endl;
        cout << "Oct : " << oct << i << " "  << showbase << i  << dec << noshowbase << endl;
        cout << "Hex : " << hex << i << " "  << showbase << i  << dec << noshowbase << endl;
        cout << "HEX : " << uppercase << hex << i << " "  << showbase << i  << dec
             << noshowbase << nouppercase << endl;
        // hexfloat is apparently broken in mingw !!!
        //cout << "Hexfloat:" << hexfloat << 1.0/3 << defaultfloat << endl;
    }

    {
        cout << "\nString streams : \n\n";

        istringstream iss("13.98  17.32");
        ostringstream oss;

        double a, b;
        iss >> a >> b;
        oss << "a = " << a << " , b = " << b << " , a*b = " << a*b << endl;

        // Now we want to reuse iss, we need clear() !!!
        iss.str("3.0 7.0");  // Change the string in iss
        iss.clear(); // To avoid failure on EOF !

        iss >> a >> b;  // And read again
        oss << "a = " << a << " , b = " << b << " , a*b = " << a*b << endl;

        cout << "oss.str() = " << oss.str();  // Write the result
    }

    {
        cout << "\nExceptions : \n\n";
        istringstream in("Bla Bla !");
        in.exceptions(ios::eofbit | ios::failbit | ios::badbit);
        try {
            int a;
            in >> a;
            // A famous bug in MinGW/ gcc. Which one will be caught in your version ?
        } catch (const system_error &  e) {
            cerr << "system_error caught !" << endl;
            cerr << e. what() << endl;
        } catch (const exception &  e) {
            cerr << "exception caught !" << endl;
            cerr << e. what() << endl;
        }

    }

    {
        cout << "\nUTF-8 output \n\n";

        cout << "If you don't see right output in Windows, \n";
        cout << "type 'chcp 65001' in the windows console" << endl;

        cout << "Український текст із літерами ґҐ !"  << endl;
        cout << "Svenska bokstäver ÅåÖöÄä !" << endl;
        cout << "Hiragana :  あ , い , う , え , お " << endl;
    }


    {
        cout << "\nprint() : ostream version of printf() \n\n";

        print(cout, "8.1 = %10.13lf , 9 = %d \n", 8.1, 9);
    }

    return 0;
}
