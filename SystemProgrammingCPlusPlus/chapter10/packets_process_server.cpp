/**
 * @File    : packets_process_server.cpp
 * @Brief   : Tring out example for processing packets
 * @Author  : Wei Li
 * @Date    : 2021-11-09
*/

/** Packets Process
 * Discuss how to process the following packets
 * from the client to the server.
 * 
 * The packet consists of some fixed-width integer data 
 * and a string (fields in a network must always be fixed width, 
 * as you might not have control of the type of computer your application is running on 
 * and non-fixed width types, such as int and long, might change depending on the computer).
 * 
 * This type of packet is common among many programs, but as will be demonstrated, 
 * this type of packet has challenges with respect to safely parsing.
 * 
 * Usage:
 * g++ -std=c++2a packets_process_server.cpp -o packets_process_server
 * g++ -std=c++2a packets_process_client.cpp -o packets_process_client 
 * 
 * ./packets_process_server
 * ./packets_process_client
 */

#include <stdint.h>
#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

// ----Step 0. define port to communication for application
#define PORT 22000
#define MAX_SIZE 0x1000

// ----Step 1. define packets to process
struct packet
{
    uint64_t data1;
    uint64_t data2;

    uint64_t len;
    char buf[MAX_SIZE];
};

// ----Step 2. define server logic
class packets_process_server
{
public:
    explicit packets_process_server(uint16_t port)
    {
        if (m_fd = ::socket(AF_INET, SOCK_STREAM, 0); m_fd == -1)
        {
            throw std::runtime_error(strerror(errno));
        }

        m_addr.sin_family = AF_INET;
        m_addr.sin_port = htons(port);
        m_addr.sin_addr.s_addr = htonl(INADDR_ANY);

        if (this->bind() == -1)
        {
            throw std::runtime_error(strerror(errno));
        }
    }

    ~packets_process_server()
    {
        close(m_fd);
    }

    int bind()
    {
        return ::bind(
            m_fd,
            reinterpret_cast<struct sockaddr *>(&m_addr),
            sizeof(m_addr));
    }

    ssize_t recv(packet &p)
    {
        return ::recv(
            m_client,
            &p,
            sizeof(p),
            0);
    }

    void recv_packet()
    {
        if (::listen(m_fd, 0) == -1)
        {
            throw std::runtime_error(strerror(errno));
        }

        if (m_client = ::accept(m_fd, nullptr, nullptr); m_client == -1)
        {
            throw std::runtime_error(strerror(errno));
        }

        packet p{};

        if (auto len = recv(p); len != 0)
        {
            auto msg = std::string(p.buf, p.len);

            std::cout << "data1: " << p.data1 << '\n';
            std::cout << "data2: " << p.data2 << '\n';
            std::cout << "msg: \"" << msg << "\"\n";
            std::cout << "len: " << len << '\n';
        }

        close(m_client);
    }

private:
    int m_fd{};
    int m_client{};
    struct sockaddr_in m_addr{};
};

int protected_main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    packets_process_server server{PORT};
    server.recv_packet();

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