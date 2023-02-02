#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace cpplab
{
    template <typename T>
    class unique_ptr
    {
    public:
        unique_ptr() : pointer(nullptr) {}
        unique_ptr(T *pointer) : pointer(pointer) {}
        unique_ptr(const unique_ptr &) = delete;
        unique_ptr &operator=(const unique_ptr &) = delete;
        unique_ptr(unique_ptr &&other) noexcept : pointer(std::exchange(other.pointer, nullptr)) {}
        unique_ptr &operator=(unique_ptr &&other) noexcept
        {
            std::swap(pointer, other.pointer);
            return *this;
        }
        ~unique_ptr() noexcept { delete pointer; }

        T *get() const noexcept { return pointer; }
        T *operator->() const noexcept { return pointer; }
        T &operator*() const noexcept { return *pointer; }

        T *release() noexcept
        {
            pointer = nullptr;
            return pointer;
        }
        void reset(T *pointer) noexcept
        {
            delete this->pointer;
            this->pointer = pointer;
        }
        void swap(unique_ptr &other) noexcept
        {
            std::swap(pointer, other.pointer);
        }

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

        void release() = delete;
    };
}

int main()
{
    cpplab::unique_ptr<int> p1(new int(2));
    std::cout << *p1 << std::endl;

    p1 = cpplab::unique_ptr<int>(new int(4));
    std::cout << *p1 << std::endl;

    cpplab::unique_ptr<int> p2(std::move(p1));
    std::cout << p1.get() << std::endl;
    std::cout << *p2 << std::endl;

    cpplab::non0_ptr<double> np1(new double(2.5));
    std::cout << *np1 << std::endl;

    try
    {
        cpplab::non0_ptr<double> np2(nullptr);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}