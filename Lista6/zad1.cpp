#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

void dot_product(std::vector<double> lhs, std::vector<double> rhs, std::promise<double> product_promise)
{   
    try
    {
        if (lhs.size() == 0 || rhs.size() == 0)
            throw std::logic_error("Dot product arguments can not be of length zero.");
        if (lhs.size() != rhs.size())
            throw std::logic_error("Dot product arguments can not be different sizes.");
        product_promise.set_value(std::inner_product(lhs.begin(), lhs.end(), rhs.begin(), 0));
    }
    catch(const std::exception& e)
    {
        product_promise.set_exception(std::current_exception());
    }
    
}

int main()
{
    const size_t THREAD_COUNT = 10;

    std::vector<double> a{1, 2, 3}, b{4, 5, 6};

    std::vector<std::promise<double>> promises;
    std::vector<std::future<double>> futures;
    std::vector<std::thread> threads;

    for (size_t i = 0; i < THREAD_COUNT; ++i)
    {
        promises.push_back(std::promise<double>());
        futures.push_back(promises.back().get_future());
        threads.push_back(std::thread(dot_product, a, b, std::move(promises.back())));
        if (i == THREAD_COUNT - 3)
            b.push_back(7);
        if (i == THREAD_COUNT - 2)
            a.clear();
    }

    double sum_of_products = 0;
    for (size_t i = 0; i < THREAD_COUNT; ++i)
    {
        try
        {
            sum_of_products += futures[i].get();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        threads[i].join();
    }
    std::cout << sum_of_products << std::endl;
}