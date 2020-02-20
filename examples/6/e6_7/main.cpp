// Example 6.7 : Random numbers
// Created by Oleksiy Grechnyev 2017

#include <iostream>
#include <string>
#include <random>
#include <ctime>
//==============================
int main(){
    using namespace std;
    {
        cout << "\nRandom numbers: :\n\n";

        // Create a random engine and seed it
        // There are tons of engines
        // Good choices are mt19937 and mt19937_64
        // There are predefined verion of mersenne_twister_engine

        // That's how you're supposed to seed it, but it's not random in MinGW !!!
//        mt19937 mt(random_device{}());

        // That is how I do it, the good old primitive way
        // Might be not good enough for serious Monte-Carlo
        mt19937 mt(time(NULL));

        // Distributions
        uniform_int_distribution<int> uiD(-2, 4);          // min, max, inclusive
        uniform_real_distribution<double> urD(-2.0, 4.0);
        normal_distribution<double> nD(3.0, 2.0);          // Mean, sigma
        bernoulli_distribution bD(0.25);                   // Returns bool, true with probability p
        // There are lots of other distributions

        // Test the distributions
        cout << boolalpha;
        for (int i =0; i<20; ++i)
            cout << uiD(mt) << " " << urD(mt) << " " << nD(mt) << " " << bD(mt) << endl;
    }

    return 0;
}
