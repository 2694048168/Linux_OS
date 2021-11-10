/**
 * @File    : placement_new.cpp
 * @Brief   : Placement of new. 
 * @Author  : Wei Li
 * @Date    : 2021-11-03
*/

/** Placement of new
 * In addition to aligned allocations and nothrow specifiers, 
 * C++ also provides the ability to allocate memory from an existing, user-controlled buffer, 
 * a situation that can often be seen while programming systems. 
 * For example, suppose you have mapped a buffer from a physical device.
 * Now suppose you wish to allocate from this buffer an integer,
 * the new() placement operator may be used to accomplish this.
 * 
 * It should be noted that the delete() operator is not needed in this case 
 * because the memory to the object being allocated is user-defined, 
 * in which case there is no heap memory to return to the heap when complete.
 */

#include <iostream>

char buf[0x1000];
alignas(0x1000) char buff[0x2000];

int main(int argc, char** argv)
{
    // placement operator to allocate memory 
    // from an existing user-controlled buffer
    auto ptr = new (buf) int;
    std::cout << ptr << '\n';

    // demonstrating that C++ doesn't automatically 
    // manage user-defined memory when the new() placement is used. 
    auto ptr1 = new (buf) int;
    auto ptr2 = new (buf) int;
    std::cout << ptr1 << '\n';
    std::cout << ptr2 << '\n';

    auto ptr_array = new (buf) int[42];
    std::cout << ptr_array << '\n';
    std::cout << &ptr_array[0] << '\n';
    std::cout << &ptr_array[1] << '\n';

    // align memory
    auto ptr_align = new (buff) int;
    std::cout << ptr_align << '\n';

    auto ptr_align_array = new (buff) int[42];
    std::cout << ptr_align_array << '\n';
    
    return 0;
}
