/**
 * @File    : disassemble_function_call.cpp
 * @Brief   : Funtion prologs and epilogs
 * --------------------------
 * @Command : objdump -d /path/to/binary;  Disassemble the resulting binary
 * @Command : objdump --disassemble /path/to/binary
 * @Command : g++ -mno-red-zone disassemble_function_call.cpp; -mno-red-zone flag with GCC
 * @Command : readelf -SW a.out; To see the '.eh_frame' table
 * @Command : readelf --debug-dump=frames a.out; To see the information for dubug
 * @Command : hexdump -C a.out; To see ELF file
 * @Command : readelf -hW a.out; To see ELF header that describes critical components of the ELF file itself.
 * --------------------------
 * @Author  : Wei Li
 * @Date    : 2021-11-01
*/

#include <cstdint>
#include <exception>
#include <iostream>


int test()
{
    int i = 1;
    int j = 2;

    return i + j;
}

// volatile and non-volatile registers
// registers to pass parameters
int test(int val1, int val2)
{
    return val1 + val2;
}

// 'rdx' can also be used to return more than one value.
struct mystruct
{
    uint64_t data1;
    uint64_t data2;
};
mystruct testMoreReturn()
{
    return {1, 2};
}

// Exception in C++ in the call stack
void test(int i)
{
    if (i == 42)
    {
        throw 42;
    }
}



int main(int argc, char** argv)
{
    test();

    // deassemble to show registers to pass parameters
    test(42, 42);

    /**The return register for System V is 'rax',
     * which means that every function that returns a value will do so using 'rax'.
     * To return more than one value, 'rdx' can also be used.
     * -----------------------------------------------
     * 00000000000011a1 <_Z14testMoreReturnv>:
     * 11a1:       f3 0f 1e fa             endbr64 
     * 11a5:       55                      push   %rbp
     * 11a6:       48 89 e5                mov    %rsp,%rbp
     * 11a9:       b8 01 00 00 00          mov    $0x1,%eax
     * 11ae:       ba 02 00 00 00          mov    $0x2,%edx
     * 11b3:       5d                      pop    %rbp
     * 11b4:       c3                      retq 
     * -----------------------------------------------
     * It should be noted that the examples make heavy use of registers
     * that are prefixed with 'e' rather than 'r'.
     * This is because 'e' denoteds a 32-bit register, 
     * while 'r' denoted a 64-bit register.
     */
    auto ret = testMoreReturn();

    /**C++ exceptions provide a way to return an error to a 'catch'
     * handler somewhere in the call stack.
     * 
     * The DWARF specification provides all the information needed to dubug an application.
     * The DWARF specification is also used to define the instructions needed to reverse the stack;
     * in other words, to execute a function in reverse with respect to the contents of the nonvolatile registers.
     */
    try
    {
        test(1);
        std::cout << "Attempt #1: passed" << std::endl;

        test(42);
        std::cout << "Attempt #2: passed" << std::endl;
    }
    catch(...)
    {
        std::cout << "Exception catch" << '\n';
    }

    return 0;
}
