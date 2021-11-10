/**
 * @File    : stateful_memory_pool_alloctor.cpp
 * @Brief   : Studying an example of a stateful, memory–pool allocator
 * @Author  : Wei Li
 * @Date    : 2021-11-08
*/

/** Stateful, memory–pool allocator
 * Create a far more complicated allocator, called a pool allocator.
 * The goal of the pool allocator is to quickly allocate memory for a fixed-size type 
 * while simultaneously (and more importantly) reducing internal fragmentation of memory 
 * (that is, the amount of memory that is wasted by each allocation, 
 * even if the allocation size is not a multiple of two or some other optimized allocation size).
 * 
 * Memory-pool allocators are so useful that some implementations of C++ already contain pool allocators. 
 * In addition, C++17 technically has support for a pool allocator in something called a polymorphic allocator 
 * and most operating systems leverage pool allocators within the kernel to reduce internal fragmentation.
 * 
 * The major advantages of a pool allocator are as follows:
 * 1. The use of malloc() is slow. Sometimes free() is slow too, but for some implementations, 
 * free() is as simple as flipping a bit, in which case it can be implemented incredibly fast.
 * 2. Most pool allocators leverage a deque structure, meaning the pool allocator 
 * allocates a large block of memory and then divides this memory up for allocations. 
 * Each block of memory is linked using a linked list so that more memory can be added to the pool as needed.
 * 
 * Pool allocators also have an interesting property where the larger the block size, 
 * the larger the reduction is on internal fragmentation. 
 * The penalty for this optimization is that if the pool is not completely utilized, 
 * the amount of memory that is wasted increases as the block size increases, 
 * so pool allocators should be tailored to meet the needs of the application.
 * 
 * First create a pool class that manages a list of blocks and gives out memory from the blocks. 
 * The list of blocks will be stored in a stack that grows forever 
 * (that is, in this example, we will attempt to defragment the memory in the blocks, 
 * or remove a block from the stack if all memory from the block has been freed). 
 * Each time we add a block of memory to the pool, 
 * we will divide up the block into chunks of the size of sizeof(T), 
 * and add the address of each chunk onto a second stack called the address stack. 
 * When memory is allocated, we will pop an address off the address stack, 
 * and when memory is deallocated, we will push the address back onto the stack.
 */

#include <list>
#include <stack>
#include <chrono>
#include <iostream>
#include <gsl/gsl>

// ---------------------------------------
// Pool memory to fast and performance
// ---------------------------------------
class pool
{
public:
    using size_type = std::size_t;

public:
    pool(size_type size) : m_size{size}
    {
    }

    void *allocate()
    {
        if (m_addrs.empty())
        {
            this->add_addrs();
        }

        auto ptr = m_addrs.top();
        m_addrs.pop();

        return ptr;
    }

    void deallocate(void *ptr)
    {
        m_addrs.push(ptr);
    }

    void rebind(size_type size)
    {
        if (!m_addrs.empty() || !m_blocks.empty())
        {
            std::cerr << "rebind after alloc unsupported\n";
            abort();
        }

        m_size = size;
    }

private:
    void add_addrs()
    {
        constexpr const auto block_size = 0x1000;
        auto block = std::make_unique<uint8_t[]>(block_size);

        auto v = gsl::span<uint8_t>(
            block.get(), block_size);

        auto total_size =
            v.size() % m_size == 0 ? v.size() : v.size() - m_size;

        for (auto i = 0; i < total_size; i += m_size)
        {
            m_addrs.push(&v.at(i));
        }

        m_blocks.push(std::move(block));
    }

private:
    size_type m_size;
    std::stack<void *> m_addrs{};
    std::stack<std::unique_ptr<uint8_t[]>> m_blocks{};
};

// ---------------------
// Allocator
// ---------------------
template <typename T>
class myallocator
{
public:
    using value_type = T;
    using pointer = T *;
    using size_type = std::size_t;
    using is_always_equal = std::false_type;
    using propagate_on_container_copy_assignment = std::false_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type;

public:
    myallocator() : m_pool{std::make_shared<pool>(sizeof(T))}
    {
        std::cout << this << " constructor, sizeof(T): "
                  << sizeof(T) << '\n';
    }

