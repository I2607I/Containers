#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <initializer_list>
#include <utility>

/*
HEADER FILE
*/

// Test vector class with some basic example operations and concepts
template <class T, size_t N>
class array
{
    // private attributes
    private:
        T arr[N] {};

    public:
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using iterator = T *;
        using const_iterator = const T *;
        using size_type = size_t;


        array() {}
        array(std::initializer_list<value_type> const &items) {
            for (auto i = 0; i < N; i++) {
                arr[i] = items[i];
            }
        }
        array(const array &a) {
            for (auto i = 0; i < N; i++) {
                arr[i] = a[i];
            }
        }
        array(array &&a) {
            for (auto i = 0; i < N; i++) {
                arr[i], a[i] = a[i], arr[i];
            }
        }
        ~array() {}
        // operator=(array &&a)


        size_type size() {
            return N;
        }

        size_type max_size() {
            return N;
        }
        bool empty() {
            return N == 0;
        }


        reference at(size_type pos)	{
            return arr[pos];
        }
        reference operator[](size_type pos) {
            return arr[pos];
        }
        const_reference front()	{
            return arr[0];
        }
        const_reference back() {
            return arr[N-1];
        }
        iterator data() {
            return arr;
        }

        void swap(array& other) {
            for (auto i = 0; i < N; i++) {
                arr[i], other[i] = other[i], arr[i];
            }
        }

        void fill(const_reference value) {
            for (auto i = 0; i < N; i++) {
                arr[i] = value;
            }
        }

        iterator begin() {
            return 0;
        }

        iterator end() {
            return N;
        }
};

#endif