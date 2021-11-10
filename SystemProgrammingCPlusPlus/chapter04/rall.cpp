/**
 * @File    : rall.cpp
 * @Brief   : Resource Acquisition Is Initialization(RAII) design pattern
 * @Author  : Wei Li
 * @Date    : 2021-10-31
*/

#include <iostream>


// The simple concept can be leveraged to guard a resource
// RAII does not just apply to pointers; 
// it can be used for any resource that must be acquired and then released.
class myclass
{
public:
    myclass()
    {
        std::cout << "Hello from constructor" << std::endl;
    }
    ~myclass()
    {
        std::cout << "Hello from deconstructor" << std::endl;
    }
};

class myclassFile
{
private:
    FILE *m_file;

public:
    myclassFile(const char *filename) : m_file(fopen(filename, "rb"))
    {
        if (m_file == 0)
        {
            throw std::runtime_error("unable to open file");
        }
    }

    ~myclassFile()
    {
        fclose(m_file);
        std::clog << "Hello from destructor" << std::endl;
    }
};

class myclassResource
{
private:
    int *ptr;

public:
    myclassResource() : ptr{new int(42)} 
    {
        std::cout << "Apply for the Memory Resources of the Heap" << std::endl;
    }
    ~myclassResource()
    {
        std::cout << "Release Memory Resources in the Heap" << std::endl;
        delete ptr;
    }
};



int main(int argc, char** argv)
{
    myclass class_user1;
    std::cout << std::endl;
    myclassResource class_user2;
    std::cout << std::endl;

    myclassFile class_file("test.txt");
    try
    {
        myclassFile class_file2("does_not_exist.txt");
    }
    catch(const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << '\n';
    }
    
    return 0;
}
