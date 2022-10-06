#include <cstring>
#include <iostream>

namespace cpplab
{
    template <typename T, typename U>
    auto add(T a, U b) -> decltype(a + b)
    {
        return a + b;
    }

    template <typename T, typename U, typename V>
    auto alias(T a, U b, V c) -> decltype(c(a, b))
    {
        return c(a, b);
    }
}

int main()
{
    std::cout << cpplab::add(5, 3.14f) << "\n";
    std::cout << cpplab::add<std::string, std::string>("hello", "world") << "\n";

    std::cout << cpplab::alias(5, 4, cpplab::add<int, int>) << "\n";
    std::cout << cpplab::alias(12.4f, 7.7f, [](auto a, auto b) { return a > b ? a : b; }) << "\n";

    return 0;
}