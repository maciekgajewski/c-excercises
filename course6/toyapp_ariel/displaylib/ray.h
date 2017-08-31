#ifndef RAY_H
#define RAY_H

#include "float3.h"

class Ray
{
public:    
    Ray(const Float3& o, const Float3& d);
    Float3 GetOrigin() const {return o;}
    Float3 GetDirection() const{return d;}
private:
    Float3 o, d;
};

#endif // RAY_H
