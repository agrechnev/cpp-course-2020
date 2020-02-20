// Example 6.6 : Time and date
// Created by Oleksiy Grechnyev 2017

#include <iostream>
#include <thread>
#include <ratio>
#include <chrono>
#include <ctime>
#include <iomanip>

using namespace std;
using namespace std::chrono;

// Some method we are going to time
int fun(int n){
    int result = 0;
    for (int i = 0; i<1000*1000; ++i)
        result = (result + i*(i+1)*(i+2))%12345;

    return result;
}


//==============================
int main(){
    {
        cout << "\nRatio: :\n\n";

        using R1 = ratio<1, 1000>;
        cout << "1/1000 = " << R1::num << "/" << R1::den << endl;

        using R2 = ratio<25, 15>;
        cout << "25/15 = " << R2::num << "/" << R2::den << endl;

        using R3 = ratio<100, -10>;
        cout << "100/-10 = " << R3::num << "/" << R3::den << endl;

        // Pre-defined ratios
        cout << "atto = " << atto::num << "/" << atto::den << endl;
        cout << "nano = " << nano::num << "/" << nano::den << endl;
        cout << "milli = " << milli::num << "/" << milli::den << endl;
        cout << "giga = " << giga::num << "/" << giga::den << endl;
        cout << "exa = " << exa::num << "/" << exa::den << endl;

        // Arithmetics
        using R5 = ratio_add<ratio<1, 2>, ratio<1, 3>>;
        cout << "1/2 + 1/3 = " << R5::num << "/" << R5::den << endl;

        using R6 = ratio_multiply<ratio<1, 2>, ratio<1, 3>>;
        cout << "1/2 * 1/3 = " << R6::num << "/" << R6::den << endl;

        // Comparison. Static field value gives true or false.
        cout << boolalpha <<  "1/2 > 1/3 = " << ratio_greater<ratio<1, 2>, ratio<1, 3>>::value << endl;
    }

    {
        cout << "\nduration, duration_cast :\n\n";

        // Define own duration types
        using DMinutes = duration<double, ratio<60>>;
        using DSeconds = duration<double>;
        using DDays = duration<double, ratio<60*60*24>>;   // 60*60*24/1
        using DHours = duration<double, ratio<60*60>>;      // 60*60/1

        // Examples from cppreference.com
        constexpr auto year = 31556952ll; // seconds in average Gregorian year
        using Shakes = duration<int, ratio<1, 100000000>>;
        using Jiffies = duration<int, centi>;
        using Microfortnights = duration<float, ratio<14*24*60*60, 1000000>>;
        using Nanocenturies = duration<float, ratio<100*year, 1000000000>>;

        // Variables
        seconds s148(148);       //148 int seconds
        minutes m1(1);          //1 int minute
        DSeconds ds1_3(1.3);    //1.3 double seconds
        auto dur1 = minutes(1) + seconds(3) - milliseconds(247);

        // Time literals, use operator""h etc.
        using namespace std::chrono_literals;
        auto dur2 = 1h + 10min + 42s;
        auto dur3 = 1s + 234ms + 567us + 890ns;

        // count(), duration_cast
        // Implicit cast
        cout.precision(9);
        cout << "148 seconds = " << DMinutes(s148).count() << " DMinutes" << endl;
        // Here we need duration_cast beacuse of loss of accuracy
        cout << "148 seconds = " << duration_cast<minutes>(s148).count() << " minutes" << endl;

        cout << "1.3 seconds = " << duration_cast<milliseconds>(ds1_3).count() << " milliseconds" << endl;
        cout << "dur1 = " << milliseconds(dur1).count() << " milliseconds" << endl;
        cout << "dur2 = " << seconds(dur2).count() << " seconds" << endl;
        cout << "dur3 = " << DSeconds(dur3).count() << " DSeconds" << endl;
    }

    {
        cout << "\nclocks, timing execution :\n\n";

        // How do we time execution? Ge the first time_point
        auto t1 = high_resolution_clock::now();
        int result = fun(17);
        auto t2 = high_resolution_clock::now();  // time_point 2
        cout << "fun(17) = " << result << endl;
        nanoseconds dNS = duration_cast<nanoseconds>(t2-t1);
        using DSeconds = duration<double>;
        DSeconds dS = duration_cast<DSeconds >(t2-t1);
        cout << "Timing(nanoseconds) : " << dNS.count() << endl;
        cout << "Timing(seconds) : " << dS.count() << endl;

        // Sleep for a while
        cout << "Going to sleep ..." << endl;
        this_thread::sleep_for(milliseconds(1260));
        cout << "Waking up ..." << endl;

    }

    {
        cout << "\nC time, printing time :\n\n";

        // time_t is the integer type for time in seconds since epoch (1970)
        // C time, returns time_t
        time_t t1 = time(nullptr);
        cout << "t1 = " << t1 << endl;

        // The same type time_t can be obtained from a C++ time_point
        system_clock::time_point tP2 = system_clock::now();  // auto is usually used, of course
        time_t t2 = system_clock::to_time_t(tP2);   // Convert to time_t
        cout << "t2 = " << t2 << endl;

        cout << "Different ways to print time_t: t1 = " << endl;
        // Preferred c++ way
        cout << "put_time(localtime()) : " << put_time(localtime(&t1), "%c %Z") << endl;
        cout << "put_time(gmtime()) : " << put_time(gmtime(&t1), "%c %Z") << endl;
        // Old C ways
        cout << "asctime(localtime()) : " << asctime(localtime(&t1));   // No endl, as asctime gives \n
        cout << "ctime : " << ctime(&t1);   // Short for asctime(localtime(&t1))
        cout << "asctime(gmtime()) : " << asctime(gmtime(&t1));

        cout << "\n\n";
        
        // tm calendar structure
        tm tM1 = *localtime(&t1);     // Copy from static buffer to tM1
        cout << "put_time(&tM1) = " << put_time(&tM1, "%c %Z") << endl;
        cout << "tM1.tm_year = " << tM1.tm_year << endl;
        cout << "tM1.tm_mon = " << tM1.tm_mon << endl;
        cout << "tM1.tm_mday = " << tM1.tm_mday << endl;
        cout << "tM1.tm_hour = " << tM1.tm_hour << endl;
        cout << "tM1.tm_min = " << tM1.tm_min << endl;
        cout << "tM1.tm_sec = " << tM1.tm_sec << endl;
        cout << "tM1.tm_wday = " << tM1.tm_wday << endl;
        cout << "tM1.tm_yday = " << tM1.tm_yday << endl;
        cout << "tM1.tm_isdst = " << tM1.tm_isdst << endl;
        
        // C clock(), time since the program started, usually in milliseconds
        clock_t c = clock();
        double cD = 1.0*c/CLOCKS_PER_SEC;
        cout << "\nThe program ran for " << cD << " seconds" << endl;
        
    }

    return 0;
}
