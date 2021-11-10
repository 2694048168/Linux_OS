/**
 * @File    : modern_cpp.cpp
 * @Brief   : Resource Acquisition Is Initialization(RAII) design pattern
 * ----------------------------------
 * @Command : g++ -std=c++2a rall.cpp -o rall.out; 指定生成文件名 -o 选项
 * @Command : g++ -std=c++2a -E rall.cpp -o rall.i; 预处理 -E 选项，生成 .i 文件
 * @Command : g++ -std=c++2a -S rall.i -o rall.s; 汇编 -S 选项，生成 .s 汇编代码文件
 * @Command : g++ -std=c++2a -c rall.s -o rall.o; 编译 -c 选项，生成 .o 二进制的目标文件
 * @Command : g++ -std=c++2a rall.o -L libc.so -o rall.out; 链接 -L 选项，链接为可执行的二进制的文件
 * ----------------------------------
 * @Author  : Wei Li
 * @Date    : 2021-10-31
*/

#include <utility>
#include <string_view>
#include <any>
#include <variant>
#include <optional>
#include <iostream>


class myclass
{
public:
    int val;
    myclass(int v) : val(v)
    {
        std::cout << "Constructed" << std::endl;
    }
};

// Structured bindings in C++17 only
std::pair<const char *, int>
give_me_a_pair()
{
    return {"The answer is: ", 42};
}

struct mystruct
{
    const char *msg;
    int answer;
};
mystruct give_me_a_struct()
{
    return {"The answer is: ", 42};
}

// Inline variable
// This type of variable can be defined in a header file 
// and included several times without multiple definitions being defined during linking. 
// as the header both defines the variable and exposes the symbol to all of the source files that need it, removing the ambiguity
// extern const char *inline_msg
inline auto inline_msg = "Hello World\n";

// compile-time to extend
constexpr const auto val = true;

// nested namespaces
namespace X
{
    namespace Y
    {
        namespace Z
        {
            auto msg = "Hello World for namespace";
        }
    }
    
} // namespace X
// C++17
namespace x::y::z
{
    auto msg = "Hello World for nested namespace";
}

struct mystructAny
{
    int data;
};



int main(int argc, char** argv)
{

    // ---------------- C++17 ---------------- 
    // Initializers in if/switch statements
    if (auto i = 42; i > 0)
    {
        std::cout << "Hello World for Init with if statement" << std::endl;
    }

    switch (auto i = 42)
    {
    case 42:
        std::cout << "Hello World for Init with switch statement" << std::endl;
        break;
    
    default:
        break;
    }

    // Additions to compile-time facilities
    // 查看汇编代码发现，编译器对判断分支这条语句进行了优化，直接移除了
    if (val)
    {
        std::cout << "Hello World for constexpr statement" << std::endl;
    }

    // To prevent this type of error, C++17 adds a constexpr if statement, 
    // which tells the compiler to specifically optimize the branch at compile time.
    if constexpr (constexpr const auto i = 42; i > 0)
    {
        std::cout << "Hello World for constexpr if statement" << std::endl;
    }

    // static_assert in compile-time
    static_assert(42 == 42, "The answer");
    static_assert(42 == 42);

    // Namespaces and nested namespaces in C++17
    std::cout << X::Y::Z::msg << std::endl;
    std::cout << x::y::z::msg << std::endl;

    auto ptr = give_me_a_pair();
    std::cout << std::get<0>(ptr) << std::get<1>(ptr) << std::endl;
    // Structured bindings in C++17
    auto [msg, answer] = give_me_a_pair();
    std::cout << msg << answer << std::endl;
    auto [msg_struct, answer_struct] = give_me_a_struct();
    std::cout << msg << answer << std::endl;

    // inline variables
    std::cout << inline_msg << std::endl;

    // std::string_view class is a wrapper around a character array, 
    // that helps to make working with basci C strings safer and easier,
    // provides accessors to the underlying array.
    std::string_view str_c("Hello World for c-string");
    std::cout << str_c << std::endl;
    std::cout << str_c.front() << std::endl;
    std::cout << str_c.back() << std::endl;
    std::cout << str_c.at(1) << std::endl;
    // std::cout << str_c.at(100) << std::endl;
    std::cout << str_c.data() << std::endl;
    std::cout << str_c.size() << std::endl;
    std::cout << str_c.max_size() << std::endl;
    std::cout << str_c.empty() << std::endl;
    // remove characters from the front or back of the std::string_view string without reallocate memory.
    str_c.remove_prefix(1);
    str_c.remove_suffix(1);
    std::cout << str_c << std::endl;
    // access substrings
    std::cout << str_c.substr(0, 5) << std::endl;
    // compare strings
    std::string_view str_compare("Hello World");
    if (str_compare.compare("Hello World") == 0)
    {
        std::cout << "Hello World for compare strings" << std::endl;
    }
    std::cout << str_compare.compare("Hello") << std::endl;
    std::cout << str_compare.compare("World") << std::endl;

    // search functions for C-style string
    std::string_view str_search("Hello this is a test of Hello World");
    std::cout << str_search.find("Hello") << std::endl;
    std::cout << str_search.rfind("Hello") << std::endl;
    std::cout << str_search.find_first_of("Hello") << std::endl;
    std::cout << str_search.find_last_of("Hello") << std::endl;
    std::cout << str_search.find_first_not_of("Hello") << std::endl;
    std::cout << str_search.find_last_not_of("Hello") << std::endl;
    std::cout << std::endl;

    // std::any{} class
    auto myany = std::make_any<int>(42);
    std::cout << std::any_cast<int>(myany) << std::endl;
    myany = 4.2;
    std::cout << std::any_cast<double>(myany) << std::endl;
    myany = mystructAny{42};
    std::cout << std::any_cast<mystructAny>(myany).data << std::endl;

    // std::ariant{} class
    std::variant<int, double> v = 42;
    std::cout << std::get<int>(v) << std::endl;
    v = 4.2;
    std::cout << std::get<double>(v) << std::endl;

    // std::optional{} class
    std::optional<myclass> opt;
    std::cout << "Created, but not constructed" << std::endl;
    if (opt)
    {
        std::cout << "Attempt #1: " << opt->val << std::endl;
    }

    opt = myclass{42};
    if (opt)
    {
        std::cout << "Attempt #2: " << opt->val << std::endl;
    }
    
    return 0;
}
