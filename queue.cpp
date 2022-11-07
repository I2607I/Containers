#include <queue.h>

template <class T>
queue<T>::queue(): head = nullptr, tail=nullptr, m_size = 0 {}

template <class T>
queue<T>::queue(std::initializer_list<value_type> const &items): head = nullptr, tail = nullptr, m_size = 0 {
    for (auto &item: items) push(item);
}

template <class T>
queue<T>::queue(const queue &q) {

}

template <class T>
queue<T>::queue(queue &&q) {

}

template <class T>
queue<T>::~queue() {
    auto m = m_size;
    Node* tmp = head;
    for (auto i = 0; i < m; i++) {
        Node* del = tmp;
        tmp = tmp->next;
        delete del;
    }
    head = nullptr;
    tail = nullptr;
    m_size = 0;
}

template <class T>
typename queue<T>::const_reference queue<T>::front() {
    return head->data;
}

template <class T>
typename queue<T>::const_reference queue<T>::back() {
    return tail->data;
}

template <class T>
bool queue<T>::empty() {
    return m_size == 0;
}

template <class T>
typename queue<T>::size_type queue<T>::size() {
    return m_size;
}

template <class T>
void queue<T>::push(const_reference value) {
    Node* tmp = new Node;
    m_size++;
    n->data = value;
    n->next = nullptr;
    if (!head) {
        head = tmp;
    }
    if (tail) {
        tail->next = tmp;
    }
    tail = tmp;
}

template <class T>
void queue<T>::pop() {
    if (m_size == 1) {
        delete head;
        tail = nullptr;
    } else {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }

    m_size--;
}

template <class T>
void queue<T>::swap(queue& other){
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(m_size, other.m_size);
}