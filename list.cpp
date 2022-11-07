#include "list.h"
#include <iostream>

template <class T>
list<T>::list(): head(nullptr), tail(nullptr), m_size(0) {}

template <class T>
list<T>::list(std::initializer_list<value_type> const &items) {
    m_size = 0;
    head = nullptr;
    tail = nullptr;
    for (const auto &element : items) push_back(element);
}

template <class T>
list<T>::list(const list &other) : head(nullptr), tail(nullptr), m_size(0) {
    iterator it(other);
    while (it.iter) {
        push_back(it.iter->_data);
        ++it;
    }
}

template <class T>
list<T>::list(list &&other) : head(nullptr), tail(nullptr), m_size(0) {
    swap(std::move(other));
}

template <class T>
list<T>::~list() {
    if (tail != nullptr) {
        Node *buf;
        buf = tail;
        while (buf != nullptr) {
            tail->next = nullptr;
            buf = tail->prev;
            tail->prev = nullptr;
            delete tail;
            tail = buf;
        }
        head = nullptr;
    }
}

template <class T>
void list<T>::push_back(const_reference value) {
    Node* n = new Node;
    m_size++;
    n->data = value;
    n->prev = tail;
    n->next = nullptr;
    if (!head) {
        head = n;
    }
    if (tail) {
        tail->next = n;
    }
    tail = n;    
}

template <class T>
void list<T>::pop_back() {
    if (m_size > 1) {
        Node* tmp = tail->prev;
        delete tail;
        tail = tmp;
        m_size-=1;
        tail->next = nullptr;
    }
    if (m_size == 1) {
        delete tail;
        tail = nullptr;
        head = nullptr;
        m_size-=1;
    }
    std::cout << m_size << std::endl;
}

template <class T>
void list<T>::push_front(const_reference value) {
    Node* n = new Node;
    m_size++;
    n->data = value;
    n->next = head;
    n->prev = nullptr;
    if (!head) {
        tail = n;
    }
    head = n;
}

template <class T>
void list<T>::pop_front() {
    if (m_size == 1) {
        delete head;
        head = nullptr;
        tail = nullptr;
        m_size--;
    }
    if (m_size > 1) {
        Node* tmp = head->next;
        delete head;
        head = tmp;
        head->prev = nullptr;
        m_size--;
    }
}

template <class T>
typename list<T>::iterator list<T>::insert(iterator pos, const_reference value) {
    iterator it = begin();
    while (it.iter != pos.iter) {
        ++it;
    }
    Node *n = it.iter;
    if (n == it.head) push_front(value);
    else if (n == it.tail) push_back(value);
    else {
        Node* tmp = new Node;
        tmp->data = value;
        n->prev->next = tmp;
        n->prev = tmp;
        tmp->prev = n->prev;
        tmp->next = n;
        m_size++;
    }
    return it;
}

template <class T>
void list<T>::erase(iterator pos) {
    if (pos.iter == pos.head) pop_front();
    else if (pos.iter == pos.tail) pop_back();
    else {
        Node* tmp = pos.iter;
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        delete tmp;
        m_size--;
    }
}

template <class T>
void list<T>::swap(list& other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(m_size, other.m_size);
}

template <class T>
void list<T>::splice(const_iterator pos, list& other) {
    if (head == pos.iter) {
        head = other.head;
        other.tail->next = pos.iter;
        pos.iter->prev = other.tail;
    } else if (cend() == pos) {
        // other.tail->next = head;
        // head->prev = other.tail;
        tail->next = other.head;
        other.head->prev = tail;
        
        // head = other.head;
    } else {
        pos.iter->prev->next = other.head;
        other.head->prev = pos.iter->prev;
        other.tail->next = pos.iter;
        pos.iter->prev = other.tail;
    }
    m_size+=other.m_size;
    other.m_size = 0;
    other.head = nullptr;
    other.tail = nullptr;
}

template <class T>
void list<T>::reverse() {
    Node* tmp = tail;
    auto m = m_size;
    for (auto i = 0; i < m; i++) {
        std::swap(tmp->next, tmp->prev);
        tmp = tmp->next;
    }
    std::swap(head, tail);
}

template <class T>
void list<T>::unique() {
    auto m = m_size;
    Node* tmp = head;
    auto val1 = tmp->data;
    Node * next_tmp = tmp;
    auto val2 = val1;
    for (auto i = 0; i < m - 1; i++) {
        next_tmp = next_tmp->next;
        val2 = next_tmp->data;
        std::cout << val1  << ' ' << val2 << std::endl;
        if (val1 == val2) {
            m_size--;
        } else {
            tmp->next = next_tmp;
            next_tmp->prev = tmp;
            tmp = next_tmp;
            val1 = val2;
        }
    }
    tmp->next = next_tmp;
    next_tmp->prev = tmp;
    if (tail->data==next_tmp->data) {
        pop_back();
    }
}

