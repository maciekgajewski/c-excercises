#include "complex_stack.hh"

void ComplexStack::push_back(Complex value)
{
    std::unique_ptr<ComplexStackNode> new_head = std::make_unique<ComplexStackNode>(value);
    new_head->next = std::move(this->head);
    this->head = std::move(new_head);
    this->element_count++;
}

void ComplexStack::pop_back()
{
    if (!this->head) throw std::runtime_error("stack is empty");
    std::unique_ptr<ComplexStackNode> current_head = std::move(this->head);
    this->head = std::move(current_head->next);
    this->element_count--;
}

Complex& ComplexStack::back() const
{
    if (!this->head) throw std::runtime_error("stack is empty");
    return this->head->value;
}