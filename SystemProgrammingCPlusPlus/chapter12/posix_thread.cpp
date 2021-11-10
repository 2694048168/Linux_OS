/**
 * @File    : posix_thread.cpp
 * @Brief   : POSIX threads
 * -----------------------------
 * @Command : g++ -std=c++2a posix_thread.cpp -lpthread
 * -----------------------------
 * @Author  : Wei Li
 * @Date    : 2021-11-09
*/

/** Understanding POSIX threads
 * A thread is similar to a process, with the main distinctions being the following:
 * 1. Threads are contained within processes
 * 2. Threads inherently share a memory space with other threads of the same process,
 *    while processes do not share resources unless explicitly told to (using interprocess communication mechanisms)
 * 
 * Like processes, however, threads are scheduled for execution at any time by the operating system. 
 * This may mean executing in parallel with other threads, 
 * leading to performance optimizations if properly used, 
 * but at the expense of introducing threading-specific logic bugs, 
 * such as race conditions and deadlock.
 * 
 * The basics of POSIX threads
 * The most basic use of threads is to 'create', 'join', waits for threads to finish its work before returning.
 * 
 * -------------------- POSIX APIs for threads --------------------
 * int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
 * int pthread_join(pthread_t thread, void **value_ptr);
 * pthread_t pthread_self(void);
 * int pthread_yield(void);
 * 
 * bool predicate = false;
 * int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
 * int pthread_cond_signal(pthread_cond_t *cond);
 * ------------------------- man pages  ----------------------------
 * 
 * serveral issues:
 * 1. Type safety
 * 2. Race conditions
 * 3. No input/output
 * 
 * Threads are implemented differently depending on the operating system, 
 * and crossplatform software needs to take this into account.
 * 
 * the pthread_t type is usually implemented using an integer type
 * 
 * Yielding
 * One advantage to using threads is that they can execute for a very long time 
 * without preventing the execution of your main thread/application. 
 * The downside is that threads that execute without an end can end up consuming too much CPU.
 * 
 * Synchronization
 * Race conditions are a common problem when using threads, 
 * and solving race conditions without introducing deadlock
 *  (a thread that can no longer execute due to logic bugs with thread synchronization logic) 
 * 
 * A mutex leverages atomic operations 
 * (operations that are guaranteed by hardware to manipulate a shared resource without corruption) 
 * to gain access to a critical region, one thread at a time.
 * If a thread attempts to gain access to a critical region while another thread is actively using the region, 
 * it waits until the thread is complete. Once the thread is complete, all the waiting threads race to get access 
 * to the critical region, and the thread that wins gets access while the remaining threads continue to wait. 
 * (Each operating system has its own way of implementing this to prevent the possibility of starvation.)
 * 
 * The problem with mutexes is that each time the mutex is locked, 
 * a thread must wait until it is unlocked before it can continue. 
 * This is what protects the critical region from other threads, 
 * but it results in deadlock if the same thread attempts to lock the same mutex more than once 
 * (for example, when using recursion), or if mutexes are locked in the wrong order.
 * To overcome this problem, the POSIX API provides the ability to turn a mutex into a recursive mutex.
 * 
 * The last POSIX API we will discuss is the condition variable. 
 * As was demonstrated previously, a mutex may be used to synchronize access to critical regions of code. 
 * Another form of thread synchronization is to ensure threads execute in the proper order, 
 * which is what condition variables allow.
 * 
 */

#include <unistd.h>
#include <pthread.h>
#include <array>
#include <iostream>

// The basic of POSIX threads
// this functon pointer to thread create need
void *mythread(void *ptr)
{
    // std::cout << "Hello World\n";

    // To identify a thread
    std::cout << "thread ID: Hi, " << pthread_self() << '\n';
    return nullptr;
}

void *mythreadIO(void *ptr)
{
    (*reinterpret_cast<int *>(ptr))++;
    return ptr;
}

void *mythreadYielding(void *ptr)
{
    while (true)
    {
        std::clog << static_cast<char *>(ptr) << '\n';
        // pthread_yield() is not available on all Unix systems.
        pthread_yield();
    }
}

void *mythreadSleep(void *ptr)
{
    while (true)
    {
        sleep(1);
        std::cout << "hello world\n";
    }
}

// attempts to demonstrate the issues with potential race conditions
int count = 0;
void *mythreadRace(void *ptr)
{
    ++count;

    return nullptr;
}
// using mutex to solve race conditions
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
void *mythreadMutex(void *ptr)
{
    pthread_mutex_lock(&lock);
    ++count;
    pthread_mutex_unlock(&lock);

    return nullptr;
}

