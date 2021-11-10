/**
 * @File    : error_handler.cpp
 * @Brief   : Error handler of reading and writing files
 * @Author  : Wei Li
 * @Date    : 2021-11-06
*/

/** Error handler of reading and writing files
 * When reading and writing, it's possible that different types of errors could occur.
 *  std::fstream provides four different functions for determining the state of the stream:
 * 1. good() function
 * 2. eof() function
 * 3. fail() function
 * 4. bad() function
 */

#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
    std::cout << std::boolalpha;
    if (auto file = std::fstream("test.txt"))
    {
        std::string hello{"Hello"}, world{"World"};
        file << hello << " " << world << '\n';
        std::cout << "Good: " << file.good() << '\n';
        std::cout << "Fail: " << file.fail() << '\n';
        std::cout << "Bad: " << file.bad() << '\n';
        std::cout << "Eof: " << file.eof() << '\n';
    }

    if (auto file = std::fstream("test.txt"))
    {
        std::string hello{"Hello"}, world{"World"};
        file << hello << " " << world << '\n';
        if (!file)
        {
            std::cout << "failed\n";
        }
    }

    if (auto file = std::fstream("test.txt"))
    {
        std::string hello{"Hello"}, world{"World"};
        file << hello << " " << world << '\n';
        if (file)
        {
            std::cout << "success\n";
        }
    }

    if (auto file = std::fstream("test.txt"))
    {
        int answer;
        std::cout << file.good() << '\n';
        file >> answer;
        std::cout << file.good() << '\n';
        file.clear();
        std::cout << file.good() << '\n';
    }
    
    return 0;
}
