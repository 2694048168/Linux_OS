/**
 * @File    : c_style_error.cpp
 * @Brief   : Learning about set jump exceptions
 * @Author  : Wei Li
 * @Date    : 2021-11-10
*/

/** Set jump exceptions
 * Set jump exceptions may be viewed as C-style exceptions. 
 * Like C++-style exceptions, 
 * set jump exceptions provide the user with the ability to set a place in the code to return 
 * to in the event of an error, and a method for generating the exception that performs the jump.
 * 
 * ----Usage:
 * g++ -std=c++2a c_style_error.cpp
 * 
 */

#include <cstring>
#include <csetjmp>
#include <iostream>

std::jmp_buf jb;

void myfunc(int val)
{
    if (val == 42)
    {
        errno = EINVAL;
        std::longjmp(jb, -42);
    }
}

std::jmp_buf jb2;
int myfunc2(int val)
{
    if (val == 42)
    {
        errno = EINVAL;
        std::longjmp(jb2, -1);
    }

    return 42;
}

void nested1(int val)
{
    myfunc2(val);
    std::cout << "nested1 success\n";
}

void nested2(int val)
{
    nested1(val);
    std::cout << "nested2 success\n";
}

void myfunc3(int val, jmp_buf &jb)
{
    if (val == 42)
    {
        std::longjmp(jb, EINVAL);
    }
}

class myclass
{
public:
    ~myclass()
    {
        std::cout << "destructor called\n";
    }
};

void myfuncRAII(int val)
{
    myclass c{};

    if (val == 42)
    {
        errno = EINVAL;
        std::longjmp(jb, -1);
    }
}

int main(int argc, char **argv)
{
    std::cout << "--------------------------\n";
    if (setjmp(jb) == -42)
    {
        std::cout << "failure: " << strerror(errno) << '\n';
        std::exit(EXIT_FAILURE);
    }

    myfunc(1);
    std::cout << "success\n";

    myfunc(42);
    std::cout << "success\n";

    std::cout << "--------------------------\n";
    if (setjmp(jb2) == -1)
    {
        std::cout << "failure: " << strerror(errno) << '\n';
        std::exit(EXIT_FAILURE);
    }

    auto handle1 = myfunc2(1);
    std::cout << "success: " << handle1 << '\n';
    auto handle2 = myfunc2(42);
    std::cout << "success: " << handle2 << '\n';

    std::cout << "--------------------------\n";
    if (setjmp(jb2) == -1)
    {
        std::cout << "failure: " << strerror(errno) << '\n';
        exit(EXIT_FAILURE);
    }

    nested2(1);
    std::cout << "nested2(1) complete\n";

    nested2(42);
    std::cout << "nested2(42) complete\n";

    std::cout << "--------------------------\n";
    std::jmp_buf jb;

    if (auto ret = setjmp(jb); ret > 0)
    {
        std::cout << "failure: " << strerror(ret) << '\n';
        exit(EXIT_FAILURE);
    }

    myfunc3(1, jb);
    std::cout << "success\n";

    myfunc3(42, jb);
    std::cout << "success\n";

    std::cout << "--------------------------\n";
    if (setjmp(jb) == -1)
    {
        std::cout << "failure: " << strerror(errno) << '\n';
        exit(EXIT_FAILURE);
    }

    myfuncRAII(1);
    std::cout << "success\n";

    myfuncRAII(42);
    std::cout << "success\n";

    return 0;
}
