#include <iostream>

namespace cpplab
{
    template <class T>
    class vector
    {
    public:
        vector()
        {
        }
        ~vector()
        {
        }

    private:
        size_t capacity;
        size_t size;
        T *data;
    };
}

int main()
{
    cpplab::vector<int> v;

    return 0;
}