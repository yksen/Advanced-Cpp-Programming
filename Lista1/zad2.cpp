#include <iostream>
#include <memory>
#include <stdexcept>

namespace cpplab
{
    template <class T>
    class vector
    {
    public:
        vector()
        {
            capacity = 0;
            size = 0;
        }
        ~vector()
        {
            data.release();
        }
        T &operator[](size_t index)
        {
            if (index >= size)
                throw std::out_of_range("vector index out of bounds");
            return data[index];
        }
        void push_back(T item)
        {
            if (size >= capacity)
            {
                size_t new_capacity = (capacity == 0) ? 1 : 2 * capacity;
                T *new_data = new T[new_capacity];
                for (size_t i = 0; i < size; ++i)
                    new_data[i] = data[i];
                data.reset(new_data);
                capacity = new_capacity;
            }
            data[size] = item;
            ++size;
        }
        void pop_back()
        {
            if (size > 0)
                --size;
        }
        void print()
        {
            for (int i = 0; i < size; ++i)
                std::cout << data[i] << "\n";
        }

    private:
        size_t capacity;
        size_t size;
        std::unique_ptr<T[]> data;
    };
}

int main()
{
    cpplab::vector<int> v;

    for (int i = 0; i < 10; ++i)
        v.push_back(i);
    v.print();

    return 0;
}