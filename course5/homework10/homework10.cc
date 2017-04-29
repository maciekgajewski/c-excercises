#include "linkedlist.hh"

#include <list>
#include <vector>
#include <string>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <sstream>

class NonCopyAble
{
public:
    explicit NonCopyAble(const std::string &str) : str(str) {}
    NonCopyAble() = delete;
    NonCopyAble(const NonCopyAble &) = delete;
    NonCopyAble& operator=(const NonCopyAble &) = delete;

    NonCopyAble(NonCopyAble &&) = default;
    NonCopyAble& operator=(NonCopyAble &&) = default;

    bool operator==(const NonCopyAble &rhs) const { return str == rhs.str; }

    std::string str;
};

int main()
{
    {
        std::list<int> list;
        LinkedList<int> mylist;
        for (int i=0; i<10; ++i)
        {
            list.push_front(i);
            mylist.push_front(i);
            assert(list.size() == mylist.size());
            assert(std::equal(list.begin(), list.end(), mylist.begin()));
        }
    }
    {
        using Data = std::tuple<std::string, int>;
        std::list<Data> list;
        LinkedList<Data> mylist;
        for (int i=0; i<10; ++i)
        {
            list.push_front(Data("mokus"+std::to_string(i), i));
            mylist.push_front(Data("mokus"+std::to_string(i), i));
            assert(list.size() == mylist.size());
            assert(std::equal(list.begin(), list.end(), mylist.begin()));
        }
    }
    {
        using Data = std::tuple<std::string, int>;
        std::list<Data> list;
        LinkedList<Data> mylist;
        for (int i=0; i<10; ++i)
        {
            list.emplace_front("mokus"+std::to_string(i), i);
            mylist.emplace_front("mokus"+std::to_string(i), i);
            assert(list.front() == mylist.front());
            assert(list.size() == mylist.size());
            assert(std::equal(list.begin(), list.end(), mylist.begin()));
        }
    }
    {
        using Data = std::tuple<std::string, int>;
        std::list<Data> list;
        LinkedList<Data> mylist;
        for (int i=0; i<10; ++i)
        {
            list.push_front(Data("mokus"+std::to_string(i), i));
            mylist.push_front(Data("mokus"+std::to_string(i), i));
            assert(list.front() == mylist.front());
            assert(list.size() == mylist.size());
            assert(std::equal(list.begin(), list.end(), mylist.begin()));
        }
    }
    {
        LinkedList<int> l;
        for (int i=0; i<10; ++i)
            l.push_front(i);
        std::list<int> list(std::begin(l), std::end(l));
        LinkedList<int> mylist(std::begin(l), std::end(l));
        assert(list.size() == mylist.size());
        assert(std::equal(list.begin(), list.end(), mylist.begin()));
    }
    {
        LinkedList<int> list;
        for (int i=0; i<10; ++i)
            list.push_front(i);
        LinkedList<int> mylist = list;
        assert(list.size() == mylist.size());
        assert(std::equal(list.begin(), list.end(), mylist.begin()));
    }
    {
        LinkedList<int> l;
        std::list<int> list(std::begin(l), std::end(l));
        LinkedList<int> mylist(std::begin(l), std::end(l));
        assert(list.size() == mylist.size());
        assert(std::equal(list.begin(), list.end(), mylist.begin()));
    }
    {
        std::list<int> ref;
        LinkedList<int> list;
        for (int i=0; i<10; ++i)
        {
            ref.push_front(i);
            list.push_front(i);
        }
        LinkedList<int> mylist = std::move(list);
        assert(ref.size() == mylist.size());
        assert(std::equal(ref.begin(), ref.end(), mylist.begin()));
    }
    {
        std::list<int> list;
        LinkedList<int> mylist;
        for (int i=0; i<10; ++i)
        {
            list.push_front(i);
            mylist.push_front(i);
        }
        for (int i=0; i<10; ++i)
        {
            assert(list.front() == mylist.front());
            list.pop_front();
            mylist.pop_front();
            assert(list.size() == mylist.size());
            assert(std::equal(list.begin(), list.end(), mylist.begin()));
        }
    }
    {
        std::list<int> ref;
        LinkedList<int> list;
        for (int i=0; i<10; ++i)
        {
            ref.push_front(i);
            list.push_front(i);
        }
        auto it_ref = ref.cbegin();
        auto it_list = list.cbegin();
        while (it_list != list.cend())
        {
            assert(*(it_ref++) == *(it_list++));
            if (it_ref != ref.end())
                assert(*it_ref == *it_list);
        }
    }

    {
        std::list<int> ref;
        LinkedList<int> list;
        for (int i=0; i<10; ++i)
        {
            ref.push_front(i);
            list.push_front(i);
        }

        {
            std::ostringstream o_ref;
            std::ostringstream o_list;
            std::for_each(ref.begin(), ref.end(), [&o_ref](int i) { o_ref << i << ", "; });
            std::for_each(list.begin(), list.end(), [&o_list](int i) { o_list << i << ", "; });
            assert(o_ref.str() == o_list.str());
        }

        {
            std::vector<int> v_ref;
            std::vector<int> v_list;
            std::copy(ref.begin(), ref.end(), std::back_inserter(v_ref));
            std::copy(list.begin(), list.end(), std::back_inserter(v_list));
            assert(std::equal(v_ref.begin(), v_ref.end(), v_list.begin()));
        }

        {
            std::list<int> v_ref;
            LinkedList<int> v_list;
            std::transform(ref.begin(), ref.end(), std::front_inserter(v_ref), [](auto i) { return i+10; });
            std::transform(list.begin(), list.end(), std::front_inserter(v_list), [](auto i) { return i+10; });
            assert(std::equal(v_ref.begin(), v_ref.end(), v_list.begin()));
        }
    }
    {
        std::list<int> ref;
        LinkedList<int> list;
        for (int i=0; i<10; ++i)
        {
            ref.push_front(0);
            list.push_front(0);
        }
        int n = 100;
        std::generate(ref.begin(), ref.end(), [&n]{ return ++n; });
        n = 100;
        std::generate(list.begin(), list.end(), [&n]{ return ++n; });
        assert(std::equal(ref.begin(), ref.end(), list.begin()));
    }
    {
        LinkedList<int> l1;
        for (int i=0; i<10; ++i)
            l1.push_front(i);
        assert(!std::is_sorted(l1.begin(), l1.end()));
        LinkedList<int> l2;
        for (int i=10; i>0; --i)
            l2.push_front(i);
        assert(std::is_sorted(l2.begin(), l2.end()));
    }
    {
        std::list<NonCopyAble> l1;
        LinkedList<NonCopyAble> l2;
        LinkedList<NonCopyAble> l3;
        for (int i=0; i<10; ++i)
        {
            l1.emplace_front("Test"+std::to_string(i));
            NonCopyAble tmp("Test"+std::to_string(i));
            l2.push_front(std::move(tmp));
            l3.push_front(NonCopyAble("Test"+std::to_string(i)));
        }
        assert(std::equal(l1.begin(), l1.end(), l2.begin()));
        assert(l2.front().str == l1.front().str);

        LinkedList<NonCopyAble> l5 = std::move(l2);
        //LinkedList<NonCopyAble> l6 = l2; // non-copyable
        assert(std::equal(l1.begin(), l1.end(), l5.begin()));

        LinkedList<NonCopyAble> l7;
        l7 = std::move(l3);
        //LinkedList<NonCopyAble> l8;
        //l8 = l2; // non-copyable
        assert(std::equal(l1.begin(), l1.end(), l7.begin()));
    }
    {
        LinkedList<int> l;
        for (int i=1; i<=5; ++i)
            l.push_front(i);
        assert(2*3*4*5 == std::accumulate(l.begin(), l.end(), 1, [](auto lhs, auto rhs){ return lhs*rhs; }));
    }
}
