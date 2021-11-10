/**
 * @File    : fork_function.cpp
 * @Brief   : fork function used to create precesses(duplicate child), 
 *            which is a system call provide by the Operating System
 * @Author  : Wei Li
 * @Date    : 2021-11-02
*/

#include <unistd.h>
#include <iostream>

// Example 3
int data = 0;


int main(int argc, char** argv)
{
    // ------------ Example 1 ------------
    // man 2 fork
    fork();
    std::cout << "Hello World\n";

    // ------------ Example 2 ------------
    // The parent process outputs Hello while the child process outputs World.
    if (fork() != 0)
    {
        // parent process
        std::cout << "Hello\n";
    }
    else
    {
        // child process
        std::cout << "World\n";
    }
    
    // ------------ Example 3 ------------
    // To examine how shared memory is handled between the parent and child process
    if (fork() != 0)
    {
        data = 42;
    }
    std::cout << "The answer is: " << data << std::endl;

    // ------------ Example 4 ------------
    // On most Unix-based operating systems, the first process to execute is 'init'(grandparent), 
    // which starts the rest of the processes on the system using fork(). 
    // complex trees of processes
    fork();
    fork();
    std::cout << "Hello World" << std::endl;

    // ------------ Example 5 ------------
    // why three processes are created instead of two.
    auto pid_1 = fork();
    std::cout << "Process id_1: " << pid_1 << std::endl;

    auto pid_2 = fork();
    std::cout << "Process id_2: " << pid_2 << std::endl;
    std::cout << "----------------------" << std::endl;

    // ------------ Example 6 ------------
    // The use of fork() creates 2^n processes, 
    // with n being the total number of times fork() is called.
    fork();
    fork();
    fork();
    std::cout << "Hello World" << std::endl;
    
    // ------------ Example 7 ------------
    // complex process tree structure
    if (fork() != 0)
    {
        std::cout << "The" << std::endl;
    }
    else
    {
        if (fork() != 0)
        {
            std::cout << "answer" << std::endl;
        }
        else
        {
            std::cout << 42 << std::endl;
        }
        
    }
    
    return 0;
}
