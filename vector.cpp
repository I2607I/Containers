#include "vector.h"

template <class T>
vector<T>& vector<T>::operator=(vector &&v) {
    m_capacity = v.m_capacity;
    m_size = v.m_size;
    delete[] arr;
    arr = v.arr;
    return *this;
}

template <class T>
typename vector<T>::reference vector<T>::at(size_type pos) {
    return arr[pos];
}

template <class T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
    return arr[pos];
}

template <class T>
typename vector<T>::const_reference vector<T>::front() {
    return arr[0];
}

template <class T>
typename vector<T>::const_reference vector<T>::back() {
    return arr[m_size - 1];
}

template <class T>
T* vector<T>::data() {
    return arr;
}

template <class T>
bool vector<T>::empty() {
    return m_size == 0;
}

template <class T>
typename vector<T>::size_type vector<T>::size() {
        return m_size;
}

template <class T>
typename vector<T>::size_type vector<T>::max_size() {
    return 2^(64-size(value_type))-1;
}

template <class T>
void vector<T>::reserve(size_type size) {
    m_capacity = size;
    *arr2 = new value_type[m_capacity];
    if (m_size > m_capacity) {
        m_size = m_capacity;
    }
    for (auto i = 0; i < m_size; i++) {
        arr2[i] = arr[i];
    }
    delete[] arr;
    arr = arr2;
}

template <class T>
typename vector<T>::size_type vector<T>::capacity() {
    return m_capacity;
}

template <class T>
void vector<T>::shrink_to_fit() {
    reserve(m_size);
}

template <class T>
void vector<T>::clear() {
    reserve(0);
}

template <class T>
typename vector<T>::iterator vector<T>::insert(iterator pos, const_reference value) {
    if (m_size == m_capacity) {
        reserve(m_capacity*2)
    }
    for (auto i = m_size - 1; i >= pos; i--) {
        arr[i+1] = arr[i];
    }
    arr[pos] = value;
    m_size++;
    return pos;
}

template <class T>
void vector<T>::erase(iterator pos) {
    m_size--;
    for (auto i = pos; i < m_size; i++) {
        arr[i] = arr[i+1];
    }
}

template <class T>
void vector<T>::push_back(value_type v) {
    if (m_size == m_capacity) {
        reserve(m_capacity*2);
    }
    arr[m_size] = v;
    m_size++;
}

template <class T>
void vector<T>::pop_back() {
    m_size--;
}

template <class T>
void vector<T>::swap(vector& other) {
    m_capacity, other.m_capacity = other.m_capacity, m_capacity;
    m_size, other.m_size = other.m_size, m_size;
    arr, other.arr = other.arr, arr;
}
