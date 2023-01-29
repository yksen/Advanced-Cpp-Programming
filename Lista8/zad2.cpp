#include <iostream>
#include <memory>
#include <string>

namespace cpplab
{
    template <typename T>
    class unique_ptr
    {
    public:
        unique_ptr(T *pointer) : pointer(pointer) {}
        unique_ptr(const unique_ptr &) = delete;
        unique_ptr &operator=(const unique_ptr &) = delete;
        ~unique_ptr() noexcept { delete pointer; }

        T *get() const { return pointer; }
        T *operator->() const { return pointer; }
        T &operator*() const { return *pointer; }

    private:
        T *pointer;
    };

    template <typename T>
    class non0_ptr : public unique_ptr<T>
    {
    public:
        non0_ptr(T *pointer) : unique_ptr<T>(pointer)
        {
            if (pointer == nullptr)
                throw std::invalid_argument("cpplab::non0_ptr cannot be initialized with nullptr");
        }
    };
}

int main()
{
    cpplab::unique_ptr<int> up{new int(3)};
    cpplab::unique_ptr<int> up2{nullptr};

    cpplab::non0_ptr<int> np{new int(7)};
    try
    {
        cpplab::non0_ptr<int> np2{nullptr};
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}