
#include <cstddef>
#include <memory>

template <typename TContent>
class LinkedList
{
    struct Node
    {
        friend class LinkedList<TContent>;

        Node(const TContent& data) : mData(data), mNext()
        {
        }

        Node(const TContent& data, std::unique_ptr<Node>&& next) : mData(data), mNext(std::move(next))
        {
        }

        Node(TContent&& data, std::unique_ptr<Node>&& next) : mData(std::move(data)), mNext(std::move(next))
        {
        }

      private:

        const TContent& data() const
        {
            return mData;
        }

        TContent& data()
        {
            return mData;
        }

        Node* next()
        {
            return mNext.get();
        }

        Node* insert_after(const TContent& data)
        {
            mNext = std::move(std::make_unique<Node>(data, std::move(mNext)));

            return mNext.get();
        }

        void eraseNext()
        {
            auto& tmp = mNext;
            mNext = std::move(mNext->mNext);
        }

        std::unique_ptr<Node>&& remove()
        {
            return std::move(mNext);
        }

        TContent mData;
        std::unique_ptr<Node> mNext;
    };

    struct Iterator
    {
        friend class LinkedList<TContent>;

        Iterator() : mPointer(nullptr)
        {
        }

        Iterator(const std::unique_ptr<Node>& node) : mPointer(node.get())
        {
        }

        bool operator!=(const Iterator& that)
        {
            return that.mPointer != mPointer;
        }

        const TContent& operator*()
        {
            return mPointer->data();
        }

        Iterator& operator++()
        {
            mPointer = mPointer->next();
            return *this;
        }

        operator bool()
        {
            return mPointer != nullptr;
        }

      private:

        bool operator!=(Node * that)
        {
            return mPointer != that;
        }

        Node* mPointer;
    };

  public:

    LinkedList() = default;

    LinkedList(const LinkedList& that)
    {
        if (!that.empty())
        {
            mHead = std::make_unique<Node>(that.mHead->data());

            auto current = mHead.get();

            for (auto thatCurrent = that.mHead->next(); thatCurrent; thatCurrent = thatCurrent->next())
            {
                current = current->insert_after(thatCurrent->data());
            }
        }
    }

    LinkedList(LinkedList&& that)
    {
        mHead = std::move(that.mHead);
    }

    const Iterator begin() const
    {
        return Iterator(mHead);
    }

    const Iterator end() const
    {
        // TODO: Since this never changes, can we have a single instance shared by all lists?
        return Iterator();
    }

    std::size_t size() const
    {
        int size = 0;

        for (auto current = mHead.get(); current; current = current->next())
            ++size;

        return size;
    }

    bool empty() const
    {
        return !mHead;
    }

    void push_front(const TContent& data)
    {
        mHead = std::move(std::make_unique<Node>(data, std::move(mHead)));
    }

    void push_front(TContent&& data)
    {
        mHead = std::move(std::make_unique<Node>(std::move(data), std::move(mHead)));
    }

    void pop_front()
    {
        mHead = std::move(mHead->remove());
    }

    const TContent& front() const
    {
        const std::unique_ptr<Node>& constHead = mHead; // Not sure if this is needed, it feels like it should be
        return mHead->data();
    }

    TContent& front()
    {
        return mHead->data();
    }

    void erase(Iterator itemToRemove)
    {
        if (!itemToRemove)
            return;

        Node* current = mHead.get();
        Node* previous = nullptr;

        while (current && itemToRemove != current)
        {
            previous = current;
            current = current->next();
        }

        if (!previous)
            pop_front();
        else
            previous->eraseNext();
    }

  private:
    std::unique_ptr<Node> mHead;
};