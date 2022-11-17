#include <iostream>
#include <vector>
#include "vector.hpp"

template <typename T, typename U>
auto operator*(T const &lhs, U const &rhs) -> decltype(lhs[0] * rhs[0])
{
    if (lhs.size() != rhs.size())
        throw std::logic_error("dot product arguments have to be the same size");
    return std::inner_product(lhs.begin(), lhs.end(), rhs.begin(), 0.);
}

int main()
{
    cpplab::vector<int> int_vector;
    cpplab::vector<std::string> string_vector;

    for (int i = 0; i < 10; ++i)
        int_vector.push_back(i);
    int_vector[5] = 999;
    std::cout << int_vector << std::endl;

    string_vector.resize(10, "Hello");
    string_vector.resize(2, "");
    string_vector.resize(5, "world");
    std::cout << string_vector << std::endl;

    std::vector<int> a{4, 5, 6};
    cpplab::vector<int> b{1, 3, 2};
    cpplab::vector<double> c{1.5, 1. / 3, 0.5};
    std::cout << a * b << std::endl;
    std::cout << c * b << std::endl;
    std::cout << a * a << std::endl;
    std::cout << b * b << std::endl;
    std::cout << std::string("a") * std::string("a") << std::endl;
    std::cout << string_vector * string_vector << std::endl;

    return 0;
}