/**
 * @File    : elf_file.cpp
 * @Brief   : Virtual memory layout and Executable and Linkable Format(ELF) 
 * ---------------------------
 * @Command : hexdump -C a.out | grep "The" -B1 -A1
 * @Command : readelf -SW a.out
 * @Command : objdump -d a.out
 * @Command : readelf -lW a.out
 * @Command : cat /etc/fstab
 * @Command : ls /dev/null
 * @Command : hexdump -n16 /dev/null
 * @Command : hexdump -n16 /dev/zero
 * @Command : hexdump -n16 /dev/random
 * ---------------------------
 * @Author  : Wei Li
 * @Date    : 2021-11-02
*/

#include <iostream>


int main(int argc, char** argv)
{
    std::cout << "The answer is: 42\n";
    /** 1. look for this string in the ELF file itself.
     *  2. look at  the ELF sections for this application.
     *  3. look at the assembly for this application using 'objdump'.
     *  4. see an ELF's segments only.
     */

    /** Physical filesystem mapped to virtual filesystem(/etc/fstab)
     *  The filesystem defines the permissions for the file's owner, the file's group, and others.
     */
    
    return 0;
}
