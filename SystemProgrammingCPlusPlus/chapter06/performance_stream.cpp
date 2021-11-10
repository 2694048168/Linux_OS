/**
 * @File    : performance_stream.cpp
 * @Brief   : Performance of C++ streams and Control manipulators
 * @Author  : Wei Li
 * @Date    : 2021-11-03
*/

#include <sstream>
#include <iostream>
#include <iomanip>

template <typename FUNC>
void cout_transaction(FUNC f)
{
    auto flags = std::cout.flags();
    f();
    std::cout.flags(flags);
}

namespace usr
{
    class hex_t
    {
    } hex;
}

std::ostream & operator<<(std::ostream &os, const usr::hex_t &obj)
{
    os << std::hex << std::showbase << std::internal
       << std::setfill('0') << std::setw(18);

    return os;
}

int main(int argc, char **argv)
{
    // Avoid flushing and manual flushing
    std::stringstream stream;
    stream << "The answer is: " << 42 << '\n';
    std::cout << stream.str() << std::flush;

    // std::clog sends output to stderr
    std::clog << "The answer is: " << 42 << '\n';

    // control manipulators
    std::cout << "Hello World" << std::endl;
    std::cout << "Hello World\n"
              << std::flush;

    // A common manipulator that is set at the beginning of any program is std::boolalpha,
    // which causes Booleans to be outputted as true or false instead of 1 or 0 (with std::noboolalpha providing the inverse, which is also the default):
    std::cout << "-----------------------------" << '\n';
    std::cout << std::boolalpha;
    std::cout << "The answer is " << true << '\n';
    std::cout << "The answer is " << false << '\n';
    std::cout << std::noboolalpha;
    std::cout << "The answer is " << true << '\n';
    std::cout << "The answer is " << false << '\n';

    // numeric base manipulators
    std::cout << "-----------------------------" << '\n';
    std::cout << "The answer is: " << 42 << '\n'
              << std::hex
              << "The answer is: " << 42 << '\n';
    std::cout << "The answer is: " << 42 << '\n'
              << std::dec
              << "The answer is: " << 42 << '\n';
    std::cout << "The answer is: " << 42 << '\n'
              << std::oct
              << "The answer is: " << 42 << '\n';
    // alphanumeric characters being uppercase
    std::cout << std::hex << std::uppercase << "The answer is: "
              << 42 << '\n';

    std::cout << "-----------------------------" << '\n';
    // printed with their base identifiers
    std::cout << std::showbase;
    std::cout << std::hex << "The answer is: " << 42 << '\n';
    std::cout << std::dec << "The answer is: " << 42 << '\n';
    std::cout << std::oct << "The answer is: " << 42 << '\n';

    std::cout << "-----------------------------" << '\n';
    // Unlike numbers, pointers always output in hexadecimal, lowercase, and with their base being shown
    // One solution to this problem is to cast the pointer to a number
    int i = 0;
    std::cout << &i << '\n';
    std::cout << std::hex << std::showbase << std::uppercase << &i << '\n';
    std::cout << std::hex << std::showbase << std::uppercase << reinterpret_cast<uintptr_t>(&i) << '\n';

    /** std::setw sets the total width (that is, the total number of characters) in the next output.
     * If the next output is not at least the size of the value passed to std::setw,
     * the stream will automatically add spaces to the stream
     */
    std::cout << "-----------------------------" << '\n';
    std::cout << std::dec;
    std::cout << "The answer is: " << std::setw(18) << 42 << '\n';
    std::cout << "The answer is: " << std::setw(18) << std::setfill('0') << 42 << '\n';
    std::cout << "The answer is: " << std::setw(18) << std::left << std::setfill('0') << 42 << '\n';
    std::cout << "The answer is: " << std::setw(18) << std::left << std::setfill('0') << 42 << '\n';

    int num = 0;
    std::cout << std::hex << std::showbase;
    std::cout << "The answer is: "
              << std::setw(18) << std::internal << std::setfill('0')
              << 42 << '\n';

    std::cout << "The answer is: "
              << std::setw(18) << std::internal << std::setfill('0')
              << &num << '\n';

    std::cout << "-----------------------------" << '\n';
    // One way to deal with this issue is to use the std::cout.flags() function,
    // which allows you to both get and set the stream's internal flags:
    auto flags = std::cout.flags();
    std::cout.flags(flags);

    cout_transaction([]
                     {
                         std::cout << std::hex << std::showbase;
                         std::cout << "The answer is: " << 42 << '\n';
                     });

    std::cout << "The answer is: " << 42 << '\n';

    std::cout << "-----------------------------" << '\n';
    std::cout << "The answer is: " << usr::hex << 42 << '\n';

    return 0;
}
