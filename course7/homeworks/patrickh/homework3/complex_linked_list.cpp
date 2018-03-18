#include "complex_linked_list.h"

void ComplexLinkedList::pop_back()
{
    if (this->empty())
        throw std::runtime_error("List is empty");

    std::unique_ptr<ComplexLinkedListNode> current = std::move(this->head);
    this->head = std::move(current->next);
    this->nr_elements--;
}

void ComplexLinkedList::push_back(const Complex& complex)
{
    std::unique_ptr<ComplexLinkedListNode> current = std::make_unique<ComplexLinkedListNode>(complex);
    current->next = std::move(this->head);
    this->head = std::move(current);
    this->nr_elements++;
}

Complex& ComplexLinkedList::back() const
{
    if (this->empty())
        throw std::runtime_error("List is empty");
    return this->head->value;
}
