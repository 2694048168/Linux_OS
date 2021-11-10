/**
 * @File    : exception_benchmark.cpp
 * @Brief   : Studying an example on exception benchmark 
 * @Author  : Wei Li
 * @Date    : 2021-11-10
*/

/** Exception
 * will demonstrate that C++ exceptions outperform POSIX-style exceptions 
 * (a claim that is largely dependent on the hardware you're executing on, 
 * as compiler optimizations and aggressive branch prediction can improve the performance of POSIX-style error handling)
 * 
 * POSIX-style error handling requires the user to check the result of a function each time it is executed. 
 * When function nesting occurs (which will almost certainly happen), this issue is exacerbated even further. 
 * In this example, we will take this case to the extreme, creating a recursive function that checks the results 
 * of itself thousands of times, while executing the test hundreds of thousands of times. 
 * Each test will be benchmarked and the results will be compared.
 * 
 * There are a lot of factors that could change the results of this test, including branch prediction, 
 *  optimizations, and the operating system. The goal of this test is to take the example so far 
 *  to the extreme that most of these issues are washed out in the noise, and any performance-related issues 
 *  with any approach are easily identifiable.
 * 
 * ----Usage:
 * g++ -std=c++2a exception_benchmark.cpp
 * 
 * ----Summary
 * Learned three different methods for performing error handling when system programming. 
 * The first method was POSIX-style error handling, which involves returning an error code from every function executed 
 * and the results of each function being checked to detect an error. 
 * The second method involved the use of standard C-style exceptions (that is, set jump), 
 * demonstrating how this form of exception-handling solves a lot of issues with POSIX-style error handling, 
 * but introduces issues with RAII support and thread safety. 
 * The third example discussed the use of C++ exceptions for error handling, 
 * and how this form of error handling solves most of the issues discussed
 * with the only disadvantage being an increase in the size of the resulting executable. 
 * 
 */

#include <csetjmp>
#include <chrono>
#include <iostream>

jmp_buf jb;

constexpr const auto bad = 0x10000000;
constexpr const auto num_iterations = 100000;

template <typename FUNC>
auto benchmark(FUNC func)
{
    auto stime = std::chrono::high_resolution_clock::now();
    func();
    auto etime = std::chrono::high_resolution_clock::now();

    return (etime - stime).count();
}

int myfunc1(int val)
{
    if (val >= bad)
    {
        return -1;
    }

    if (val < 0x1000)
    {
        if (auto ret = myfunc1(val + 1); ret == -1)
        {
            return ret;
        }
    }

    return 0;
}

void myfunc2(int val)
{
    if (val >= bad)
    {
        std::longjmp(jb, -1);
    }

    if (val < 0x1000)
    {
        myfunc2(val + 1);
    }
}

void myfunc3(int val)
{
    if (val >= bad)
    {
        throw -1;
    }

    if (val < 0x1000)
    {
        myfunc3(val + 1);
    }
}

void test_func1()
{
    if (auto ret = myfunc1(0); ret == 0)
    {
        std::cout << "myfunc1: success\n";
    }
    else
    {
        std::cout << "myfunc1: failure\n";
    }

    if (auto ret = myfunc1(bad); ret == 0)
    {
        std::cout << "myfunc1: success\n";
    }
    else
    {
        std::cout << "myfunc1: failure\n";
    }

    uint64_t total = 0;
    for (auto i = 0; i < num_iterations; i++)
    {
        total += benchmark([&]
                           { myfunc1(0); });
    }

    std::cout << "time1: " << total << '\n';
}

void test_func2()
{
    if (setjmp(jb) == -1)
    {
        std::cout << "myfunc2: failure\n";

        uint64_t total = 0;
        for (auto i = 0; i < num_iterations; i++)
        {
            total += benchmark([&]
                               { myfunc2(0); });
        }

        std::cout << "time2: " << total << '\n';
        return;
    }

    myfunc2(0);
    std::cout << "myfunc2: success\n";

    myfunc2(bad);
    std::cout << "myfunc2: success\n";
}

void test_func3()
{
    try
    {
        myfunc3(0);
        std::cout << "myfunc3: success\n";

        myfunc3(bad);
        std::cout << "myfunc3: success\n";
    }
    catch (...)
    {
        std::cout << "myfunc3: failure\n";
    }

    uint64_t total = 0;
    for (auto i = 0; i < num_iterations; i++)
    {
        total += benchmark([&]
                           { myfunc3(0); });
    }

    std::cout << "time3: " << total << '\n';
}

int protected_main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    test_func1();
    test_func2();
    test_func3();

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