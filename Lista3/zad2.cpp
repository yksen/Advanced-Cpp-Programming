#include "vector.hpp"

struct Pixel
{
    int r;
    int g;
    int b;

    Pixel()
    {
    }
    Pixel(int r, int g, int b)
        : r(r), g(g), b(b)
    {
        std::cout << "default constructor" << std::endl;
    }
    Pixel(const Pixel &other)
    {
        r = other.r;
        g = other.g;
        b = other.b;
        std::cout << "copy constructor" << std::endl;
    }

    friend std::ostream &operator<<(std::ostream &os, const Pixel &p)
    {
        os << "(" << p.r << ", " << p.g << ", " << p.b << ")";
        return os;
    }
};

int main()
{
    cpplab::vector<Pixel> a;

    a.emplace_back(1, 2, 3);
    a.emplace_back(4, 5, 6);

    return 0;
}