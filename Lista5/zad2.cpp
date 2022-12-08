#include <future>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

static size_t i = 0;

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
        std::cout << "Thread #" << std::to_string(generateThreadId()) << " | " << text << std::endl;
    }

    void get_async(std::launch launch_policy)
    {
        while (i < 3)
        {
            ++i;
            auto f1 = std::async(launch_policy, get_async, launch_policy);
            print("Hello x" + std::to_string(i));
            f1.get();
        }
    }
}

int main()
{
    cpplab::get_async(std::launch::async);
    i = 0;
    cpplab::get_async(std::launch::deferred);

    return 0;
}