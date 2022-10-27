#include <iostream>

namespace cpplab
{
    template <class T, int dim, T side>
    class Hypercube
    {
    public:
        constexpr T get_volume() const
        {
            if (dim < 0)
                return -1;
            T volume = 0;
            for (int i = 0; i < dim; ++i)
                volume = (i == 0) ? side : volume * side;
            return volume;
        }
    };
}

int main()
{
    constexpr cpplab::Hypercube<int, 4, 2> a;
    constexpr cpplab::Hypercube<double, 0, 3.14> b;
    constexpr cpplab::Hypercube<float, -1, 2.71f> c;

    static_assert(a.get_volume() == 16, "Assertion failed");
    static_assert(b.get_volume() == 0, "Assertion failed");
    static_assert(c.get_volume() == -1, "Assertion failed");

    std::cout << a.get_volume() << std::endl;
    std::cout << b.get_volume() << std::endl;
    std::cout << c.get_volume() << std::endl;

    return 0;
}