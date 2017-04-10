#include <iostream>

#include "linked_list.h"

int main(int, char**)
{
	jds::LinkedList<int> list;
	list.push_front(1);
	list.push_front(4);
	for (jds::LinkedList<int>::iterator it = list.begin(); it != list.end(); ++it)
	{
		std::cout << "Next element: " << *it << std::endl;
	}
	return 0;
}
