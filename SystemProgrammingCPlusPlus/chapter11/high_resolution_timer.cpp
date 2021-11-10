/**
 * @File    : high_resolution_timer.cpp
 * @Brief   : Studying an example on high-resolution timer
 * ---------------------------------
 * @Command : g++ high_resolution_timer.cpp -o high_resolution_time
 * @Command : ./high_resolution_time 10000000
 * ---------------------------------
 * @Author  : Wei Li
 * @Date    : 2021-11-09
*/

#include <chrono>
#include <iostream>

#include <gsl/gsl>

/** A simple benchmark using hig_resolution_clock{}
 * 
 * functional programming to wrap a function call
 * (likely a lambda) between two calls to the high-resolution  clock. 
 * define a 'benchmark' function as following:
 */
template <typename FUNC>
auto benchmark(FUNC func)
{
    auto start_time = std::chrono::high_resolution_clock::now();
    func();
    auto end_time = std::chrono::high_resolution_clock::now();

    return end_time - start_time;
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

    // functional programming and lambda expression
    auto d = benchmark([&arg]
                       {
                           for (uint64_t i = 0; i < std::stoi(arg.data()); i++);
                       });

    std::cout << "time: " << std::chrono::duration_cast<std::chrono::seconds>(d).count() << '\n';
    std::cout << "time: " << std::chrono::duration_cast<std::chrono::milliseconds>(d).count() << '\n';
    std::cout << "time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(d).count() << '\n';

    return EXIT_SUCCESS;
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