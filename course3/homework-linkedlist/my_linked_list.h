#include <cstdlib>
#include <memory>

class MyLinkedList {
	struct Node {
		int data;
		std::unique_ptr<Node> next;
		Node(const int& value) : data(value), next(nullptr) {}
	};

	public:
		std::size_t size() const;
		bool empty() const;
		MyLinkedList();
		void push_front(const int&);
		void pop_front();

	private:
		std::size_t numNodes;
		std::unique_ptr<Node> mHead;
};
