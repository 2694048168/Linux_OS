/**
 * @File    : allocate_deallocate_memory.cpp
 * @Brief   : Allocate and deallocate memory using new and delete function instead of malloc and free function to increase the type-safety.
 * @Author  : Wei Li
 * @Date    : 2021-11-03
*/

/** Memory Layout in ELF binary
 * 1. Global memory allocated by OS'loader and located '.bss' and '.data' segment
 * 2. Stack memory allocated on the stack, which local variables
 * 3. Heap memory or dynamic memory, quite large if the physical system and OS can support, need apply and release manually.
 * 4. Aligning memory, some APIs and physical devices require memory to be allocated with a certain minimum granularity.
 */

#include <iostream>

// 1. global memory
int bss_mem = 0;
int data_mem = 42;

// The delete operator calls the destructor for single object.
class myclass
{
public:
    ~myclass()
    {
        std::cout << "my delete\n";
    }
};

// 4. Aligning memory
alignas(0x1000) int ptr_align[42];

// C++17 for heap memory align
using aligned_int alignas(0x1000) = int;

int main(int argc, char** argv)
{
    std::cout << bss_mem << '\n';
    std::cout << data_mem << '\n';

    // 2. stack memory
    // in function and the memory's scope is complete released automaticly,
    // but using stack memory as the memory is limited in size.
    int stack_mem = 42;
    std::cout << stack_mem << '\n';
    // total size of stack, small and how to determine?
    // segmentation fault(core dumped)
    // int stack_mem_array[268435456];
    // std::cout << stack_mem_array[0] << '\n';

    // 3. heap memory
    // return the address of the newlyallocated memory
    auto ptr = new int;
    std::cout << ptr << '\n';
    delete ptr;

    auto ptr_array = new int[42];
    std::cout << ptr_array << '\n';
    std::cout << &ptr_array[0] << '\n';
    std::cout << &ptr_array[1] << '\n';
    delete [] ptr_array;

    // The delete operator calls the destructor for single object.
    auto ptr_object = new myclass[2];
    std::cout << ptr_object << '\n';
    delete [] ptr_object;

    // 4. Aligning memory
    // To allocated aligned memory globally using C++, use the 'alignas()' specifier
    // align the array to a 4k page boundary, 
    // that the first 12 bits are zero
    std::cout << ptr_align << '\n';

    // To allocated aligned memory on the stack
    /** compiler to move the stack pointer in order to align this memory.
     * alignment is high(2MB) stack space run out quickly.
     * another way to allocate aligned memory is to manually calculate an aligned position with an existing characater buffer.
     */
    alignas(0x1000) int ptr_align_stack[42];
    std::cout << ptr_align_stack << '\n';

    // manually calculate an aligned position
    char buffer[0x2000];
    // converted into an unsigned integer pointer type
    auto ptr1 = reinterpret_cast<uintptr_t>(buffer);
    // page-aligned and 4k page boundary
    auto ptr2 = ptr1 - (ptr1 % 0x1000) + 0x1000;

    std::cout << std::hex << std::showbase;
    std::cout << ptr1 << '\n';
    std::cout << ptr2 << '\n';

    // allocate aligned memory is to use dynamic allocations
    // use 'posix_memalign()' or C11 'aligned_alloc()' 
    int *ptr_dynamic;

    if (posix_memalign(reinterpret_cast<void  **>(&ptr_dynamic), 0x1000, 42*sizeof(int)))
    {
        std::clog << "ERROR: unable to allocate aligned memory\n";
        ::exit(EXIT_FAILURE);
    }

    std::cout << ptr_dynamic << '\n';
    // posix_memalign() function is a C-style function
    free(ptr_dynamic);

    // C++11
    if (auto ptr_heap = aligned_alloc(0x1000, 42 * sizeof(int)))
    {
        std::cout << ptr_heap << '\n';
        // aligned_alloc() functions like a regular malloc() but with an additional alignment parameter. 
        // the total size of the array must be manually calculated.
        free(ptr_heap);
    }

    // C++17 for heap memory align
    // the aligned versions added to C++17,
    // automatically calculate the total number of bytes that need to be allocated for you,
    // removing potential errors.
    auto ptr_cpp = new aligned_int;
    std::cout << ptr_cpp << '\n';
    delete ptr_cpp;

    auto ptr_array_cpp = new aligned_int[42];
    std::cout << ptr_array_cpp << '\n';
    delete [] ptr_array_cpp;

    return 0;
}
