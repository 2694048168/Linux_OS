/**
 * @File    : exec_function.cpp
 * @Brief   : The 'exec' system call is used to override the existing process with a completely new process.
 * @Author  : Wei Li
 * @Date    : 2021-11-02
*/

#include <unistd.h>
#include <sys/wait.h>
#include <iostream>


// example 3 for 'fork' function and 'exec' function together
void mysystem(const char *command)
{
    if (fork() == 0)
    {
        execlp(command, command, nullptr);
    }
    else
    {
        wait(nullptr);
    }
}


int main(int argc, char** argv)
{
    // ------------- Example 1 -------------
    // man 3 exec
    // specific version of the exec() family of system calls
    execl("/bin/ls", "ls", nullptr);
    std::cout << "Hello WOrld" << std::endl;
    /** This is why fork() and exec() are usually called together. 
     * The call to fork() creates a new process, 
     * while the call to exec() takes that new process and executes the desired program as that new process.
     */

    // ------------- Example 2 -------------
    /** This is because the system() call forks a new process and runs exec() from that new process. 
     * The parent process runs wait() and returns when the child process is complete.
     */
    system("ls");
    std::cout << "-------------------------------" << std::endl;
    std::cout << "Hello World with system command" << std::endl;
    
    // ------------- Example 3 -------------
    mysystem("ls");
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Hello World for fork and exec function" << std::endl;

    // ------------- Example 4 -------------
    // The last argument is 'nullptr', argv[argc] == nullptr
    execl("/bin/ls", "ls", "-al", nullptr);

    // ------------- Example 5 -------------
    const char *envp_1[] = {"ENV1=1", "ENV1=2", nullptr};
    execle("/bin/ls", "ls", nullptr, envp_1);

    // ------------- Example 6 -------------
    //  absolute path or relative path
    execlp("ls", "ls", nullptr);

    // ------------- Example 7 -------------
    const char *argv_1[] = {"ls", nullptr};
    execv("/bin/ls", const_cast<char **>(argv_1));

    // ------------- Example 8 -------------
    const char *argv_2[] = {"ls", nullptr};
    const char *envp_2[] = {"ENV1", "ENV2", nullptr};
    execve("/bin/ls", const_cast<char **>(argv_2), const_cast<char **>(envp_2));

    // ------------- Example 9 -------------
    const char *argv_3[] = {"ls", nullptr};
    execvp("ls", const_cast<char **>(argv_3));

    return 0;
}
