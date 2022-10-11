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
    auto alias(T a, U b, V f) -> decltype(f(a, b))
    {
        return f(a, b);
    }
}

int main()
{
    std::cout << cpplab::add(5, 3.14f) << "\n";
    std::cout << cpplab::add('d', 4) << "\n";
    std::cout << cpplab::add<std::string, std::string>("Hello", "world") << "\n";

    std::cout << cpplab::alias(5, 9, cpplab::add<int, int>) << "\n";
    std::cout << cpplab::alias(12.4f, 7.7, [](auto a, auto b) { return a > b ? a : b; }) << "\n";
    std::cout << cpplab::alias("Hello", "world", [](auto a, auto b) { return std::strcmp(a, b) > 0 ? a : b; }) << "\n";

    return 0;
}