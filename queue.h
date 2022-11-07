#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <initializer_list>
#include <utility>

/*
HEADER FILE
*/

// Test vector class with some basic example operations and concepts
template <class T>
class queue
{
    // private attributes
    private:
        struct Node {
            T data;
            Node* next;
        };
        Node* head;
        Node* tail;
        size_t m_size;

    public:
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using size_type = size_t;


        // using const_iterator = ListConstIterator<T>;

        queue();
        queue(std::initializer_list<value_type> const &items);
        queue(const queue &q);
        queue(queue &&q);
        ~queue();

        const_reference front();
        const_reference back();

        bool empty();
        size_type size();

        void push(const_reference value);
        void pop();
        void swap(queue& other);


        
};

#endif