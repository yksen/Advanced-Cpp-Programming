#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <thread>
#include <queue>
#include <vector>

namespace cpplab
{
    class ThreadPool
    {
    public:
        ThreadPool(size_t threadCount)
        {
            start(threadCount);
        }

        ~ThreadPool()
        {
            stop();
        }

        void add_task(std::function<double()> task)
        {
            {
                std::unique_lock<std::mutex> lock(mutex);
                tasks.emplace(task);
            }
        }

        double average()
        {
            return (tasksFinished == 0) ? 0 : sumOfResults / static_cast<double>(tasksFinished);
        }

    private:
        void start(size_t threadCount)
        {
            for (size_t i = 0; i < threadCount; ++i)
                threads.emplace_back(std::thread());
        }

    private:
        std::vector<std::thread> threads;
        std::queue<std::function<double()>> tasks;
        std::mutex mutex;
        std::condition_variable condition;
        size_t tasksFinished{0};
        double sumOfResults{0};
        bool stopProcessing{false};
    };
};

int main()
{
    cpplab::ThreadPool pool(10);
}