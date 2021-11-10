/**
 * @File    : logger_thread_server.cpp
 * @Brief   : Studying an example on thread logging 
 * @Author  : Wei Li
 * @Date    : 2021-11-10
*/

/** log deubg with threads to support for multiple clients
 * The example will build upon our existing debugger example to add support for multiple clients. 
 * 
 * added support for networking to the example debugger,
 *  providing the ability to offload our debugging logs to a server in addition to the local system.
 * The problem with this is that the server could only accept one connection before closing, 
 * as it didn't have the logic for handling more than one client. 
 * In this example, we will fix that issue.
 * 
 * ----Usage:
 * g++ -std=c++2a logger_thread_server.cpp -lpthread -o logger_thread_server
 * g++ -std=c++2a logger_thread_client.cpp -lpthread -o logger_thread_client
 * ./logger_thread_server
 * ./logger_thread_client
 * ./logger_thread_client
 * 
 * cat client_log.txt
 * cat server_log.txt
 * 
 */

// ----Step 1. define port and max dubug string length
#define PORT 22000
#define MAX_SIZE 0X1000

#include <array>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <mutex>
#include <thread>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

// ----Step 2.
// the log file will be defined as global,
// and a mutex will be added to synchronize access to the log:
std::mutex log_mutex;
std::fstream g_log{"server_log.txt", std::ios::out | std::ios::app};

// -----Step 4.
// Instead of the recv() function being defined in the server,
// we will define it globally to provide easy access to our client threads (each client will spawn a new thread):
ssize_t recv(int handle, std::array<char, MAX_SIZE> &buf)
{
    return ::recv(handle, buf.data(), buf.size(), 0);
}

// ----Step 5.
// Each time a connection is made by a client, the server will
// spawn a new thread (the log() function), which is implemented as follows:
void log(int handle)
{
    while (true)
    {
        std::array<char, MAX_SIZE> buf{};

        if (auto len = recv(handle, buf); len != 0)
        {
            std::unique_lock lock(log_mutex);

            g_log.write(buf.data(), len);
            std::clog.write(buf.data(), len);

            g_log.flush();
        }
        else
        {
            break;
        }
    }

    close(handle);
}

// ----Step 6.
// server is modified to accept incoming connections and spawn threads as a result.
class myserver
{
public:
    myserver(uint16_t port)
    {
        if (m_fd = ::socket(AF_INET, SOCK_STREAM, 0); m_fd == -1)
        {
            throw std::runtime_error(strerror(errno));
        }

        m_addr.sin_family = AF_INET;
        m_addr.sin_port = htons(port);
        m_addr.sin_addr.s_addr = htonl(INADDR_ANY);

        if (bind() == -1)
        {
            throw std::runtime_error(strerror(errno));
        }
    }

    int bind()
    {
        return ::bind(
            m_fd,
            reinterpret_cast<struct sockaddr *>(&m_addr),
            sizeof(m_addr));
    }

    void listen()
    {
        if (::listen(m_fd, 0) == -1)
        {
            throw std::runtime_error(strerror(errno));
        }

        while (true)
        {
            if (int c = ::accept(m_fd, nullptr, nullptr); c != -1)
            {
                std::thread t{log, c};
                t.detach();

                continue;
            }

            throw std::runtime_error(strerror(errno));
        }
    }

    ~myserver()
    {
        close(m_fd);
    }

private:
    int m_fd{};
    struct sockaddr_in m_addr{};
};

int protected_main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    myserver server{PORT};
    server.listen();

    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    try
    {
        return protected_main(argc, argv);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Caught unhandled exception:\n";
        std::cerr << " - whart(): " << e.what() << '\n';
    }
    catch(...)
    {
        std::cerr << "Caught unkonwn exception\n";
    }

    return EXIT_FAILURE;
}