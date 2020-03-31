// Example 10.2 mutex. atomic. condition_variable.
// Created by Oleksiy Grechnyev 2017

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include <future>
#include <condition_variable>

using namespace std;
using namespace std::chrono;

//==============================
int main() {
    {
        cout << "\nData race :\n\n";
        int result = 0;
        auto lam = [&result]{
          for (int i=0; i < 10000; ++i) {
              ++result;
          }
        };
        vector <thread> v;
        for (int i=0; i < 100; ++i)
            v.emplace_back(lam);
        for (auto & t : v)
            t.join();
        cout << "The result should be 1000000 (one million), but ..." << endl;
        cout << "result = " << result << endl;
    }

    {
        cout << "\natomic variables :\n\n";
        // With atomic we get 1 million !
        atomic<int> result(0);
        auto lam = [&result]{
          for (int i=0; i < 10000; ++i) {
              ++result;
          }
        };
        vector <thread> v;
        for (int i=0; i < 100; ++i)
            v.emplace_back(lam);
        for (auto & t : v)
            t.join();
        cout << "The result should be 1000000 (one million), and with atomic<int> ..." << endl;
        cout << "result = " << result.load() << endl;
    }

    {
        cout << "\nmutex :\n\n";
        // With mutex we get 1 million !
        int result = 0;
        mutex m;
        auto lam = [&result, &m]{
          for (int i=0; i < 10000; ++i) {
              lock_guard<mutex> lock(m);        // Lock until '}'
              ++result;
          }  // Unlock here
        };
        vector <thread> v;
        for (int i=0; i < 100; ++i)
            v.emplace_back(lam);
        for (auto & t : v)
            t.join();
        cout << "The result should be 1000000 (one million), and with mutex ..." << endl;
        cout << "result = " << result << endl;
    }

    {
        cout << "\nThread interaction : flag\n\n";

        atomic<bool> stop(false);
        auto lam = [&stop]{
            int i = 0;
            while (!stop) {
                cout << i++;
                this_thread::sleep_for(milliseconds(50));
            }
        };
        thread t1(lam), t2(lam);
        this_thread::sleep_for(milliseconds(500));
        stop = true;   // Signal stop
        t1.join();
        t2.join();
        cout << endl;
    }

    {
        cout << "\ncondition_variable 1 :\n\n";

        // Minimal example
        // Dangerous ! Spurious wakeup can happen !!!
        vector <string> data;
        mutex m;
        condition_variable cv;

        // This thread prints vector of strings
        thread worker([&data, &m, &cv]{
            // We must use unique_lock for condition_variable
            unique_lock<mutex> lk(m);
            cv.wait(lk); // Wait for the notify
            // The mutex m was released while waiting, after wait we aquire it again

            // Print data
            for (const string &s : data)
                cout << s << " ";
            cout << endl;
            // Here we release the mutex
        });

        // Now let's supply the data to the worker thread
        data = {"Karin", "Lucia", "Anastasia"};
        // Notify the worker thread that the data has arrived
        this_thread::sleep_for(milliseconds(10)); // To make sure we don't notify before wait !
        cv.notify_one();
        //  or notify_all()

        cout << "Now join worker thread ..." << endl;
        worker.join();
    }

    {
        cout << "\ncondition_variable 2 :\n\n";

        // Minimal example with condition
        vector <string> data;
        mutex m;      // mutex protects both cv and data
        condition_variable cv;

        // This thread prints vector of strings
        thread worker([&data, &m, &cv]{
            // We must use unique_lock for condition_variable
            unique_lock<mutex> lk(m);
            cv.wait(lk, [&data]{return !data.empty();}); // Wait until we get any data
            // The mutex m was released while waiting, after wait we aquire it again

            // Print data
            for (const string &s : data)
                cout << s << " ";
            cout << endl;
            // Here we release the mutex
        });

        // Now let's supply the data to the worker thread
        this_thread::sleep_for(milliseconds(10)); // To make sure we don't notify before wait !
        // Must lock mutex to change data for the condition_variable to work
        m.lock();
        data = {"Karin", "Lucia", "Anastasia"};
        m.unlock(); // Now we ulock
        // Notify the worker thread that the data has arrived
        cv.notify_one();
        //  or notify_all()

        cout << "Now join worker thread ..." << endl;
        worker.join();
    }

    {
        cout << "\ncondition_variable 3 :\n\n";

        // Slightly more complicated example
        // Here the main thread uses the same conditional variable to signal the end of operation
        vector <string> data;
        mutex m;      // mutex protects both cv and data
        condition_variable cv;
        bool finished = false;  // Signal that the job is finished

        // This thread prints vector of strings
        thread worker([&data, &m, &cv, &finished]{
            // We must use unique_lock for condition_variable
            unique_lock<mutex> lk(m);
            cv.wait(lk, [&data]{return !data.empty();}); // Wait until we get any data
            // The mutex m was released while waiting, after wait we aquire it again

            // Print data
            for (const string &s : data)
                cout << s << " ";
            cout << endl;
            finished = true; // We are still under the mutex

            // Here we unlock the mutex and uniqe_lock by hand
            lk.unlock();
            cv.notify_one(); // And notify
        });

        // Now let's supply the data to the worker thread
        this_thread::sleep_for(milliseconds(10)); // To make sure we don't notify before wait !
        // Must lock mutex to change data for the condition_variable to work
        m.lock();
        data = {"Karin", "Lucia", "Anastasia"};
        m.unlock(); // Now we ulock
        cv.notify_one();  // Notify one or notify_all()

        // Note: the same cv is reused here
        // It's fine in simple cases, probably would be better to use
        // different ones in general
        cout << "Now wait for the worker thread ..." << endl;
        {
            unique_lock<mutex> lk(m);
            cv.wait(lk, [&finished]{return finished;});
        }

        cout << "Now join worker thread ..." << endl;
        worker.join();
    }

    {
        cout << "\npromise and future for a one-shot communication :\n\n";

        promise<void> p;   // promise + future pair
        future<void> f = p.get_future();
        thread t([&f]{
            f.get(); // Wait for the signal
            cout << "One !\n";
            this_thread::sleep_for(milliseconds(10));
            cout << "Two !\n";
            this_thread::sleep_for(milliseconds(10));
            cout << "Three !\n";
        });

        for (int i = 0; i < 10; ++i) {
            cout << i << endl;
            if (4 == i)
                p.set_value(); // Send the signal
            this_thread::sleep_for(milliseconds(10));
        }

        t.join();
    }
    return 0;
}
