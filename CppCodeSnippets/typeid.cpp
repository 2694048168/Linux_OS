/**
 * @file typeid.cpp
 * @author Wei Li (weili_yzzcq@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */

 /**
 * @file cpp_snippets.cpp
 * @author Wei Li (weili_yzzcq@163.com)
 * @date 2023-05-09
 * @version 0.1.1
 * 
 * @copyright Copyright (c) 2023
 * @license GPL | Apache 2.0 | BSD | LGPL | MIT
 *
 * @brief 
 * @attention 
 */

#include <iostream>
#include <typeinfo>

// ===================================
int main(int argc, const char **argv)
{
    // https://en.cppreference.com/w/cpp/language/typeid
    /* name() function implementation depended compiler and OS */
    std::cout << typeid(int).name() << "\n";
    if (typeid(42) == typeid(int))
    {
        std::cout << "the same type of int\n";
    }

    return 0;
}
