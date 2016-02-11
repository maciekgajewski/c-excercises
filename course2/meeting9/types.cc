#include <iostream>
#include <vector>
#include <list>

template<typename Container>
typename Container::value_type avg(const Container& data)
{
    auto total = typename Container::value_type();
    for(auto i : data)
        total += i;
    return total / data.size();
}

int main()
{
    
    
    
    
    std::vector<const int> data = {1, 4, 5, 3, 66 ,7 ,8 };
    std::vector<float> dataFloat = {1.3, 4.4, 5, 3.14, 6.6 ,7 ,8 };
    
    std::list<double> dataDouble = { 1.2, 4.5, 6.7};
    
    //std::cout << "average int=" << avg(data) <<  std::endl;
    std::cout << "average float=" << avg(dataFloat) <<  std::endl;
    std::cout << "average double=" << avg(dataDouble) <<  std::endl;
}