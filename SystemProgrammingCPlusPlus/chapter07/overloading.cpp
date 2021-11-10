/**
 * @File    : overloading.cpp
 * @Brief   : overloading to memory allocation 
 * @Command : g++ -std=c++2a overloading.cpp
 * @Author  : Wei Li
 * @Date    : 2021-11-04
*/

/** Overloading
 * the default allocation scheme provide by C++ is undesirable.
 * Custom memory layouts
 * Fragmentation
 * Performance optimizations
 * Dubugging and statistics
 */

#include <iostream>

// ------------- example 1 -------------
/** new and delete operator overload
 * Instead of using the dufault allocation scheme provided by C++,
 * your user-defined versions will be used instead.
 */
void *operator new (std::size_t count)
{
    // Warning: Do not use std::cout here.
    return malloc(count);
}

void operator delete (void *ptr)
{
    // Warning: Do not use std::cout here.
    return free(ptr);
}

void *operator new[] (std::size_t count)
{
    // Warning: Do not use std::cout here.
    return malloc(count);
}

void operator delete[] (void *ptr)
{
    // Warning: Do not use std::cout here.
    return free(ptr);
}

// ------------- example 2 -------------
/** Debugging and statistics are a common reason
 * to overload the new() and delete() operators,
 * providing useful information about the types of allocations that are occurring.
 * For example, suppose you wish to record the total number of allocations larger than,
 * or equal to, a page:
 */
std::size_t allocations = 0;

void *operator new (std::size_t count)
{
    if (count >= 0x1000)
    {
        ++allocations;
    }

    return malloc(count);
}

void operator delete (void *ptr)
{
    return free(ptr);
}

// no allocations larger than a page were performed by our program
// Let's see what happens if we allocate a page
struct mystruct
{
    char buf[0x1000];
};

// ------------- example 3 -------------
class mycalss
{
public:
    void *operator new (std::size_t count)
    {
        std::cout << "my new\n";
        return ::operator new (count);
    }

    void operator delete (void *ptr)
    {
        std::cout << "my delete\n";
        return ::operator delete (ptr);
    }
};

// ------------- example 4 -------------
class myclass
{
public:
    void *operator new[](std::size_t count, std::align_val_t al)
    {
        std::cout << "my  new\n";
        return ::operator new(count, al);
    }

    void operator delete[](void *ptr, std::align_val_t al)
    {
        std::cout << "my delete\n";
        return ::operator delete (ptr, al);
    }
};

using aligned_myclass alignas(0x1000) = myclass;


int main(int argc, char **argv)
{
    // ------------- example 1 -------------
    // overloading new and delete opertor
    auto ptr = new int;
    std::cout << ptr << '\n';
    delete ptr;

    // overloading new[] and delete[] opertor
    auto ptr_array = new int[42];
    std::cout << ptr_array << '\n';
    std::cout << &ptr_array[1] << '\n';
    delete [] ptr_array;

    // ------------- example 2 -------------
    auto ptr = new int;
    std::cout << allocations << '\n';
    delete ptr;

    auto ptr_page = new mystruct;
    std::cout << allocations << '\n';
    delete ptr_page;

    // ------------- example 3 -------------
    auto ptr = new mycalss;
    std::cout << ptr << '\n';
    delete ptr;

    // ------------- example 4 -------------
    auto ptr1 = new  aligned_myclass;
    auto ptr2 = new  aligned_myclass[42];
    std::cout << ptr1 << '\n';
    std::cout << ptr2 << '\n';
    delete ptr1;
    delete [] ptr2;

    return 0;
}
