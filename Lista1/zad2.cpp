#include <iostream>
#include <memory>
#include <stdexcept>

namespace cpplab
{
    template <class T>
    class vector
    {
    public:
        typedef T value_type;
        vector()
        {
            capacity = 0;
            size = 0;
        }
        vector(std::initializer_list<T> list)
        {
            capacity = list.size();
            size = list.size();
            data = std::make_unique<T[]>(capacity);
            std::copy(list.begin(), list.end(), data.get());
        }
        ~vector()
        {
            data.release();
        }
        T &operator[](size_t index)
        {
            if (index < 0 || index >= size)
                throw std::out_of_range("vector index out of bounds");
            return data[index];
        }
        T operator[](size_t index) const
        {
            if (index < 0 || index >= size)
                throw std::out_of_range("vector index out of bounds");
            return data[index];
        }
        void push_back(T item)
        {
            if (size >= capacity)
                reallocate();
            data[size] = item;
            ++size;
        }
        void pop_back()
        {
            if (size > 0)
                --size;
        }
        void resize(size_t new_size, T value)
        {
            if (new_size > size && new_size <= capacity)
                for (size_t i = size; i < new_size; ++i)
                    data[i] = value;
            else if (new_size > capacity)
            {
                reallocate();
                for (size_t i = size; i < new_size; ++i)
                    data[i] = value;
            }
            size = new_size;
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

        void reallocate()
        {
            size_t new_capacity = (capacity == 0) ? 1 : 2 * capacity;
            T *new_data = new T[new_capacity];
            for (size_t i = 0; i < size; ++i)
                new_data[i] = data[i];
            data.reset(new_data);
            capacity = new_capacity;
        }
    };
}

int main()
{
    cpplab::vector<int> int_vector;
    cpplab::vector<std::string> string_vector;

    for (int i = 0; i < 10; ++i)
        int_vector.push_back(i);
    int_vector.resize(20, 0);
    int_vector.print();

    return 0;
}