/**
 * @File    : smart_pointer.cpp
 * @Brief   : Smart pointers to increase the safety, reliability, and stability
 * --------------------------------------------
 * @Command : sudo apt update
 * @Command : sudo apt install valgrind
 * @Command : valgrind ./a.out
 * --------------------------------------------
 * @Author  : Wei Li
 * @Date    : 2021-11-05
*/

/** Smart pointers and ownership
 * std::unique_ptr{} :  Defines a pointer uniquely owned by a single entity.
 * Copying this pointer is not allowed and is explicitly prevented by the compiler,
 * and deallocations are automatically handled by C++.
 * 
 * std::shared_ptr{} : Defines a pointer that may be owned by one or more entities. 
 * Copying this pointer is allowed, and deallocation only occurs 
 * when all of the owners have released their ownership.
 * 
 * memory leaks and memory API mismatching have been prevented
 * 
 * std::make_unique<type>(args): To perform a single-object allocation, 
 * the type is provided as the template argument, 
 * and the object's constructor arguments are provided as the arguments to std::make_unique()
 * 
 * std::make_unique<type[]>(size): To perform an array allocation, 
 * the array type is provided as the template argument, 
 * and the size of the array is provided as the argument to std::make_unique()
 * 
 * Since there is no alignment version for std::unique_ptr{} in C++17,
 * if aligned memory is required, it must be allocated manually 
 * 
 * To get std::unique_ptr{} to release its allocation, 
 * the pointer needs to lose scope,
 * causing the destructor of std::unique_ptr{} to be called, 
 * which in turn releases the allocation back to the heap. 
 * std::unique_ptr{} also provides the reset() function,
 * which explicitly tells the pointer to release its memory on demand, 
 * without having to lose scope
 * 
 * Here are a couple of ways std::unique_ptr{} could be invalid (but this is not an exhaustive list):
 * 1. It was originally created using nullptr
 * 2. reset() or release() was called
 * 
 * To check whether std::unique_ptr{} is valid, 
 * to ensure a null dereference doesn't accidentally occur, the Boolean operator may be used
 * 
 * If std::unique_ptr{} is created using the array syntax, 
 * the subscript operator may be used to access a specific element in the array, 
 * similar to using the subscript operator for a standard C array, or std::array{}
 */

#include <memory>
#include <iostream>

class myclass
{
public:
    ~myclass()
    {
        std::cout << "my delete\n";
    }
};

class myclass1
{
public:
    ~myclass1()
    {
        std::cout << "my delete for class 1\n";
    }
};

class myclass2
{
    std::unique_ptr<myclass1> m_data;

public:
    myclass2() : m_data{std::make_unique<myclass1>()}
    {
    }
};

class int_deleter
{
public:
    // To support these types of scenarios,
    // std::unique_ptr{} accepts custom deleters:
    void operator()(int *ptr) const
    {
        std::cout << "My delete for custom\n";
        delete ptr;
    };
};

// alignment version
using aligned_int alignas(0x1000) = int;

struct mystruct
{
    int data{42};
};

/**One limitation of C++17 with respect to std::unique_ptr{} is 
 * the inability to directly add one to an IO stream such as std::cout. 
 * 
 * With C++17, the best way to output the address of std::unique_ptr{} 
 * is to use the get() function, which returns the address of the pointer. 
 * Another way to accomplish this is to create a user-defined overload
 */
template<typename T>
std::ostream &operator << (std::ostream &os, const std::unique_ptr<T> &ptr)
{
    os << ptr.get();
    return os;
}

int main(int argc, char **argv)
{
    // forget to release memory back to the heap.
    // 内存检测
    auto ptr = new int;
    std::cout << ptr << '\n';
    // valgrind ./a.out
    delete ptr;

    auto ptr_array = new int[42];
    std::cout << ptr_array << '\n';
    std::cout << &ptr_array[1] << '\n';
    // valgrind ./a.out
    delete[] ptr_array;

    // smart pointers
    // std::make_unique<Type>(init_value) to create std::unique_ptr{}
    // std::make_shared<Type>(init_value) to create std::shared_ptr{}
    auto ptr_smart = std::make_unique<int>(42);
    std::cout << *ptr_smart << '\n';
    std::cout << &ptr_smart << '\n';

    // automaticlly to delete heap memory
    auto ptr_obj = std::make_unique<myclass>();
    std::cout << ptr_obj.get() << '\n';

    std::cout << "-------------------------" << std::endl;
    myclass2();
    std::cout << "Complete\n";

    // array to memory
    auto ptr_smart_array = std::unique_ptr<myclass1[]>(new myclass1[2]);
    std::cout << &ptr_smart_array << '\n';

    auto ptr_array_smart = std::make_unique<int[]>(42);
    std::cout << ptr_array_smart.get() << '\n';

    // To support these types of scenarios,
    // std::unique_ptr{} accepts custom deleters:
    auto ptr_custom = std::unique_ptr<int, int_deleter>(new int, int_deleter());
    std::cout << ptr_custom.get() << '\n';

    // alignment version
    auto ptr_align = std::unique_ptr<int>(new aligned_int);
    std::cout << ptr_align.get() << '\n';

    // Like a normal C++-style pointer,
    // * and -> may be used to dereference
    auto ptr1 = std::make_unique<int>(42);
    auto ptr2 = std::make_unique<mystruct>();
    std::cout << *ptr1 << '\n';
    std::cout << ptr2->data << '\n';

    // which explicitly tells the pointer to release its memory on demand,
    // without having to lose scope
    auto ptr_scope = std::make_unique<int>();
    std::cout << ptr_scope.get() << '\n';
    ptr_scope.reset();
    std::cout << ptr_scope.get() << '\n';

    // check whether std::make_unique{} is valid
    auto ptr_check = std::make_unique<int>(42);
    if (ptr_check)
    {
        std::cout << *ptr_check << '\n';
    }
    ptr_check.reset();
    if (ptr_check)
    {
        std::cout << *ptr_check << '\n';
    }

    // array syntax
    auto ptr_array_syntax = std::make_unique<int[]>(42);
    std::cout << ptr_array_syntax[1] << '\n';

    // overlaoding for std::make_unique
    auto ptr_overload = std::make_unique<int>();
    std::cout << ptr_overload << '\n';
    std::cout << ptr_overload.get() << '\n';

    return 0;
}
