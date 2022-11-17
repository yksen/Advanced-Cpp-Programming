#include "vector.hpp"

int main()
{
    cpplab::vector<int> a{1, 2, 3};
    cpplab::vector<int> b(a);
    std::cout << b << std::endl;

    cpplab::vector<int> c;
    c = a;
    std::cout << c << std::endl;

    cpplab::vector<int> d(std::move(c));
    std::cout << d << std::endl;

    cpplab::vector<int> e;
    e = std::move(d);
    std::cout << e << std::endl;

    return 0;
}