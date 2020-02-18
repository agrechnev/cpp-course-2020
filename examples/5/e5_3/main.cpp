// Example 5_3 : Exceptions
// Created by Oleksiy Grechnyev 2017

#include <iostream>
#include <string>
#include <stdexcept>


//=========================
// Create your own exception like this
struct DiamondException : public std::runtime_error{
    explicit DiamondException(const std::string & s) : runtime_error("Diamond " + s) {}
};

// Or like this
struct SapphireException : public std::exception{
    const char * what() const noexcept override {
        return "Al2O3";
    }
};


// Or like this: you can create your own class not descended from std::exeption
struct RubyException{
    // Returns string, not C-string ! Same syntax though.
    // But what() is NOT printed if not caught, which is a BIG minus
    std::string what() const {
        return "Ruby Weapon";
    }
};

using namespace std;

//=========================

// This is declared nocept, cannot be caught (Compile warning !)
void f4() noexcept {
    cout << "Start f4()" << endl;
    throw runtime_error("The user is an idiot !");
    cout << "End f4()" << endl;
}

void f3(){
    cout << "Start f3()" << endl;
    throw runtime_error("The user is an idiot !");
//    throw logic_error("The user is an idiot !");
    cout << "End f3()" << endl;
}

void f2(){
    try {
        cout << "Start f2()" << endl;
        f3(); // f3 throws
        cout << "End f2()" << endl;
    } catch (...) {
        cout << "Exception is rethrown in f2() !" << endl;
        throw;  // Rethrow
    }
}

void f1() {
    cout << "Start f1()" << endl;
    f2();  // f2 throws
    cout << "End f1()" << endl;
}



//=========================
int main() {
    {
        cout << "\nExceptions 1:\n" << endl;

        using MYINT = int;

        try {
            throw string("Idiot !");  // string
            //            throw "Idiot !";  // const char[] , char * is OK
            //            throw MYINT(19);  // int
            //            throw 17; // int
            //            throw (unsigned)17; // unsigned, not int !


        } catch (int i) {
            cout << "int exception " << i << endl;
        } catch (double d) {
            cout << "double exception " << d << endl;
        } catch (const string & s) {
            cout << "string exception " << s << endl;
        } catch (const char * cS) {
            cout << "char * exception " << cS << endl;
        } catch (...) {
            cout << "Unknown exception" << endl;
        }
    }


    {
        cout << "\nExceptions 2:\n" << endl;

        try {
            f1();  // f1() callf f2() calls f(3) which throws runtime_error
//            f4();  // This cannot be caught beacause of noexcept
        } catch(const runtime_error & e) {
            cout << "Caught std::runtime_error " << e.what() << endl;
        } catch(const exception & e) {
            cout << "Caught std::exception " << e.what() << endl;
        }

    }

    {
        cout << "\nExceptions 3:\n" << endl;

        try {
//            throw DiamondException("Anvil Cell");
//            throw SapphireException();
            throw RubyException();
        } catch(const DiamondException & e) {
            cout << "Caught DiamondException " << e.what() << endl;
        } catch(const SapphireException & e) {
            cout << "Caught SapphireException " << e.what() << endl;
        } catch(const RubyException & e) {
            cout << "Caught RubyException " << e.what() << endl;
        } catch(const runtime_error & e) {
            cout << "Caught std::runtime_error " << e.what() << endl;
        } catch(const exception & e) {
            cout << "Caught std::exception " << e.what() << endl;
        }

    }

    return 0;
}
