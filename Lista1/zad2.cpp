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
        double operator*(vector<T> const &rhs) const
        {
            double result = 0;
            size_t min_size = size < rhs.size ? size : rhs.size;
            for (size_t i = 0; i < min_size; i++)
                result += data[i] * rhs[i];
            return result;
        }
        friend std::ostream &operator<<(std::ostream &os, const vector<T> &v)
        {
            for (int i = 0; i < v.size; ++i)
                os << v[i] << " ";
            return os;
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
                for (size_t i = size; i < new_size; ++i)
                    this->push_back(value);
            size = new_size;
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
    int_vector[5] = 999;
    std::cout << int_vector << std::endl;

    string_vector.resize(10, "Hello");
    string_vector.resize(2, "");
    string_vector.resize(5, "world");
    std::cout << string_vector << std::endl;

    cpplab::vector<int> a{1, 2, 3};
    cpplab::vector<int> b{4, 5, 6, 7};
    std::cout << a * b << std::endl;

    return 0;
}