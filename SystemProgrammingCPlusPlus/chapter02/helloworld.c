/**
 * @File    : helloworld.c
 * @Brief   : understand the start up process of a C program, see each step the compiler takes to compile.
 * ------------------------------
 * @Complie : gcc -v helloworld.c
 * @Complie : gcc -c helloworld.c; objdump -d helloworld.o
 * @Complie : AR tool to extract the original object files(static libraries)
 * @Complie : LDD tool to see dynamic libraries are needed(dynamic libraries); ldd a.out;
 * ------------------------------
 * @Author  : Wei Li
 * @Date    : 2021-10-29
*/

#include <stdio.h>

int main(int argc, char* argv[])
{
    printf("Hello World\n");

    return 0;
}