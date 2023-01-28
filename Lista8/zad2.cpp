#include <concepts>

namespace cpplab
{
    template <typename T>
    class unique_ptr
    {
    public:
        unique_ptr(T *pointer) : pointer(pointer) {}

    private:
        T *pointer;
    };

    template <typename T>
        requires std::is_pointer_v<T>
    class non0_ptr
    {
    public:
        non0_ptr(T *pointer) : pointer(pointer) {}

    private:
        T *pointer;
    };
}

int main()
{
}