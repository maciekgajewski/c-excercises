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
		T value;
		std::unique_ptr<Node> next{nullptr};

		Node() = default;
		Node(Node const &) = delete;
		Node(Node &&) = delete;
		Node(T const & initial_value): value(initial_value) { }
		Node(T && initial_value): value(initial_value) { }
		Node & operator=(Node const &) = delete;
		Node & operator=(Node &&) = delete;
	};

	std::unique_ptr<Node> head{nullptr};
public:
	class iterator: public std::forward_iterator_tag {
	public:
		iterator() = default;
		iterator(Node * initial): current(initial) { }
		iterator(iterator const & that) = default;
		iterator & operator=(iterator const & that) { this->current = that.current; return *this; }
		iterator & operator++() {
			current = current->next.get();
			return *this;
		}
		iterator operator++(int) {
			iterator old = *this;
			current = current->next.get();
			return old;
		}
		T & operator*() const { return current->value; }
		bool operator==(iterator const & that) const { return this->current == that.current; }
		bool operator!=(iterator const & that) const { return this->current != that.current; }
	private:
		Node * current{nullptr};
	};

	class const_iterator: public std::forward_iterator_tag {
	public:
		const_iterator() = default;
		const_iterator(const_iterator const & that) = default;
		const_iterator & operator=(const_iterator const & that) { this->current = that.current; return *this; }
		const_iterator(Node const * initial): current(initial) { }
		const_iterator & operator++() {
			current = current->next.get();
			return *this;
		}
		const_iterator operator++(int) {
			const_iterator old = *this;
			current = current->next.get();
			return old;
		}
		T const & operator*() const { return current->value; }
		bool operator==(const_iterator const & that) const { return this->current == that.current; }
		bool operator!=(const_iterator const & that) const { return this->current != that.current; }
	private:
		Node const * current{nullptr};
	};

	LinkedList() = default;
	LinkedList(LinkedList const & that): LinkedList(that.begin(), that.end()) { }
	LinkedList(LinkedList && that): head(std::move(that.head)) { }

	template <class InputIt>
	LinkedList(InputIt const & first, InputIt const & last)
	{
		std::unique_ptr<Node> * current{&head};
		for (auto it = first; it != last; ++it)
		{
			*current = std::make_unique<Node>(*it);
			current = &((*current)->next);
		}
	}

	LinkedList & operator=(LinkedList const & that)
	{
		this->head = nullptr;
		std::unique_ptr<Node> * current{&head};
		for (auto it = that.begin(); it != that.end(); ++it)
		{
			*current = std::make_unique<Node>(*it);
			current = &((*current)->next);
		}
		return *this;
	}
		
	LinkedList & operator=(LinkedList && that) { this->head = std::move(that.head); return *this; }

	bool operator==(LinkedList const & that) const
	{
		auto itl = begin(), itr = that.begin();
		for (; itl != end() && itr != that.end(); ++itl, ++itr)
		{
			if (*itl != *itr)
				return false;
		}
		return itl == end() && itr == that.end();
	}
	bool operator!=(LinkedList const & that) const { return !(*this == that); }

	LinkedList::iterator begin() { return iterator(head.get()); }
	LinkedList::const_iterator begin() const { return const_iterator(head.get()); }
	LinkedList::iterator end() { return iterator(nullptr); }
	LinkedList::const_iterator end() const { return const_iterator(nullptr); }

	void push_front(T const & element)
	{
		std::unique_ptr<LinkedList<T>::Node> newNode = std::make_unique<LinkedList<T>::Node>(element);
		newNode->next = std::move(head);
		head = std::move(newNode);
	}
	void push_front(T && element)
	{
		std::unique_ptr<LinkedList<T>::Node> newNode = std::make_unique<LinkedList<T>::Node>(element);
		newNode->next = std::move(head);
		head = std::move(newNode);
	}

	template <class... Args>
	void emplace_front(Args&& ... args)
	{
		std::unique_ptr<LinkedList<T>::Node> newNode = std::make_unique<LinkedList<T>::Node>(T(std::forward<Args>(args)...));
		newNode->next = std::move(head);
		head = std::move(newNode);
	}

	void pop_front() { if (head) head = std::move(head->next); }
	T & front() const { return head->value; }
	std::size_t size()
	{
		std::size_t result{0};
		for (auto it = begin(); it != end(); ++it)
			++result;
		return result;
	}
		
};

}
