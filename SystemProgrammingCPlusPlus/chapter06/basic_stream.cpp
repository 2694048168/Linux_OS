/**
 * @File    : basic_stream.cpp
 * @Brief   : The basics of stream 
 * @Author  : Wei Li
 * @Date    : 2021-11-02
*/

#include <fcntl.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <stdio.h>

// ---------- example 2 ----------
// provides an overload for the << stream operator
// to print an error code provided by a POSIX-style function
class custom_errno
{
};

std::ostream &operator<<(std::ostream &os, const custom_errno &e)
{
    // man 3 strerror
    return os << strerror(errno);
}

// ---------- example 3 ----------
struct object_t
{
    int data1;
    int data2;
};

std::ostream &operator<< (std::ostream &os, const object_t &obj)
{
    os << "data1: " << obj.data1 << std::endl;
    os << "data1: " << obj.data2 << std::endl;
    return os;
}

std::istream &operator>> (std::istream &is, object_t &obj)
{
    is >> obj.data1;
    is >> obj.data2;
    return is;
}

// ---------- example 5 ----------
template <std::size_t N>
class buf_t
{
private:
    char m_buf[N];

public:
    constexpr auto size()
    {
        return N;
    }

    constexpr auto data()
    {
        return m_buf;
    }
};

template <std::size_t N>
std::istream &operator>> (std::istream &is, buf_t<N> &b)
{
    is >> std::setw(b.size()) >> b.data();
    return is;
}


int main(int argc, char **argv)
{
    // ------------- example 1 -------------
    /**By default, the std::cout and std::wcout objects, which are instantiations of std::ostream, 
     * output data to the standard C stdout, with the only difference being that 
     * std::wcout provides support for Unicode, while std::cout provides support for ASCII.
     * In addition to several non-member overloads,
     * C++ provides the following arithmetic-style member overloads:
     * 
     * basic_ostream &operator<< (arithmetic-style);
     */
    std::cout << "Hello World" << std::endl;
    std::cout << "The answer is: " << 42 << std::endl;

    // std::cin >> ; std::wcin >>
    auto number = 0;
    std::cin >> number;
    std::cout << "User input: " << number << std::endl;

    // Advantages and disadvantages of C++ stream-based IO

    // Beginning with user-defined types
    // ------------- example 2 -------------
    if (open("filename.txt", O_RDWR) == -1)
    {
        std::cout << custom_errno{} << std::endl;
    }

    // ------------- example 3 -------------
    object_t obj;
    std::cin >> obj;
    std::cout << obj;

    // ------------- example 4 -------------
    // safety and implicit memory managemetn
    // buffer overflow situation
    char buf[2];
    // scanf("%s", buf);
    // addressed by specifying a length limit on scanf function
    scanf("%2s", buf);

    // ------------- example 5 -------------
    buf_t<2> buf_2;
    std::cin >> buf_2;

    // ------------- example 6 -------------
    std::string buf_3;
    std::cin >> buf_3;

    return 0;
}
