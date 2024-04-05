#ifndef __cplusplus
#    error C++ is required
#elif __cplusplus > 199711
// C++11 (or newer) code goes here
#else
// old-school code goes here
#endif

/** # ISO Standard Values
 * C++98	#define __cplusplus   199711
 * C++11	#define __cplusplus   201103
 * C++14	#define __cplusplus   201402
 * C++17	#define __cplusplus   201703
 * C++20	#define __cplusplus   202002
 */
#ifdef __cplusplus
#    include <iostream>
#else
#    include <stdio.h>
#endif // __cplusplus

#ifdef __cplusplus
extern "C"
{
#endif

// C-style code

#ifdef __cplusplus
}
#endif

// ===============================
int main(int argc, char **argv)
{
#ifdef __cplusplus
    {
        std::cout << "Hello CPP World.\n";
    }
#else
    {
        printf("Hello CPP World.\n");
    }
#endif // __cplusplus

    return 0;
}
