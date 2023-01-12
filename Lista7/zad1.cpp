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
    public:
        std::vector<std::thread> threads;
        size_t tasksFinished{0};
        double sumOfResults{0};

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
        }

        double average()
        {
            return sumOfResults / tasksFinished;
        }

    private:
        void start(size_t threadCount)
        {
            for (size_t i = 0; i < threadCount; ++i)
                threads.emplace_back(std::thread());
        }

        void stop()
        {
        }
    };
};

int main()
{
    cpplab::ThreadPool pool(10);
}