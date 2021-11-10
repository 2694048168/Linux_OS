/**
 * @File    : time_interfaces.cpp
 * @Brief   : the POSIX and C++ time interfaces
 * @Author  : Wei Li
 * @Date    : 2021-11-09
*/

/** the POSIX and C++ time interfaces
 * Discussing POSIX time.h APIs, 
 * which provide APIs for reading various clocks and performing calculations on these clock times. 
 * Although these APIs are specific to standard C, 
 * as will be demonstrated in the following section, 
 * the C time interfaces are still needed when working with C++, 
 * a problem that is being addressed in C++20.
 * 
 * The UNIX epoch defines the number of seconds from January 1, 1970. 
 * Interfaces described in this chapter leverage the UNIX epoch to define the notion of time. 
 * 
 * Define three different, opaque types:
 * 1. tm: An opaque structure that holds a date and time
 * 2. time_t: A typedef that stores a time that is typically implemented using an integer that stores the number of seconds from the UNIX epoch.
 * 3. clock_t: A typedef that stores the amount of processor time the application has executed.
 * 
 * Different types of clocks:
 * 1. System clock: 
 * 2. Steady clock:
 * 3. High-resolution clock:
 * 
 */

#include <unistd.h>
#include <ctime>
#include <iostream>

int main(int argc, char** argv)
{
    /** The 'time' API returns the current system clock and takes on the following form:
     * time_t time(time_t *arg);
     * 
     * the time() API to get the current number of seconds from the UNIX epoch. 
     * usually implemented using an integer value.
     * 
     * time() will return -1 in the event of anerror, 
     * which can be checked and handled as needed.
     * 
     * man 2 time
     */
    auto timestamp = time(nullptr);
    // time_t t;
    // time(&t);
    std::cout << "The current number of seconds from the UNIX epoch.: " << timestamp << '\n';

    /** The ctime() typedef
     * char *ctime(const time_t *time);
     * 
     * The ctime() API takes a pointer to a time_t variable 
     * and outputs a standard C character string. 
     * 
     * man 3 ctime
     */
    std::cout << "The current time: " << ctime(&timestamp) << '\n';

    /** The localtime and gmtime APIs
     * the numbers of seconds from the Unix epoch, expose date and time information.
     * how to convert the date and time to the localtime and Greenwich Mean Time(GMT).
     * The POSIX API provides both the 'localtime()' and 'gmtime()' function.
     * 
     * struct tm *localtime(const time_t *time);
     * struct tm *gmtime(const time_t *time);
     * 
     * thus is not freed by the user, meaning the results of this function are not thread-safe.
     * the POSIX API provides the 'asctime()' function
     * 
     * char *asctime(const struct tm *time_ptr);
     * 
     * man 3 localtime
     * man 3 gmtime
     * man 3 asctime
     */
    // the only difference being a time zone change.
    std::cout << "Time(Local): " << asctime(localtime(&timestamp));
    std::cout << "Time(GMT): " << asctime(gmtime(&timestamp));

    /** The strftime() function
     * the output of 'ctime' and 'asctime' was predetermind 
     * by POSIX API. the POSIX API added the 'strftime' function,
     * which is the recommended API for converting an opaque 'tm'
     * structure to a character string.
     * 
     * size_t strftime(char *str, size_t count, const char *format, const struct tm *time);
     * 
     *  similar to the format string provided to other POSIX functions, such as 'printf()'.
     * 
     * man 3 strftime
     */
    char buf_date[256]{};
    char buf_time[256]{};
    char buf_date_time[256]{};
    strftime(buf_date, sizeof(buf_date), "%m/%d/%Y", localtime(&timestamp));
    strftime(buf_time, sizeof(buf_time), "%H:%M", localtime(&timestamp));
    strftime(buf_date_time, sizeof(buf_date_time), "%a %b %d %H:%M:%S %Y", localtime(&timestamp));
    std::cout << "Time format: " << buf_date << '\n';
    std::cout << "Time format: " << buf_time << '\n';
    std::cout << "Time format: " << buf_date_time << '\n';

    /** The fifftime() function
     * time_t typedef is a signed 32-bit integer on Unix systems.
     * The difference of between two time_t values by difftime() function.
     * 
     * double difftime(time_t time_end, time_t time_beg);
     * 
     * man 3 difftime
     */
    auto timestamp1 = time(nullptr);
    sleep(2);
    auto timestamp2 = time(nullptr);
    std::cout << "Difference of time_t value: " << difftime(timestamp2, timestamp1) << '\n';
    std::cout << "Difference of time_t value: " << timestamp2 - timestamp1 << '\n';

    /** The mktime() function
     * how to diff the two 'tm' struct?
     * the mktime() function convert 'tm' structure back into 'time_t' value.
     * 
     * time_t mktime(struct tm *time);
     * 
     * man 3 mktime 
     */
    auto timestamp_value = time(nullptr);
    auto time_struct = localtime(&timestamp_value);
    auto time_t_value = mktime(time_struct);
    std::cout << "Time: " << ctime(&time_t_value);

    /** The clock() function
     * time() has been used to get the current system date and time. 
     * The problem with this type of clock is it returns the value the operating system 
     * is managing with respect to the current date and time, 
     * which can change at any point and time (for example, the user might be flying between time zones). 
     * 
     * This can be a problem, for example, 
     * if you are using the time APIs to keep track of how long something has executed. 
     * In this case, when a time zone change occurs, 
     * the application using time() might record the amount of time that has passed as being negative.
     * 
     * To overcome this issue, POSIX provoides the clock() function:
     * clock_t clock(void);
     * 
     * The clock() API returns a clock_t value, which is similar to a time_t value. 
     * The difference between time() and clock() is that time() returns the current system time,
     * while clock() returns a value that represents the total amount of time 
     * that has passed since the start of the application.
     * 
     * the return value is implementation-specific.
     * To convert clock_t into seconds, POSIX provides the 'CLOCKS_PER_SEC' macro
     * 
     * man 3 clock
     * 
     * 
     */
    std::cout << "clock from the start of application: " << clock() << '\n';
    auto clock_value1 = clock();
    sleep(2);
    auto clock_value2 = clock();
    std::cout << "clock convert into second: " << static_cast<double>(clock_value2 - clock_value1) / CLOCKS_PER_SEC << '\n';

    /**
     *  Once the application is executed again by the operating system, 
     * the clock value is read again and the difference is converted into milliseconds
     * using CLOCKS_PER_SEC (and then multiplied by 1,000). 
     * Notice the value does not equate to 2,000 milliseconds. 
     * This is because the application does not record execution while sleeping,
     * and thus, only the execute time of the application is seen by clock().
     */
    auto clock1 = clock();
    auto time_1 = time(nullptr);
    while (time(nullptr) - time_1 <= 2);
    auto clock2 = clock();
    std::cout << "clock into second: " << static_cast<double>(clock2 - clock1) / CLOCKS_PER_SEC << '\n';

    return 0;
}