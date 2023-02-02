#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace cpplab
{
    template <typename T>
    class unique_ptr
    {
    public:
        unique_ptr() : pointer(nullptr) {}
        unique_ptr(T value) : pointer(new T(value)) {}
        unique_ptr(T *pointer)
        {
            if (pointer != nullptr)
                pointer = new T(*pointer);
            else
                pointer = nullptr;
        }
        unique_ptr(const unique_ptr &) = delete;
        unique_ptr &operator=(const unique_ptr &) = delete;
        unique_ptr(unique_ptr&& other) noexcept : pointer(std::exchange(other.pointer, nullptr)) {}
        unique_ptr& operator=(unique_ptr&& other) noexcept
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
        non0_ptr(T value) : unique_ptr<T>(value) {}
        non0_ptr(T *pointer) : unique_ptr<T>(pointer)
        {
            static_assert(pointer != nullptr, "cpplab::non0_ptr cannot be initialized with nullptr");
        }

        void release() = delete;
    };
}

int main()
{
}