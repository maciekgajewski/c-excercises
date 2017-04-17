#pragma once
#include <iostream>
#include <memory>
#include <stdexcept>

namespace linked_list
{

// This is a very helpful website: https://www.cs.northwestern.edu/~riesbeck/programming/c++/stl-iterator-define.html#TOC23
template<class T> class LinkedListIter;

template<class T, class Allocator = std::allocator<T>>
class LinkedList
{
public:
    friend class LinkedListIter<T>;
    typedef LinkedListIter<T> iterator;

    // Basic assignment constructors
    LinkedList() = default;
    LinkedList(const T& val) // TODO T&& val ?
    {
        std::cout << "Basic construction: from " << val << std::endl;
        data = std::make_unique<T>(val);
        mSize += 1;
    }
    // Copy construction
    LinkedList(const LinkedList& src)
    {
        if (src.data)
        {
            std::cout << "Copy construction: from " << src.front() << std::endl;
            data = std::make_unique<T>(src.front());
            std::cout << "copy -- set data" << std::endl;
        }
        else
        {
            std::cout << "Copy construction: from empty" << std::endl;
        }

        if (src.next)
        {
            std::cout << "copy -- setting next" << std::endl;
            next = std::make_unique<LinkedList<T>>(*src.next.get());
            std::cout << "copy -- set next" << std::endl;
        }
        else
            std::cout << "copy -- no next" << std::endl;
        mSize = src.mSize;
        std::cout << "copy -- set size" << std::endl;
    }
    // Move construction
    LinkedList(LinkedList&& src)
    {
        std::cout << "Move construction: from " << src.front() << std::endl;
        data = std::move(src.data);
        next = std::move(src.next);
        mSize = src.mSize;
    }
    // Copy assignment
    LinkedList& operator=(const LinkedList& src)
    {
        std::cout << "Copy assignment: from " << src.front() << std::endl;
        data = std::make_unique<T>(src.front());
        if (src.next)
            next = std::make_unique<LinkedList<T>>(*src.next.get());
        mSize = src.mSize;
        return *this;
    }
    // Move assignment
    LinkedList& operator=(LinkedList&& src)
    {
        std::cout << "Move assignment: from " << src.front() << std::endl;
        data = std::move(src.data);
        next = std::move(src.next);
        mSize = src.mSize;
        return *this;
    }

    bool operator==(LinkedList& cmp) const
    {
        std::cout << mSize << " " << cmp.mSize << std::endl;
        if (mSize != cmp.mSize)
            return false;
        if (data != cmp.data)
            return false;
        if (!(next && cmp.next))
             return true;
        if  (next != cmp.next)
            return false;
        return true;
    }

    int size() const { return mSize; }
    T front() const // TODO should this be a pointer? const?
    {
        if (data)
            return *data.get();
        throw std::range_error("Calling front on empty LinkedList is undefined.");
    }
    void push_front(const T& val)
    {
        if (mSize > 0)
        {
            LinkedList<T> new_node;
            new_node.data = std::move(this->data);
            new_node.next = std::move(this->next);
            data = std::make_unique<T>(val);
            next = std::make_unique<LinkedList<T>>(std::move(new_node));
        }
        else
        {
            data = std::make_unique<T>(val);
        }
        mSize++;
    }

    template< class... Args >
    void emplace_front(Args&&... args)
    {
        if (mSize > 0)
        {
            LinkedList<T> new_node;
            new_node.data = std::move(this->data);
            new_node.next = std::move(this->next);
            data = std::make_unique<T>(args...);
            next = std::make_unique<LinkedList<T>>(std::move(new_node));
        }
        else
        {
            data = std::make_unique<T>(args...);
        }
        mSize++;
    }

    void pop_front()
    {
        if (next)
        {
            LinkedList<T> new_head = std::move(*next.get());
            data = std::move(new_head.data);
            next = std::move(new_head.next);
            mSize--;
        }
    }

    void print() const
    {
        std::cout << "------------------------------------------------------------------------------" << std::endl;
        std::cout << "getting this" << std::endl;
        LinkedList<T> current = *this;
        std::cout << "got this" << std::endl;
        for (auto i = 0; i < mSize; i++)
        {
            std::cout << i << " [" << current.front() << "]" << std::endl;
            if (current.next)
            {
                std::cout << "getting next ptr" << std::endl;
                LinkedList<T> *newcurrent = current.next.get();
                std::cout << "getting next current" << std::endl;
                current = *(newcurrent);
                std::cout << "got next" << std::endl;
            }
            else
            {
                std::cout << "breaking" << std::endl;
                break;
            }
        }
        std::cout << std::endl;
    }

    iterator begin() { return iterator(*this); }
    iterator end() { return iterator(nullptr); }

private:
    std::unique_ptr<T> data;
    std::unique_ptr<LinkedList<T>> next;
    int mSize = 0;

}; // LinkedList

template<class T>
class LinkedListIter {
    public:
        LinkedListIter(LinkedList<T>& list_arg) : mList(list_arg) {}
        bool operator==(LinkedListIter & cmp)
        {
            return (mList == cmp.mList);
        }
        bool operator!=(LinkedListIter & cmp)
        {
            return !(this == cmp);
        }
        T & operator*() {
            // if (my_list.data)
                return *mList.data.get();
            // else
                // return *nullptr;
        }
        LinkedListIter & operator++() {
            // if (mList.next)
            // {
                mList = *mList.next.get();
                return *this;
            // }
            // else
            //     return nullptr;
        }
    private:
        LinkedList<T>& mList;
};

// template<class T>
// bool operator==(const LinkedList<T>& cmp1, const LinkedList<T>& cmp2)
// {
//     std::cout << " binary " << std::endl;
//     return cmp1.operator==(&cmp2);
// }

} // namespace
