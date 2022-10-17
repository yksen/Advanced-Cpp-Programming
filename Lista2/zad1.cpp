#include <cstring>
#include <iostream>

namespace cpplab
{
    template <typename T, typename U>
    auto add(T a, U b) -> decltype(a + b)
    {
        return a + b;
    }

    template <typename T, typename U>
    auto add(T *a, U *b) -> decltype(*a + *b)
    {
        return *a + *b;
    }

}

int main()
{
    int a = 2, b = 5;

    std::cout << cpplab::add(&a, &b) << std::endl;

    return 0;
}