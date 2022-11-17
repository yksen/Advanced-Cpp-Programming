#include "vector.hpp"

int main()
{
    cpplab::vector<int> a{1, 2, 3};
    std::cout << a << std::endl;

    a.push_back(7);
    std::cout << a << std::endl;

    a.emplace_back(9, 10, 11);
    std::cout << a << std::endl;

    return 0;
}