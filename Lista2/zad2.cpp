#include <iostream>

namespace cpplab
{
    template <class T>
    class Hypercube
    {
    public:
        constexpr Hypercube(T dim, T side) : dimension_(dim), side_length_(side) {}

        constexpr T get_volume() const
        {
            if (dimension_ < 0)
                return -1;
            T volume = 0;
            for (T i = 0; i < dimension_; ++i)
                volume = (i == 0) ? side_length_ : volume * side_length_;
            return volume;
        }

    private:
        int dimension_;
        T side_length_;
    };
}

int main()
{
    constexpr cpplab::Hypercube<int> a(4, 2);
    constexpr cpplab::Hypercube<double> b(0, 3.14);
    constexpr cpplab::Hypercube<float> c(-1, 2.71);

    std::cout << a.get_volume() << std::endl;
    std::cout << b.get_volume() << std::endl;
    std::cout << c.get_volume() << std::endl;

    return 0;
}