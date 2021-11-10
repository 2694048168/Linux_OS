/**
 * @File    : shared_pointer.cpp
 * @Brief   : Smart Pointer : std::shared_ptr pointer
 * ---------------------------------------
 * @Command : g++ -std=c++2a -pthread shared_pointer.cpp
 * ---------------------------------------
 * @Author  : Wei Li
 * @Date    : 2021-11-05
*/

/** In most cases, std::unique_ptr{} should be used to allocate dynamic memory. 
 * In some use cases, however, std::unique_ptr{} is incapable of properly representing pointer ownership. 
 * Pointer ownership refers to who owns a pointer, or in other words, 
 * who is responsible for allocating, and more importantly, deallocating a pointer. 
 * In most cases, a single entity within a program is responsible for this task. 
 * There are, however, some use cases where more than one entity must claim responsibility for deallocating a pointer
 * 
 * The most common scenario where more than one entity 
 * must claim ownership over a variable involves threading. 
 * Suppose you have two threads:
 * Thread #1 creates a pointer (and thus owns it)
 * Thread #2 uses the pointer from thread #1
 * 
 * To overcome this issue, C++ provides a second smart pointer,
 * called std::shared_ptr{}, 
 * that is capable of assigning ownership to more than one entity. 
 * The syntax for std::shared_ptr{} is almost identical to std::unique_ptr{}
 * 
 * std::shared_ptr{} doesn't store the pointer itself, 
 * but rather stores a pointer to a managed object that stores the pointer). 
 * Each time std::shared_ptr{} is destroyed, the managed object's count is decreased, 
 * and when the count reaches 0, the pointer is finally released back to the heap
 * 
 * It should be noted that there are some disadvantages
 * 1. Memory footprint
 * 2. Performance
 * 3. Memory leaks
 * 4. Cyclic references
 * 
 * One issue with the C++17 version of std::shared_ptr{} is a lack of an array version,
 * similar to std::unique_ptr{}. That is, there is no std::shared_ptr<type[]> version of std::shared_ptr{}, 
 * similar to the std::unique_ptr<type[]>{} API. 
 * As a result, there is no way to allocate an array using std::make_shared(), 
 * and there is no subscript operator to access each element in the array. 
 */

#include <thread>
#include <memory>
#include <iostream>

// // ------------ example 1 ------------
// class myclass
// {
// private:
//     int m_data{0};

// public:
//     ~myclass()
//     {
//         std::cout << "myclass deleted\n";
//     }

//     void inc()
//     {
//         m_data++;
//     }
// };

// std::thread t1;
// std::thread t2;

// void thread2(myclass *ptr)
// {
//     for (auto i = 0; i < 100000; i++)
//     {
//         ptr->inc();
//     }

//     std::cout << "thread2: complete\n";
// }

// void thread1()
// {
//     auto ptr = std::make_unique<myclass>();
//     t2 = std::thread(thread2, ptr.get());

//     for (auto i = 0; i < 10; i++)
//     {
//         ptr->inc();
//     }

//     std::cout << "thread1: complete\n";
// }

// ------------ example 2 ------------
class myclass
{
private:
    int m_data{0};

public:
    ~myclass()
    {
        std::cout << "myclass deleted\n";
    }

    void inc()
    {
        m_data++;
    }
};

std::thread t1;
std::thread t2;

void thread2(const std::shared_ptr<myclass> ptr)
{
    for (auto i = 0; i < 100000; i++)
    {
        ptr->inc();
    }

    std::cout << "thread2: complete\n";
}

void thread1()
{
    auto ptr = std::make_shared<myclass>();
    t2 = std::thread(thread2, ptr);

    for (auto i = 0; i < 10; i++)
    {
        ptr->inc();
    }

    std::cout << "thread1: complete\n";
}

// both the * and -> operators are provided to dereference
// std::shared_ptr{} (but no subscript operator since arrays are not supported
struct mystruct
{
    int data;
};

// issue with std::shared_ptr{} is that of cyclic references
// class myclass2;

// class myclass1
// {
// public:
//     ~myclass1()
//     {
//         std::cout << "delete myclass1\n";
//     }

//     std::shared_ptr<myclass2> m;
// };

// class myclass2
// {
// public:
//     ~myclass2()
//     {
//         std::cout << "delete myclass2\n";
//     }

//     std::shared_ptr<myclass1> m;
// };

class myclass2;

class myclass1
{
public:
    ~myclass1()
    {
        std::cout << "delete myclass1\n";
    }

    std::weak_ptr<myclass2> m;
};

class myclass2
{
public:
    ~myclass2()
    {
        std::cout << "delete myclass2\n";
    }

    std::weak_ptr<myclass1> m;
};

int main(int argc, char **argv)
{
    // // -------- example 1 --------
    // intro. to std::shared_ptr smart pointer
    // t1 = std::thread(thread1);

    // t1.join();
    // t2.join();

    // using of std::shared_ptr
    auto ptr = std::make_shared<int>();
    std::cout << ptr.get() << '\n';

    // -------- example 2 --------
    t1 = std::thread(thread1);

    t1.join();
    t2.join();

    // Like std::unique_ptr{}, std::shared_ptr{} provides a reset() function
    auto ptr1 = std::make_shared<int>();
    auto ptr2 = ptr1;
    std::cout << ptr1.get() << '\n';
    std::cout << ptr2.get() << '\n';
    ptr2.reset();
    std::cout << ptr1.get() << '\n';
    std::cout << ptr2.get() << '\n';

    // ISSUE
    auto ptr_array = std::shared_ptr<int>(new int[42]());
    std::cout << ptr_array.get()[0] << '\n';

    //  determining how many copies of std::shared_ptr{} exist
    // which essentially just asks the managed object for its reference count
    auto ptr1_copy = std::make_shared<int>();
    auto ptr2_copy = ptr1_copy;
    std::cout << ptr1_copy.get() << '\n';
    std::cout << ptr2_copy.get() << '\n';
    // call to the use_count() function that reports the total number of copies of std::shared_ptr{}.
    std::cout << ptr1_copy.use_count() << '\n';
    ptr2_copy.reset();
    std::cout << ptr1_copy.get() << '\n';
    std::cout << ptr2_copy.get() << '\n';
    std::cout << ptr1_copy.use_count() << '\n';

    // Boolean for checking
    auto ptr_check = std::make_shared<int>();
    if (ptr_check)
    {
        std::cout << "before: " << ptr_check.get() << '\n';
    }
    ptr_check.reset();
    if (ptr_check)
    {
        std::cout << "after: " << ptr_check.get() << '\n';
    }

    // both the * and -> operators are provided to dereference
    auto ptr_refer = std::make_shared<mystruct>();
    std::cout << ptr_refer->data << '\n';

    // // issue with std::shared_ptr{} is that of cyclic references
    // std::cout << "--------------------------\n";
    // auto ptr_1 = std::make_shared<myclass1>();
    // auto ptr_2 = std::make_shared<myclass1>();
    // ptr_1->m = ptr_2;
    // ptr_2->m = ptr_1;

    return 0;
}
