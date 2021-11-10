/**
 * @File    : read_system_clock.cpp
 * @Brief   : Studying an example on the read system clock 
 * @Author  : Wei Li
 * @Date    : 2021-11-09
*/

#include <unistd.h>
#include <chrono>
#include <iostream>

#include <gsl/gsl>

/** A user-defined overload for std::ostream{} 
 * is provided to convert time_point{} into a standard C string, 
 * and then stream the result to stdout.
 * 
 * A simple demonstration that reads the system clock
 * at an interval specified by the user.
 * the example is run with an interval of two seconds, 
 * and the application outputs the system clock to the console every two seconds.
 * 
 * C++20 have solved this problem using the overlaoding tech. ???
 * 
 * Usage:
 * g++ -std=c++2a read_system_clock.cpp
 * ./a.out 2
 */
template <typename C, typename D>
std::ostream &operator<<(std::ostream &os, std::chrono::time_point<C, D> &obj)
{
    auto t = std::chrono::system_clock::to_time_t(obj);
    return os << ctime(&t);
}

int protected_main(int argc, char **argv)
{
    auto args = gsl::make_span(argv, argc);
    if (args.size() != 2)
    {
        std::cerr << "wrong number of arguments\n";
        ::exit(1);
    }

    gsl::cstring_span<> arg = gsl::ensure_z(args.at(1));
    while (true)
    {
        auto now = std::chrono::system_clock::now();
        std::cout << "time: " << now;

        // then the program sleeps for the amount of time provided by the user:
        sleep(std::stoi(arg.data()));
    }
}

int main(int argc, char **argv)
{
    try
    {
        return protected_main(argc, argv);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Caught unhandled exception:\n";
        std::cerr << " - what(): " << e.what() << '\n';
    }
    catch (...)
    {
        std::cerr << "Caught unknown exception\n";
    }

    return EXIT_FAILURE;
}