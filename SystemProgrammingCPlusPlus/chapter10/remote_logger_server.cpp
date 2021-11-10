/**
 * @File    : remote_logger_server.cpp
 * @Brief   : the implements of remote logging facility. 
 * @Author  : Wei Li
 * @Date    : 2021-11-09
*/

/** Usage
 * g++ -std=c++2a remote_logger_server.cpp -o remote_logger_server
 * g++ -std=c++2a remote_logger_client.cpp -o remote_logger_client
 * 
 * ./remote_logger_server
 * ./remote_logger_client
 * 
 */

#include <array>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

// TCP connecting for port application and buffer maximum size
#define PORT 22000
#define MAX_SIZE 0x1000

// define the log file
std::fstream g_log{"server_log.txt", std::ios::out | std::ios::app};

// using RAII design pattern for server
class remote_logger_server
{
public:
    explicit remote_logger_server(uint16_t port)
    {
        if (m_fd = ::socket(AF_INET, SOCK_STREAM, 0); m_fd == -1)
        {
            throw std::runtime_error(strerror(errno));
        }

        m_addr.sin_family = AF_INET;
        m_addr.sin_port = htons(port);
        m_addr.sin_addr.s_addr = htons(INADDR_ANY);

        if (this->bind() == -1)
        {
            throw std::runtime_error(strerror(errno));
        }
    }

    int bind()
    {
        return ::bind(m_fd, reinterpret_cast<struct sockaddr *>(&m_addr), sizeof(m_addr));
    }

    ssize_t recv(std::array<char, MAX_SIZE> &buf)
    {
        return ::recv(m_client, buf.data(), buf.size(), 0);
    }

    void log()
    {
        if (::listen(m_fd, 0) == -1)
        {
            throw std::runtime_error(strerror(errno));
        }

        if (m_client = ::accept(m_fd, nullptr, nullptr); m_client == -1)
        {
            throw std::runtime_error(strerror(errno));
        }

        while (true)
        {
            std::array<char, MAX_SIZE> buf{};
            if (auto len = recv(buf); len != 0)
            {
                g_log.write(buf.data(), len);
                std::clog.write(buf.data(), len);
            }
            else
            {
                break;
            }
        }

        close(m_client);
    }

    ~remote_logger_server()
    {
        close(m_fd);
    }

private:
    int m_fd{};
    int m_client{};
    struct sockaddr_in m_addr
    {
    };
};

int protected_main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    remote_logger_server server{PORT};
    server.log();

    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    try
    {
        return protected_main(argc, argv);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Caught unhandled exception:\n";
        std::cerr << " - what(): " << e.what() << '\n';
    }
    catch (...)
    {
        std::cerr << "Caught unknown exception\n";
    }

    return EXIT_FAILURE;
}
