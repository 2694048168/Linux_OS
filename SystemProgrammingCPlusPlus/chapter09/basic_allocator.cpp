/**
 * @File    : basic_allocator.cpp
 * @Brief   : basic allocator(stateless and equal allocator) 
 * @Author  : Wei Li
 * @Date    : 2021-11-08
*/

/** Allocators
 * C++ allocators define a template class that allocates memory for a specific type T 
 * and are defined by the allocator concept definition. 
 * There are two different types of allocators:
 * 1. Allocators that are equal
 * 2. Allocators that are unequal
 * 
 * An allocator that is equal is an allocator that can allocate memory from one allocator 
 * and deallocate memory from another
 * 
 * We allocate memory from one of the allocators and then deallocate memory from the other allocator. 
 * For this to be valid, the allocators must be equal
 * If this does not hold true, the allocators are considered unequal, 
 * which greatly complicates how the allocators can be used.
 * 
 * An unequal allocator is usually an allocator that is stateful,
 * meaning it stores a state within itself that prevents an allocator from deallocating memory
 * from another instance of the same allocator (because the state is different).
 * 
 * Before we dive into the details of a stateful, unequal allocator, 
 * let's review the most basic allocator, which is a stateless, equal allocator.
 * 
 * The properties and options of allocator
 * 1. the value pointer type
 * 2. equality(std::true_type)
 * 3. different allocation types
 * 4. coping equal allocators
 * 5. moving equal allocators
 * 
 * Some optional properties
 * The optional properties tell a container how the allocator should
 * be handled during a specific operation(that is, copy, move, and swap).
 * The propagate properties tell the container to propagate the operation to the allocator. 
 */

#include <iostream>

template <typename T>
class myallocator
{
public:
    // alias to provide a more complete implementation
    using value_type = T;
    using pointer = T *;
    using size_type = std::size_t;

public:
    //  default constructor
    myallocator() = default;

    template <typename U>
    myallocator(const myallocator<U> &other) noexcept
    {
        (void)other;
    }

    pointer allocate(size_type n)
    {
        if (auto ptr = static_cast<pointer>(malloc(sizeof(T) * n)))
        {
            return ptr;
        }

        throw std::bad_alloc();
    }

    void deallocate(pointer p, size_type n)
    {
        (void)n;
        return free(p);
    }
};

template <typename T1, typename T2>
bool operator==(const myallocator<T1> &, const myallocator<T2> &)
{
    return true;
}

template <typename T1, typename T2>
bool operator!=(const myallocator<T1> &, const myallocator<T2> &)
{
    return false;
}

int main(int argc, char **argv)
{
    // C++ containers need allocators
    myallocator<int> myalloc1;
    myallocator<int> myalloc2;

    auto ptr = myalloc1.allocate(1);
    myalloc2.deallocate(ptr, 1);

    return 0;
}
