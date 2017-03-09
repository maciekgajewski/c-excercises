#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_

#include <iostream>

namespace jds {

        class Vector2D
        {
        public:
                Vector2D(double x, double y);
        
                static Vector2D Polar(double r, double p);
        
                double GetX() const;
        
                double GetY() const;
        
                double GetR() const;
        
                double GetPhi() const;
        
                Vector2D operator+(const Vector2D& that) const;
        
                Vector2D operator-() const;
        
                Vector2D operator-(const Vector2D& that) const;
        
                Vector2D& operator+=(const Vector2D& that);
        
                Vector2D& operator-=(const Vector2D& that);
        
                bool operator==(const Vector2D& that) const;

        private:
                double x, y;
        };
}

using namespace jds;

std::ostream& operator<<(std::ostream& s, const Vector2D& v);

Vector2D operator "" _x(long double x);
Vector2D operator "" _y(long double y);
Vector2D operator "" _r(long double r);
Vector2D operator "" _t(long double t);

#endif
