/**
 * @File    : cpp_style_error.cpp
 * @Brief   : Understanding exception support in C++ 
 * @Author  : Wei Li
 * @Date    : 2021-11-10
*/

/** Exception in C++
 * C++ exceptions provide a mechanism for reporting errors in a thread-safe manner, 
 * without the need to manually unwind the call stack, 
 * while also providing support for RAII and complex data types. 
 * 
 * As with most C++, the catch block is typesafe, 
 * meaning you must state what type of return data you plan to receive in the event of an exception being thrown.
 * 
 * 
 * C++ includes a stack unwinder, which is capable of automatically unwinding the stack, 
 * similar to how we manually unwound the call stack using POSIX-style error handling, 
 * but automatically and without the need to execute branch statements through the code, 
 * resulting in optimal performance (as if error checking was not taking place). 
 * This is called zero-overhead exception handling.
 * 
 * The details of how the unwinder automatically unwinds the call stack without incurring any performance overhead, 
 * while still supporting RAII in a thread-safe manner, is outside the scope of this book, 
 * since this process is extremely complicated. However, a brief explanation follows.
 * 
 * When C++ exceptions are enabled and your code is compiled, 
 * a set of stack-unwinding instructions are also compiled for each function and placed the executable 
 * in a place where the C++ exception unwinder can find them. 
 * The compiler then compiles the code as if error handling is not taking place, 
 * and the code executes as such. If an exception is thrown, 
 * a thread-safe object is created that wraps the data being thrown and is stored. 
 * From there, the execution of the function is reversed using the call stack-unwinding instructions 
 * that were previously saved in the executable, eventually resulting in the function 
 * that threw the exception being exited to its caller. 
 * Before the function exits, all destructors are executed, 
 * and this process is continued for each function that was called in the call stack until a catch{} block 
 * is encountered that is capable of handling the data that was thrown.
 * 
 * Here are some key points to keep in mind:
 * step 1. The unwind instructions are stored in a table in the executable. 
 *   Each time a function's execution needs to be reversed (from a register point of view), 
 *   the unwinder must look up these instructions for the next function in the table. 
 *   This operation is slow (although some optimizations have been added, including the use of a hash table). 
 *   For this reason, exceptions should never be used for control flow as they are slow and inefficient in the error case, 
 *   while extremely efficient in the success case. C++ exceptions should only be used for error handling.
 * 
 * step 2. The more functions you have in a program, or the larger the functions are 
 *   (that is, the more the function touches the CPUs registers), 
 *   the more information that must be stored in the unwind instructions table, resulting in a larger program. 
 *   If C++ exceptions are never used in your program, this information is still compiled and stored in the application. 
 *   For this reason, exceptions should be disabled if they are not used.
 * 
 * In addition to being thread-safe, performant, and capable of supporting RAII, 
 * C++ exceptions all support complex data types. 
 * The typical data type that is used by C++ includes strings.
 * 
 */

#include <cstring>
#include <iostream>
#include <stdexcept>

// ----- Step 1. -----
void myfunc(int val)
{
    if (val == 42)
    {
        throw EINVAL;
    }
}

// ----- Step 2. -----
int myfunc2(int val)
{
    if (val == 42)
    {
        throw EINVAL;
    }

    return 42;
}

// ----- Step 3. -----
int nested1(int val)
{
    myfunc(val);
    std::cout << "nested1 success\n";
}

int nested2(int val)
{
    nested1(val);
    std::cout << "nested2 success\n";
}

// ----- Step 4. -----
class myclass
{
public:
    ~myclass()
    {
        std::cout << "destructor called\n";
    }
};

void myfunc4(int val)
{
    myclass c{};

    if (val == 42)
    {
        throw EINVAL;
    }
}

// ----- Step 5. -----
void myfunc5(int val)
{
    if (val == 42)
    {
        throw std::runtime_error("invalid val");
    }
}

// ----- Step 6. -----
void myfunc6(int val)
{
    if (val == 42)
    {
        throw -1;
    }
}

// ----- Step 7. -----
void myfunc71(int val)
{
    if (val == 42)
    {
        throw std::runtime_error("runtime_error");
    }
}

