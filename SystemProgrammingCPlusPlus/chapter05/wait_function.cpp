/**
 * @File    : wait_function.cpp
 * @Brief   : Each process is executed by the operating system in whatever order the operating system chooses. To handle this, POSIX provide 'wait' function.
 * @Author  : Wei Li
 * @Date    : 2021-11-02
*/

#include <unistd.h>
#include <sys/wait.h>
#include <iostream>


int main(int argc, char** argv)
{
    // ------------ Example 1 ------------
    if (fork() != 0)
    {
        std::cout << "Parent" << std::endl;

        /** The wait() function, which tells the parent to wait for a child to complete its execution.
         * Pass nullptr to the wait() function, as that tells the wait() function that we are not interested in an error code.
         * The wait() function waits for any child process to complete.
         */
        wait(nullptr);
    }
    else
    {
        std::cout << "Child" << std::endl;;
    }
    
    // ------------ Example 2 ------------
    // man 2 wait
    // The wait() function waits for any child process to complete.
    int id;
    auto id1 = fork();
    auto id2 = fork();
    auto id3 = fork();

    while (true)
    {
        id = wait(nullptr);

        if (id == -1)
        {
            break;
        }

        if (id == id1)
        {
            std::cout << "Child #1 finished" << std::endl;
        }
        
        if (id == id2)
        {
            std::cout << "Child #2 finished" << std::endl;
        }
        
        if (id == id3)
        {
            std::cout << "Child #3 finished" << std::endl;
        }
    }

    if (id1 != 0 && id2 != 0 && id3 != 0)
    {
        std::cout << "Parent done" << std::endl;
    }

    return 0;
}
