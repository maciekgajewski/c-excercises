#include <iostream>


struct Container
{
    int* mData;
    int* mEnd;
    
    int* begin() const { return mData; }
    int* end() const { return mEnd; }
};


void InitWithIncreasing(Container& container)
{
    int count = 0;
    for(int* i = container.mData; i != container.mEnd; i++, count++)
    {
        *i = count;
    }
}


void Print(const Container& container)
{
    //for(auto i = container.begin(); i != container.end(); i++)
    for(auto i : container)
    {
        std::cout << i << std::endl;
    }
}

int main()
{
    std::cout << "Hello, group, shal we start?" << std::endl;
    
    Container c;
    c.mData = new int[10];
    c.mEnd = c.mData + 10;
    
    InitWithIncreasing(c);
    Print(c);
}