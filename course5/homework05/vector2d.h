#include<iostream>
#include<cmath>

namespace homework{

    class Polar
    {
        public:
            Polar(double rr, double tt);

            double GetR() const {return r;}
            double GetTheta() const {return theta;}

            Polar operator+(const Polar& src) const;

        private:
            double r;
            double theta;
    };

    homework::Polar operator "" _r (long double rr);
    homework::Polar operator "" _theta (long double tt);


    class Vector2D
    {
        public:
            Vector2D(double xx, double yy);
            Vector2D(const Vector2D& src); //copy constructor
            Vector2D(const Polar& src); //copy constructor

            double GetX() const {return x;}
            double GetY() const {return y;}

            void SetX(unsigned xx) {x=xx;}
            void SetY(unsigned yy) {y=yy;}

            double GetRadius() const {return std::sqrt(x*x + y*y);}
            double GetTheta() const {return std::atan2(y, x);}

            Vector2D& operator=(const Vector2D& src); //copy assignment
            Vector2D operator+(const Vector2D& src) const;
            Vector2D operator-(const Vector2D& src) const;
            Vector2D operator-();
            Vector2D& operator+=(const Vector2D& src);
            Vector2D& operator-=(const Vector2D& src);
            bool operator==(Vector2D src);
            bool operator!=(Vector2D src);


        private:
            double x;
            double y;
    };

    homework::Vector2D operator "" _x (long double xx);
    homework::Vector2D operator "" _y (long double yy);

}

std::ostream& operator<< (std::ostream& s, const homework::Vector2D vector);

