/**
 * @File    : types.cpp
 * @Brief   : System types for C and C++
 * @Author  : Wei Li
 * @Date    : 2021-10-30
*/

#include <iostream>
#include <limits>

int main(int argc, char** argv)
{
    // ------------ Character types ------------
    // char type for American Standard Code for Information Interchange (ASCII)
    char c = 0x42;
    int i = 0x42;
    const char *str = "Hello World\n";
    std::cout << c << std::endl;
    std::cout << i << std::endl;
    std::cout << str << std::endl;
    std::cout << *str << std::endl;
    std::cout << std::endl;

    // std::numeric_limits{} class can provide real-time information about a type.
    auto num_bytes_signed = sizeof(signed char);
    auto min_signed = std::numeric_limits<signed char>().min();
    auto max_signed = std::numeric_limits<signed char>().max();
    auto num_bytes_unsigned = sizeof(unsigned char);
    auto min_unsigned = std::numeric_limits<unsigned char>().min();
    auto max_unsigned = std::numeric_limits<unsigned char>().max();
    std::cout << "num bytes (signed): " << num_bytes_signed << std::endl;
    std::cout << "min value (signed): " << static_cast<int>(min_signed) << std::endl;
    std::cout << "max value (signed): " << static_cast<int>(max_signed) << std::endl;
    // std::cout << "min value (signed): " << +min_signed << std::endl;
    // std::cout << "max value (signed): " << +max_signed << std::endl;
    std::cout << std::endl;
    std::cout << "num bytes (unsigned): " << num_bytes_unsigned << std::endl;
    std::cout << "min value (unsigned): " << static_cast<int>(min_unsigned) << std::endl;
    std::cout << "max value (unsigned): " << static_cast<int>(max_unsigned) << std::endl;

    std::cout << std::endl;
    // wide char type or wchar_t for Unicode characters
    // https://github.com/google/googletest/pull/2270
    // GCC 9 不支持 signed wchar_t and unsigned wchar_t，实现的标准有变化？
    auto num_bytes_signed_wide = sizeof(wchar_t);
    // auto num_bytes_signed_wide = sizeof(signed wchar_t);
    // auto num_bytes_unsigned_wide = sizeof(unsigned wchar_t);
    auto min_signed_wide = std::numeric_limits<wchar_t>().min();
    auto max_signed_wide = std::numeric_limits<wchar_t>().max();
    std::cout << "num bytes (signed): " << num_bytes_signed_wide << std::endl;
    std::cout << "min value (signed): " << min_signed_wide << std::endl;
    std::cout << "max value (signed): " << max_signed_wide << std::endl;

    std::cout << std::endl;
    // ------------ Integer types ------------
    auto num_bytes_signed_short = sizeof(signed short int);
    auto min_signed_short = std::numeric_limits<signed short int>().min();
    auto max_signed_short = std::numeric_limits<signed short int>().max();
    auto num_bytes_unsigned_short = sizeof(unsigned short int);
    auto min_unsigned_short = std::numeric_limits<unsigned short int>().min();
    auto max_unsigned_short = std::numeric_limits<unsigned short int>().max();
    std::cout << "num bytes (signed): " << num_bytes_signed_short << std::endl;
    std::cout << "min value (signed): " << min_signed_short << std::endl;
    std::cout << "max value (signed): " << max_signed_short << std::endl;
    std::cout << std::endl;
    std::cout << "num bytes (unsigned): " << num_bytes_unsigned_short << std::endl;
    std::cout << "min value (unsigned): " << min_unsigned_short << std::endl;
    std::cout << "max value (unsigned): " << max_unsigned_short << std::endl;

    std::cout << std::endl;
    short int s = 42;
    std::cout << s << std::endl;
    ++s;
    std::cout << s << std::endl;

    std::cout << std::endl;
    auto num_bytes_signed_int = sizeof(signed int);
    auto min_signed_int = std::numeric_limits<signed int>().min();
    auto max_signed_int = std::numeric_limits<signed int>().max();
    auto num_bytes_unsigned_int = sizeof(unsigned int);
    auto min_unsigned_int = std::numeric_limits<unsigned int>().min();
    auto max_unsigned_int = std::numeric_limits<unsigned int>().max();
    std::cout << "num bytes (signed): " << num_bytes_signed_int << std::endl;
    std::cout << "min value (signed): " << min_signed_int << std::endl;
    std::cout << "max value (signed): " << max_signed_int << std::endl;
    std::cout << std::endl;
    std::cout << "num bytes (unsigned): " << num_bytes_unsigned_int << std::endl;
    std::cout << "min value (unsigned): " << min_unsigned_int << std::endl;
    std::cout << "max value (unsigned): " << max_unsigned_int << std::endl;

    std::cout << std::endl;
    auto num_bytes_signed_long = sizeof(signed long int);
    auto min_signed_long = std::numeric_limits<signed long int>().min();
    auto max_signed_long = std::numeric_limits<signed long int>().max();
    auto num_bytes_unsigned_long = sizeof(unsigned long int);
    auto min_unsigned_long = std::numeric_limits<unsigned long int>().min();
    auto max_unsigned_long = std::numeric_limits<unsigned long int>().max();
    std::cout << "num bytes (signed): " << num_bytes_signed_long << std::endl;
    std::cout << "min value (signed): " << min_signed_long << std::endl;
    std::cout << "max value (signed): " << max_signed_long << std::endl;
    std::cout << std::endl;
    std::cout << "num bytes (unsigned): " << num_bytes_unsigned_long << std::endl;
    std::cout << "min value (unsigned): " << min_unsigned_long << std::endl;
    std::cout << "max value (unsigned): " << max_unsigned_long << std::endl;

    std::cout << std::endl;
    // ------------ Floating-point numbers ------------
    auto num_bytes_float = sizeof(float);
    auto min_float = std::numeric_limits<float>().min();
    auto max_float = std::numeric_limits<float>().max();
    std::cout << "num bytes : " << num_bytes_float << std::endl;
    std::cout << "min value : " << min_float << std::endl;
    std::cout << "max value : " << max_float << std::endl;

    auto num_bytes_double = sizeof(double);
    auto min_double = std::numeric_limits<double>().min();
    auto max_double = std::numeric_limits<double>().max();
    std::cout << "num bytes : " << num_bytes_double << std::endl;
    std::cout << "min value : " << min_double << std::endl;
    std::cout << "max value : " << max_double << std::endl;

    auto num_bytes_long_double = sizeof(long double);
    auto min_long_double = std::numeric_limits<long double>().min();
    auto max_long_double = std::numeric_limits<long double>().max();
    std::cout << "num bytes : " << num_bytes_long_double << std::endl;
    std::cout << "min value : " << min_long_double << std::endl;
    std::cout << "max value : " << max_long_double << std::endl;

    std::cout << std::endl;
    // ------------ Boolean ------------
    auto num_bytes_bool = sizeof(bool);
    auto min_bool = std::numeric_limits<bool>().min();
    auto max_bool = std::numeric_limits<bool>().max();
    std::cout << "num bytes : " << num_bytes_bool << std::endl;
    std::cout << "min value : " << min_bool << std::endl;
    std::cout << "max value : " << max_bool << std::endl;

    return 0;
}