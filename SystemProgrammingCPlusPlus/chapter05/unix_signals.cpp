/**
 * @File    : unix_signals.cpp
 * @Brief   : Unix signals, Interrupt, handle specific types of control flow and errors, segmentation fault; kill command
 * @Author  : Wei Li
 * @Date    : 2021-11-02
*/

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <iostream>

// example 2
void handler_1(int sig)
{
    if (sig == SIGINT)
    {
        std::cout << "handler called" << std::endl;
    }
}

// example 3
// To overcome this would be to use a global variable capable of stopping the loop
auto loop = true;
void handler(int sig)
{
    if (sig == SIGINT)
    {
        std::cout << "handler called" << std::endl;
        loop = false;
    }
}

// example 4
void mysystem(const char *command)
{
    if (auto id = fork(); id > 0)
    {
        sleep(2);
        // man 2 kill
        kill(id, SIGINT);
    }
    else
    {
        execlp(command, command, nullptr);
    }
}


int main(int argc, char** argv)
{
    // ------------ Example 1 ------------
    // Ctrl + C 键盘中断信号
    while (true)
    {
        std::cout << "Hello World" << std::endl;
        sleep(1);
    }
    
    // ------------ Example 2 ------------
    // man 2 signal
    signal(SIGINT, handler_1);
    for (auto i = 0; i < 10; ++i)
    {
        std::cout << "Hello World" << std::endl;
        sleep(1);
    }

    // ------------ Example 3 ------------
    // Ctrl + C command to kill 
    signal(SIGINT, handler);

    while (loop)
    {
        std::cout << "Hello World" << std::endl;
        sleep(1);
    }

    // ------------ Example 4 ------------
    mysystem("b.out");

    return 0;
}