// recursive mutex to solve deadlock
int count = 0;
pthread_mutex_t lock;
pthread_mutexattr_t attr;
void *mythreadRecursiveMutex(void *ptr)
{
    pthread_mutex_lock(&lock);
    pthread_mutex_lock(&lock);
    pthread_mutex_lock(&lock);
    ++count;
    pthread_mutex_unlock(&lock);
    pthread_mutex_unlock(&lock);
    pthread_mutex_unlock(&lock);

    return nullptr;
}

// condition variables with order execute
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
void *mythread1(void *ptr)
{
    pthread_mutex_lock(&lock);
    std::cout << "Hello World: 1\n";
    pthread_mutex_unlock(&lock);

    return nullptr;
}
void *mythread2(void *ptr)
{
    pthread_mutex_lock(&lock);
    std::cout << "Hello World: 2\n";
    pthread_mutex_unlock(&lock);

    return nullptr;
}

// the POSIX API provides a condition variable that may be used to synchronize the order of threads, 
bool predicate = false;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
void *mythread_condition1(void *ptr)
{
    pthread_mutex_lock(&lock);
    std::cout << "Hello World: 1\n";
    predicate = true;
    pthread_mutex_unlock(&lock);
    pthread_cond_signal(&cond);

    return nullptr;
}
void *mythread_condition2(void *ptr)
{
    pthread_mutex_lock(&lock);
    while (!predicate)
    {
        pthread_cond_wait(&cond, &lock);
    }
    std::cout << "Hello World: 2\n";
    pthread_mutex_unlock(&lock);

    return nullptr;
}


int main(int argc, char** argv)
{
    // -------- The basic of POSIX threads
    pthread_t thread1;
    pthread_t thread2;
    // man 3 pthread_create
    pthread_create(&thread1, nullptr, mythread, nullptr);
    pthread_create(&thread2, nullptr, mythread, nullptr);
    // man 3 pthread_join
    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);

    int in_value = 42;
    void *out_value = nullptr;
    pthread_t threadIO1;
    pthread_t threadIO2;
    pthread_create(&threadIO1, nullptr, mythreadIO, &in_value);
    pthread_create(&threadIO2, nullptr, mythreadIO, &in_value);
    pthread_join(threadIO1, &out_value);
    pthread_join(threadIO2, &out_value);
    std::cout << "value: " << *reinterpret_cast<int *>(out_value) << '\n';

    // -------- Yielding very fast to run
    std::cout << "Yielding ----------------\n";
    char name1[9] = "thread 1";
    char name2[9] = "thread 2";
    pthread_t thread_yield1;
    pthread_t thread_yield2;
    pthread_create(&thread_yield1, nullptr, mythreadYielding, name1);
    pthread_create(&thread_yield2, nullptr, mythreadYielding, name2);
    pthread_join(thread_yield1, nullptr);
    pthread_join(thread_yield2, nullptr);

    pthread_t thread_sleep;
    pthread_create(&thread_sleep, nullptr, mythreadSleep, nullptr);
    pthread_join(thread_sleep, nullptr);

    // -------- Synchronization
    // attempts to demonstrate the issues with potential race conditions
    while (true)
    {
        count = 0;
        for (auto i = 0; i < 1000; i++)
        {
            std::array<pthread_t, 8> threads;

            for (auto &t : threads)
            {
                // using mutex to solve the race conditions
                pthread_create(&t, nullptr, mythreadMutex, nullptr);

                // pthread_create(&t, nullptr, mythreadRace, nullptr);
            }

            for (auto &t : threads)
            {
                pthread_join(t, nullptr);
            }
        }
        std::cout << "count: " << count << '\n';
    }

    // recursive mutex to solve deadlock
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&lock, &attr);

    pthread_t thread1;
    pthread_t thread2;
    pthread_create(&thread1, nullptr, mythreadRecursiveMutex, nullptr);
    pthread_create(&thread2, nullptr, mythreadRecursiveMutex, nullptr);
    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);

    std::cout << "count: " << count << '\n';

    // condition variables with order execute
    // the POSIX API provides a condition variable that may be used to synchronize the order of threads, 
    pthread_t thread1;
    pthread_t thread2;
    pthread_create(&thread2, nullptr, mythread_condition2, nullptr);
    pthread_create(&thread1, nullptr, mythread_condition1, nullptr);
    // pthread_create(&thread1, nullptr, mythread1, nullptr);
    // pthread_create(&thread1, nullptr, mythread1, nullptr);
    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);

    
    return 0;
}