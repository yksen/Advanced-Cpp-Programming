#include <iostream>

namespace cpplab
{
    template <typename T, typename... Ts>
    auto add_total(T head, Ts... tail)
    {
        if constexpr (sizeof...(tail) == 0)
            return head;
        else
            return head + add_total(tail...);
    }

}

int main()
{
    std::cout << cpplab::add_total(5) << std::endl;
    std::cout << cpplab::add_total(2.5, 6) << std::endl;
    std::cout << cpplab::add_total(1, 1.0, 1.0f) << std::endl;

    return 0;
}