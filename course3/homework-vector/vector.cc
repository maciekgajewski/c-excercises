#include <iostream>
#include <cassert>
#include <cmath>

class Vector
{
    private:
        int private_x, private_y;

    public:
        // required constructors
        Vector(int x, int y): private_x(x), private_y(y) {}
        Vector() {
            private_x = 0;
            private_y = 0;
        }

        int GetX() { return private_x; }
        int GetY() { return private_y; }

        void SetX(int x) { private_x = x; }
        void SetY(int y) { private_y = y; }

        float GetTheta() {
            return std::atan2(private_y, private_x) * 180 / M_PI;
        }

        float GetR() {
            return std::pow(std::pow(private_x, 2) + std::pow(private_y, 2), 0.5);
        }

        friend std::ostream& operator<< (std::ostream& stream, Vector& v) {
            stream << "{(" << v.GetX() << ", " << v.GetY() << "), (" << v.GetR() << "@" << v.GetTheta() << ")}";
            return stream;
        }

        bool operator== (Vector& rhs) {
            if (private_x == rhs.GetX() && private_y == rhs.GetY())
                return true;
            return false;
        }

        bool operator!= (Vector& rhs) {
            return !operator==(rhs);
        }

        Vector operator+ (Vector& rhs) {
            Vector result;
            result.SetX(private_x + rhs.GetX());
            result.SetY(private_y + rhs.GetY());
            return result;
        }
};

int main()
{
    // this all should compile and work
    
    Vector v1;
    Vector v2(5, 6);
    
    assert(v2.GetX() == 5);
    assert(v2.GetY() == 6);
    
    v1 = v2;
    assert(v1.GetX() == 5);
    assert(v1.GetY() == 6);
    assert(v1 == v2);
    
    v1.SetY(7);
    assert(v1.GetY() == 7);
    assert(v1 != v2);
    
    Vector v3 = v1 + v2;
    assert(v3.GetX() == 10);
    assert(v3.GetY() == 13);
    
    std::cout << v1 << " + " << v2 << " = " << v3 << std::endl;
}
