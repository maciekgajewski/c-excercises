#include "complex_linked_list.h"

void ComplexLinkedList::pop_back()
{
    if (this->empty())
        throw std::runtime_error("List is empty");

    std::unique_ptr<ComplexLinkedListNode> current_head = std::move(this->head);
    this->head = std::move(current_head->next);
    this->nr_elements--;
}

void ComplexLinkedList::push_back(const Complex& complex)
{
    std::unique_ptr<ComplexLinkedListNode> new_head = std::make_unique<ComplexLinkedListNode>(complex);
    new_head->next = std::move(this->head);
    this->head = std::move(new_head);
    this->nr_elements++;
}

void ComplexLinkedList::clear()
{
    if (this->empty())
        throw std::runtime_error("List is empty");
    this->head = std::move(nullptr);
    this->nr_elements = 0;
}

Complex ComplexLinkedList::back()
{
    if (this->empty())
        throw std::runtime_error("List is empty");
    return this->head->value;
}
