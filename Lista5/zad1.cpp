#include <iostream>
#include <mutex>
#include <string>
#include <thread>

size_t generateThreadId()
{
    static std::mutex mutex;
    const std::lock_guard<std::mutex> lock(mutex);
    static size_t id = 0;
    thread_local size_t thread_id = id++;
    return thread_id;
}

namespace cpplab
{
    void print(std::string text)
    {
        static std::mutex mutex;
        const std::lock_guard<std::mutex> lock(mutex);
        std::cout << "Thread #" << generateThreadId() << " | " << text << std::endl;
    }
}

int main()
{
    auto callable = []
    { cpplab::print("Hello world!"); };

    const size_t THREADS_COUNT = 10;
    std::thread threads[THREADS_COUNT];

    for (size_t i = 0; i < THREADS_COUNT; ++i)
        threads[i] = std::thread(callable);
    
    for (size_t i = 0; i < THREADS_COUNT; ++i)
        threads[i].join();

    return 0;
}