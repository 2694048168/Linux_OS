/**
 * @File    : json_process_server.cpp
 * @Brief   : Processing an example of processing JSON 
 * @Author  : Wei Li
 * @Date    : 2021-11-09
*/

/** JSON file processing
 * Demonstrate how packets can be marshaled using JSON to safely reduce the size of a network packet, 
 * at the expense of some additional processing. 
 * To support this example, the following C++ JSON library will be used: 
 * https:/​/​github.​com/nlohmann/​json
 * 
 * Usage:
 * mkdir build && cd build
 * cmake .. -G "Unix Makefiles"
 * make
 * 
 * ./json_process_server
 * ./json_process_client
 */

#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
// -------------------------------------
// https:/​/​github.​com/nlohmann/​json
// using CMkae solution
#include <nlohmann/json.hpp>
using json = nlohmann::json;
// -------------------------------------

// define the port to communication for application
#define PORT 22000
#define MAX_SIZE 0x1000

class json_process_server
{
public:
    explicit json_process_server(uint16_t port)
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

    ~json_process_server()
    {
        close(m_fd);
    }

    int bind()
    {
        return ::bind(m_fd, reinterpret_cast<struct sockaddr *>(&m_addr), sizeof(m_addr));
    }

    ssize_t recv(std::array<char, MAX_SIZE> &buf)
    {
        return ::recv(m_client, buf.data(), buf.size(), 0);
    }

    void recv_packet()
    {
        std::array<char, MAX_SIZE> buf{};

        if (::listen(m_fd, 0) == -1)
        {
            throw std::runtime_error(strerror(errno));
        }

        if (m_client = ::accept(m_fd, nullptr, nullptr); m_client == -1)
        {
            throw std::runtime_error(strerror(errno));
        }

        if (auto len = recv(buf); len != 0)
        {
            auto j = json::parse(buf.data(), buf.data() + len);

            std::cout << "data1: " << j["data1"] << '\n';
            std::cout << "data2: " << j["data2"] << '\n';
            std::cout << "msg: " << j["msg"] << '\n';
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

    json_process_server server{PORT};
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