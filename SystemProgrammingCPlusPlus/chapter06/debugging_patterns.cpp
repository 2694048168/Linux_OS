/**
 * @File    : debugging_patterns.cpp
 * -----------------------------------------
 * @Brief   : In programming systems, one of the main uses of console output is debugging.
 * C++ streams provide two different global objects—std::cout and std::cerr.
 * The first option, std::cout, is typically buffered, sent to stdout, 
 * and only flushed when either std::flush or std::endl is sent to the stream. 
 * The second option, std::cerr, provides the same functionality as std::cout, 
 * but is sent to stderr instead of stdout, and is flushed on every call to the global object.
 * -------------------------------
 * @Command : g++ -std=c++2a -DDEBUG_LEVLE=1 debugging_patterns.cpp
 * @Command : g++ -std=c++2a -O3 -DNDEBUG debugging_patterns.cpp
 * @Command : ls -al a.out
 * @Command : readelf -s a.out | grep cout
 * -------------------------------
 * @Author  : Wei Li
 * @Date    : 2021-11-02
*/

#include <iostream>

// ------------- Example 1 -------------
// The following shows a typical pattern in C for debugging
#ifndef NDEBUG
#define DEBUG(...) fprintf(stdout, __VA_ARGS__);
#else
#define DEBUG(...)
#endif

// ------------- Example 2 -------------
// Another common debugging pattern is to provide the debug macro with
// a debug level that allows the developer to dial in how verbose the program is while debugging
#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#ifndef NDEBUG
#define DEBUG(level,...) if(level <= DEBUG_LEVEL) fprintf(stdout, __VA_ARGS__);
#else
#define DEBUG(...)
#endif

// ------------- Example 3 -------------
// debugging with C++17
#ifdef NDEBUG
constexpr auto g_ndebug = true;
#else
constexpr auto g_ndebug = false;
#endif

// ------------- Example 4 -------------
// debug level can also be implemented
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

// ------------- Example 5 -------------
#ifdef DEBUG_LEVLE
constexpr auto g_debug_level = DEBUG_LEVLE;
#else
constexpr auto g_debug_level = 0;
#endif

#ifdef NDEBUG
constexpr auto g_ndebug = true;
#else
constexpr auto g_ndebug = false;
#endif

template <std::size_t LEVEL>
constexpr void debug(void(*func)())
{
    if constexpr (!g_ndebug && (LEVEL <= g_debug_level))
    {
        func();
    };
}

// ------------- Example 6 -------------
/**Another common debugging pattern is to include
 * both the current line number and the filename
 * into debugging statements for additional context.
 * The __LINE__ and __FILE__ macros are used to provide this information.
 */
#ifndef NDEBUG
#define DEBUG(fmt, args...) fprintf(stdout, "%s [%d]: " fmt, __FILE__, __LINE__, args);
#else
#define DEBUG(...)
#endif

// ------------- Example 7 -------------
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

#define console std::cout << __FILE__ << " [" << __LINE__ << "]: "

template <std::size_t LEVEL>
constexpr void debug(void (*func)())
{
    if constexpr (!g_ndebug && (LEVEL <= g_debug_level))
    {
        func();
    };
}

// ------------- Example 8 -------------
/**Finally, to complete our C++17 debugging patterns,
 * we add a debug, warning, and fatal version of the preceding example with color, 
 * and an overload for the fatal function that defaults to exiting with -1 on error.
 */
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

#define console std::cout << __FILE__ << " [" << __LINE__ << "]: "

template <std::size_t LEVEL>
constexpr void debug(void (*func)())
{
    if constexpr (!g_ndebug && (LEVEL <= g_debug_level))
    {
        std::cout << "\033[1;32mDEBUG\033[0m ";
        func();
    };
}

template <std::size_t LEVEL>
constexpr void warning(void (*func)())
{
    if constexpr (!g_ndebug && (LEVEL <= g_debug_level))
    {
        std::cout << "\033[1;33mWARNING\033[0m ";
        func();
    };
}

template <std::size_t LEVEL>
constexpr void fatal(void (*func)())
{
    if constexpr (!g_ndebug && (LEVEL <= g_debug_level))
    {
        std::cout << "\033[1;31mFATAL ERROR\033[0m ";
        func();
        ::exit(-1);
    };
}

template <std::size_t LEVEL>
constexpr void fatal(int error_code, void (*func)())
{
    if constexpr (!g_ndebug && (LEVEL <= g_debug_level))
    {
        std::cout << "\033[1;31mFATAL ERROR\033[0m ";
        func();
        ::exit(error_code);
    };
}

int main(int argc, char **argv)
{
    // ------------- Example 0 -------------
    std::cout << "buffered" << '\n';
    // '\n' is used to send a newline instead of std::endl
    // unless an explicit flush is required.
    std::cout << "buffer flushed" << std::endl;
    std::cerr << "buffer flushed" << '\n';

    // ------------- Example 1 -------------
    // The following shows a typical pattern in C for debugging
    DEBUG("The answer is: %d\n", 42);

    // ------------- Example 2 -------------
    //  the debug macro with a debug level
    DEBUG(0, "The answer is: %d\n", 42);
    DEBUG(1, "The answer no is: %d\n", 43);

    // ------------- Example 3 -------------
    // debugging with C++17
    if constexpr (!g_ndebug)
    {
        std::cout << "The answer is: " << 42 << '\n';
    }

    // ------------- Example 4 -------------
    // debug level can also be implemented
    if constexpr (!g_ndebug && (0 <= g_debug_level))
    {
        std::cout << "The answer is: " << 42 << '\n';
    }
    if constexpr (!g_ndebug && (1 <= g_debug_level))
    {
        std::cout << "The answer is not: " << 43 << '\n';
    }

    // ------------- Example 5 -------------
    debug<0> ([] {std::cout << "The answer is: " << 42 << '\n';});

    debug<1> ([] {std::cout << "The answer is: " << 43 << '\n';});

    // ------------- Example 6 -------------
    DEBUG("The answer is: %d", 42);

    // ------------- Example 7 -------------
    // Lambda expression
    debug<0>([] { console << "The answer is: " << 42 << '\n'; });

    // ------------- Example 8 -------------
    debug<0>([] { console << "The answer is: " << 42 << '\n'; });

    warning<0>([] { console << "The answer might be: " << 42 << '\n'; });

    fatal<0>([] { console << "The answer was not: " << 42 << '\n'; });

    return 0;
}
