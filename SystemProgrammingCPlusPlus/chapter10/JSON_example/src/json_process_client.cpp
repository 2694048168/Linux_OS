/**
 * @File    : json_process_client.cpp
 * @Brief   : Processing an example of processing JSON 
 * @Author  : Wei Li
 * @Date    : 2021-11-09
*/

#include <string>
#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
// -------------------------------------
// https:/​/​github.​com/nlohmann/​json
#include <nlohmann/json.hpp>
using json = nlohmann::json;
// -------------------------------------

// define the port to communication for application
#define PORT 22000
#define MAX_SIZE 0x1000

class json_process_client
{
public:
    explicit json_process_client(uint16_t port)
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

    ~json_process_client()
    {
        close(m_fd);
    }

    int connect()
    {
        return ::connect(m_fd, reinterpret_cast<struct sockaddr *>(&m_addr), sizeof(m_addr));
    }

    ssize_t send(const std::string &str)
    {
        return ::send(m_fd, str.data(), str.size(), 0);
    }

    void send_packet()
    {
        json j;

        j["data1"] = 42;
        j["data2"] = 43;
        j["msg"] = "Hello World";

        send(j.dump());
    }

private:
    int m_fd{};
    struct sockaddr_in m_addr{};
};

int protected_main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    json_process_client client{PORT};
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