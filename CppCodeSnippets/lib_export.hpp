#ifndef __LIB_EXPORT_HEAD_HPP__
#define __LIB_EXPORT_HEAD_HPP__
/**
 * @brief C/C++ header guard way
 * maybe can use '#pragma once' by main-stream compiler supported.
 * Consider using precompiled header files.
 */

/**
 * @file lib_export.hpp
 * @brief 简述该类接口的功能
 * @author Wei Li (Ithaca)
 * @date 2024-10-12
 * @version 0.1
 * @note C++ library API interface
 * @details C++ library API interface
 * @copyright Copyright (c) 2024
 * @example
 *
 * UML: Interface; Class; Struct; Module; Pipeline; Function;
 * draw.io ----> github repo
 * 
 * 
 */

/**
 * @brief Controlling Symbol Visibility (在C/C++中控制符号的可见性)
 * 在C语言中, 可以使用static关键字限制符号(函数或变量)只对当前的文件可见, 即 static 对符号的限制在单个文件级别;
 * 而共享库(动态库)可能包含一个或多个文件, 如何将符号限制在库文件(模块)的级别,
 * 大多数链接器(Linker)提供了将一个模块的所有符号进行隐藏(hidden)或导出(visible)的方法, 但这样对符号的控制会缺乏灵活性;
 * ----------------------------------------------------------------------------------
 * 序号      Windows                                    Linux/Mac/Unix
 * 文件后缀  .dll + .lib                                .so(static library .a)
 * 文件格式  PE                                         ELF
 * 问题本质  编译器默认 all symbols hidden               编译器默认 all symbols export
 * 使用方式  符号导入库.lib + .dll + interface.h/.hpp    .so + interface.h/.hpp
 * 控制符号  MSVC __declspec(dllexport/dllimport/deprecated)    GCC -fvisibility=hidden
 * ----------------------------------------------------------------------------------
 * 建议在一个比较大的共享库(动态库)中, 编译时使用 -fvisibility=hidden 选项默认隐藏全部符号,
 * 而在代码中使用 __attribute__((visibility("default"))) 有选择的显式指定要导出的符号,
 * 这样可以极大地减少符号冲突, 并且减少动态解析额外符号的成本.
 *
 */
// Step 1. 符号的导出
#ifdef _WIN32
#    ifdef LIB_NAME_API_EXPORT // 编译库的时候需要添加该预处理宏
#        define LIB_NAME_API __declspec(dllexport)
#    else
#        define LIB_NAME_API __declspec(dllimport)
#    endif
#elif __linux__
#    define LIB_NAME_API
#elif __APPLE__
#    define LIB_NAME_API
#endif

// Step 1. 符号的导出
#ifdef _WIN32
#    ifdef LIB_NAME_API
// #define LIB_NAME_API __declspec(dllexport) // 将该宏定义在.cpp中做预处理
#    else
#        define LIB_NAME_API __declspec(dllimport)
#    endif
#elif __linux__
#    define LIB_NAME_API
#elif __APPLE__
#    define LIB_NAME_API
#endif

/**
 * @brief 调用约定(Calling Convention)是计算机编程中一个比较底层的设计,它主要涉及:
 * 1. 函数参数通过寄存器传递还是栈?
 * 2. 函数参数从左到右还是从右到左压栈?
 * 3. 是否支持可变参数函数(vararg function or variadic function)?
 * 4. 是否需要函数原型?
 * 5. 怎么修饰函数名, 唯一标识函数?
 * 6. 调用者(caller)还是被调用者(called or callee)清理堆栈?
 *
 */
// Step 2. 调用约定 calling-conventions: __stdcall or __cdecl
#define CLAAING_CONVERTIONS __stdcall

#include <memory>
#include <string>
#include <string_view>

