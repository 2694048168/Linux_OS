/**
 * @File    : copy_move_allocator.cpp
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
#include <iostream>

// overload to adds copy construtor and copy assignment operator
// move constructor and move assignment operator
template <typename T>
class myallocator
{
public:
    using value_type = T;
    using pointer = T *;
    using size_type = std::size_t;
    using is_always_equal = std::true_type;

public:
    myallocator()
    {
        std::cout << this << " constructor, sizeof(T): "
                  << sizeof(T) << '\n';
    }

    template <typename U>
    myallocator(const myallocator<U> &other) noexcept
    {
        (void)other;
    }

    myallocator(myallocator &&other) noexcept
    {
        (void)other;
        std::cout << this << " move constructor, sizeof(T): "
                  << sizeof(T) << '\n';
    }

    myallocator &operator=(myallocator &&other) noexcept
    {
        (void)other;
        std::cout << this << " move assignment, sizeof(T): "
                  << sizeof(T) << '\n';
        return *this;
    }

    myallocator(const myallocator &other) noexcept
    {
        (void)other;
        std::cout << this << " copy constructor, sizeof(T): "
                  << sizeof(T) << '\n';
    }

    myallocator &operator=(const myallocator &other) noexcept
    {
        (void)other;
        std::cout << this << " copy assignment, sizeof(T): "
                  << sizeof(T) << '\n';
        return *this;
    }

    pointer allocate(size_type n)
    {
        if (auto ptr = static_cast<pointer>(malloc(sizeof(T) * n)))
        {
            std::cout << this << "  A [" << n << "]: " << ptr << '\n';
            return ptr;
        }

        throw std::bad_alloc();
    }

    void deallocate(pointer p, size_type n)
    {
        (void)n;

        std::cout << this << "  D [" << n << "]: " << p << '\n';
        free(p);
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
    std::cout << "================ list copy ================" << '\n';
    std::list<int, myallocator<int>> mylist_copy1;
    std::list<int, myallocator<int>> mylist_copy2;

    mylist_copy1.emplace_back(42);
    mylist_copy1.emplace_back(42);

    std::cout << "----------------------------------------\n";
    mylist_copy2 = mylist_copy1;
    std::cout << "----------------------------------------\n";

    mylist_copy2.emplace_back(42);
    mylist_copy2.emplace_back(42);

    std::cout << "================ list move ================" << '\n';
    std::list<int, myallocator<int>> mylist1;
    std::list<int, myallocator<int>> mylist2;

    mylist1.emplace_back(42);
    mylist1.emplace_back(42);

    std::cout << "----------------------------------------\n";
    mylist2 = std::move(mylist1);
    std::cout << "----------------------------------------\n";

    mylist2.emplace_back(42);
    mylist2.emplace_back(42);

    return 0;
}
