// Example 2_3 : if, switch, loops
// Created by Oleksiy Grechnyev 2017

#include <iostream>
#include <string>

int main(){
    using namespace std;
    
    {
        cout << "if statement" << endl;
        int a = 17;
        if (a > 0) 
            cout << "a is positive" << endl;
        else if (0 == a)  {
            cout << "a is equal to zero" << endl;
        } else
            cout << "a is negative" << endl;
        
        cout << endl;
    }    
    
    {
        cout << "switch statement" << endl;
        int m = 9;
        // Don't forget break !
        switch(m) {
        case 1:
            cout << "January" << endl;
            break;
        case 2:
            cout << "February" << endl;
            break;
        case 3:
            cout << "March" << endl;
            break;
        case 4:
            cout << "April" << endl;
            break;
        case 5:
            cout << "May" << endl;
            break;
        case 6:
            cout << "June" << endl;
            break;
        case 7:
            cout << "July" << endl;
            break;
        case 8:
            cout << "August" << endl;
            break;
        case 9:
            cout << "September" << endl;
            break;
        case 10:
            cout << "October" << endl;
            break;
        case 11:
            cout << "November" << endl;
            break;
        case 12:
            cout << "December" << endl;
            break;
        default:
            cout << "Error: Wrong month !" << endl;
        }
        
        cout << endl;
    }

    {
        cout << "loops" << endl;
        
        cout << "for" << endl;
        for (int i=0;  i<10; ++i)
            cout << i << endl;
        
        cout << "while" << endl;
        int j=0;
        while (j<10)
            cout << j++ << endl;
        
        cout << "do while" << endl;
        int k=0;
        // This runs at least once !
        do
            cout << k++ << endl;
        while (k<10);
        
        cout << "range for :" << endl;
        for (char c: string("Tower"))
            cout << c;
        
        cout << endl << endl;
    }
    
    {
        cout << "Loops : bad style" << endl;
        int i;
        cout << "Enter a number (0 = exit) :" << endl;
        cin >> i;
        while (i != 0) {
            cout << i << " * 2 = " << i*2 << endl;
            // This is repeated = bad
            cout << "Enter a number (0 = exit) :" << endl;
            cin >> i;
        }
        cout << endl;
    }
    
    {
        cout << "Loops : good style" << endl;
        int i;
        // Infinite loop
        for (;;) {
            cout << "Enter a number (0 = exit) :" << endl;
            cin >> i;
            if (0 == i)  // break in the MIDDLE of the loop
                break;
            cout << i << " * 2 = " << i*2 << endl;
        }
        cout << endl;
    }
    
    return 0;
}
