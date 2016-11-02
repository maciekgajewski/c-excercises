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
    std::shared_ptr<ListElement<T>> next;
    bool isTerminal;
    ListElement() = default;
    static std::shared_ptr<ListElement<T>> GetTerminalElement()
    {
        ListElement<T> result;
        result.isTerminal = true;
        return std::make_shared<ListElement<T>>(result);
    }

public:

    ListElement(T newItem)
    {
        item = newItem;
        next = nullptr;
        isTerminal = false;
    }

    ~ListElement() {}
};

template<typename T>
class ListIterator : public std::iterator<std::input_iterator_tag, T, T, const T*, T>
{
private:
    std::shared_ptr<ListElement<T>> current;

public:
    ListIterator(std::shared_ptr<ListElement<T>> element)
    {
        current = element;
    }

    T& operator*() const
    {
        return current -> item;
    }

    ListIterator<T>& operator ++()
    {
        current = current -> next;
        return *this;
    }

    bool operator ==(const ListIterator<T>& other)
    {
        return current -> isTerminal == other -> current.isTerminal;
    }

    bool operator !=(const ListIterator<T>& other)
    {
        return current -> isTerminal != other.current -> isTerminal;
    }
};

template<typename T>
class List
{
private:
    int mSize = 0;
    std::shared_ptr<ListElement<T>> terminalElement = ListElement<T>::GetTerminalElement();
    std::shared_ptr<ListElement<T>> head = terminalElement;

public:
    ListIterator<T> begin() const
    {
        return ListIterator<T>(head);
    }

    ListIterator<T> end() const
    {
        return ListIterator<T>(terminalElement);
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

    void push_front(T newItem)
    {
        std::shared_ptr<ListElement<T>> oldHead = std::move(head);
        head = std::make_shared<ListElement<T>>(newItem);
        mSize++;
        head->next = std::move(oldHead);
    }

    T pop_front()
    {
        T value = head -> item;
        std::shared_ptr<ListElement<T>> newHead = std::move(head -> next);
        head = std::move(newHead);
        mSize--;
        return value;
    }
};}
