/**
 * @File    : interprocess_communication.cpp
 * @Brief   : Interprocess communication (IPC)
 * @Author  : Wei Li
 * @Date    : 2021-11-02
*/

#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <string>
#include <array>
#include <string_view>
#include <iostream>


// example 2 Unix pipe for IPC
class mypipe
{
private:
    std::array<int, 2> m_handles;

public:
    mypipe()
    {
        // man 2 pipe
        /** The pipe itself is an array of two file handles. 
         * The first handle is used to read from the pipe,
         * while the second handle is used to write to the pipe. 
         * The pipe() function will return -1 if an error occurs.
         */
        if (pipe(m_handles.data()) < 0)
        {
            exit(1);
        }
    }

    ~mypipe()
    {
        close(m_handles.at(0));
        close(m_handles.at(1));
    }

    // std::string readWithPipe()
    std::string read()
    {
        std::array<char, 256> buf;
        // std::size_t bytes = read(m_handles.at(0), buf.data(), buf.size());
        // man 2 read; system call function
        std::size_t bytes = ::read(m_handles.at(0), buf.data(), buf.size());

        if (bytes > 0)
        {
            return {buf.data(), bytes};
        }

        return {};
    }

    // void writeWithPipe(const std::string &msg)
    void write(const std::string &msg)
    {
        // write(m_handles.at(1), msg.data(), msg.size());
        // man 2 write; system call function
        ::write(m_handles.at(1), msg.data(), msg.size());
    }
};
/** :: 是作用域符，是运算符中等级最高的
 * 
 * 1. global scope(全局作用域符），用法（::name)
 * 2. class scope(类作用域符），用法(class::name)
 * 3. namespace scope(命名空间作用域符），用法(namespace::name)
 * 
 * 都是左关联（left-associativity)，作用都是为了更明确的调用想要的变量:
 * 1. 如在程序中的某一处想调用全局变量 a，那么就写成 ::a（也可以是全局函数）
 * 2. 如果想调用 class A 中的成员变量 a，那么就写成 A::a
 * 3. 如果想调用 namespace std 中的 cout 成员，就写成 std::cout (相当于using namespace std；cout)
 */

// Example 3 Unix shared memory for IPC
char *get_shared_memory()
{
    // man 3 ftok; generate unique key for shared memory
    auto key = ftok("myfile" , 42);
    // man 2 shmget; open the shared memory
    auto shm = shmget(key, 0x1000, 0666 | IPC_CREAT);

    // man 2 shmat; return pointer to the shared memory
    return static_cast<char *>(shmat(shm, nullptr, 0));
}
    


int main(int argc, char** argv)
{
    // ------------ Example 1 ------------
    if (fork() != 0)
    {
        sleep(1);
        std::cout << "Parent" << std::endl;
        wait(nullptr);
    }
    else
    {
        std::cout << "Child" << std::endl;
    }

    // ------------ Example 2 ------------
    /** To prevent the child from executing first, we need to set up a communication channel
     * between the parent and child process so that the child process knows to wait for the parent
     * to finish outputting to stdout before the child does. This is called synchronization
     * 
     * use to synchronize the parent and child process is called Interprocess communication (IPC).
     * There are several different types of IPC that can be leveraged in a Unix system.
     * 1. Unix pipes
     * 2. Unix shared memory
     */
    /**IPC (InterProcess Communication)
     * In computer science, inter-process communication or interprocess communication (IPC) refers specifically to the mechanisms an operating system provides to allow the processes to manage shared data. Typically, applications using IPC, are categorized as clients and servers, where the client requests data and the server responds to client requests. Many applications are both clients and servers, as commonly seen in distributed computing.
     * 
     * An independent process is not affected by the execution of other processes while  cooperating processes can be affected by, and may affect, other executing processes. Though one can think that those processes, which are running independently, will execute very efficiently, in reality, there are many situations where the co-operative nature can be utilized for increasing computational speed, convenience and modularity. Inter process communication (IPC) is a mechanism which allows processes to communicate with each other and synchronize their actions. 
     * 
     * IPC is very important to the design process for operating system kernels that desire to be kept small, therefore reduce the number of functionalities provided by the kernel. Those functionalities are then obtained by communicating with servers via IPC, leading to a large increase in communication when compared to a regular type of operating system kernel, which provides a lot more functionality. 
     * 
     * Methods in Interprocess Communication
     * There are several different ways to implement IPC. IPC is set of programming interfaces, used by programs to communicate between series of processes. This allows running programs concurrently in an Operating System. Below are the methods in IPC:
     * 
     * 1. Pipes (Same Process) 
     * This allows flow of data in one direction only. Analogous to simplex systems (Keyboard). Data from the output is usually buffered until input process receives it which must have a common origin.
     * 
     * 2. Names Pipes (Different Processes) 
     * This is a pipe with a specific name it can be used in processes that don’t have a shared common process origin. E.g. is FIFO where the details written to a pipe is first named.
     * 
     * 3. Message Queuing 
     * This allows messages to be passed between processes using either a single queue or several message queue. This is managed by system kernel these messages are coordinated using an API.
     * 
     * 4. Semaphores 
     * This is used in solving problems associated with synchronization and to avoid race condition. These are integer values which are greater than or equal to 0.
     * 
     * 5. Shared memory 
     * This allows the interchange of data through a defined area of memory. Semaphore values have to be obtained before data can get access to shared memory.
     * 
     * 6. Sockets 
     * This method is mostly used to communicate over a network between a client and a server. It allows for a standard connection which is computer and OS independent.
     */

    // Unix pipes to interprocess communication
    /** A pipe is a mechanism for sending information from one process to another.
     * pipe is a file (in RAM) that one process can write to, and the other can read from.
     * The file starts out empty, and no bytes can be read from the pipe until bytes are written to it.
     * 
     * Using this simple example, 
     * we are able to send information from one process to another. 
     * In this case, we use this communication to synchronize the parent and child processes.
     */
    mypipe p;
    if (fork() != 0)
    {
        sleep(1);
        std::cout << "Parent" << std::endl;

        p.write("Done");
        wait(nullptr);
    }
    else
    {
        auto msg = p.read();
        std::cout << "Child" << std::endl;
        std::cout << "msg: " << msg << std::endl;
    }

    // ------------ Example 3 ------------
    // Unix shared memory for IPC
    if (fork() != 0)
    {
        sleep(1);
        std::cout << "Parent" << std::endl;

        auto msg = get_shared_memory();
        msg[0] = 42;
        wait(nullptr);
    }
    else
    {
        auto msg = get_shared_memory();
        while (msg[0] != 42);

        std::cout << "Child" << std::endl;
    }
    
    return 0;
}