template <class T>
void list<T>::merge(list &other) {
    // list<int>::ListIterator this_it(*this);
    // list<int>::ListConstIterator other_it(other);
    iterator this_it = begin();
    const_iterator other_it = other.cbegin();
    while (other_it.iter != nullptr) {
        if (this_it.iter == nullptr) {
            splice(other_it, other);
            break;
        }
        if (this_it.iter->data >= other_it.iter->data) {
            insert(this_it, other_it.iter->data);
            ++other_it;
        } else {
            ++this_it;
        }
    }
}





template <class T>
list<T>::ListIterator::ListIterator() : head(nullptr), tail(nullptr), iter(nullptr) {}

template <class T>
list<T>::ListIterator::ListIterator(const list<T> &other)
    : head(other.head), tail(other.tail), iter(other.head) {}

template <class T>
T list<T>::ListIterator::operator*() {
    return iter ? iter->data : 0;
}

template <class T>
void list<T>::ListIterator::operator++() {
    if (iter) iter = iter->next;
}

template <class T>
void list<T>::ListIterator::operator--() {
    if (iter == head) {
        throw std::out_of_range("Out of list size");
    } else {
        if (iter) {
            iter = iter->prev;
        } else {
            iter = tail;
        }
    }
}

template <class T>
bool list<T>::ListIterator::operator==(const ListIterator &other) {
    return iter == other.iter;
}

template <class T>
bool list<T>::ListIterator::operator!=(const ListIterator &other) {
    return iter != other.iter;
}



template <class T>
typename list<T>::iterator list<T>::begin() {
    return ListIterator(*this);
}

template <class T>
typename list<T>::iterator list<T>::end() {
    iterator buf(*this);
    while (buf.iter != nullptr) buf.iter = buf.iter->next;
    return buf;
}

template <class T>
typename list<T>::const_iterator list<T>::cbegin() {
    return const_iterator(*this);
}

template <class T>
typename list<T>::const_iterator list<T>::cend() {
    const_iterator buf(*this);
    while (buf.iter != nullptr) buf.iter = buf.iter->next;
    return buf;
}

template <class T>
list<T>::ListConstIterator::ListConstIterator() : head(nullptr), tail(nullptr), iter(nullptr) {}

template <class T>
list<T>::ListConstIterator::ListConstIterator(const list<T> &other)
    : head(other.head), tail(other.tail), iter(other.head) {}

template <class T>
T list<T>::ListConstIterator::operator*() {
    return iter ? iter->_data : 0;
}

template <class T>
void list<T>::ListConstIterator::operator++() {
    if (iter) iter = iter->next;
}

template <class T>
void list<T>::ListConstIterator::operator--() {
    if (iter == head) {
        throw std::out_of_range("Out of list size");
    } else {
        if (iter) {
            iter = iter->prev;
        } else {
            iter = tail;
        }
    }
}

template <class T>
bool list<T>::ListConstIterator::operator==(const ListConstIterator &other) {
    return iter == other.iter;
}

template <class T>
bool list<T>::ListConstIterator::operator!=(const ListConstIterator &other) {
    return iter != other.iter;
}




int main() {
    // list<int> a = {2, 3, 4};
    // list<int> b = {3, 4, 0, -45, 22, 1};
    // a.push_back(7);
    // a.pop_back();
    // a.push_front(1);
    // a.push_front(12345);
    // // a.pop_back();
    // a.pop_front();
    // a.pop_front();
    // a.pop_front();
    // a.pop_front();
    // a.pop_front();
    // typename list<int>::iterator it = a.begin();
    // ++it;
    // ++it;
    // a.erase(it);
    // a.swap(b);
    // a.swap(b);
    // list<int> list1 = {1, 1, 2, 3, 3, 3, 4, 3, 4, 5, 5, 89, 89, 89, 89, 89};
    list<int> list1 = {1, 2, 3, 4};
    list<int> list2 = {10, 20, 30, 40, 50};
 
    // typename list<int>::const_iterator it = list1.cbegin();
    // ++it;
    // ++it;
    // ++it;
    // ++it;
    // ++it;
    // list1.splice(it, list2);
    list1.merge(list2);

    std::cout << "l = { ";
    for (int n : list1)
        std::cout << n << ", ";
    std::cout << "};\n";
}


