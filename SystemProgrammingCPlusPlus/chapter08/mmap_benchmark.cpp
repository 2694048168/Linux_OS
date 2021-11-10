/**
 * @File    : mmap_benchmark.cpp
 * @Brief   : Comparing C++ versus mmap benchmark
 * @Author  : Wei Li
 * @Date    : 2021-11-07
*/

/** Comparing C++ versus mmap benchmark
 * In this example, we will benchmark the difference 
 * between reading the contents of a file using std::fstream and reading them using mmap().
 * It should be noted that the mmap() function leverages a system call to directly map a file into the program, 
 * and we expect mmap() to be faster than the C++ APIs highlighted in this chapter. 
 * This is because the C++ APIs have to perform an additional memory copy, 
 * which is obviously slower.
 */

#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <chrono>
#include <fstream>
#include <iostream>

// Step 1. define the size of the file to read
constexpr auto size = 0x1000;

// Step 2. define a 'benchmark' function to recored how long it takes to perform an action
template <typename FUNC>
auto benchmark(FUNC func)
{
    auto startTime = std::chrono::high_resolution_clock::now();
    func();
    auto endTime = std::chrono::high_resolution_clock::now();

    return endTime - startTime;
}

// Step 3. create a file read, and then read the file using std::fstream and mmap function
int protected_main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    {
        char buf[size] = {};
        if (auto file = std::fstream("test.txt", std::ios::out))
        {
            file.write(buf, size);
        }
    }

    {
        char buf[size];
        if (auto file = std::fstream("test.txt", std::ios::in))
        {
            auto time = benchmark([&file, &buf]
                                  { file.read(buf, size); });

            std::cout << "c++ time: " << std::chrono::duration_cast<std::chrono::microseconds>(time).count() << '\n';
        }
    }

    {
        void *buf;
        if (int fd = open("test.txt", O_RDONLY); fd != 0)
        {
            auto time = benchmark([&fd, &buf]
                                  { buf = mmap(NULL, size, PROT_READ, 0, fd, 0); });

            munmap(buf, size);

            std::cout << "mmap time: " << std::chrono::duration_cast<std::chrono::microseconds>(time).count() << '\n';
        }
    }

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
