/**
 * @File    : echo_server_tcp.cpp
 * @Brief   : echo server program wth TCP connectting 
 * @Author  : Wei Li
 * @Date    : 2021-11-09
*/

/** Usage Command
 * g++ -std=c++2a echo_server_tcp.cpp -o echo_server_tcp
 * g++ -std=c++2a echo_client_tcp.cpp -o echo_client_tcp
 * ./echo_server_tcp
 * ./echo_client_tcp
 * 
 * exit or <Ctrl + C>
 */

// Step 1. define the maximum buffer size plan to send from the client to the server and back.
//         and define the port wish to use.
#define PORT 22000
#define MAX_SIZE 0x10

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <array>
#include <string.h>
#include <iostream>

class echo_server_tcp
{
public:
    explicit echo_server_tcp(uint16_t port)
    {
        if (m_fd = ::socket(AF_INET, SOCK_STREAM, 0); m_fd == -1)
        {
            throw std::runtime_error(strerror(errno));
        }

        m_addr.sin_family = AF_INET;
        // man 3 htons
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

    ssize_t send(std::array<char, MAX_SIZE> &buf, ssize_t len)
    {
        if (len >= buf.size())
        {
            throw std::out_of_range("len >= buf.size()");
        }

        return ::send(m_client, buf.data(), len, 0);
    }

    void echo()
    {
        if (::listen(m_fd, 0) == -1)
        {
            throw std::runtime_error(strerror(errno));
        }

        if (m_client == ::accept(m_fd, nullptr, nullptr); m_client == -1)
        {
            throw std::runtime_error(strerror(errno));
        }

        while (true)
        {
            std::array<char, MAX_SIZE> buf{};

            if (auto len = recv(buf); len != 0)
            {
                std::cout << buf.data() << '\n';
                send(buf, len);
            }
            else
            {
                break;
            }
        }

        close(m_client);
    }

    ~echo_server_tcp()
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

    echo_server_tcp server{PORT};
    server.echo();

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
