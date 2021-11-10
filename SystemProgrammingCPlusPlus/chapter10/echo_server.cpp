/**
 * @File    : echo_server.cpp
 * @Brief   : echo server source code
 * @Author  : Wei Li
 * @Date    : 2021-11-08
*/

/** Exampel on the UDP echo server
 * In this example, will walk you through a simple echo server example using UDP. 
 * An echo server (as is the same with our previous chapters) echoes any input to its output. 
 * In the case of this UDP example, the server echoes data sent to it from a client back to the client. 
 * To keep the example simple, character buffers will be echoed. 
 * How to properly process structured packets will be covered in the following examples.
 * 
 * Usage:
 * g++ -std=c++2a echo_server.cpp -o echo_server
 * g++ -std=c++2a echo_client.cpp -o echo_client
 * ./echo_server
 * ./echo_client
 * 
 */

// Step 1. define the maximum buffer size plan to send from the client to the server and back.
//         and define the port wish to use.
#define PORT 22000
#define MAX_SIZE 0x10

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <array>
#include <iostream>
#include <stdexcept>

class echo_server
{
public:
    explicit echo_server(uint16_t port)
    {
        if (m_fd = ::socket(AF_INET, SOCK_DGRAM, 0); m_fd == -1)
        {
            throw std::runtime_error(strerror(errno));
        }

        m_addr.sin_family = AF_INET;                // IPv4
        m_addr.sin_port = htons(port);              // port to application
        m_addr.sin_addr.s_addr = htons(INADDR_ANY); // IP address

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
        socklen_t client_len = sizeof(m_client);

        return ::recvfrom(m_fd, buf.data(), buf.size(), 0, (struct sockaddr *) &m_client, &client_len);
    }

    ssize_t send(std::array<char, MAX_SIZE> &buf, ssize_t len)
    {
        if (len >= buf.size())
        {
            throw std::out_of_range("len >= buf.size()");
        }

        return ::sendto(m_fd, buf.data(), buf.size(), 0, (struct sockaddr *) &m_client, sizeof(m_client));
    }

    void echo()
    {
        while (true)
        {
            std::array<char, MAX_SIZE> buf{};

            if (auto len = recv(buf); len != 0)
            {
                send(buf, len);
                std::cout << buf.data() << '\n';
            }
            else
            {
                break;
            }
        }
    }

    ~echo_server()
    {
        close(m_fd);
    }

private:
    int m_fd{};
    struct sockaddr_in m_addr
    {
    };
    struct sockaddr_in m_client
    {
    };
};

int protected_main(int argc, char** argv)
{
    (void) argc;
    (void) argv;

    echo_server server{PORT};
    server.echo();

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
        std::cerr << "Caught unhandled exception:" << '\n';
        std::cerr << "- what (): " << e.what() << '\n';
    }
    catch(...)
    {
        std::cerr << "Caught unkonwn exception\n";
    }

    return EXIT_FAILURE;
}