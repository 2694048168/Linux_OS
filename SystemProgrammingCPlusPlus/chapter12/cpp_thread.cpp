/**
 * @File    : cpp_thread.cpp
 * @Brief   : Exploring C++ threads 
 * ---------------------------------
 * @Command : g++ -std=c++2a cpp_thread.cpp -lpthread
 * ---------------------------------
 * @Author  : Wei Li
 * @Date    : 2021-11-10
*/

/** C++ threads
 * how POSIX provides support for threads. 
 * Discuss C++ threads, which are largely inspired by POSIX threads. 
 * They provide similar functionality while simplifying the APIs in some ways, and also providing type safety.
 * 
 * The basic of C++ threads
 * under the hood, C++ is using pthread instances to provide thread support, so the 'pthread' library still needs to be linked.
 * 
 * Yielding
 * Similar to POSIX threads, C++ threads provide the ability to yield a thread, 
 * relinquishing the CPU so that other threads that need to perform their tasks may do so.
 * 
 * Synchronization
 * Another notable difference between POSIX threads and C++ threads is the simplicity of thread synchronization. 
 * Like the POSIX APIs, C++ provides the ability to create a mutex.
 * 
 */

#include <thread>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <chrono>
#include <future>
#include <iostream>

// ----Step 1. The basic of C++ threads
void mythread()
{
    std::cout << "Hello World\n";
    // C++ to get thread ID like POSIX
    std::cout << "thread ID: " << std::this_thread::get_id() << '\n';
}

// Input/Output and type safety, C++ provides a concept called C++ futures
int mythreadIO(int value)
{
    return ++value;
}

// ----Step 2. Yielding
void mythreadYield(const char *str)
{
    while (true)
    {
        std::clog << str << '\n';
        std::this_thread::yield();
    }
}

// C++ provides the ability to sleep the currently executing thread.
using namespace std::chrono_literals;
void mythreadSleep()
{
    while (true)
    {
        std::this_thread::sleep_for(1s);
        std::cout << "Hello world\n";
    }
}

// ----Step 3. Synchronization
int count = 0;
std::mutex mutex;
void mythreadMutex()
{
    mutex.lock();
    ++count;
    mutex.unlock();
}

// solution to issue
int count = 0;
std::mutex mutex;
void mythread()
{
    std::lock_guard lock(mutex);

    if (count == 1)
    {
        return;
    }

    count++;
}

// solution to issue
int count = 0;
std::mutex mutex;
void mythread()
{
    while (!mutex.try_lock())
        ;
    count++;
    mutex.unlock();
}

// solution to issue
int count = 0;
std::mutex mutex;
using namespace std::chrono_literals;
void mythread()
{
    std::unique_lock lock(mutex, std::defer_lock);

    while (!lock.try_lock())
    {
        std::this_thread::sleep_for(1s);
    }

    count++;
}

// solution to issue
int count = 0;
std::recursive_mutex mutex;
void mythread()
{
    std::lock_guard lock1(mutex);
    std::lock_guard lock2(mutex);
    count++;
}

// solution to issue
int count = 0;
std::mutex mutex;
void mythread()
{
    std::lock_guard lock(mutex);
    count++;
}

// solution to issue
int count = 0;
std::mutex mutex1;
std::mutex mutex2;
void mythread()
{
    std::scoped_lock lock(mutex1, mutex2);
    count++;
}

// solution to issue
int count = 0;
std::shared_mutex mutex;
void mythread1()
{
    while (true)
    {
        std::unique_lock lock(mutex);
        count++;
    }
}
void mythread2()
{
    while (true)
    {
        std::shared_lock lock(mutex);
        std::cout << "count: " << count << '\n';
    }
}

// solution to issue
int count = 0;
std::mutex mutex1;
std::mutex mutex2;
void mythread()
{
    std::unique_lock lock1(mutex1, std::defer_lock);
    std::unique_lock lock2(mutex2, std::defer_lock);

    std::lock(lock1, lock2);

    count++;
}

// solution to issue
std::mutex mutex;
std::condition_variable cond;
void mythread1()
{
    std::cout << "Hello World: 1\n";
    cond.notify_one();
}
void mythread2()
{
    std::unique_lock lock(mutex);
    cond.wait(lock);
    std::cout << "Hello World: 2\n";
}

// solution to issue
std::mutex mutex;
std::condition_variable cond;
void mythread1()
{
    std::cout << "Hello World: 1\n";
    cond.notify_all();
}
void mythread2()
{
    std::unique_lock lock(mutex);
    cond.wait(lock);
    std::cout << "Hello World: 2\n";
    cond.notify_one();
}

// solution to issue
std::shared_mutex mutex;
std::condition_variable_any cond;
void mythread1()
{
    std::cout << "Hello World: 1\n";
    cond.notify_all();
}
void mythread2()
{
    std::shared_lock lock(mutex);
    cond.wait(lock);
    std::cout << "Hello World: 2\n";
}

// solution to issue
std::once_flag flag;
void mythread()
{
    std::call_once(flag, []
                   { std::cout << "Hello World\n"; });
}

int main(int argc, char **argv)
{
    // ----Step 1. The basic of C++ threads
    std::cout << "--------- Step 1 --------------\n";
    std::thread basic_thread1{mythread};
    std::thread basic_thread2{mythread};
    basic_thread1.join();
    basic_thread2.join();

    // Input/Output and type safety, C++ provides a concept called C++ futures
    std::packaged_task<int(int)> task1(mythreadIO);
    std::packaged_task<int(int)> task2(mythreadIO);
    auto f1 = task1.get_future();
    auto f2 = task2.get_future();
    std::thread t1(std::move(task1), 42);
    std::thread t2(std::move(task2), 42);
    t1.join();
    t2.join();
    std::cout << "value1: " << f1.get() << '\n';
    std::cout << "value2: " << f2.get() << '\n';

    // ----Step 2. Yielding
    std::thread thread_yield1{mythreadYield, "thread 1"};
    std::thread thread_yield2{mythreadYield, "thread 2"};
    thread_yield1.join();
    thread_yield2.join();
    // Similar to sleep() in POSIX,
    // C++ provides the ability to sleep the currently executing thread.
    std::thread thread_sleep{mythreadSleep};
    thread_sleep.join();

    // ----Step 2. Synchronization
    std::thread thread_mutex1{mythreadMutex};
    std::thread thread_mutex2{mythreadMutex};
    thread_mutex1.join();
    thread_mutex2.join();
    std::cout << "count: " << count << '\n';

    // solution to issue

    return 0;
}