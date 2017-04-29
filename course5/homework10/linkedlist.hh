#pragma once

#include <memory>
#include <iterator>
#include <cassert>

template <typename T>
class LinkedList
{
private:
    struct Node
    {
        Node(std::unique_ptr<Node> &&next, const T& data)
            : next(std::move(next))
            , data(data)
        {}

        template <typename ...Args>
        Node(std::unique_ptr<Node> &&next, Args &&...args)
            : next(std::move(next))
            , data(std::forward<Args>(args)...)
        {}
        std::unique_ptr<Node> next;
        T data;
    };
public:
    using value_type = T;

    LinkedList() = default;

    // deep copy
    LinkedList(LinkedList &rhs)
    {
        *this = rhs;
    }

    // move
    LinkedList(LinkedList &&rhs)
        : mHead(std::move(rhs.mHead))
        , mSize(rhs.mSize)
    {
        rhs.mSize = 0;
    }

    ~LinkedList()
    {
        std::unique_ptr<Node> tmp = std::move(mHead);
        while (tmp != nullptr)
            tmp = std::move(tmp->next);
    }

     // deep copy
    LinkedList& operator=(const LinkedList &rhs)
    {
        *this = LinkedList(std::cbegin(rhs), std::cend(rhs));
        return *this;
    }

    // move
    LinkedList& operator=(LinkedList &&rhs)
    {
        if (this == &rhs)
            return *this;
        mHead = std::move(rhs.mHead);
        mSize = rhs.mSize;
        rhs.mSize = 0;
        return *this;
    }

    template<typename Iter>
    LinkedList(Iter begin_iter, Iter end_iter)
    {
        if (begin_iter == end_iter)
            return;
        mHead = std::make_unique<Node>(nullptr, *begin_iter);
        ++mSize;
        Node *tail = mHead.get();
        auto it = begin_iter;
        ++it;
        for (; it != end_iter; ++it)
        {
            tail->next = std::make_unique<Node>(nullptr, *it);
            tail = tail->next.get();
            ++mSize;
        }
    }

    template <typename NodeType, typename ValueType>
    class IteratorType : public std::iterator<std::forward_iterator_tag, ValueType>
    {
    public:
        IteratorType(NodeType *node)
            : node(node)
        {}

        bool operator==(const IteratorType &rhs)
        {
            return node == rhs.node;
        }

        bool operator!=(const IteratorType &rhs)
        {
            return !(*this == rhs);
        }

        IteratorType& operator++()
        {
            node = node->next.get();
            return *this;
        }

        IteratorType operator++(int)
        {
            IteratorType it = *this;
            ++(*this);
            return it;
        }

        ValueType& operator*()
        {
            return node->data;
        }

        const ValueType& operator*() const
        {
            return node->data;
        }
    private:
        NodeType *node;
    };

    using Iterator = IteratorType<Node, T>;
    using ConstIterator = IteratorType<const Node, const T>;

    Iterator begin()
    {
        return Iterator(mHead.get());
    }

    Iterator end()
    {
        return Iterator(nullptr);
    }

    ConstIterator begin() const
    {
        return ConstIterator(mHead.get());
    }

    ConstIterator end() const
    {
        return ConstIterator(nullptr);
    }

    ConstIterator cbegin() const
    {
        return ConstIterator(mHead.get());
    }

    ConstIterator cend() const
    {
        return ConstIterator(nullptr);
    }

    void push_front(const T &e)
    {
        mHead = std::make_unique<Node>(std::move(mHead), e);
        ++mSize;
    }

    void push_front(T &&e)
    {
        mHead = std::make_unique<Node>(std::move(mHead), e);
        ++mSize;
    }

    template <typename ...Args>
    void emplace_front(Args &&...args)
    {
        mHead = std::make_unique<Node>(std::move(mHead), std::forward<Args>(args)...);
        ++mSize;
    }

    const T& front() const
    {
        return mHead->data;
    }

    T& front()
    {
        return mHead->data;
    }

    void pop_front()
    {
        assert(mHead != nullptr);
        mHead = std::move(mHead->next);
        --mSize;
    }

    std::size_t size() const
    {
        return mSize;
    }

private:
    std::unique_ptr<Node> mHead;
    std::size_t mSize = 0;
};
