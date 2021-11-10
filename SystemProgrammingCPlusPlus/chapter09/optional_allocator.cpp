/**
 * @File    : optional_allocator.cpp
 * @Brief   : Exploring some optional properties
 * @Author  : Wei Li
 * @Date    : 2021-11-08
*/

/**
 * Some optional properties
 * The optional properties tell a container how the allocator should
 * be handled during a specific operation(that is, copy, move, and swap).
 * The propagate properties tell the container to propagate the operation to the allocator. 
 * 
 * Optional functions
 * there are several optional functions thar provide containers with
 * additional information about the type of allocator they are provideed.
 */

#include <list>
#include <memory>
#include <iostream>

class myallocator_object
{
public:
    using size_type = std::size_t;

public:
    void *allocate(size_type size)
    {
        if (auto ptr = malloc(size))
        {
            std::cout << this << "  A " << ptr << '\n';
            return ptr;
        }

        throw std::bad_alloc();
    }

    void deallocate(void *ptr)
    {
        std::cout << this << "  D " << ptr << '\n';
        free(ptr);
    }
};

template <typename T>
class myallocator
{
public:
    using value_type = T;
    using pointer = T *;
    using size_type = std::size_t;
    using is_always_equal = std::false_type;

    // o overcome these issues, add the following to allocator:
    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type;

public:
    myallocator() : m_object{std::make_shared<myallocator_object>()}
    {
        std::cout << this << " constructor, sizeof(T): "
                  << sizeof(T) << '\n';
    }

    template <typename U>
    myallocator(const myallocator<U> &other) noexcept : m_object{other.m_object}
    {
        std::cout << this << " copy constructor (U), sizeof(T): "
                  << sizeof(T) << '\n';
    }

    myallocator(myallocator &&other) noexcept : m_object{std::move(other.m_object)}
    {
        std::cout << this << " move constructor, sizeof(T): "
                  << sizeof(T) << '\n';
    }

    myallocator &operator=(myallocator &&other) noexcept
    {
        std::cout << this << " move assignment, sizeof(T): "
                  << sizeof(T) << '\n';

        m_object = std::move(other.m_object);
        return *this;
    }

    myallocator(const myallocator &other) noexcept : m_object{other.m_object}
    {
        std::cout << this << " copy constructor, sizeof(T): "
                  << sizeof(T) << '\n';
    }

    myallocator &operator=(const myallocator &other) noexcept
    {
        std::cout << this << " copy assignment, sizeof(T): "
                  << sizeof(T) << '\n';

        m_object = other.m_object;
        return *this;
    }

    pointer allocate(size_type n)
    {
        auto ptr = m_object->allocate(sizeof(T) * n);
        return static_cast<pointer>(ptr);
    }

    void deallocate(pointer p, size_type n)
    {
        (void)n;
        return m_object->deallocate(p);
    }

private:
    std::shared_ptr<myallocator_object> m_object;

    template <typename T1, typename T2>
    friend bool operator==(const myallocator<T1> &lhs, const myallocator<T2> &rhs);

    template <typename T1, typename T2>
    friend bool operator!=(const myallocator<T1> &lhs, const myallocator<T2> &rhs);

    template <typename U>
    friend class myallocator;
};

template <typename T1, typename T2>
bool operator==(const myallocator<T1> &lhs, const myallocator<T2> &rhs)
{
    return lhs.m_object.get() == rhs.m_object.get();
}

template <typename T1, typename T2>
bool operator!=(const myallocator<T1> &lhs, const myallocator<T2> &rhs)
{
    return lhs.m_object.get() != rhs.m_object.get();
}

int main(int argc, char **argv)
{
    std::cout << "================ list ================" << '\n';
    std::list<int, myallocator<int>> mylist;
    mylist.emplace_back(42);

    std::cout << "================ unequal container ================" << '\n';
    std::list<int, myallocator<int>> mylist1;
    std::list<int, myallocator<int>> mylist2;

    mylist1.emplace_back(42);
    mylist1.emplace_back(42);

    mylist2.emplace_back(42);
    mylist2.emplace_back(42);

    std::cout << "----------------------------------------\n";
    mylist2 = mylist1;
    std::cout << "----------------------------------------\n";

    mylist2.emplace_back(42);
    mylist2.emplace_back(42);

    std::cout << "================ unequal container MOVE ================" << '\n';
    std::list<int, myallocator<int>> mylist_move1;
    std::list<int, myallocator<int>> mylist_move2;

    mylist_move1.emplace_back(42);
    mylist_move1.emplace_back(42);

    mylist_move2.emplace_back(42);
    mylist_move2.emplace_back(42);

    std::cout << "----------------------------------------\n";
    mylist_move2 = std::move(mylist_move1);
    std::cout << "----------------------------------------\n";

    mylist_move2.emplace_back(42);
    mylist_move2.emplace_back(42);

    return 0;
}
