#pragma once
#include <memory>
#include<iostream>

namespace course{

template<typename T>
class List;

template<typename T>
class ListIterator;

template<typename T>
class ListElement
{
    friend class List<T>;
    friend class ListIterator<T>;

private:
    T item;
    std::unique_ptr<ListElement<T>> next;

    ListElement() = default;

public:

    ListElement(const T& newItem)
        :item(newItem),
         next(nullptr)
    {
    }

    ~ListElement() {}
};

template<typename T>
class ListIterator : public std::iterator<std::input_iterator_tag, T, T, const T*, T>
{
private:
    ListElement<T>* current;

public:
    ListIterator(ListElement<T>* element)
    {
        current = element;
    }

    T& operator*() const
    {
        return current -> item;
    }

    ListIterator<T>& operator ++()
    {
        current = current -> next.get();
        return *this;
    }

    bool operator ==(const ListIterator<T>& other)
    {
        return current == other.current;
    }

    bool operator !=(const ListIterator<T>& other)
    {
        return current != other.current;
    }
};

template<typename T>
class List
{
private:
    int mSize = 0;
    std::unique_ptr<ListElement<T>> head = nullptr;

public:
    ListIterator<T> begin() const
    {
        return ListIterator<T>(head.get());
    }

    ListIterator<T> end() const
    {
        return ListIterator<T>(nullptr);
    }

    bool empty()
    {
        return mSize == 0;
    }

    int size() const
    {
        return mSize;
    }

    T& front() const
    {
        return head->item;
    }

    void push_front(const T& newItem)
    {
        std::unique_ptr<ListElement<T>> oldHead = std::move(head);
        head = std::make_unique<ListElement<T>>(newItem);
        mSize++;
        head->next = std::move(oldHead);
    }

    void pop_front()
    {
        head = std::move(head -> next);
        mSize--;
    }
};}
