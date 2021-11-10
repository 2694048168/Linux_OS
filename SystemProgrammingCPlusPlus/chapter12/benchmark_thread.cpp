/**
 * @File    : benchmark_thread.cpp
 * @Brief   : studying an example on benchmarking with threads 
 * @Author  : Wei Li
 * @Date    : 2021-11-10
*/

/** Benchmarking with threads
 * Discussed how to benchmark software using various different mechanisms. 
 * In this example, we will explore creating our own high-resolution timer using a thread, 
 * instead of using the high-resolution timer provided by the C++ chrono APIs.
 * 
 * To accomplish this, we will create a thread with the sole job of counting as fast as possible.
 * It should be noted that although this will provide a high-resolution timer that is extremely sensitive, 
 * it has a lot of disadvantages compared to computer architectures such as Intel. 
 * These provide hardware instructions with higher resolution than is possible here, 
 * while being less susceptible to CPU frequency scaling.
 * 
 */

#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>

#include <gsl/gsl>

/** ----Step 1. store the high-resolution timer in a count variable
 * The enable_counter Boolean will be used to turn the timer off, 
 * while the mutex and condition variable will be used to turn the timer on at the correct time.
 * 
 * ----Usage:
 * g++ -std=c++2a benchmark_thread.cpp -lpthread -o benchmark_thread
 * ./benchmark_thread 100000000
 */
int count = 0;
bool enable_counter = true;
std::mutex mutex;
std::condition_variable cond;

// ----Step 2. high-resolution timer
void tick()
{
    cond.notify_one();
    while (enable_counter)
    {
        ++count;
    }
}

// time an operation
template <typename FUNC>
auto timer(FUNC func)
{
    std::thread timer{tick};

    std::unique_lock lock(mutex);
    cond.wait(lock);

    func();

    enable_counter = false;
    timer.join();

    return count;
}

// ----Step 3. logic porcess for whole program
int protected_main(int argc, char **argv)
{
    auto args = gsl::make_span(argv, argc);
    if (args.size() != 2)
    {
        std::cerr << "wrong number of arguments\n";
        ::exit(1);
    }

    auto ticks = timer([&]{
        for (auto i = 0; i < std::stoi(args.at(1)); i++);
    });

    std::cout << "ticks: " << ticks << '\n';

    return EXIT_SUCCESS;
}


int main(int argc, char** argv)
{
    try
    {
        return protected_main(argc, argv);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Caught unhandled exception:\n";
        std::cerr << " - whart(): " << e.what() << '\n';
    }
    catch(...)
    {
        std::cerr << "Caught unkonwn exception\n";
    }

    return EXIT_FAILURE;
}
