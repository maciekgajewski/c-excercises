
#include <cstddef>

template <typename TNode>
class LinkedList
{
public:
    
    struct Iterator
    {
    };
    
//     const Iterator begin() const
//     {
//     }
//     
//     const Iterator end() const
//     {
//     }
    
    std::size_t size() const 
    {
        return 0;
    }

    bool empty() const
    {
        return true;
    }
    
    void push_front(const TNode&)
    {
    }
    
    void pop_front()
    {
    }
    
//     const TNode& front() const
//     {
//     }
//         
//     TNode& front()
//     {
//     }
//     
    void erase(Iterator itemToRemove)
    {
    }
    
        
private:
    TNode* mHead;
    TNode* mTail;
};
