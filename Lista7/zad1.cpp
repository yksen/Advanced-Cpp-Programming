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
        std::vector<std::thread> threads;
        size_t tasksFinished;
        double sumOfResults{0};

        void add_task(std::function<double()> task)
        {
        }

        double average()
        {
            return sumOfResults / tasksFinished;
        }

        void stop()
        {
        }
    };
};

int main()
{
}