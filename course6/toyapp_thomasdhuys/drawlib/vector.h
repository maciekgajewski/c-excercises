#pragma once

#include <cassert>
#include <iostream>
#include <array>

namespace Draw {

template<size_t X, typename T>
class VectorXD {
public:
    VectorXD() {}
    VectorXD(VectorXD<X-1,T> v, T e)
    {
       std::copy(v.begin(), v.end(), this->begin());
       data[X-1] = e;
    }
    VectorXD(std::initializer_list<T> il)
    {
        //assert(args.size() == X); //, "Incorrect number of arguments");
        std::copy(il.begin(), il.end(), data.begin());
    }

	T& operator[](std::size_t index) {return data.at(index);}
	const T& operator[](std::size_t index) const {return data.at(index);}

    auto begin() {return data.begin();}
    auto end()   {return data.end();}

protected:
    std::array<T, X> data;
};

template<size_t X, typename T>
std::ostream& operator<<(std::ostream& s , const VectorXD<X,T>& v)
{
	s << "(";
    for(int i=0; i<X-1; ++i)
    {
        s  << v[i] << ",";
    }
    s << v[X-1] << ")" ;
    return s;
}

using VCoord = double;
using Pixel = VectorXD<2, int>;
using Vector3D = VectorXD<3, VCoord>;
using Vector4D = VectorXD<4, VCoord>;

}
