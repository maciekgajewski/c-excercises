#include <iostream>
#include <vector>


int avg(const std::vector<int>& data)
{
    int total = 0;
    for(int i : data)
        total += i;
    return total / data.size();
}

int main()
{
    std::vector<int> data = {1, 4, 5, 3, 66 ,7 ,8 };
    
    std::cout << "average=" << avg(data) <<  std::endl;
}