
#include <cstddef>

template <typename TNode>
class LinkedList
{
    struct Node 
    {
        Node(const TNode& data, Node* next) : Data(data), Next(next)
        {
        }
        const TNode& Data;
        Node* Next;
    };
    
    struct Iterator
    {
        friend struct LinkedList<TNode>;
        
        Iterator(Node* pointer) : mPointer(pointer)
        {
        }
        
        bool operator!=(const Iterator& that) 
        {
            return that.mPointer != mPointer;
        }
        
        const TNode& operator*() 
        {
            return mPointer->Data;
        }
        
        void operator++() 
        {
            mPointer = mPointer->Next;
        }
        
    private:
        Node* mPointer;
    };
    
public:
        
    LinkedList()
    {
        mHead = nullptr;
    }
    
    LinkedList(const LinkedList& that)
    {   
        if(that.empty())
        {
            mHead = nullptr;  
        }
        else
        {
            mHead = new Node(that.mHead->Data, nullptr);            
            auto current =  mHead;
            
            for(auto thatCurrent= that.mHead->Next; thatCurrent != nullptr; thatCurrent = thatCurrent->Next)
            {
                current->Next = new Node(thatCurrent->Data, nullptr);
                current = current->Next;
            }
        }           
    }
    
    LinkedList(LinkedList&& that)
    {
        mHead = that.mHead;
        that.mHead = nullptr;        
    }
    
    ~LinkedList()
    {        
        auto current = mHead;
        while(current != nullptr)
        {
            auto tmp = current;
            current = current->Next;
            delete tmp;
        }
    }
    
    const Iterator begin() const
    {
        return Iterator(mHead);
    }
    
    const Iterator end() const
    {
        return Iterator(nullptr);
    }
    
    std::size_t size() const 
    {
        int size = 0;
        
        for(auto current = mHead; current != nullptr; current = current->Next)
            ++size;
        
        return size;
    }

    bool empty() const
    {
        return mHead == nullptr;
    }
    
    void push_front(const TNode& data)
    {
        mHead = new Node(data, mHead);
    }
    
    void pop_front()
    {
        if(empty())
            return; // TODO: Maybe this should just throw?
  
        auto tmp = mHead;
        mHead = mHead->Next;
        delete tmp;
    }
    
    const TNode& front() const
    {
        // TODO: What is the correct response to calling front() on an empty list?
        
        return mHead->Data;
    }

    void erase(Iterator itemToRemove)
    {
        if(itemToRemove.mPointer == nullptr)
            return;
        
        auto current = mHead;
        Node* previous = nullptr;
        
        while(current != nullptr && current != itemToRemove.mPointer)
        {
            previous = current;
            current = current->Next;            
        }
        
        if(previous == nullptr)
        {
            auto tmp = mHead;
            mHead = mHead->Next;
            delete tmp;
        }
        else
        {   
            auto tmp = previous->Next;
            previous->Next = current->Next;
            if(tmp != nullptr)
                delete tmp;            
        }
    }     
        
private:
    Node* mHead;
};
