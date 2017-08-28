#include <iostream>

namespace vector{

    class Vector2D
    {
    public:
            Vector2D() = delete;
            Vector2D(double, double);
            Vector2D(const Vector2D&);
            Vector2D& operator=(const Vector2D&);
            double GetX() const;
            double GetY() const;
            void SetX(double);
            void SetY(double);
            double GetR() const;
            double GetAngle() const;
            Vector2D operator+(const Vector2D&) const;
            Vector2D operator-(const Vector2D&) const;
            Vector2D operator-() const;
            Vector2D& operator+=(const Vector2D&);
            Vector2D& operator-=(const Vector2D&);
            bool operator==(const Vector2D&) const;
            bool operator!=(const Vector2D&) const;

    private:
            double x;
            double y;
    };

    std::ostream& operator<<(std::ostream&, const Vector2D&);

    Vector2D operator "" _x(long double);
    Vector2D operator "" _y(long double);
    Vector2D operator "" _phi(long double);
    Vector2D operator*(double, const Vector2D&);

}