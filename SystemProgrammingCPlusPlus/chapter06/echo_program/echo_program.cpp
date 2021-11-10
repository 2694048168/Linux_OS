/**
 * @File    : echo_program.cpp
 * @Brief   : Recreating the echo program
 * -----------------------------------
 * @Command : g++ -std=c++2a echo_program.cpp -o a.out
 * -----------------------------------
 * @Author  : Wei Li
 * @Date    : 2021-11-03
*/

/** Recreating the echo program
 * In this hands-on example, we will be recreating the popular echo program found on almost all POSIX systems.
 * The echo program takes all of the input provided to the program and echoes it back to stdout. 
 * This program is very simple, with the following program options:
 *   -n: Prevents echo from outputting a newline on exit
 *   --help: Prints the Help menu
 *   --version: Prints some version information
 * 
 * There are two other options, -e and -E; 
 * we have omitted them here to keep things simple,
 * but, if desired, would serve as a unique exercise for the reader.
 * 
 * The main function presented here is a useful pattern to add to all programs 
 * and deviates slightly from the original echo program as exceptions 
 * (which are highly unlikely in this example) could generate error messages not seen in the original echo program.
 */

#include <iostream>

// ------------------------------------------------
// sudo apt update
// sudo apt install libmsgsl-dev
#include <gsl/gsl>

using namespace gsl;
// ------------------------------------------------

/** --help to user
 * If --help was provided by the user,
 * the handle_help() function would be executed as follows
 */
void handle_help()
{
    std::cout << "Usage: echo [SHORT-OPTION]... [STRING]...\n"
              << " or: echo LONG-OPTION\n"
              << "Echo the STRING(s) to standard output.\n"
              << "\n"
              << " -n do not output the trailing newline\n"
              << " --help display this help and exit\n"
              << " --version output version information and exit \n"
              << '\n';

    ::exit(EXIT_SUCCESS);
}

/** --version to user
 * If --version was provided by the user,
 * the handle_version() function would be executed as follows
 */
void handle_version()
{
    std::cout << "echo (example) 1.0\n"
              << "Copyright (C) Wei Li\n"
              << "\n";

    ::exit(EXIT_SUCCESS);
}

/** The goal of the protected_main() function is 
 *  to parse the arguments provided to the program, 
 *  and handle each argument as expected:
 */
int protected_main(int argc, char **argv)
{
    auto endl = true;
    auto args = make_span(argv, argc);

    // The first argument in the argument list is
    // always the program name
    for (int i = 1, num = 0; i < argc; i++)
    {
        // ensures that the string is complete,
        // preventing possible unwanted corruption
        cstring_span<> span_arg = ensure_z(args.at(i));

        if (span_arg == "-n")
        {
            endl = false;
            continue;
        }

        if (span_arg == "--help")
        {
            handle_help();
        }

        if (span_arg == "--version")
        {
            handle_version();
        }

        // some additional logic is needed to ensure that a space is outputted to stdout as needed.
        if (num++ > 0)
        {
            std::cout << " ";
        }

        std::cout << span_arg.data();
    }

    if (endl)
    {
        std::cout << '\n';
    }

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
        std::cerr << "Caught unhandled exception: \n";
        std::cerr << "- What(): " << e.what() << '\n';
    }
    catch (...)
    {
        std::cerr << "Caught unknown exception\n";
    }

    return EXIT_FAILURE;
}
