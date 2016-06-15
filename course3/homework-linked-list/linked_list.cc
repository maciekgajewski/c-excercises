#include "linked_list.h"

#include <cstring>
#include <stdexcept>

template<class T>
LinkedList<T>::LinkedList(): length(0) { }

template<class T>
const T* LinkedList<T>::begin() const {
    return this->head->data;
}

template<class T>
T* LinkedList<T>::begin() {
    return this->head->data;
}

template<class T>
const T* LinkedList<T>::end() const {
    return this->tail->data;
}

template<class T>
T* LinkedList<T>::end() {
    return this->tail->data;
}

template<class T>
std::size_t LinkedList<T>::size() const {
    return this->length;
}

template<class T>
bool LinkedList<T>::empty() const {
    return this->length == 0;
}

template<class T>
void LinkedList<T>::push_front(const T& input) {
    auto n = Node(input);
    n.next = this->head;
    this->head = &n;
    this->length++;
}

template<class T>
void LinkedList<T>::pop_front() {
    if (this->empty()) {
        throw std::out_of_range("The list is empty");
    }
    auto topop = this->head;
    this->head = this->head->next;
    delete topop;
    this->length--;

}

template<class T>
const T& LinkedList<T>::front() const {
    return *this->head;
}

template<class T>
T& LinkedList<T>::front() {
    return *this->head;
}