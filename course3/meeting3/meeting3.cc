#include <iostream>

class Array
{
private:
    int mData[3];
public:
    
    int& operator[](int index) {
        std::cout<< "non const" << std::endl;
        return mData[index];
    }
    int operator[](int index) const {
        std::cout<< "const" << std::endl;
        return mData[index];
    }
};

int main()
{
    Array a;
    const Array& cr = a;
    
    a[1] = 5;
    cr[2] = 5;
    std::cout << a[1] << std::endl;
    std::cout << cr[1] << std::endl;
}

