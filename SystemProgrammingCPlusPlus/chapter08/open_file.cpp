/**
 * @File    : open_file.cpp
 * @Brief   : Different ways to open a file.
 * -------------------------------------
 * @Command : touch test.txt; POSIX touch command
 * @Command : g++ -std=c++2a open_file.cpp
 * -------------------------------------
 * @Author  : Wei Li
 * @Date    : 2021-11-06
*/

#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
    /** 1. std::fstream object has an overloaded bool operator
     *  2. is_open() function
     *  3. constructor to initialize
     * 
     * In all of the preceding examples, there was no need to call close() on the file. 
     * This is because, like other C++ classes such as std::unique_ptr that leverage RAII,
     * std::fstream objects close the file automatically for you on destruction.
     */
    // if (auto file = std::fstream("test.txt"))
    // if (auto file = std::fstream("test.txt"); file.is_open())
    auto file = std::fstream();
    if (file.open("test.txt"); file.is_open())
    {
        std::cout << "open file successfully\n";
    }
    else
    {
        std::cout << "open file failurely\n";
    }

    // It is possible, however, to close the file explicitly if so desired
    std::cout << std::boolalpha;
    if (auto file_descriptor = std::fstream("test.txt"))
    {
        std::cout << file_descriptor.is_open() << '\n';
        file_descriptor.close();
        std::cout << file_descriptor.is_open() << '\n';
    }

    // Modes for opening a file
    /** default mode : read and write permissions, and text mode, and beginning of the file.
     * std::ios::in  Open the file for reading
     * std::ios::out  Open the file for writing
     * 
     * several other modes that may be used in conjunction with
     * std::ios::binary
     * std::ios::app
     * std::ios::ate
     * std::ios::trunc
     */
    constexpr auto mode_file = std::ios::in | std::ios::binary;
    if (auto file = std::fstream("test.txt", mode_file))
    {
        std::cout << "open file successfully\n";
    }

    // constexpr auto mode = std::ios::out | std::ios::binary | std::ios::ate;
    constexpr auto mode = std::ios::out | std::ios::binary | std::ios::app;
    if (auto file = std::fstream("test.txt", mode))
    {
        std::cout << "open file successfully\n";
    }

    // The problem with this is that there is no way to open a file for write-only 
    // at the beginning of the file without truncating the file.
    // constexpr auto mode_trunc = std::ios::out  | std::ios::binary | std::ios::trunc;
    constexpr auto mode_trunc = std::ios::out  | std::ios::binary | std::ios::ate;
    if (auto file = std::fstream("test.txt", mode); file.seekp(0))
    {
        std::cout << "open file successfully\n";
    }

    return 0;
}
