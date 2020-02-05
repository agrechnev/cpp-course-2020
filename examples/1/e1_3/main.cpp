// Standard header for cout, endl
#include <iostream>

// Standard header for std::string
#include <string>

// Include Boost.format header 
#include <boost/format.hpp>

int main(){
    // boost::format is a powerful formatting tool, similar to printf()
    std::cout << boost::format{"%1%.%2%.%3%"} % 12 % 5 % 2014 << std::endl;
    
    // Also works with C-strings !
    std::cout << boost::format{"I ate %1% %2% today !"} % 8 % "cakes" << std::endl;
    
    // Or with classes (here : std::string)
    int n(50);
    std::string s = "cookies";
    std::cout << boost::format{"I will eat %1% %2% tomorrow !"} % n % s << std::endl;
    
    // Return 0 = OK
    return 0;
}
