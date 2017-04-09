#pragma once

#include <memory>
#include <utility>

namespace course 
{
template<class T>
struct node
{
//public:
        node() { /*next.get() = nullptr;*/ }
        
 /*       class iterator
        {
        public:
                iterator operator++() : current(current->next), {}
        private:
                node* current;
        }*/
        T value;
        std::unique_ptr<node<T>> next;
};

template<class T>
class llist
{
private:
        std::unique_ptr<node<T>> first;
        int len = 0;
public:
        struct iterator
        {
            iterator() : node_ptr(nullptr) { }
            iterator(node<T>* ptr) : node_ptr(ptr) {}
            iterator(const iterator& other) : node_ptr(other.node_ptr) { }
            iterator(iterator&& other) : node_ptr(other.node_ptr) { }
            iterator& operator=(const iterator& other) { return other.node_ptr; }
            iterator& operator=(iterator&& other) { return other.node_ptr; }
            bool operator==(const iterator& other) { return node_ptr == other.node_ptr; }
            bool operator!=(const iterator& other) { return node_ptr != other.node_ptr; }
            iterator& operator++() 
            {
                if (node_ptr != nullptr)
                {
                    node_ptr = node_ptr->next.get();
                    return *this;
                }
                else
                {
                    throw std::range_error("End of list");
                }
            }
            T& operator*() { return node_ptr->value; }
            node<T>* node_ptr;
        };
        llist() : len(0) { first = std::make_unique<node<T>>(); }
        llist(llist&& other) : len( other.size() ) { first = std::move( other.get_first() ); }
        llist& operator=( llist&& other )
        {
            len = other.size();
            first = std::move( other.get_first() );
            return *this;
        }

        llist(const llist& other) : len( other.size() )
        {
            first = std::make_unique<node<T>>();
            node<T>* new_node = first.get();

            for( auto i = other.begin(); i != other.end(); ++i )
            {
                new_node->value = *i;
                new_node->next = std::make_unique<node<T>>();
                new_node = new_node->next.get();
            }
        }

        llist& operator=( const llist& other )
        {
            len = other.size();
            first = std::make_unique<node<T>>();
            node<T>* new_node = first.get();

            for( auto i = other.begin(); i != other.end(); ++i )
            {
                new_node->value = *i;
                new_node->next = std::make_unique<node<T>>();
                new_node = new_node->next.get();
            }
            return *this;
        }

        llist(const iterator& it1, const iterator& it2)
        {
            first = std::make_unique<node<T>>();
            len = 0;
            node<T>* new_node = first.get();

            for( auto i = it1; i != it2; ++i )
            {
                if (new_node == nullptr)
                {
                    throw std::range_error("End iterator haven't found in the path");
                } else
                {
                    len++;
                    new_node->value = *i;
                    new_node->next = std::make_unique<node<T>>();
                    new_node = new_node->next.get();
                }
            }
        }

        void push_front(const T& val)
        {
            if (len)
            {
                std::unique_ptr<node<T>> new_node = std::make_unique<node<T>>();
                new_node.get()->next = std::move(first);
                first = std::move(new_node);
            }
            first.get()->value = val;
            len++;
        }

        void pop_front()
        {
            if (len)
            {
                first = std::move(first.get()->next);
                len--;
            } else 
            {   
                throw std::range_error("List is empty");
            }
        }

        T& front() 
        { 
            if(len)
            {
                return first.get()->value;
            } else
            {
                throw std::range_error("List is empty");
            }
            
        }

        iterator begin() 
        {
             iterator it( first.get() );
             return it;
        }
        const iterator begin() const
        {
             iterator it( first.get() );
             return it;
        }
        iterator end()
        { 
             iterator it;
             return it;
        }
        const iterator end() const 
        {
            iterator it;
            return it;
        }

        std::unique_ptr<node<T>> get_first() { return first; }
        int size() const { return len; }
};
}