void myfunc72(int val)
{
    try
    {
        myfunc71(val);
    }
    catch (...)
    {
        auto e = std::current_exception();
        std::rethrow_exception(e);
    }
}

// ----- Step 8. -----
class myexception : public std::exception
{
private:
    int m_error{0};

public:
    myexception(int error) noexcept : m_error{error}
    {
    }

    const char *what() const noexcept
    {
        return "error";
    }

    int error() const noexcept
    {
        return m_error;
    }
};

void myfunc8(int val)
{
    if (val == 42)
    {
        throw myexception(42);
    }
}

// ----- Step 9. -----
class myexception2 : public std::runtime_error
{
public:
    myexception2(int error) noexcept : std::runtime_error("error: " + std::to_string(42))
    {
    }
};

void myfunc9(int val)
{
    if (val == 42)
    {
        throw myexception2(42);
    }
}

// ----- Step 10. -----
class myclass2
{
public:
    ~myclass2()
    {
        std::cout << "uncaught_exceptions: "
                  << std::uncaught_exceptions() << '\n';
    }
};

void myfunc10(int val)
{
    myclass2 c{};

    if (val == 42)
    {
        throw EINVAL;
    }
}

int main(int argc, char **argv)
{
    //  ------------------------- Step 1. -------------------------
    try
    {
        myfunc(1);
        std::cout << "success\n";

        myfunc(42);
        std::cout << "success\n";
    }
    catch(int ret)
    {
        std::cout << "failure: " << strerror(errno) << '\n';
    }

    //  ------------------------- Step 2. -------------------------
    try
    {
        auto handle1 = myfunc2(1);
        std::cout << "success: " << handle1 << '\n';

        auto handle2 = myfunc2(42);
        std::cout << "success: " << handle2 << '\n';
    }
    catch(int ret)
    {
        std::cout << "failure: " << strerror(ret) << '\n';
    }

    //  ------------------------- Step 3. -------------------------
    try
    {
        nested2(1);
        std::cout << "nested2(1) complete\n";

        nested2(42);
        std::cout << "nested2(42) complete\n";
    }
    catch (int ret)
    {
        std::cout << "failure: " << strerror(ret) << '\n';
    }

    //  ------------------------- Step 4. -------------------------
    try
    {
        myfunc4(1);
        std::cout << "success\n";

        myfunc4(42);
        std::cout << "success\n";
    }
    catch (int ret)
    {
        std::cout << "failure: " << strerror(ret) << '\n';
    }

    //  ------------------------- Step 5. -------------------------
    try
    {
        myfunc5(1);
        std::cout << "success\n";

        myfunc5(42);
        std::cout << "success\n";
    }
    catch (const std::exception &e)
    {
        std::cout << "failure: " << e.what() << '\n';
    }

    //  ------------------------- Step 6. -------------------------
    try
    {
        myfunc6(1);
        std::cout << "success\n";

        myfunc6(42);
        std::cout << "success\n";
    }
    catch (...)
    {
        std::cout << "failure\n";
    }

    //  ------------------------- Step 7. -------------------------
    try
    {
        myfunc72(42);
    }
    catch (const std::exception &e)
    {
        std::cout << "caught: " << e.what() << '\n';
    }

    //  ------------------------- Step 8. -------------------------
    try
    {
        myfunc8(1);
        std::cout << "success\n";

        myfunc8(42);
        std::cout << "success\n";
    }
    catch (const myexception &e)
    {
        std::cout << "failure: " << std::to_string(e.error()) << '\n';
    }

    //  ------------------------- Step 9. -------------------------
    try
    {
        myfunc9(1);
        std::cout << "success\n";

        myfunc9(42);
        std::cout << "success\n";
    }
    catch (const std::exception &e)
    {
        std::cout << "failure: " << e.what() << '\n';
    }

    //  ------------------------- Step 10. -------------------------
    try
    {
        myfunc10(1);
        std::cout << "success\n";

        myfunc10(42);
        std::cout << "success\n";
    }
    catch (int ret)
    {
        std::cout << "failure: " << strerror(ret) << '\n';
    }

    return 0;
}
