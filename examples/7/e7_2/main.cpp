// Example 7.2 Lambda expressions in algorithms.
// Created by Oleksiy Grechnyev 2017

#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

using namespace std;

/// Print a container
template<typename C>
void print(const C &c) {
    for (const auto &e : c)
        cout << e << " ";
    cout << endl;
}

//==============================
int main() {
    {
        cout << "\nSort with a lambda :\n\n";

        vector<int> unsorted{3, 17, 3, 81, -20, 0, 685, 185, -9, 37, 62};
        cout << "unsorted = ";
        print(unsorted);

        vector<int> v;

        cout << "Sort a vector (ascending, default) : \n";
        v = unsorted;
        sort(v.begin(), v.end());    // Sort ascending
        cout << "v = ";
        print(v);

        cout << "Sort a vector (descending, lambda) : \n";
        v = unsorted;
        sort(v.begin(), v.end(), [](int x, int y) -> bool {
            return x > y;
        });
        cout << "v = ";
        print(v);

        cout << "Sort a vector (descending, greater<int>) : \n";
        v = unsorted;
        sort(v.begin(), v.end(), greater<int>());
        cout << "v = ";
        print(v);

        // You can use greater<>(), a wrapper for >
        cout << "Sort a vector (descending, greater<>) : \n";
        v = unsorted;
        sort(v.begin(), v.end(), greater<>());
        cout << "v = ";
        print(v);
    }

    {
        cout << "\nAlgorithms and lambdas 1 :\n\n";

        vector<int> v{3, 17, 3, 81, -20, 0, 685, 185, -9, 37, 62};


        cout << "for_each:\n";
        for_each(v.cbegin(), v.cend(), [](int x) -> void {
            cout << x << " : " << 2 * x << endl;
        });

        // Count negative elements
        cout << "count_if:\n";
        int n = count_if(v.cbegin(), v.cend(), [](int x) -> bool {
            return x < 0;
        });
        cout << "n = " << n << endl;

        // Transform
        cout << "transform:\n";
        vector<int> v2;  // Elements must exist beforehand !
        transform(v.cbegin(), v.cend(), back_inserter(v2), [](int x) -> int {
            return x * 2;
        });

        cout << "v = ";
        print(v);
        cout << "v2 = ";
        print(v2);
    }

    {
        cout << "\nAlgorithms and lambdas 2 :\n\n";

//        vector<int> v{3, 17, 3, 81, -20, 0, 685, 185, -9, 37, 62};
        cout << "generate:\n";
        vector<int> v(10);   // Pre-allocate 10 elements
        int n = 0;
        generate(v.begin(), v.end(), [&n]()->int{
            return n++;
        });
        cout << "v = ";
        print(v);

        v.clear();
        n = 0;
        // noexcept goes here, just for fun !
        generate_n(back_inserter(v), 10, [&n]() noexcept ->int{
            return n++;
        });
        cout << "v = ";
        print(v);

    }
    return 0;
}
