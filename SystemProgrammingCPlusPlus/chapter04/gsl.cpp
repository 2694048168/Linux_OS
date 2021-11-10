/**
 * @File    : gsl.cpp
 * @Brief   : Guideline Support Library(GSL)
 *           The goal of the C++ Core Guidelines is to provide a set of best practices associated with programming C++. 
 * ----------------------------
 * @Command : sudo apt install libgsl-dev
 * @Command : sudo apt remove libgsl-dev
 * @Command : sudo apt remove --auto-remove libgsl-dev
 * @Command : ll | wc -l
 * @Command : https://www.gnu.org/software/gsl/#downloading
 * ----------------------------
 * @Author  : Wei Li
 * @Date    : 2021-11-01
*/

#define GSL_THROW_ON_CONTRACT_VIOLATION
#include <gsl/gsl>
#include <iostream>

void init(int *ptr)
{
    *ptr = 0;
}

gsl::not_null<int *>
test(gsl::not_null<int *> p)
{
    return p;
}

int test(int i)
{
    Expects(i >= 0 && i < 41);
    i++;

    Ensures(i < 42);
    return i;
}

int main(int argc, char **argv)
{
    // -------- Pointer ownership --------
    auto ptr = new int;
    init(ptr);
    delete ptr;

    gsl::owner<int *> p = new int;
    init(p);
    delete p;

    auto p1 = std::make_unique<int>();
    auto p2 = test(gsl::not_null(p1.get()));

    // -------- Pointer arithmetic --------
    int array[5] = {1, 2, 3, 4, 5};
    auto span = gsl::span(array);

    for (const auto &elem : span)
    {
        std::clog << elem << '\n';
    }

    for (auto i = 0; i < 5; i++)
    {
        std::clog << span[i] << '\n';
    }

    try
    {
        std::clog << span[5] << '\n';
    }
    catch (const gsl::fail_fast &e)
    {
        std::cout << "exception: " << e.what() << '\n';
    }

    gsl::cstring_span<> str = gsl::ensure_z("Hello World\n");
    std::cout << str.data();
    for (const auto &elem : str)
    {
        std::clog << elem;
    }

    // -------- Contracts --------
    try
    {
        Expects(false);
    }
    catch (const gsl::fail_fast &e)
    {
        std::cout << "exception: " << e.what() << '\n';
    }

    test(0);
    try
    {
        test(42);
    }
    catch (const gsl::fail_fast &e)
    {
        std::cout << "exception: " << e.what() << '\n';
    }

    // -------- Utilities --------
    // if SNIPPET34


    return 0;
}



#if SNIPPET34

#define concat1(a,b) a ## b
#define concat2(a,b) concat1(a,b)
#define ___ concat2(dont_care, __COUNTER__)

#include <gsl/gsl>
#include <iostream>

int main(void)
{
    auto ___ = gsl::finally([]{
        std::cout << "Hello World\n";
    });
}

// > g++ scratchpad.cpp; ./a.out
// Hello World

#endif

#if SNIPPET35

#include <gsl/gsl>
#include <iostream>

int main(void)
{
    uint64_t val = 42;

    auto val1 = gsl::narrow<uint32_t>(val);
    auto val2 = gsl::narrow_cast<uint32_t>(val);
}

// > g++ scratchpad.cpp; ./a.out
//

#endif

#if SNIPPET36

#define GSL_THROW_ON_CONTRACT_VIOLATION
#include <gsl/gsl>
#include <iostream>

int main(void)
{
    uint64_t val = 0xFFFFFFFFFFFFFFFF;

    try {
        gsl::narrow<uint32_t>(val);
    }
    catch(...) {
        std::cout << "narrow failed\n";
    }
}

// > g++ scratchpad.cpp; ./a.out
// narrow failed

#endif