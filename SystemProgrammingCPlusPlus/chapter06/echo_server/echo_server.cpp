/**
 * @File    : echo_server.cpp
 * @Brief   : Understanding the Serial Echo server example
 * -----------------------------------
 * @Command : g++ -std=c++2a echo_server.cpp
 * -----------------------------------
 * @Author  : Wei Li
 * @Date    : 2021-11-03
*/

/** Understanding the Serial Echo server example
 * In this example, we will be creating a serial-based echo server. 
 * An echo server (regardless of the type) takes an input 
 * and echoes the input to the program's output
 * (similar to the first example, 
 * but in this case using a server-style application over a serial port).
 * 
 * To compile and use this example, two computers are needed, 
 * one that acts as the echo server 
 * and a second one that acts as the client, 
 * with both computers' serial ports connected to each other. 
 * On the echo server computer, use the following:
 * ./echo_server /dev/ttyS0
 * 
 * Note that your serial port device might be different. \
 * On the client computer, open two terminals. 
 * In the first terminal, run the following:
 * cat < /dev/S0
 * 
 * This code waits for the serial device to output data. 
 * In the second terminal, run:
 * echo "Hello World" > /dev/ttyS0
 * 
 */

#include <fstream>
#include <iostream>
// ------------------------------------------------
// sudo apt update
// sudo apt install libmsgsl-dev
#include <gsl/gsl>

using namespace gsl;
// ------------------------------------------------

void redirect_output(
    const std::ifstream &is,
    const std::ofstream &os,
    std::function<void()> f)
{
    auto cinrdbuf = std::cin.rdbuf();
    auto coutrdbuf = std::cout.rdbuf();

    std::cin.rdbuf(is.rdbuf());
    std::cout.rdbuf(os.rdbuf());

    f();

    std::cin.rdbuf(cinrdbuf);
    std::cout.rdbuf(coutrdbuf);
}

auto open_streams(cstring_span<> port)
{
    std::ifstream is(port.data());
    std::ofstream os(port.data());

    if (!is || !os)
    {
        std::clog << "ERROR: unable to open serial port:" << port.data() << '\n';
        ::exit(EXIT_FAILURE);
    }

    return std::make_pair(std::move(is), std::move(os));
}

int protected_main(int argc, char **argv)
{
    auto args = make_span(argv, argc);

    if (argc != 2)
    {
        std::clog << "ERROR: unsupported number of arguments\n";
        ::exit(EXIT_FAILURE);
    }

    auto [is, os] = open_streams(
        ensure_z(args.at(1)));

    redirect_output(is, os, []
                    {
                        std::string buf;

                        std::cin >> buf;
                        std::cout << buf << std::flush;
                    });

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