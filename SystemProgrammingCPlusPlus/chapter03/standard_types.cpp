/**
 * @File    : standard_types.cpp
 * @Brief   : Standard integer types
 * @Author  : Wei Li
 * @Date    : 2021-10-30
*/

#include <typeinfo>
#include <cxxabi.h>
#include <string>
#include <cstdint>
#include <cstdlib>
#include <iostream>

template <typename T>
std::string type_name()
{
    int status;
    std::string name = typeid(T).name();

    auto demangled_name = abi::__cxa_demangle(name.c_str(), nullptr, nullptr, &status);

    if (status == 0)
    {
        name = demangled_name;
        std::free(demangled_name);
    }
    
    return name;
}

template <typename T1, typename T2>
void are_equal()
{
    #define red "\033[1;31m"
    #define reset "\033[0m"

    std::cout << type_name<T1>() << " VS " << type_name<T2>() << std::endl;

    if (sizeof(T1) == sizeof(T2))
    {
        std::cout << " - size: both == " << sizeof(T1) << std::endl;
    }
    else
    {
        std::cout << red " - size: " << sizeof(T1) << " != " << sizeof(T2) << reset << std::endl;
    }

    if (type_name<T1>() == type_name<T2>())
    {
        std::cout << " - name: both == " << type_name<T1>() << std::endl;
    }
    else
    {
        std::cout << red " - name: " << type_name<T1>() << " != " << type_name<T2>() << reset << std::endl;
    }
}

struct mystructSame
{
    uint64_t data1;
    uint64_t data2;
};

struct mystruct16
{
    uint16_t data1;
    uint16_t data2;
};

struct mystructBit
{
    uint16_t data1 : 2, data2 : 14;
    uint64_t data3;
};

struct mystruct
{
    uint64_t data1;
    uint16_t data2;

    // The order in which we specify our integers also does not matter.
    // uint16_t data2;
    // uint64_t data1;
};

/**To fix this issue, we wrap the structure with the #pragma pack and #pragma pop macros. 
 * These macros tell the compiler (since we passed a 1 to the macro, 
 * which indicates a byte) to pack the structure using a byte granularity, 
 * telling the compiler it is not allowed to make a substitution optimization.
 */
#pragma pack(push, 1)
struct mystructPack
{
    uint64_t data1;
    uint16_t data2;

    // uint16_t data2;
    // uint64_t data1;
};
#pragma pack(pop)

// The address is byte aligned, not cache aligned.
//  leverage the alignas() function
#pragma pack(push, 1)
struct alignas(16) mystructAligned
{
    uint16_t data1;
    uint64_t data2;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct mystructPointer
{
    uint16_t *data1;
    uint64_t data2;
};
#pragma pack(pop)


int main(int argc, char** argv)
{
    // -------- Default Types in C++ vssus Standard Types by Compiler --------

    are_equal<uint8_t, int8_t>();
    are_equal<uint8_t, uint32_t>();

    are_equal<signed char, int8_t>();
    are_equal<unsigned char, uint8_t>();

    are_equal<signed short int, int16_t>();
    are_equal<unsigned short int, uint16_t>();
    are_equal<signed int, uint32_t>();
    are_equal<unsigned int, uint32_t>();
    are_equal<signed long int, int64_t>();
    are_equal<unsigned long int, uint64_t>();
    are_equal<signed long long int, int64_t>();
    are_equal<unsigned long long int, uint64_t>();
    
    // -------- Standard integers provide a compiler-supported method for dictating the size of an integer type at compile  time. They map bit widths to default types so that the coder does not have to do this manually. However, do not always guarantee the width of a type, and structures are a good example of this. --------
    std::cout << std::endl;
    std::cout << "Size: " << sizeof(mystructSame) << std::endl;
    std::cout << "Size: " << sizeof(mystruct) << std::endl;

    // -------- alignment issue; imporve memory caching; porperly aligned in memory --------
    /**科幻小说《银河系漫游指南》，英国作家 道格拉斯·亚当斯 所著系列科幻小说。
     * 小说中一个超高级文明生物制造了一台名叫 “深思” 的超高级计算机器，想用它来回答宇宙的终极问题，
     * 经过数百万年的计算和整理这台超级计算机给出的答案就是 “42”
     * 宇宙万物终极问题的答案是 42, 认为 42 这个数字隐藏了宇宙秘密
     */
    int16_t secrets_universe = 42;
    auto result_compiler = secrets_universe + 42;
    int16_t result = secrets_universe + 24;
    std::cout << "Size: " << sizeof(result) << std::endl;
    std::cout << "Size: " << sizeof(result_compiler) << std::endl;

    // All of these issues are a consequence of the compiler's ability to perform type conversions
    // from a smaller width type to a higher width type in order to optimize performance 
    // to reduce the possibility of overflows. 
    // This type of conversion is not always guaranteed.
    std::cout << "Size: " << sizeof(mystruct16) << std::endl;

    // Bit fields also do not change the compiler's ability to perform this type of conversion.
    std::cout << "Size: " << sizeof(mystructBit) << std::endl;

    // The way to overcome this problem is to pack the structure.
    std::cout << "Size:" << sizeof(mystructPack) << std::endl;

    // To explain why packed structures and bit fields should be avoided, 
    // let's look at an alignment issue with the following example:
    mystructPack s;
    std::cout << "Addr: " << &s << std::endl;
    // The address is byte aligned, not cache aligned.
    mystructAligned stru;
    std::cout << "Size:" << sizeof(mystructAligned) << std::endl;
    std::cout << "Addr: " << &stru << std::endl;
    std::cout << "Addr data1: " << &stru.data1 << std::endl;
    std::cout << "Addr data2: " << &stru.data2 << std::endl;

    std::cout << "Size: " << sizeof(mystructPointer) << std::endl;
    // Attempting to pass this structure to the kernel world result in a bug,
    // as the application and kernel world see the structure differently.
    
    return 0;
}
