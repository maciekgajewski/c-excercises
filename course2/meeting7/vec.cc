#include <iostream>


template<typename Tag>
class Id
{
public:
    Id(int i) : mId(i) {}
    bool operator==(Id o) const { return mId == o.mId; }
    
private:
    int mId;
};

template<typename ValueType>
class Vec
{
public:
        Vec operator+ (const Vec&) const;
	bool operator == (const Vec& o) const
	{
		return x == o.x && y == o.y;
	}


	ValueType x;
	ValueType y;
};

template<typename T>
Vec<T> Vec<T>::operator + (const Vec<T>& o) const
{
        return Vec<T>{x + o.x, y + o.y};
}


struct script_id_tag {};
using ScriptId = Id<script_id_tag>;

struct rit {};
using RuleId = Id<rit>;

int main()
{
	Vec<int> v = Vec<int>{1,1} + Vec<int>{4,5};
	auto v4 = Vec<double>{1,1} + Vec<double>{4,5};

        Vec<double> v2{10, 12};
        
	std::cout << "v=" << v.x << "," << v.y  << std::endl;
//        auto v3 = v2 + v;

    RuleId ri = 7;
    ScriptId sid = 7;
    //bool eq = ri == sid;
        
}
