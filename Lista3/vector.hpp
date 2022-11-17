#pragma once

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
            _capacity = 0;
            _size = 0;
        }
        vector(std::initializer_list<T> list)
        {
            _capacity = list.size();
            _size = list.size();
            _data = std::make_unique<T[]>(_capacity);
            std::copy(list.begin(), list.end(), _data.get());
        }
        ~vector()
        {
            _data.release();
        }
        vector(const vector &other)
        {
            _capacity = other._capacity;
            _size = other._size;
            _data = std::make_unique<T[]>(_capacity);
            std::copy(other._data.get(), other._data.get() + _size, _data.get());
            std::cout << "copy constructor" << std::endl;
        }
        vector(vector &&other) noexcept
        {
            *this = std::move(other);
            std::cout << "move constructor" << std::endl;
        }
        vector &operator=(const vector &other)
        {
            if (this != &other)
            {
                _capacity = other._capacity;
                _size = other._size;
                _data = std::make_unique<T[]>(_capacity);
                std::copy(other._data.get(), other._data.get() + _size, _data.get());
            }
            std::cout << "copy assignment" << std::endl;
            return *this;
        }
        vector &operator=(vector &&other) noexcept
        {
            if (this != &other)
            {
                _capacity = other._capacity;
                _size = other._size;
                _data = std::move(other._data);

                other._capacity = 0;
                other._size = 0;
                other._data.release();
            }
            std::cout << "move assignment" << std::endl;
            return *this;
        }
        T &operator[](size_t index)
        {
            if (index < 0 || index >= _size)
                throw std::out_of_range("vector index out of bounds");
            return _data[index];
        }
        T operator[](size_t index) const
        {
            if (index < 0 || index >= _size)
                throw std::out_of_range("vector index out of bounds");
            return _data[index];
        }
        friend std::ostream &operator<<(std::ostream &os, const vector<T> &v)
        {
            for (size_t i = 0; i < v._size; ++i)
                os << v[i] << " ";
            return os;
        }

        template <typename... Ts>
        void emplace_back(Ts &&...args)
        {
            if (_size >= _capacity)
                reallocate();
            _data[_size] = T(std::forward<Ts>(args)...);
            ++_size;
        }
        void push_back(T value)
        {
            if (_size >= _capacity)
                reallocate();
            _data[_size] = value;
            ++_size;
        }
        void pop_back()
        {
            if (_size > 0)
                --_size;
        }
        void resize(size_t new_size, T value)
        {
            if (new_size > _size && new_size <= _capacity)
                for (size_t i = _size; i < new_size; ++i)
                    _data[i] = value;
            else if (new_size > _capacity)
                for (size_t i = _size; i < new_size; ++i)
                    this->push_back(value);
            _size = new_size;
        }

        size_t size() const
        {
            return _size;
        }
        T *begin() const
        {
            return &_data[0];
        }
        T *end() const
        {
            return &_data[_size];
        }

    private:
        void reallocate()
        {
            size_t new_capacity = (_capacity == 0) ? 1 : 2 * _capacity;
            _capacity = new_capacity;
            T *new_data = new T[new_capacity];
            for (size_t i = 0; i < _size; ++i)
                new_data[i] = _data[i];
            _data.reset(new_data);
        }

        size_t _size;
        size_t _capacity;
        std::unique_ptr<T[]> _data;
    };
}