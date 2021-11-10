/**
 * @File    : posix_style_error.cpp
 * @Brief   : Error handling POSIX-style 
 * @Author  : Wei Li
 * @Date    : 2021-11-10
*/

/** Error handling POSIX-style
 * POSIX-style error handling provides 
 * the most basic form of error handling possible,
 * capable of being leveraged on almost any system, in almost any program.
 * 
 * if (foo() != 0)
 * {
 *      std::cout << errno << '\n';
 * }
 * 
 * Generally, each function called either returns 0 on success or -1 on failure, 
 * and stores the error code into a global (non-thread safe) implementation-defined macro, called errno. 
 * The reason 0 is used for success is that on most CPUs, 
 * comparing a variable to 0 is faster than comparing a variable to any other value, 
 * and the success case is the expected case.
 * 
 * 
 *  POSIX-style error handling does support Resource Acquisition Is Initialization (RAII), 
 * meaning objects defined in the scope of a function are 
 * destroyed properly the function exits in both the success case and the error case
 * 
 */

#include <utility>
#include <cstring>
#include <iostream>

int myfunc(int val)
{
    if (val == 42)
    {
        // set 'errno' to 'EINVAL'
        // which states that the function was provided an invalid argument
        errno = EINVAL;
        return -1;
    }

    return 0;
}

int myfunc2(int val)
{
    if (val == 42)
    {
        errno = EINVAL;
        return 0;
    }

    return 42;
}

std::pair<int, bool> myfunc3(int val)
{
    if (val == 42)
    {
        errno = EINVAL;
        return {0, false};
    }

    return {42, true};
}

int myfunc4(int val, int &error)
{
    if (val == 42)
    {
        error = EINVAL;
        return 0;
    }

    return 42;
}

int nested1(int val)
{
    if (auto ret = myfunc(val); ret != 0)
    {
        std::cout << "nested1 failure: " << strerror(errno) << '\n';
        return ret;
    }
    else
    {
        std::cout << "nested1 success\n";
    }

    return 0;
}

int nested2(int val)
{
    if (auto ret = nested1(val); ret != 0)
    {
        std::cout << "nested2 failure: " << strerror(errno) << '\n';
        return ret;
    }
    else
    {
        std::cout << "nested2 success\n";
    }

    return 0;
}

// RAII
class myclass
{
public:
    ~myclass()
    {
        std::cout << "destructor called\n";
    }
};

int myfuncRAII(int val)
{
    myclass c{};

    if (val == 42)
    {
        errno = EINVAL;
        return -1;
    }

    return 0;
}


int main(int argc, char **argv)
{
    // POSIX-style error handling
    std::cout << "--------------- 1 ---------------------\n";
    if (myfunc(1) == 0)
    {
        std::cout << "success\n";
    }
    else
    {
        // the strerror() function,
        // which converts POSIX-defined error codes into their string equivalent.
        std::cout << "failure: " << strerror(errno) << '\n';
    }

    if (myfunc(42) == 0)
    {
        std::cout << "success\n";
    }
    else
    {
        std::cout << "failure: " << strerror(errno) << '\n';
    }

    // ----step next
    std::cout << "--------------- 2 ---------------------\n";
    if (auto handle = myfunc2(1); handle != 0)
    {
        std::cout << "success: " << handle << '\n';
    }
    else
    {
        std::cout << "failure: " << strerror(errno) << '\n';
    }

    if (auto handle = myfunc2(42); handle != 0)
    {
        std::cout << "success: " << handle << '\n';
    }
    else
    {
        std::cout << "failure: " << strerror(errno) << '\n';
    }

    // ----step next
    std::cout << "--------------- 3 ---------------------\n";
    if (auto [handle, succeess] = myfunc3(1); succeess)
    {
        std::cout << "success: " << handle << '\n';
    }
    else
    {
        std::cout << "failure: " << strerror(errno) << '\n';
    }

    if (auto [handle, succeess] = myfunc3(42); succeess)
    {
        std::cout << "success: " << handle << '\n';
    }
    else
    {
        std::cout << "failure: " << strerror(errno) << '\n';
    }

    // ----step next
    std::cout << "--------------- 4 ---------------------\n";
    int error = 0;
    if (auto handle = myfunc4(1, error); error == 0)
    {
        std::cout << "success: " << handle << '\n';
    }
    else
    {
        std::cout << "failure: " << strerror(error) << '\n';
    }

    if (auto handle = myfunc4(42, error); error == 0)
    {
        std::cout << "success: " << handle << '\n';
    }
    else
    {
        std::cout << "failure: " << strerror(error) << '\n';
    }

    // ----step next
    std::cout << "--------------- 5 ---------------------\n";
    if (nested2(1) == 0)
    {
        std::cout << "nested2(1) complete\n";
    }
    else
    {
        std::cout << "nested2(1) failure: " << strerror(errno) << '\n';
    }

    if (nested2(42) == 0)
    {
        std::cout << "nested2(42) complete\n";
    }
    else
    {
        std::cout << "nested2(42) failure: " << strerror(errno) << '\n';
    }

    // ----RAII 
    std::cout << "--------------- 5 ---------------------\n";
    if (myfuncRAII(1) == 0)
    {
        std::cout << "success\n";
    }
    else
    {
        std::cout << "failure: " << strerror(errno) << '\n';
    }

    if (myfuncRAII(42) == 0)
    {
        std::cout << "success\n";
    }
    else
    {
        std::cout << "failure: " << strerror(errno) << '\n';
    }

    return 0;
}