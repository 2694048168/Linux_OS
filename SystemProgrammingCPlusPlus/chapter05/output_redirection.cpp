/**
 * @File    : output_redirection.cpp
 * @Brief   : Output redirection to shell
 * @Author  : Wei Li
 * @Date    : 2021-11-02
*/

#include <unistd.h>
#include <string>
#include <sys/wait.h>
#include <array>
#include <string_view>
#include <iostream>

class mypipe
{
private:
    std::array<int, 2> m_handles;

public:
    mypipe()
    {
        if (pipe(m_handles.data()) < 0)
        {
            exit(1);
        }
    }

    ~mypipe()
    {
        close(m_handles.at(0));
        close(m_handles.at(1));
    }

    std::string read()
    {
        std::array<char, 256> buf;
        std::size_t bytes = ::read(m_handles.at(0), buf.data(), buf.size());

        if (bytes > 0)
        {
            return {buf.data(), bytes};
        }

        return {};
    }

    void redirect()
    {
        // man 2 dup2
        // redirect the output of STDOUT to Unix pipe
        dup2(m_handles.at(1), STDOUT_FILENO);
        close(m_handles.at(0));
        close(m_handles.at(1));
    }
};

int main(int argc, char **argv)
{
    mypipe p;

    if (fork() == 0)
    {
        p.redirect();
        execlp("ls", "ls", nullptr);
    }
    else
    {
        wait(nullptr);
        std::cout << p.read() << std::endl;
    }

    return 0;
}
