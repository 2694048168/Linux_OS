/**
 * @File    : helloworld.cpp
 * @Brief   : slightly longer than the equivalent C example.
 * ------------------------------
 * @Complie : gcc helloworld.c -o c_helloworld
 * @Complie : g++ helloworld.cpp -o cpp_helloworld
 * @Complie : stat -c "%s %n" c_helloworld cpp_helloworld
 * @Complie : nm -gC cpp_helloworld; To show the symbols
 * @Complie : c++filt _ZSt4cout; To demange these mangled names
 * ------------------------------
 * @Author  : Wei Li
 * @Date    : 2021-10-29
*/

#include <iostream>

void test(void) {}
void test(bool b) {}

int main(int argc, char** argv)
{
    test();
    test(false);

    // std::cout << "Hello World" << std::endl;
    
    return 0;
}