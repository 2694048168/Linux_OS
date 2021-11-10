/**
 * @File    : memory_map.cpp
 * @Brief   : Allocating memory on POSIX system.  POSIX style for allocating memory is to use mmap() fucntion.
 * ---------------------------------
 * @Comman : g++ -std=c++2a memory_map.cpp -lrt
 * ---------------------------------
 * @Author  : Wei Li
 * @Date    : 2021-11-05
*/

/** memory mapping and permissions
 * The mmap() function may be used to map memory from different sources into a program.
 * want to make device memory into your application, you would use mmap(). 
 * 
 * If MAP_ANONYMOUS is passed to mmap(), it can be used to allocate memory the 
 * same way you would allocate memory using malloc() and free(). 
 * mmap() is used to allocate a 4k page of memory that is marked read/write. 
 * 
 * The use of MAP_PRIVATE tells mmap() that you do not intend to share this memory with other applications
 * (for example, for interprocess communication).
 * 
 * Advantages: 
 * 1. Fragmentation
 * 2. Permissions(read-write-execute)
 * 3. Shared memory
 * Disadvantages:
 * 1. Performance
 * 2. Granularity
 * 
 * Permissions:
 * On systems that support read/write or read/execute
 * write and execute permissions should not be used together at the same time.(enforce W^E permissions.)
 * 
 * while still providing a means to set the desired permissions,
 * POSIX provides mprotect(),
 * which allows you to change the permissions of memory that has already been allocated. 
 */

/** Memory fragmentation
 * Memory fragmentation refers to a process in which memory is broken up into chunks, 
 * often spread out, almost always resulting in the allocator's inability to allocate memory for an application, 
 * ultimately resulting in std::bad_alloc() being thrown in C++. 
 * When programming systems, fragmentation should always be a concern as it can
 * dramatically impact the stability and reliability of your program, 
 * especially on resourceconstrained systems, such as embedded and mobile applications. 
 * 
 * There are two types of fragmentation — external and internal fragmentation
 * 
 * External fragmentation refers to the process by 
 * which memory is allocated and deallocated in different sized chunks, 
 * ultimately leading to large amounts of unusable, unallocatable memory. 
 * in other words, the free memory is fragmented.
 * External fragmentation, in the general case, is an extremely difficult problem to solve, 
 * and this problem has been studied for years, with operating systems implementing various approaches over time.
 * 
 * How C++ allocators can be used to address some external fragmentation issues 
 * in your program using various different custom allocator patterns
 * 
 * Internal fragmentation refers to memory being wasted during an allocation. 
 * For example, when we allocate an integer using mmap(), as we did in the preceding examples, 
 * mmap() allocates an entire page for the integer, wasting nearly 4k of memory in the process. 
 * This is known as internal fragmentation.
 * 
 * Internal over external fragmentation
 * External over internal fragmentation
 */

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <memory>
#include <string>
#include <iostream>

constexpr auto PROT_RW = PROT_READ | PROT_WRITE;
constexpr auto MAP_ALLOC = MAP_PRIVATE | MAP_ANONYMOUS;

// Smart  pointers and mmap() function
// Memory leaks and Memory mismatch
class mmap_deleter
{
private:
    std::size_t m_size;

public:
    mmap_deleter(std::size_t size) : m_size(size)
    {

    }

    void operator() (int *ptr) const
    {
        munmap(ptr, m_size);
    }
};

template <typename T, typename... Args>
auto mmap_unique(Args&&... args)
{
    if (auto ptr = mmap(0, sizeof(T), PROT_RW, MAP_ALLOC, -1, 0))
    {
        auto obj = new (ptr) T(args...);
        auto del = mmap_deleter(sizeof(T));

        return std::unique_ptr<T, mmap_deleter>(obj, del);
    }

    throw std::bad_alloc();
}

// shared memory for interprocess  communications
auto name = "/shm";

template <typename T, typename... Args>
auto mmap_unique_server(Args&&... args)
{
    if (int fd = shm_open(name, O_CREAT | O_RDWR, 0644); fd != -1)
    {
        ftruncate(fd, sizeof(T));

        if (auto ptr = mmap(0, sizeof(T), PROT_RW, MAP_SHARED, fd, 0))
        {
            auto obj = new (ptr) T(args...);
            auto del = mmap_deleter(sizeof(T));

            return std::unique_ptr<T, mmap_deleter>(obj, del);
        }
    }

    throw std::bad_alloc();
}

template <typename T>
auto mmap_unique_client()
{
    if (int fd = shm_open(name, O_RDWR, 0644); fd != -1)
    {
        ftruncate(fd, sizeof(T));

        if (auto ptr = mmap(0, sizeof(T), PROT_RW, MAP_SHARED, fd, 0))
        {
            auto obj = static_cast<T*>(ptr);
            auto del = mmap_deleter(sizeof(T));

            return std::unique_ptr<T, mmap_deleter>(obj, del);
        }
    }

    throw std::bad_alloc();
}


int main(int argc, char** argv)
{
    // man 2 mmap
    auto ptr = mmap(0, 0x1000, PROT_RW, MAP_ALLOC, -1, 0);
    std::cout << ptr << '\n';

    // To demonstrate the potential waste of mmap() function
    auto ptr1 = mmap(0, 42, PROT_RW, MAP_ALLOC, -1, 0);
    auto ptr2 = mmap(0, 42, PROT_RW, MAP_ALLOC, -1, 0);

    std::cout << ptr1 << '\n';
    std::cout << ptr2 << '\n';

    // man 2 munmap
    munmap(ptr1, 42);
    munmap(ptr2, 42);

    // mmap() functon may be used to allocate memory with special parameters.
    auto ptr_permissions = mmap(0, 0x1000, PROT_READ | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    std::cout << ptr_permissions << '\n';

    munmap(ptr_permissions, 0x1000);

    // change the permissions of memory
    auto ptr_permiss = mmap(0, 0x1000, PROT_RW, MAP_ALLOC, -1, 0);
    std::cout << ptr_permiss << '\n';
    if (mprotect(ptr_permiss, 0x1000, PROT_READ) == 1)
    {
        std::clog << "ERROR: Failed to change memory permissions\n";
        ::exit(EXIT_FAILURE);
    }
    munmap(ptr_permiss, 0x1000);

    // Smart  pointers and mmap() function
    // Memory leaks and Memory mismatch
    auto ptr_smart = mmap_unique<int>(42);
    std::cout << *ptr_smart << '\n';

    // shared memory for interprocess communications
    // g++ -std=c++2a memory_map.cpp -lrt
    auto ptr_server = mmap_unique_server<int>(42);
    auto ptr_client = mmap_unique_client<int>();
    std::cout << *ptr_server << '\n';
    std::cout << *ptr_client << '\n';
    
    return 0;
}
