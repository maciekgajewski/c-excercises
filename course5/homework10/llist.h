#pragma once
#include <memory>
#include <utility>
#include <iostream>

namespace course 
{
template<class T>
class llist
{
private:
        struct node
        {
                node() { }
                T value;
                std::unique_ptr<node> next;
        };
        std::unique_ptr<node> first;
        int len = 0;
public:
 /*       struct iterator
        {
            iterator() : node_ptr(nullptr) { }
            iterator(node* ptr) : node_ptr(ptr) {}
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
            node* node_ptr;
        };*/
        template<class P, class Q>
        struct iterator_class
        {
            iterator_class() : node_ptr(nullptr) { }
            iterator_class(node* ptr) : node_ptr(ptr) {}
            iterator_class(const iterator_class& other) : node_ptr(other.node_ptr) { }
            iterator_class(iterator_class&& other) : node_ptr(other.node_ptr) { }
            iterator_class& operator=(const iterator_class& other) { return other.node_ptr; }
            iterator_class& operator=(iterator_class&& other) { return other.node_ptr; }
            bool operator==(const iterator_class& other) { return node_ptr == other.node_ptr; }
            bool operator!=(const iterator_class& other) { return node_ptr != other.node_ptr; }
            iterator_class& operator++() 
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
            Q& operator*() { return node_ptr->value; }
            P node_ptr;
        };
        using iterator = iterator_class<node*, T>;
        using const_iterator = iterator_class<const node*, const T>;

        llist() : len(0) {}
        llist(llist&& other) : len( other.size() ) { first = std::move( other.first ); }
        llist& operator=( llist&& other )
        {
            len = other.size();
            first = std::move( other.first );
            return *this;
        }


        llist(const llist& other) : len( other.size() )
        {
            first = std::make_unique<node>();
            node* new_node = first.get();

            for( auto i = other.begin(); i != other.end(); ++i )
            {
                new_node->value = *i;
                new_node->next = std::make_unique<node>();
                new_node = new_node->next.get();
            }
        }

        llist& operator=( const llist& other )
        {
            len = other.size();
            first = std::make_unique<node>();
            node* new_node = first.get();

            for( auto i = other.begin(); i != other.end(); ++i )
            {
                new_node->value = *i;
                new_node->next = std::make_unique<node>();
                new_node = new_node->next.get();
            }
            return *this;
        }

        template<typename Q>
        llist(const Q& it1, const Q& it2)
        {
            first = std::make_unique<node>();
            len = 0;
            node* new_node = first.get();

            for( auto i = it1; i != it2; ++i )
            {
                if (new_node == nullptr)
                {
                    throw std::range_error("End iterator haven't found in the path");
                } else
                {
                    len++;
                    new_node->value = *i;
                    new_node->next = std::make_unique<node>();
                    new_node = new_node->next.get();
                }
            }
        }

        void push_front(const T& val)
        {
            std::unique_ptr<node> new_node = std::make_unique<node>();
            new_node.get()->next = std::move(first);
            first = std::move(new_node);
            first.get()->value = val;
            len++;
        }

        void push_front(T&& val)
        {
            std::unique_ptr<node> new_node = std::make_unique<node>();
            new_node.get()->next = std::move(first);
            first = std::move(new_node);
            first.get()->value = std::move(val);
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

        iterator begin() { return iterator( first.get() ); }
        const_iterator begin() const{ return const_iterator(first.get() ); }
        iterator end() { return iterator(); }
        const_iterator end() const {  return const_iterator(); }

        int size() const { return len; }
};
}