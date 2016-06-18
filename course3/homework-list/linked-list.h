
#include <cstddef>
#include <memory>

template <typename TElement>
class LinkedList
{
    struct Node
    {
        Node(const TElement& data) : mData(data), mNext()
        {
        }

        Node(const TElement& data, std::unique_ptr<Node>&& next) : mData(data), mNext(std::move(next))
        {
        }

        Node(TElement&& data, std::unique_ptr<Node>&& next) : mData(std::move(data)), mNext(std::move(next))
        {
        }

        const TElement& data() const
        {
            return mData;
        }

        TElement& data()
        {
            return mData;
        }

        Node* next()
        {
            return mNext.get();
        }

        Node* insert_after(const TElement& data)
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
        
      private:
        TElement mData;
        std::unique_ptr<Node> mNext;
    };

    struct Iterator
    {
        using value_type = TElement;
        using pointer = TElement*;
        using reference = TElement&;
        using difference_type = size_t;
        using iterator_category = std::forward_iterator_tag;

        Iterator() : mPointer(nullptr)
        {
        }

        Iterator(const Iterator& other) : mPointer(other.mPointer)
        {
        }

        Iterator(const std::unique_ptr<Node>& node) : mPointer(node.get())
        {
        }

        bool operator!=(const Iterator& that)
        {
            return that.mPointer != mPointer;
        }
        
        bool operator==(const Iterator& that)
        {
            return that.mPointer == mPointer;
        }
                
        const TElement& operator*()
        {
            return mPointer->data();
        }

        Iterator& operator++()
        {
            mPointer = mPointer->next();
            return *this;
        }

        Iterator operator++ (int)
        {
            // FIXME: wrong order
            return Iterator(mPointer->next());
        }

        operator bool()
        {
            return mPointer != nullptr;
        }

        bool operator!=(Node* that)
        {
            return mPointer != that;
        }
        
    private:
        
        Node* mPointer;
    };

public:
    using value_type = TElement;

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

    LinkedList(std::initializer_list<TElement> args)
    {
        if (args.size() > 0)
        {
            auto start = args.begin();            
            mHead = std::make_unique<Node>(*start);

            auto current = mHead.get();

            auto stop = args.end();
            for (auto next = start + 1; next != stop; ++next)
                current = current->insert_after(*next);
        }
    }

    LinkedList(LinkedList&& that)
    {
        mHead = std::move(that.mHead);
    }

    Iterator begin() const
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
    
    void push_front(const TElement& data)
    {
        mHead = std::move(std::make_unique<Node>(data, std::move(mHead)));
    }

    void push_front(TElement&& data)
    {
        mHead = std::move(std::make_unique<Node>(std::move(data), std::move(mHead)));
    }

    void pop_front()
    {
        mHead = std::move(mHead->remove());
    }

    const TElement& front() const
    {
        return mHead->data();
    }

    TElement& front()
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

 
 
 
 
 
