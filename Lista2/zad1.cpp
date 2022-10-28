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

    auto add(const char *a, const char *b) -> const char *
    {
        char *result = new char[strlen(a) + strlen(b)];
        strcpy(result, a);
        strcat(result, b);
        return result;
    }
}

int main()
{
    int a = 2, b = 5;
    const char *c = "Hello", *d = "World";

    std::cout << cpplab::add(&a, &b) << std::endl;
    std::cout << cpplab::add(c, d) << std::endl;

    return 0;
}