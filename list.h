#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <initializer_list>
#include <utility>

/*
HEADER FILE
*/

// Test vector class with some basic example operations and concepts
template <class T>
class list
{
    // private attributes
    private:
        struct Node {
            T data;
            Node* next;
            Node* prev;
        };
        Node* head;
        Node* tail;
        size_t m_size;

    public:
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using size_type = size_t;

        class ListIterator {
            public:
                Node* head;
                Node* tail;
                Node* iter;
                // constructors & destructor
                ListIterator();
                explicit ListIterator(const list<T>& other);
                // overload operators
                value_type operator*();
                void operator++();
                void operator--();
                bool operator==(const ListIterator& other);
                bool operator!=(const ListIterator& other);
        };

        typedef typename list<T>::ListIterator iterator;

        class ListConstIterator {
        public:
            Node* head;
            Node* tail;
            Node* iter;
            // constructors & destructor
            ListConstIterator();
            explicit ListConstIterator(const list<T>& other);
            // overload operators
            value_type operator*();
            void operator++();
            void operator--();
            bool operator==(const ListConstIterator& other);
            bool operator!=(const ListConstIterator& other);
        };

        typedef typename list<T>::ListConstIterator const_iterator;

        // using const_iterator = ListConstIterator<T>;

        list();
        list(std::initializer_list<value_type> const &items);
        list(const list &l);
        list(list &&l);
        ~list();


        const_reference front();
        const_reference back();
 
        iterator begin();
        iterator end();

        const_iterator cbegin();
        const_iterator cend();

        bool empty();
        size_type size();
        size_type max_size();


        void clear();
        iterator insert(iterator pos, const_reference value);
        void erase(iterator pos);
        void push_back(const_reference value);
        void pop_back();
        void push_front(const_reference value);
        void pop_front();
        void swap(list& other);
        void merge(list& other);
        void splice(const_iterator pos, list& other);
        void reverse();
        void unique();
        void sort();
};

#endif