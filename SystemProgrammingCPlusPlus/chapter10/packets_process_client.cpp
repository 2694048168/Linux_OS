/**
 * @File    : packets_process_client.cpp
 * @Brief   : Tring out example for processing packets
 * @Author  : Wei Li
 * @Date    : 2021-11-09
*/

#include <stdint.h>
#include <string>
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

class packets_process_client
{
public:
    explicit packets_process_client(uint16_t port)
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

    ~packets_process_client()
    {
        close(m_fd);
    }

    int connect()
    {
        return ::connect(m_fd, reinterpret_cast<struct sockaddr *>(&m_addr), sizeof(m_addr));
    }

    ssize_t send(const packet &p)
    {
        return ::send(m_fd, &p, sizeof(p), 0);
    }

    void send_packet()
    {
        auto msg = std::string("Hello World");

        packet p = {
            42,
            43,
            msg.size(),
            {}};

        memcpy(p.buf, msg.data(), msg.size());

        send(p);
    }

private:
    int m_fd{};
    struct sockaddr_in m_addr{};
};

int protected_main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    packets_process_client client{PORT};
    client.send_packet();

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
