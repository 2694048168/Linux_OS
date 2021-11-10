/**
 * @File    : nothrow.cpp
 * @Brief   : nothrow, throw exceptions for new and delete function. 
 * @Author  : Wei Li
 * @Date    : 2021-11-03
*/

/** nothrow
 * The new() and delete() operators are allowed to throw exceptions.
 * If an allocation fails, the default new operator throws std::bad_alloc 
 * instead of returning nullptr. 
 * In some situations, often seen when programming systems, 
 * an exception on an invalid allocation is unwanted, and for this reason, 
 * a nothrow version has been provided.
 * 
 * It should be noted that nullptr is only returned for types provided by C++. 
 * For userdefined types, if an exception is thrown during construction, 
 * the nothrow version of new(), which is marked nothrow, 
 * will call std::terminate and abort.
 */

#include <iostream>

// aligned memory
using aligned_int alignas(0x1000) = int;

class myclass
{
public:
    myclass()
    {
        throw std::runtime_error("the answer was not 42");
    }
};


int main(int argc, char **argv)
{
    auto ptr = new (std::nothrow) int;
    std::cout << ptr << '\n';
    delete ptr;

    auto ptr_array = new (std::nothrow) int[42];
    std::cout << ptr_array << '\n';
    delete [] ptr_array;

    // the aligned allocation versions of these functions were 
    // also provided for single-object allocations:
    auto ptr_align = new (std::nothrow) aligned_int;
    std::cout << ptr_align << '\n';
    delete ptr_align;

    auto ptr_align_array = new (std::nothrow) aligned_int[42];
    std::cout << ptr_align_array << '\n';
    delete [] ptr_align_array;

    // marked 'nothrow' , will call 'std::terminate' and abort
    auto ptr_terminate = new (std::nothrow) myclass;
    std::cout << ptr_terminate << '\n';
    delete ptr_terminate;

    return 0;
}
