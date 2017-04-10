#pragma once

#include <iterator>
#include <memory>

namespace jds {

template <typename T>
class LinkedList
{
private:
	struct Node
	{
		std::unique_ptr<T> value{nullptr};
		std::unique_ptr<Node> next{nullptr};
	};

	std::unique_ptr<Node> head{nullptr};
public:
	class iterator {
	public:
		iterator() = default;
		iterator(Node * initial): current(initial) { }
		iterator(iterator const & that) = default;
		iterator & operator++() {
			current = current->next.get();
			return *this;
		}
		iterator operator++(int) {
			iterator old = *this;
			current = current->next.get();
			return old;
		}
		T & operator*() const { return *(current->value); }
		bool operator==(iterator const & that) const { return this->current == that.current; }
		bool operator!=(iterator const & that) const { return this->current != that.current; }
	private:
		LinkedList<T>::Node * current{nullptr};
	};
	class const_iterator {
	public:
		const_iterator() = default;
		const_iterator(const_iterator const & that) = default;
		const_iterator(Node const * initial): current(initial) { }
		const_iterator operator++(int) {
			const_iterator old = *this;
			current = current->next.get();
			return old;
		}
		T & operator*() const { return *(current->value); }
		bool operator==(const_iterator const & that) const { return this->current == that.current; }
		bool operator!=(const_iterator const & that) const { return this->current != that.current; }
	private:
		Node const * current{nullptr};
	};

	LinkedList() = default;
	LinkedList(LinkedList const & that) { *(this->value) = *(that.value); *(this->next) = *(that.next); }
	LinkedList(LinkedList && that) { this->value = std::move(that.value); this->next = std::move(that.next); }
	LinkedList(iterator const & first, iterator const & last)
	{
		std::unique_ptr<Node> * current = &head;
		for(auto it = first; it != last; it++)
		{
			*current = std::make_unique<Node>();
			(*current)->value = std::make_unique<T>(*it);
			current = &(head->next);
		}
	}
	void operator=(LinkedList const & that) { *(this->value) = *(that.value); *(this->next) = *(that.next); }
	void operator=(LinkedList && that) { this->value = std::move(that.value); this->next = std::move(that.next); }
	//LinkedList operator+(LinkedList const & that) const;
	//LinkedList& operator+=(LinkedList const & that);
	bool operator==(LinkedList const & that) const { return this->value == nullptr && that.value == nullptr || this->value == that.value && *(this->next) == *(that.next); }
	//bool operator!=(LinkedList const & that) const;
	LinkedList::iterator begin() { return iterator(head.get()); }
	LinkedList::const_iterator begin() const { const_iterator(head.get()); }
	LinkedList::iterator end() { return iterator(nullptr); }
	LinkedList::const_iterator end() const { return const_iterator(nullptr); }
	void push_front(T const & element)
	{
		std::unique_ptr<LinkedList<T>::Node> newNode = std::make_unique<LinkedList<T>::Node>();
		newNode->value = std::make_unique<T>(element);
		newNode->next = std::move(head);
		head = std::move(newNode);
	}

	//template <typename... Args> LinkedList & emplace(Args&& ... args);
};

}