/**
 * @brief 函数名修饰
 * 在C语言中不存在重载, 因此不需要担心同名函数问题:
 * __cdecl ---> (编译后函数名改编为: "_函数名", 如_funcname)
 * __stdcall ---> (函数名改编: "_函数名@参数字节大小十进制", 如_funcname@8)
 * 但是在C++中, 使用C中的函数名修饰方式就存在问题;
 * 对于重载的函数, 仅仅凭函数名和参数内存大小无法完全区分, 类的成员函数表示并没有说明;
 * 所以在C++中, 对于函数名改编需要一套策略, 函数名格式大致如?FuncName@@YGXZ这种形式:
 * 1. 修饰名以?开始, 后面接函数名;
 * 2. 函数名后为@@YG、@@YA、@@YI, 分别代表__stdcall、__cdecl、__fastcall;
 * 3. @@YG等后面接着参数类型字符, 第一个表示返回值类型;
 * 4. 字符串以@Z结束, 如果函数没有参数, 则直接以Z结束;
 * 5. 命名空间的限制和修饰;
 * 其中参数符号如下:
 * ------------------------------------------
 * X ----> void
 * D ----> char
 * E ----> unsigned char
 * F ----> short
 * H ----> int
 * I ----> unsigned int
 * J ----> long
 * K ----> unsigned long
 * M ----> float
 * N ----> double
 * _N ----> bool
 * PA ----> 指针
 * PB ----> const指针
 * U ----> struct
 * ------------------------------------------
 * 所以在C++中函数名改编和C不同, 如果需要遵循C中的改编方式, 可以使用extern "C"{}.
 *
// https://www.cnblogs.com/tkorays/p/C_Cpp_Calling_Convention.html
 *
 * C++成员函数名修饰
 * 类的成员函数的调用方式为thiscall, 其函数名修饰方式和普通函数有些差别,
 * 成员函数名改编需在函数名和参数中间插入类名, 且需要指定函数一些性质, 如
 * 1. public为@@QAE, protected为@@IAE, private为@@AAE;
 * 2. 如果函数声明为const, 则public为@QBE; protected为@@IBE; private为@@ABE;
 * 3. 如果参数类型是类实例的引用, 则使用"AAV1", const引用则为"ABV1";
 *
 */
// Step 3. 是否兼容 C 风格
#ifdef __cplusplus
extern "C"
{
#endif

namespace ProjectName { namespace ModuleName {
class LIB_NAME_API RenderGraphicsImage
{
public:
    /**
                 * @brief 函数功能简述
                 *
                 * @param x 参数说明, 输入/输出参数, 表达含义, 是否有范围/限制等说明
                 * @param y
                 * @return void 返回值说明, 一般可能是 bool, 表示操作是否正常处理(error_no)
                 * @note
                 */
    virtual void AddLines(int x, int y)           = 0;
    virtual void AddRects(int x, int y)           = 0;
    virtual void AddCircles(int x, int y)         = 0;
    virtual void SetName(const std::string &name) = 0;
    virtual void SetName(std::string_view name)   = 0;
    virtual void SetImage(void *image)            = 0;
};

/**
             * @brief Create 'RenderGraphicsImage' Instance
             * The function createSaveRenderImage create instance to render graphics into image.
             * The supported graphics see in 'RenderGraphics.hpp'
             * @return std::shared_ptr<RenderGraphicsImage>
             */
LIB_NAME_API std::shared_ptr<RenderGraphicsImage> CLAAING_CONVERTIONS createRenderGraphicsImage();
}} // namespace ProjectName::ModuleName

#ifdef __cplusplus
}
#endif

// Step 4. 屏蔽具体的实现, 只提供抽象接口和公有的数据结构
// Step 5. 公有的数据结构最佳实现是单独的头文件, 并且最好不依赖第三库
// Step 6. 宏定义最佳实现是单独的头文件
// Step 7. 编程语言绑定, 常规的需要 C-sharp, Python, Java...

#endif /* __LIB_EXPORT_HEAD_HPP__ */
