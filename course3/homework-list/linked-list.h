
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
        Iterator(Node* pointer) : mPointer(pointer)
        {
        }
        
        bool operator!=(const Iterator& other) 
        {
            return other.mPointer != mPointer;
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
    
    ~LinkedList()
    {        
        Node* current = mHead;
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
        
        auto current = mHead;
        while(current != nullptr)
        {
            current = current->Next;
            ++size;
        }
        
        return size;
    }

    bool empty() const
    {
        return mHead == nullptr;
    }
    
    void push_front(const TNode& data)
    {
        if(empty())
        {
            mHead = new Node(data, nullptr);
        }
        else
        {
           mHead = new Node(data, mHead);
        }
    }
    
    void pop_front()
    {
        if(empty())
            return;
  
        auto tmp = mHead;
        mHead = mHead->Next;
        delete tmp;
    }
    
//     const TNode& front() const
//     {
//     }
//         
//     TNode& front()
//     {
//     }
//     
//     void erase(Iterator itemToRemove)
//     {
//     }
//     
        
private:
    Node* mHead;
};
