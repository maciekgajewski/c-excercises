
#include "list.h"

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <iterator>


int main()
{
	{
		List::List<int> l;
		l.emplace_front(2);
		l.emplace_front(4);

		assert(l.size() == 2);
		assert(l.mFirstNode->mObj == 4);
		assert(l.mFirstNode->mNextNode->mObj == 2);
	}

	{
		List::List<std::string> l;
		l.emplace_front("abc");
		l.emplace_front("def");

		assert(l.size() == 2);

		List::List<std::string> newList = l;

		auto origIter = l.begin();
		for (auto& val : newList)
		{
			assert(val == *origIter);
			++origIter;
		}
	}

	{
		List::List<std::string> l;
		l.push_front("abc");
		l.push_front("def");

		assert(l.size() == 2);
		assert(l.mFirstNode->mObj == "def");
		assert(l.mFirstNode->mNextNode->mObj == "abc");
	}

	{
		List::List<std::string> l;
		std::string abc = "abc";
		std::string def = "def";
		l.push_front(abc);
		l.push_front(def);

		assert(l.size() == 2);
		assert(l.mFirstNode->mObj == "def");
		assert(l.mFirstNode->mNextNode->mObj == "abc");
	}

	{
		std::vector<std::string> v = { "abc", "def", "ghi" };
		List::List<std::string> l;

		for (auto& elem : v)
			l.push_front(elem);

		int i = v.size();
		for (auto& node : l)
		{
			--i;
			assert(v[i] == node);
		}
	}

	{
		std::vector<std::string> v = { "abc", "def", "ghi" };
		List::List<std::string> l;

		for (auto& elem : v)
			l.push_front(elem);

		auto itr = std::find(l.begin(), l.end(), "ghi");
		assert(*itr == "ghi");
	}

	{
		std::vector<std::string> v = { "abc", "def", "ghi" };
		List::List<std::string> l;

		for (auto& elem : v)
			l.push_front(elem);

		auto itr = l.begin();
		assert(*itr == "ghi");
		std::advance(itr, 2);
		assert(*itr == "abc");
	}

	{
		std::vector<std::string> v = { "abc", "def", "ghi" };
		List::List<std::string> l;

		for (auto& elem : v)
			l.push_front(elem);

		std::vector<std::string> newV;
		newV.resize(l.size());
		std::copy(l.begin(), l.end(), newV.begin());

		int i = newV.size();
		for (auto& elem : v)
		{
			--i;
			assert(newV[i] == elem);
		}
	}
}
