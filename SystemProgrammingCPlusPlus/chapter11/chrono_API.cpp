/**
 * @File    : chrono_API.cpp
 * @Brief   : exploring C++ Chrono APIs
 * @Author  : Wei Li
 * @Date    : 2021-11-09
*/

/** C++ time Chrono APIs
 * C++ includes the Chrono APIs which, mostly, provide C++ wrappers around the POSIX time.h APIs. 
 * For this reason, some time.h functions are still needed to provide full functionality, 
 * including the conversion to standard C strings. 
 * It should be noted that although some additions have been made in C++17 
 * (specifically floor(), ceil(), and round()), 
 * the Chrono APIs are expected to see a relatively large overhaul with the introduction of C++20, 
 * for this reason, the C++ Chrono APIs are briefly explained.
 * 
 * g++ -std=c++17 chrono_API.cpp
 */

#include <unistd.h>
#include <chrono>
#include <iostream>

template <typename C, typename D>
std::ostream &operator<<(std::ostream &os, std::chrono::time_point<C, D> &obj)
{
    auto t = std::chrono::system_clock::to_time_t(obj);
    return os << ctime(&t);
}

int main(int argc, char **argv)
{
    /** The system_clock() API
     * The std::chrono::system_clock{} API is similar to time() 
     * in that it is capable of getting the system clock. 
     * system_clock{} is also the only clock that is capable of being
     * converted into time_t (as it is likely implemented using time())
     * 
     * https://en.cppreference.com/w/cpp/chrono/system_clock
     */
    auto t = std::chrono::system_clock::now();
    std::cout << "time: " << std::chrono::system_clock::to_time_t(t) << '\n';

    /** The time_point API
     * The result of the system_clock::now() API is a time_point{}. 
     * C++ does not provide a function to convert a time_point{} to a string (it won't until C++20), 
     * and as a result, the POSIX functions discussed in the previous section are 
     * still needed to perform this translation
     * 
     * the Chrono libraries provided various functions for
     * incrementing, decrementing, and comparing a time_point{} using C++ operator overloads
     * 
     */
    using namespace std::chrono;
    auto now = std::chrono::system_clock::now();
    std::cout << '\n' << "time: " << now;
    now += 1h;
    std::cout << "time: " << now;
    now -= 1h;
    std::cout << "time: " << now;

    auto now1 = std::chrono::system_clock::now();
    auto now2 = std::chrono::system_clock::now();
    std::cout << '\n' << std::boolalpha;
    std::cout << "Compare: " << (now1 < now2) << '\n';
    std::cout << "Compare: " << (now1 > now2) << '\n';
    std::cout << "Compare: " << (now1 >= now2) << '\n';
    std::cout << "Compare: " << (now1 <= now2) << '\n';
    std::cout << "Compare: " << (now1 == now2) << '\n';
    std::cout << "Compare: " << (now1 != now2) << '\n';

    /** Duration
     * The time_point{} type provides arithmetic to increment, decrement, and perform addition and subtraction. 
     * This arithmetic is all done using a C++ Chrono duration{}, which defines a range of time. 
     * Another way to view duration{} is that it would be theresulting abstraction of the POSIX difftime() call. 
     * In fact, the subtraction of two time_point{} types results in a duration{}.
     * 
     * Like the hour literal, 
     * C++ provides the following literals for a duration of time, which may be used for this arithmetic:
     * 1. Hour: h
     * 2. Minute: min
     * 3. Second: s
     * 4. Millisecond: ms
     * 5. Microsecond: us
     * 6. Nanosecond: ns
     * 
     * Durations have a relatively complex template structure, 
     * for defining their resolution (that is, whether a duration is in seconds, milliseconds, or hours), 
     * and can technically take on almost any resolution as a result. 
     * Although this functionality exists, C++ provides some predefined helpers for converting 
     * from one duration to another, preventing you from needing to know the inner workings of duration{}:
     * 
     * 1. std::chrono::nanoseconds
     * 2. std::chrono::microseconds
     * 3. std::chrono::milliseconds
     * 4. std::chrono::seconds
     * 5. std::chrono::minutes
     * 6. std::chrono::hours
     * 
     * Like time_point{}, a duration can also be manipulated using arithmetic.
     * 
     * comparisons are also supported
     */
    std::cout << '\n';
    auto now_time1 = std::chrono::system_clock::now();
    sleep(2);
    auto now_time2 = std::chrono::system_clock::now();
    std::cout << "time: " << duration_cast<seconds>(now_time2 - now_time1).count() << '\n';
    std::cout << "time: " << duration_cast<milliseconds>(now_time2 - now_time1).count() << '\n';
    std::cout << "time: " << duration_cast<nanoseconds>(now_time2 - now_time1).count() << '\n';

    std::cout << '\n';
    std::chrono::seconds time_sec(42);
    ++time_sec;
    std::cout << "time: " << time_sec.count() << '\n';
    --time_sec;
    std::cout << "time: " << time_sec.count() << '\n';
    time_sec += 1s;
    std::cout << "time: " << time_sec.count() << '\n';
    time_sec -= 1s;
    std::cout << "time: " << time_sec.count() << '\n';
    time_sec %= 2s;
    std::cout << "time: " << time_sec.count() << '\n';

    auto time_duration1 = 0s;
    auto time_duration2 = 42s;
    std::cout << '\n' << std::boolalpha;
    std::cout << "Compare: " << (time_duration1 < time_duration2) << '\n';
    std::cout << "Compare: " << (time_duration1 > time_duration2) << '\n';
    std::cout << "Compare: " << (time_duration1 == time_duration2) << '\n';
    std::cout << "Compare: " << (time_duration1 != time_duration2) << '\n';
    std::cout << "Compare: " << (time_duration1 >= time_duration2) << '\n';
    std::cout << "Compare: " << (time_duration1 <= time_duration2) << '\n';

    /**
     * Most of the modifications to the Chrono library that are taking place will likely occur in C++20 
     * with a large number of APIs being added to address the relatively obvious shortcomings of the existing API. 
     * 
     * In C++17, however, the floor(), ceil(), round(), and abs() APIs were added to the Chrono APIs, 
     * which return the floor, ceil, round, or absolute values of a duration, 
     * as shown in the following example (with similar APIs also being added to the time_point{} type):
     */
    auto timeDuration = -42001ms;
    std::cout << '\n';
    std::cout << "floor: " << floor<seconds>(timeDuration).count() << '\n';
    std::cout << "ceil: " << ceil<seconds>(timeDuration).count() << '\n';
    std::cout << "round: " << round<seconds>(timeDuration).count() << '\n';
    std::cout << "abs: " << abs(timeDuration).count() << '\n';

    /** The steady_clock function
     * system_clock{} is similar to time(), while steady_clock{} is similar to clock(), 
     * and performs the same objective—to provide a clock that represents 
     * the amount of time the application has executed, 
     * regardless of the current system date and time (which might change depending on the user of the system).
     * 
     */
    auto now_clock1 = std::chrono::steady_clock::now();
    sleep(2);
    auto now_clock2 = std::chrono::steady_clock::now();
    std::cout << '\n' << "time: " << duration_cast<seconds>(now_clock2 - now_clock1).count() << '\n'; 
    std::cout << "time: " << duration_cast<milliseconds>(now_clock2 - now_clock1).count() << '\n'; 
    std::cout << "time: " << duration_cast<nanoseconds>(now_clock2 - now_clock1).count() << '\n'; 

    /** The high_resolution_clock function
     * On most systems, high_resolution_clock{} and steady_clock{} are the same. 
     * In general, high_resolution_clock{} represents the highest-resolution clock available 
     * as a steady clock and, as shown in the following example, 
     * the result is the same with stead_clock{}
     * 
     */
    auto high_clock1 = std::chrono::steady_clock::now();
    sleep(2);
    auto high_clock2 = std::chrono::steady_clock::now();
    std::cout << '\n' << "time: " << duration_cast<seconds>(high_clock2 - high_clock1).count() << '\n'; 
    std::cout << "time: " << duration_cast<milliseconds>(high_clock2 - high_clock1).count() << '\n'; 
    std::cout << "time: " << duration_cast<nanoseconds>(high_clock2 - high_clock1).count() << '\n'; 

    return 0;
}