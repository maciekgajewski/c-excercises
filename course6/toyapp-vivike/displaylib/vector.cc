#include "vector.h"

namespace Display {

template<>
Vector3D Vector3D::cross(Vector3D vecr)
{
	Vector3D result;
	result.vec[0] = (this->vec[1]) * vecr[2] - (this->vec[2]) * vecr[1];
	result.vec[1] = (this->vec[2]) * vecr[0] - (this->vec[0]) * vecr[2];
	result.vec[2] = (this->vec[0]) * vecr[1] - (this->vec[1]) * vecr[0];
	
	return result;
}

}