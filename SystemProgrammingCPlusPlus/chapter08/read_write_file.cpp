/**
 * @File    : read_write_file.cpp
 * @Brief   : Reading and writing to a file 
 * -----------------------------
 * @Command : echo "Hello World" > test.txt
 * @Command : echo "42" > test.txt
 * @Command : echo "" > test_write.txt
 * @Command : cat test_write.txt
 * -----------------------------
 * @Author  : Wei Li
 * @Date    : 2021-11-06
*/

/** Reading and Writing Files
 * Reading from a file
 * several different methods for reading a file, 
 * includeing by field, by line, and by number of bytes.
 * 
 * std::fstream can be overloaded to provide support for user-defined types.
 * 
 * Writing to a file
 * several defferent modes of tile writing,
 * include by field, by bytes.
 * 
 * When reading and writing, it's possible that different types of errors could occur.
 *  std::fstream provides four different functions for determining the state of the stream:
 * 1. good() function
 * 2. eof() function
 * 3. fail() function
 * 4. bad() function
 */

#include <fstream>
#include <string.h>
#include <iostream>

struct myclass
{
    std::string hello;
    std::string world;
};

std::fstream &operator>>(std::fstream &is, myclass &obj)
{
    is >> obj.hello;
    is >> obj.world;

    return is;
}

std::ostream &operator<<(std::ostream &os, myclass &obj)
{
    os << obj.hello;
    os << ' ';
    os << obj.world;

    return os;
}

/** Reading by bytes
 * We need to ensure that the total number of bytes being read does not exceed the total size of the buffer itself
 *  — an operation that often leads to a coding error, generating hard-todebug buffer overflows.
 * 
 * The simple solution to this problem is to use a wrapper around the read() function 
 *  that checks to make sure the requested number of bytes does not exceed the total size of the buffer
 */
template <typename T, std::size_t N>
void myread(std::fstream &file, T (&str)[N], std::size_t count)
{
    if (count >= N)
    {
        throw std::out_of_range("file.read out of bounds");
    }

    file.read(static_cast<char *>(str), count);
}

// User-defined types are also supported with respect to writing
struct mycalss_write
{
    std::string hello{"Hello"};
    std::string world{"Wrold"};
};

std::fstream &operator<<(std::fstream &os, const mycalss_write &obj)
{
    os << obj.hello;
    os << ' ';
    os << obj.world;

    return os;
}

// buffer overflow issue
// To overcome this, a wrapper should be used whenever using these types of unsafe functions
void mywrite(std::fstream &file, const char *str, std::size_t count)
{
    if (count > strlen(str))
    {
        throw std::out_of_range("file.write out of bounds");
    }

    file.write(str, count);
}

int main(int argc, char **argv)
{
    // The most type-safe method for reading from a file is by field
    if (auto file = std::fstream("test.txt"))
    {
        std::string hello, world;
        // using >> operator() to reading from files
        // For a string, the stream reads characters until the first whitespace or newline is discovered.
        file >> hello >> world;
        std::cout << hello << " " << world << '\n';
    }

    if (auto file = std::fstream("test.txt"))
    {
        int answer;
        // the stream reads in bytes until a whitespace or newline is discovered,
        // and then interprets the input as a number.
        file >> answer;
        std::cout << "The answer is: " << answer << '\n';
    }

    // overloading for fstream
    if (auto file = std::fstream("test.txt"))
    {
        myclass obj;
        file >> obj;
        std::cout << obj << '\n';
    }

    // Reading bytes
    if (auto file = std::fstream("test.txt"))
    {
        // To read a single byte from the stream.
        char c = file.get();
        std::cout << c << '\n';
    }

    if (auto file = std::fstream("test.txt"))
    {
        // To read more than one bytes from the stream.
        // C-style buffer
        char buf[25] = {};
        file.read(buf, 11);
        std::cout << buf << '\n';
    }

    // wrapper function to address the buffer overflow
    if (auto file = std::fstream("test.txt"))
    {
        char buf[25] = {};
        myread(file, buf, 11);
        std::cout << buf << '\n';
    }

    // To overcome these types of issues, gsl::span should be used instead.
    if (auto file = std::fstream("test.txt"))
    {
        // the current read pointer
        std::cout << file.tellg() << '\n';
        // internal read pointer is not incremented; peek() function
        // char c = file.peek();
        // char c = file.get();
        file.ignore(1);
        std::cout << file.tellg() << '\n';
    }

    // C++ also provides the seekg() function,
    // which sets the read pointer to an absolute position
    if (auto file = std::fstream("test.txt"))
    {
        std::string hello, world;

        file >> hello >> world;
        std::cout << hello << " " << world << '\n';

        file.seekg(1);

        file >> hello >> world;
        std::cout << hello << " " << world << '\n';
    }

    // Reading by line
    if (auto file = std::fstream("test.txt"))
    {
        char buf[25] = {};
        file.getline(buf, 25, '\n');
        std::cout << buf << '\n';
    }

    if (auto file = std::fstream("test.txt"))
    {
        std::string str;
        std::getline(file, str);
        std::cout << str << '\n';
    }

    // Finally, if changes are made to a file that has already been opened,
    // the following will sync the current stream with these changes:
    if (auto file = std::fstream("test.txt"))
    {
        // the sync() function may be used to resync an already
        // open file with changes to the file.
        file.sync();
    }

    // ----------------------------------------
    // Writing to fils
    std::cout << "----------------------" << '\n';
    if (auto file = std::fstream("test_write.txt"))
    {
        std::string hello{"Hello"}, world{"World"};
        file << hello << " " << world << '\n';
        file << "The answer is: " << 42 << '\n';
    }

    // User-defined types are also supported with respect to writing
    if (auto file = std::fstream("test_write.txt"))
    {
        file << mycalss_write{} << '\n';
    }

    // writit by byrtes
    if (auto file = std::fstream("test_write.txt"))
    {
        file.put('H');
        file.put('\n');
    }

    if (auto file = std::fstream("test_write.txt"))
    {
        file.write("Hello World\n", 12);
        // to buffer overflow
        // mywrite(file, "Hello World\n", 100);
    }

    // the write stream also has the ability to get
    // the current write pointer position using the tellp() function
    if (auto file = std::fstream("test_write.txt"))
    {
        std::cout << file.tellp() << '\n';
        file << "Hello";
        std::cout << file.tellp() << '\n';
        file << ' ';
        std::cout << file.tellp() << '\n';
        file << "Wrold";
        std::cout << file.tellp() << '\n';
        file << '\n';
        std::cout << file.tellp() << '\n';
    }

    // It is also possible to move the write pointer
    // to an absolute position within the file using the seekp() function,
    if (auto file = std::fstream("test_write.txt"))
    {
        std::cout << file.tellp() << '\n';
        file << "Hello World\n";
        std::cout << file.tellp() << '\n';
        file.seekp(0);
        std::cout << file.tellp() << '\n';
        file << "The answer is: " << 42 << '\n';
        std::cout << file.tellp() << '\n';
    }

    // Finally, as with the sync() function, 
    // the writes to a file can be flushed to the filesystem
    if (auto file = std::fstream("test_write.txt"))
    {
        file.flush();
    }

    return 0;
}
