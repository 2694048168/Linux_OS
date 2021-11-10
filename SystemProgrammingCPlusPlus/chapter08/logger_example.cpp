/**
 * @File    : logger_example.cpp
 * @Brief   : Example for logger to debug
 * ----------------------------
 * @Command : g++ -std=c++2a logger_example.cpp -o logger
 * @Command : ./logger
 * @Command : cat log.txt
 * ----------------------------
 * @Author  : Wei Li
 * @Date    : 2021-11-06
*/

#include <sstream>
#include <fstream>
#include <iostream>

/** Step 1. To create two constant expressions
 * one for the debug level, 
 * one to enable or disable debugging outright.
 */
#ifdef DEBUG_LEVEL
constexpr auto g_debug_level = DEBUG_LEVAL;
#else
constexpr auto g_debug_level = 0;
#endif

#ifdef NDEBUG
constexpr auto g_ndebug = true;
#else
constexpr auto g_ndebug = false;
#endif

// Step 2. create a global variable is the log file stream
std::fstream g_log{"log.txt", std::ios::out | std::ios::app};

/** Step 3. log function
 * This function needs to be able to output to both std::clog and
 * to our log file stream without executing the dubug logic more than once.
 */
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
    };
}

// Step 4. protected_main function
int protected_main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    log<0>([]
           { std::clog << "Hello World\n"; });

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
