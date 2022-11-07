#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <initializer_list>
#include <utility>

template <class T>
class vector
{
    // private attributes
    private:
        size_t m_size;
        size_t m_capacity;
        T *arr;
        // public attribures
    public:
        // member types
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using iterator = T *;
        using const_iterator = const T *;
        using size_type = size_t;
        // private method
        // public methods
    public:
        // default constructor (simplified syntax for assigning values to attributes)
        vector() : m_size(0U), m_capacity(0U), arr(nullptr) {}
        // parametrized constructor for fixed size vector (explicit was used in order to
        // avoid automatic type conversion)
        explicit vector(size_type n) : m_size(n), m_capacity(2*n), arr(n ? new T[2*n] : nullptr) {}
        // initializer list constructor (allows creating lists with initializer lists, see main.cpp)
        vector(std::initializer_list<value_type> const &items);
        // copy constructor with simplified syntax
        vector(const Vector &v) : m_size(v.m_size), m_capacity(v.m_capacity), arr(v.arr) {};
        // move constructor with simplified syntax
        vector(Vector &&v) : m_size(v.m_size), m_capacity(v.m_capacity), arr(v.arr)
        {
            v.arr = nullptr;
            v.m_size = 0;
            v.m_capacity = 0;
        }

        // destructor
        ~Vector() { delete[] arr; }

        vector<T>& operator=(vector &&v);



        reference at(size_type pos);
        reference operator[](size_type pos);
        const_reference front();
        const_reference back();
        T* data();


        bool empty();
        size_type size();
        size_type max_size();
        void reserve(size_type size);
        size_type capacity();
        void shrink_to_fit();

        // some method examples
        // size getter
        // element accessor
        value_type at(size_type i) {
            return arr[i];
        }
        // append new element
        void push_back(value_type v);


        void clear();
        iterator insert(iterator pos, const_reference value);
        void erase(iterator pos);
        void push_back(const_reference value);
        void pop_back();
        void swap(vector& other);
};





#endif