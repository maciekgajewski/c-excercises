#include "complex_stack.hh"

void ComplexStack::push(Complex value)
{
    std::unique_ptr<ComplexStackNode> new_head = std::make_unique<ComplexStackNode>(value);
    new_head->next = std::move(this->head);
    this->head = std::move(new_head);
}

Complex ComplexStack::pop()
{
    if (!this->head) throw std::runtime_error("stack is empty");
    std::unique_ptr<ComplexStackNode> current_head = std::move(this->head);
    this->head = std::move(current_head->next);
    return current_head->value;
}

Complex ComplexStack::top() const
{
    if (!this->head) throw std::runtime_error("stack is empty");
    return this->head->value;
}