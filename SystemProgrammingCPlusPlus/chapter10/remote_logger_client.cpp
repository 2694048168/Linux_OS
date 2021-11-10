/**
 * @File    : remote_logger_client.cpp
 * @Brief   : the implements of remote logging facility. 
 * @Author  : Wei Li
 * @Date    : 2021-11-09
*/

#include <array>
#include <string>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

// ----Step 1. defining the debug level and enable macros
#ifdef DEBUG_LEVEL
constexpr auto g_debug_level = DEBUG_LEVEL;
#else
constexpr auto g_debug_level = 0;
#endif

#ifdef NDEBUG
constexpr auto g_ndebug = true;
#else
constexpr auto g_ndebug = false;
#endif

// ----Step 2. defining the client logic using RAII
class remote_logger_client
{
private:
    int m_fd{};
    struct sockaddr_in m_addr{};

public:
    explicit remote_logger_client(uint16_t port)
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

    ~remote_logger_client()
    {
        close(m_fd);
    }
};

// ----Step 3. defining the client log file and port application
#define PORT 22000
#define MAX_SIZE 0x1000
remote_logger_client g_client{PORT};
std::fstream g_log{"client_log.txt", std::ios::out | std::ios::app};


// ----Step 4. defining the client logic
template <std::size_t LEVEL>
constexpr void log(void (*func)())
{
    if constexpr (!g_ndebug && (LEVEL <= g_debug_level))
    {
        std::stringstream buf;

        auto g_buf = std::clog.rdbuf();
        std::clog.rdbuf(buf.rdbuf());

        func();

        std::clog.rdbuf(g_buf);

        std::clog << "\033[1;32mDEBUG\033[0m: ";
        std::clog << buf.str();

        g_log << "\033[1;32mDEBUG\033[0m: ";
        g_log << buf.str();

        g_client.send("\033[1;32mDEBUG\033[0m: ");
        g_client.send(buf.str());
    };
}

int protected_main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    // lambda expression
    log<0>([]{ std::clog << "Hello World\n"; });

    std::clog << "Hello World\n";

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