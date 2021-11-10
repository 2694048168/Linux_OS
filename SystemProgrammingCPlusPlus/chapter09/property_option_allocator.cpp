/**
 * @File    : property_option_allocator.cpp
 * @Brief   : The properties and options of allocator 
 * @Author  : Wei Li
 * @Date    : 2021-11-08
*/

/** The properties and options of allocator
 * 1. the value pointer type
 * 2. equality(std::true_type)
 * 3. different allocation types
 * 4. coping equal allocators
 * 5. moving equal allocators
 */

#include <list>
#include <vector>
#include <deque>
#include <iostream>

template <typename T>
class myallocator
{
public:
    // The properties and options of allocator
    using value_type = T;
    using pointer = T *;
    using size_type = std::size_t;
    using is_always_equal = std::true_type;

public:
    myallocator()
    {
        std::cout << this << " constructor, sizeof(T): " << sizeof(T) << '\n';
    }

    template <typename U>
    myallocator(const myallocator<U> &other) noexcept
    {
        (void)other;
    }

    pointer allocate(size_type n)
    {
        if (auto ptr = static_cast<pointer>(malloc(sizeof(T) * n)))
        {
            std::cout << this << "A [" << n << "]: " << ptr << '\n';
            return ptr;
        }

        throw std::bad_alloc();
    }

    void deallocate(pointer p, size_type n)
    {
        (void)n;
        std::cout << this << " D [" << n << "]: " << p << '\n';
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


int main(int argc, char** argv)
{
    std::cout << "-------------------- list --------------------" << '\n';
    std::list<int, myallocator<int>> mylist;
    mylist.emplace_back(42);
    // g++ -std=c++2a property_option_allocator.cpp

    std::cout << "-------------------- vector --------------------" << '\n';
    std::vector<int, myallocator<int>> myvector;
    myvector.emplace_back(42);
    myvector.emplace_back(42);
    myvector.emplace_back(42);
    
    std::cout << "-------------------- deque --------------------" << '\n';
    std::deque<int, myallocator<int>> mydeque;
    mydeque.emplace_back(42);
    mydeque.emplace_back(42);
    mydeque.emplace_back(42);

    std::cout << "-------------------- a lot of element deque --------------------" << '\n';
    std::deque<int, myallocator<int>> mydeque_element;
    // three block of memory
    for (auto i = 0; i < 127; i++)
    {
        mydeque_element.emplace_back(42);
    }
    
    for (auto i = 0; i < 127; i++)
    {
        mydeque_element.emplace_back(42);
    }
    
    for (auto i = 0; i < 127; i++)
    {
        mydeque_element.emplace_back(42);
    }

    return 0;
}
