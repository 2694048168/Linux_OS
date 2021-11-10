/**
 * @File    : stateless_cache_aligned_allocator.cpp
 * @Brief   : Studying an example of stateless, cache–aligned allocator
 * @Author  : Wei Li
 * @Date    : 2021-11-08
*/

/** Stateless and cache-aligned alloctor
 * Create a stateless, equal allocator designed to allocator cachealigned memory. 
 * The goal of this allocator is to show a C++17 allocator 
 * that can be leveraged to increase the efficiency of the objects a container is storing 
 * (for example, a linked list), as cache-thrashing is less likely to occur
 * 
 */

#include <vector>
#include <iostream>

template <typename T, std::size_t Alignment = 0x40>
class myallocator
{
public:
    using value_type = T;
    using pointer = T *;
    using size_type = std::size_t;
    using is_always_equal = std::true_type;

    template <typename U>
    struct rebind
    {
        using other = myallocator<U, Alignment>;
    };

public:
    myallocator()
    {
    }

    template <typename U>
    myallocator(const myallocator<U, Alignment> &other) noexcept
    {
        (void)other;
    }

    pointer allocate(size_type n)
    {
        if (auto ptr = aligned_alloc(Alignment, sizeof(T) * n))
        {
            return static_cast<pointer>(ptr);
        }

        throw std::bad_alloc();
    }

    void deallocate(pointer p, size_type n)
    {
        (void)n;
        free(p);
    }
};

int main(int argc, char **argv)
{
    std::cout << "======== allocate single object ==========\n";
    myallocator<int> myalloc;
    auto ptr = myalloc.allocate(1);
    std::cout << ptr << '\n';
    myalloc.deallocate(ptr, 1);

    std::cout << "======== allocate multiple objects ==========\n";
    myallocator<int> myalloc_multiple;
    auto ptr_multiple = myalloc_multiple.allocate(42);
    std::cout << ptr_multiple << '\n';
    myalloc_multiple.deallocate(ptr_multiple, 42);

    std::cout << "======== std::vector single element ==========\n";
    std::vector<int, myallocator<int>> myvector;
    myvector.emplace_back(42);
    std::cout << myvector.data() << '\n';

    return 0;
}
