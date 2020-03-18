#include <iostream>

#include "config.h"

// Some preprocessor magic to convert defines into string, two macros are needed for some reason
#define STR1(x) #x
#define STR(x) STR1(x)

int main(){
    using namespace std;
    
    // Print variables
    
    // cout << "BRIANNA = " << STR(BRIANNA) << endl;
    
#ifdef WITH_MAGIC
    cout << "WITH_MAGIC = " << STR(WITH_MAGIC) << endl;
#endif
    
#ifdef WITH_DRAGONS
    cout << "WITH_DRAGONS = " << STR(WITH_DRAGONS) << endl;
#endif
    
#ifdef WITH_ELVES
    cout << "WITH_ELVES = " << STR(WITH_ELVES) << endl;
#endif
    
#ifdef WITH_ORCS
    cout << "WITH_ORCS = " << STR(WITH_ORCS) << endl;
#endif
       
#ifdef NDEBUG
    cout << "NDEBUG = " << STR(NDEBUG) << endl;
#endif
    
    return 0;
}