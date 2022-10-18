#include <iostream>

namespace cpplab
{
    int add_total() { return 0; }

    template <typename T, typename... Ts>
    auto add_total(T head, Ts... tail)
    {
        return head + add_total(tail...);
    }

}

int main()
{
    std::cout << cpplab::add_total() << std::endl;
    std::cout << cpplab::add_total(5) << std::endl;
    std::cout << cpplab::add_total(2.5, 6) << std::endl;
    std::cout << cpplab::add_total(1, 1.0, 1.0f) << std::endl;

    return 0;
}