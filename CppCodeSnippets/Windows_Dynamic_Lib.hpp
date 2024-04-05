#ifndef __HEADER_HPP__
#define __HEADER_HPP__

#ifdef _WIN32
// Windows MSVC '__declspec' 特有的动态库装载方式
#    ifdef HEADER_API_EXPORT
#        define HEADER_API __declspec(dllexport) /* generate dynamic library */
#    else
#        define HEADER_API __declspec(dllimport) /* using dynamic library */
#    endif                                       // HEADER_API_EXPORT
#elif __linux__
#    define HEADER_API
#elif __APPLE__
#    define HEADER_API
#endif // _WIN32

#ifdef __cplusplus
extern "C"
{
#endif

/** 调用约定范式,
 * 在高级语言中，就是通过函数的调用方式来说明这两个问题的。常见的调用方式有： C
 * 语言： __cdecl、__stdcall、__fastcall、naked、__pascal。 C++ 语言：
 * __cdecl、__stdcall、__fastcall、naked、__pascal、__thiscall。
 */
HEADER_API int __stdcall addNumber(const int &integer_1, const int integer_2);

#ifdef __cplusplus
extern
}
#endif

// Windows OS export functions or symbols explicitly
extern "C" HEADER_API int __stdcall subNumber(const int &integer_1, const int &integer_2);
extern "C" HEADER_API int __stdcall divNumber(const int &integer_1, const int &integer_2);
extern "C" HEADER_API int __stdcall mulNumber(const int &integer_1, const int &integer_2);

// Windows OS export class symbols explicitly
class HEADER_API MathClass
{
public:
    MathClass()  = default;
    ~MathClass() = default;

public:
    int sub(int, int);
    // or only export the methods in class explicitly
    // HEADER_API int sub(int, int);
    int mul(int, int);

private:
    int num1;
    int num2;
};

#endif // !__HEADER_HPP__
