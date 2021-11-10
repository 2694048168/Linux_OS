/**
 * @File    : parallel_computation.cpp
 * @Brief   : Studying an example on parallel computation
 * @Author  : Wei Li
 * @Date    : 2021-11-10
*/

/** Parallel Computation Using threads
 * Demonstrate how to perform a parallel computation task
 * that will calculate prime numbers using threading.
 * 
 * Calculating prime values is an expensive operation for large numbers, 
 * but thankfully, they can be calculated in parallel. 
 * It should be noted that in our example, we don't attempt to optimize our search algorithm, 
 * as our goal here is to provide a readable example of threading. 
 * There are many methods, some simple, for improving the performance of the code in this example.
 * 
 * ----Usage:
 * g++ -std=c++2a parallel_computation.cpp -lpthread -o parallel_computation
 * ./parallel_computation 20 4 print
 * time ./parallel_computation 20 4 print
 * time ./parallel_computation 20 20 print
 * time ./parallel_computation 20 40 print
 * 
 */

#include <list>
#include <thread>
#include <mutex>
#include <algorithm>
#include <iostream>

#include <gsl/gsl>

// ------ Step 1. To store the prime numbers that fined
class primes
{
public:
    void add(int prime)
    {
        std::unique_lock lock(m_mutex);
        m_primes.push_back(prime);
    }

    void print()
    {
        std::unique_lock lock(m_mutex);
        m_primes.sort();

        for (const auto prime : m_primes)
        {
            std::cout << prime << ' ';
        }
        std::cout << '\n';
    }

private:
    std::list<int> m_primes;
    mutable std::mutex m_mutex;
};

primes g_primes;

// ------ Step 2. The thread that check whether a number is a prime number
void check_prime(int num)
{
    for (auto i = 2; i < num; i++)
    {
        if (num % i == 0)
        {
            return;
        }
    }

    // prime number is found, and add to stored list
    g_primes.add(num);
}

// ------ Step 3. parllel computation to logic procession
int protected_main(int argc, char **argv)
{
    auto args = gsl::make_span(argv, argc);
    /** argument list
     * argv[0] : filename
     * argv[1] : require to provide the highest possible number
     * argv[2] : require to provide the total number of thread
     * argv[3] : require to provide whether print the results
     * 
     */
    if (args.size() != 4)
    {
        std::cerr << "wrong number of arguments\n";
        ::exit(1);
    }

    // get the highest possible prime number to search for
    int max_prime = std::stoi(args.at(1));
    int max_threads = std::stoi(args.at(2));

    if (max_prime < 3)
    {
        std::cerr << "Max_prime must be 2 or more\n";
        ::exit(1);
    }

    if (max_threads < 1)
    {
        std::cerr << "Max_threads must be 1 or more\n";
        ::exit(1);
    }

    // parallel to solve porblem(there are many ways to further optimize this logic)
    for (auto i = 2; i < max_prime; i += max_threads)
    {
        std::list<std::thread> threads;
        for (auto t = 0; t < max_threads; t++)
        {
            threads.push_back(std::thread{check_prime, i + t});
        }

        for (auto &thread : threads)
        {
            thread.join();
        }
    }

    // check whether print result
    using namespace std::string_literals;
    if (args.at(3) == "print"s)
    {
        g_primes.print();
    }

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