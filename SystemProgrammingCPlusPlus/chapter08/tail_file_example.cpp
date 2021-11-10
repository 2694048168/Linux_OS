/**
 * @File    : tail_file_example.cpp
 * @Brief   : The tail file example 
 * @Author  : Wei Li
 * @Date    : 2021-11-07
*/

/** The tail file
 * we will create a simple program to tail a file. 
 * The goal of this example is to mimic the behavior of tail -f -n0, 
 * which outputs new additions to a file. 
 * The -f argument tells the tail to follow the file 
 * and -n0 tells tail to only output to stdout new additions.
 * 
 * How to test the program:
 * 0. g++ -std=c++2a tail_file_example.cpp -o tail_file
 * 1. touch test_tail.txt
 * 2. ./tail_file test_tail.txt
 * 3. echo "Hello World" > test_tail.txt
 * 4. ./tail_file test_tail.txt
 * 5. echo -n "Hello World" > test_tail.txt
 * 6. ./tail_file test_tail.txt
 */

#include <unistd.h>
#include <fstream>
#include <iostream>

#include <gsl/gsl>

// Step 1. define the mode plan to use when opening the file to tail
// the file as read-only and move the read pointer to the end of file on open.
constexpr auto mode = std::ios::in | std::ios::ate;

// Step 2. 'tail' function that watches for changes to a file
// and outputs the changes to stdout
[[noreturn]] void tail(std::fstream &file)
{
    while (true)
    {
        // checks whether the end of the file has been reached by first peeking the file
        file.peek();
        while (!file.eof())
        {
            auto pos = file.tellg();

            std::string buf;
            std::getline(file, buf, '\n');
            // the read pointer is not at the end of the file
            if (file.eof() && !file.good())
            {
                file.seekg(pos);
                break;
            }

            std::cout << buf << '\n';
        }
        //  sleeps for a second, clears all status bits,
        // resyncs with the filesystem to see if any new changes have been made
        sleep(1);

        file.clear();
        file.sync();
    }
}

// Step 3. Parse the arguments provided to our program
// to get the file name to tail, open the file,
// and then call the 'tail' function with the newly opened file.
int protected_main(int argc, char **argv)
{
    std::string filename;
    // parse the arguments using a gsl::span
    // to ensure safety and remain compliant with C++ Core Guidelines.
    auto args = gsl::make_span(argv, argc);

    if (args.size() < 2)
    {
        std::cin >> filename;
    }
    else
    {
        filename = gsl::ensure_z(args[1]).data();
    }

    if (auto file = std::fstream(filename, mode))
    {
        tail(file);
    }

    throw std::runtime_error("failed to open file");
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
