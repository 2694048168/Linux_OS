/**
 * @file location.cpp
 * @author Wei Li (weili_yzzcq@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <source_location>
#include <string>

void location_log(const std::string message);

void location_log(const char *message)
{
    // Since C++ 20 compile flags to add --std=c++20
    // https://en.cppreference.com/w/cpp/utility/source_location
    auto location = std::source_location::current();

    std::cout << "info: " << location.file_name() << ":" << location.line() << " " << location.function_name() << " "
              << message << '\n';
}

// macro definition way before C++20
#define LOCATION_LOG(message) location_log(message, __FILE__, __LINE__)

void location_log(const std::string message, const std::string filename, int line_num);

void location_log(const char *message, const char *filename, int line_num)
{
    std::cout << "info: " << filename << ":" << line_num << " " << message << '\n';
}

// ====================================
int main(int argc, const char **argv)
{
    LOCATION_LOG("error");

    return 0;
}