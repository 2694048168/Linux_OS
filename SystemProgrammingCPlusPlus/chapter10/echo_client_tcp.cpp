/**
 * @File    : echo_client_tcp.cpp
 * @Brief   : echo client program wth TCP connectting 
 * @Author  : Wei Li
 * @Date    : 2021-11-09
*/

#include <array>
#include <string>
#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Step 1. define the maximum buffer size plan to send from the client to the server and back.
//         and define the port wish to use.
#define PORT 22000
#define MAX_SIZE 0x10

class echo_client_tcp
{
public:
    explicit echo_client_tcp(uint16_t port)
    {
        if (m_fd = ::socket(AF_INET, SOCK_STREAM, 0); m_fd == -1)
        {
            throw std::runtime_error(strerror(errno));
        }

        m_addr.sin_family = AF_INET;
        m_addr.sin_port = htons(port);
        m_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

        if (connect() == -1)
        {
            throw std::runtime_error(strerror(errno));
        }
    }

    int connect()
    {
        return ::connect(m_fd, reinterpret_cast<struct sockaddr *>(&m_addr), sizeof(m_addr));
    }

    ssize_t send(const std::string &buf)
    {
        return ::send(m_fd, buf.data(), buf.size(), 0);
    }

    ssize_t recv(std::array<char, MAX_SIZE> &buf)
    {
        return ::recv(m_fd, buf.data(), buf.size() - 1, 0);
    }

    void echo()
    {
        while (true)
        {
            std::string sendbuf{};
            std::array<char, MAX_SIZE> recvbuf{};

            std::cin >> sendbuf;

            send(sendbuf);
            recv(recvbuf);

            std::cout << recvbuf.data() << '\n';
        }
    }

    ~echo_client_tcp()
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

    echo_client_tcp client{PORT};
    client.echo();

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