    template <typename U>
    myallocator(const myallocator<U> &other) noexcept : m_pool{other.m_pool}
    {
        std::cout << this << " copy constructor (U), sizeof(T): "
                  << sizeof(T) << '\n';

        m_pool->rebind(sizeof(T));
    }

    myallocator(myallocator &&other) noexcept : m_pool{std::move(other.m_pool)}
    {
        std::cout << this << " move constructor, sizeof(T): "
                  << sizeof(T) << '\n';
    }

    myallocator &operator=(myallocator &&other) noexcept
    {
        std::cout << this << " move assignment, sizeof(T): "
                  << sizeof(T) << '\n';

        m_pool = std::move(other.m_pool);
        return *this;
    }

    myallocator(const myallocator &other) noexcept : m_pool{other.m_pool}
    {
        std::cout << this << " copy constructor, sizeof(T): "
                  << sizeof(T) << '\n';
    }

    myallocator &operator=(const myallocator &other) noexcept
    {
        std::cout << this << " copy assignment, sizeof(T): "
                  << sizeof(T) << '\n';

        m_pool = other.m_pool;
        return *this;
    }

    pointer allocate(size_type n)
    {
        if (n != 1)
        {
            return static_cast<pointer>(malloc(sizeof(T) * n));
        }

        return static_cast<pointer>(m_pool->allocate());
    }

    void deallocate(pointer ptr, size_type n)
    {
        if (n != 1)
        {
            free(ptr);
        }

        m_pool->deallocate(ptr);
    }

private:
    std::shared_ptr<pool> m_pool;

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
    return lhs.m_pool.get() == rhs.m_pool.get();
}

template <typename T1, typename T2>
bool operator!=(const myallocator<T1> &lhs, const myallocator<T2> &rhs)
{
    return lhs.m_pool.get() != rhs.m_pool.get();
}

// -----------------------
// Tests
// -----------------------
template <typename FUNC>
auto benchmark(FUNC func)
{
    auto stime = std::chrono::high_resolution_clock::now();
    func();
    auto etime = std::chrono::high_resolution_clock::now();

    return (etime - stime).count();
}

int main(int argc, char **argv)
{
    std::cout << "======== compare add many ==========\n";
    constexpr const auto num = 100000;

    std::list<int> mylist1;
    std::list<int, myallocator<int>> mylist2;

    auto time1 = benchmark([&]
                           {
                               for (auto i = 0; i < num; i++)
                               {
                                   mylist1.emplace_back(42);
                               }
                           });

    auto time2 = benchmark([&]
                           {
                               for (auto i = 0; i < num; i++)
                               {
                                   mylist2.emplace_back(42);
                               }
                           });

    std::cout << "[TEST] add many:\n";
    std::cout << "  - time1: " << time1 << '\n';
    std::cout << "  - time2: " << time2 << '\n';

    std::cout << "======== compare remove many ==========\n";
    std::list<int> mylist_remove1;
    std::list<int, myallocator<int>> mylist_remove2;

    for (auto i = 0; i < num; i++)
    {
        mylist_remove1.emplace_back(42);
        mylist_remove2.emplace_back(42);
    }

    auto time_remove1 = benchmark([&]
                                  {
                                      for (auto i = 0; i < num; i++)
                                      {
                                          mylist_remove1.pop_front();
                                      }
                                  });

    auto time_remove2 = benchmark([&]
                                  {
                                      for (auto i = 0; i < num; i++)
                                      {
                                          mylist_remove2.pop_front();
                                      }
                                  });

    std::cout << "[TEST] remove many:\n";
    std::cout << "  - time1: " << time_remove1 << '\n';
    std::cout << "  - time2: " << time_remove2 << '\n';

    std::cout << "======== std::list verify ==========\n";
    std::list<int, myallocator<int>> mylist;

    for (auto i = 0; i < num; i++)
    {
        mylist.emplace_back(i);
    }

    uint64_t total1{};
    uint64_t total2{};

    for (auto i = 0; i < num; i++)
    {
        total1 += i;
        total2 += mylist.back();
        mylist.pop_back();
    }

    std::cout << "[TEST] verify: ";
    if (total1 == total2)
    {
        std::cout << "success\n";
    }
    else
    {
        std::cout << "failure\n";
        std::cout << "  - total1: " << total1 << '\n';
        std::cout << "  - total2: " << total2 << '\n';
    }

    return 0;
}