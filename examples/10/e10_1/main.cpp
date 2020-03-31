// Example 10.1 Concurrency: asunc(), futures, threads
// Created by Oleksiy Grechnyev 2017

#include <iostream>
#include <thread>
#include <future>
#include <chrono>

using namespace std;
using namespace std::chrono;


//==============================
int main() {

    // Print a char and sleep a bit (100 times)
    auto lamChar = [](char c)->void{
        // Print the thread id at the start
        cout << this_thread::get_id() << " : starting !\n";
        for (int i = 0; i< 100; ++i) {
            cout << c;
            this_thread::sleep_for(milliseconds(1)); // Sleep a bit
        }
    };

    // This version uses yield
    auto lamChar2 = [](char c)->void{
        for (int i = 0; i< 100; ++i) {
            cout << c;
            this_thread::yield(); // Similar to sleep for for a short while
        }
    };

    {
        cout << "\nasync() : basics:\n\n";

        //  future<int> is a result obtained some time in the future
        //  async starts a task
        // The arguments (here 3, 7) are passed std::bind() style
        // Use std::ref() wrapper to pass by reference !!!
        future<int> f1 = async([](int x, int y)->int{
            return x*y;
        }, 3, 7);

        // Use f1.get() to wait for the task to finish and get the result
        // get() can be used only once on a future !
        cout << "f1.get() = " << f1.get() << endl;

        // Again, use std::ref() wrapper to pass by reference !!!
        auto lam2 = [](int & x)->int{  // Remember, lambda can be stored in auto !
            x *= x; // Square x
            return x; // And return it
        };
        int x = 17;
        future<int> f2 = async(lam2, ref(x)); // ref wrapper, like for std::bind !!!
        // It's important to check x AFTER f2.get() !
        cout << "f2.get() = " << f2.get() << ", x = " << x << endl;
        // Or wrap it in another lambda, might be better, reusing x and f2
        x = 17;
        f2 = async([&lam2, &x]{
            return lam2(x);
        });
        cout << "f2.get() = " << f2.get() << ", x = " << x << endl;
    }

    {
        cout << "\nasync() : launch::async vs launch::deferred :\n\n";
        // The task is launched by default as launch::async | launch::deferred
        // Specify launch::async to guarantee the multithread
        // Note: use future<void> if no results are returned

        cout << "Launching as launch::async ..." << endl;
        future<void> f1 = async(launch::async, []{
            cout << "launch::async !!!" << endl;
        });
        cout << "After async() ..." << endl;
        this_thread::sleep_for(milliseconds(1)); // Wait a bit, our task shoul run now
        cout << "Before get() ..." << endl;
        f1.get();
        cout << "After get() ..." << endl;

        cout << "Launching as launch::deferred ..." << endl;
        future<void> f2 = async(launch::deferred, []{
            cout << "launch::deferred !!!" << endl;
        });
        cout << "After async() ..." << endl;
        this_thread::sleep_for(milliseconds(1)); // Wait a bit, doesn't help
        cout << "Before get() ..." << endl;
        f2.get();  // Now the task will run, no threads !
        cout << "After get() ..." << endl;

        cout << "\nTwo tasks in parallel ..." << endl;
        // Run 2 tasks in parallel
        future<void> fA = async(launch::async, lamChar, 'A');
        future<void> fB = async(launch::async, lamChar, 'B');
        future<void> fC = async(launch::deferred, lamChar, 'C');  // This one will never start, no get/wait !

        // No real need for wait() or get() for the launch::async tasks
        // We wait for them at the closing }
        // But for launch::deferred you have to wait()/get(), or they never start at all !!!
    }

    {
        cout << "\n\nasync() : wait(), wait_for() :\n\n";

        // wait() waits for the task to finish (and starts it, for deferred task)
        // Not really needed if we use get()
        future<int> f1 = async([](int x, int y)->int{
            return x*y;
        }, 3, 7);
        f1.wait();
        cout << "f1.get() = " << f1.get() << endl;

        // wait_for waits for a given time at most, use seconds(0) to check
        future<int> f2 = async(launch::async, [](int x, int y)->int{
            this_thread::sleep_for(seconds(1)); // Sleep for 1s
            return x*y;
        }, 3, 7);

        auto printFS = [](const future_status & fs){
            if (fs == future_status::deferred)
                cout << "deferred" << endl;
            else if (fs == future_status::ready)
                cout << "ready" << endl;
            else if (fs == future_status::timeout)  // Running, not ready !
                cout << "timeout" << endl;
        };
        future_status result;
        for (int i =0; i< 12; ++i) {
            result = f2.wait_for(milliseconds(100));
            printFS(result);
        }
        cout << "f2.get() = " << f2.get() << endl;

        // Now we wait for 0s just to check !
        future<int> f3 = async(launch::async, [](int x, int y)->int{
            this_thread::sleep_for(seconds(1)); // Sleep for 1s
            return x*y;
        }, 3, 7);
        while (f3.wait_for(seconds(0)) == future_status::timeout) {
            cout << "Still waiting ..." << endl;
            this_thread::sleep_for(milliseconds(100));
        }
        cout << "f3.get() = " << f3.get() << endl;

    }

    {
        cout << "\nasync() : exceptions :\n\n";
        // Suppose our task throws, what happends ???
        try{
            cout << "Starting the task ..." << endl;
            future <int> f = async(launch::async, [](int x, int y)->int{
                // Suppose we don't like negative ints for some reason ...
                if (x<0 || y<0)
                    throw runtime_error("The user is an IDIOT !!!");
                return x*y;
            }, 7, -3);
            cout << "Task started ..." << endl;
            this_thread::sleep_for(milliseconds(3)); // Give it some time
            cout << "Before get ..." << endl;
            cout << "f.get() = " << f.get() << endl;   // Gets throws here at get() in the main thread !
            cout << "After get ..." << endl;
        } catch (const exception & e) {
            cout << "Caught exception : " << e.what() << endl;
        }
    }

    {
        cout << "\nthread : basics :\n\n";

        // Start 3 threads
        thread tA(lamChar, 'A');
        thread tB(lamChar, 'B');
        thread tC(lamChar, 'C');
        tC.detach();  // Detach this one from the std::thread handle
        // And another , stupid one
        thread t0([]{cout << "IDIOT\n";});

        cout << "Threads  started ..." << endl;
        this_thread::sleep_for(milliseconds(10));

        cout << "About to join threads ..." << endl;
        // Join threads, means : wait for them to finish
        tA.join();   // Join tA, tB, t0, but not tC !
        tB.join();
        t0.join();
        // We do not join tC, it's detached, it's better NOT to detatch
        cout << endl;
    }

    {
        cout << "\nthread : future, promise, packaged_task :\n\n";
        // The really low-level way: make future out of a promise
        cout << "promise\n";
        promise<int> p1;  // Create a promise/future pair
        future<int> f1 = p1.get_future();
        // Now we start the thread, capturing promise by ref
        thread t1([&p1](int x, int y)->void{
            p1.set_value(x*y);  // We use set_value() on promise instead of return !!!
        }, 3, 7);
        // Now we run get() on the future as usual
        cout << "f1.get() = " << f1.get() << endl;
        t1.join();  // Don't forget to join, before or after get(), doesn't really matter

        // We can put exception into a promise
        cout << "\npromise, exception \n";
        try {
            promise<int> p2;
            future<int> f2 = p2.get_future();
            // Now we start the thread, capture promise by ref
            thread t2([&p2](int x, int y)->void{
                // set_exception() needs an exception_ptr
                // We can make one like this ...
                p2.set_exception(make_exception_ptr(runtime_error("The user is an IDIOT !!!")));
                // Or, within a catch clause :
                // p2.set_exception(current_exception());
            }, 3, 7);
            t2.join();  // Let's join here to be safe
            cout << "Before get ..." << endl;
            cout << "f2.get() = " << f2.get() << endl;   // Throws here
            cout << "After get ..." << endl;
        } catch (const exception & e) {
            cout << "Caught exception : " << e.what() << endl;
        }

        // packaged_task : a bit higher level than promise
        // It is sort of std::function which creates a future
        // Lambda which eitherreturns int or throws
        auto lam = [](int x, int y)->int{
            if (x<0 || y<0)
                throw runtime_error("The user is an IDIOT !!!");
            else
                return x*y;
        };

        cout << "\npackaged_task : \n";
        packaged_task<int(int, int)> pt3(lam);

        future<int> f3 = pt3.get_future();
        // Now run pt3 instead of the bare lambda
        thread t3(move(pt3), 3, 7);  // Must move !
        t3.join();
        cout << "Before get ..." << endl;
        cout << "f3.get() = " << f3.get() << endl;
        cout << "After get ..." << endl;

        cout << "\npackaged_task, exception : \n";
        try {
            packaged_task<int(int, int)> pt4(lam);
            future<int> f4 = pt4.get_future();
            thread t4(move(pt4), 3, -7);  // Now we want exception !
            t4.join();
            cout << "Before get ..." << endl;
            cout << "f4.get() = " << f4.get() << endl;  // thrown here !
            cout << "After get ..." << endl;
        } catch (const exception & e) {
            cout << "Caught exception : " << e.what() << endl;
        }
    }
    return 0;
}
