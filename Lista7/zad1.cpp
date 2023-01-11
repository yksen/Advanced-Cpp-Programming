#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

namespace cpplab
{
    class ThreadPool
    {
        std::vector<std::function<double()>> tasks;

        void add_task(std::function<double()> task)
        {
        }

        double average()
        {
        }

        void stop()
        {
        }
    };
};

int main()
{
}