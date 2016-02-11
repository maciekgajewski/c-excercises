#include <iostream>
#include <vector>
#include <list>
//#include <algorithm>


void print(int i)
{
    std::cout << "i=" << i << std::endl;
}
void print2(int i, std::string s)
{
    std::cout << "i=" << i << ", s=" << s << std::endl;
}

struct Printer
{
    std::string boundS;
    void operator() (int i) { print2(i, boundS); }
};

struct Counter
{
    int& total;
    void operator() (int i) { total += i;}
};

template <typename it, typename action>
void for_each(it begin, it end, action act)
{
   for(it i=begin; i != end; ++i)
   {
      act(*i);   
   }
}

int main()
{
    std::vector<int> data = {1, 2, 3, 5, 7, 8};
    
    for_each(data.begin(), data.end(),
                    &print);
    
    Printer p{"hello"};
    
    for_each(data.begin(), data.end(),
                    p);

    int t = 0;
    Counter c{t};
    for_each(data.begin(), data.end(),
                    c);
    std::cout << "t=" << t << std::endl;
    
    std::cout << "total=" << c.total << std::endl;
 
    int total = 0;
    auto lambda = [&total](int i) { total += i; };
    for_each(data.begin(), data.end(),
            lambda);
    
    std::cout << "total from lambda=" << total << std::endl;
    
}