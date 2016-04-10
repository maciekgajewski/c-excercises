// author: dancollier@optiver.com
#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

class Vector
{
    // TODO
    public:
        Vector(){
	     std::cout << "Default constructor, this=" << this << std::endl;
	};
	Vector(int argX, int argY) { 
    	     std::cout << "Constructor(x,y), this=" << this << std::endl; 
    	     x = argX;
             y = argY;
	};
	~Vector(){
             std::cout << "Freeing memory this=" << this << std::endl;
	};

	bool operator == (Vector &vec){
	    return ( this->x == vec.GetX() && this->y == vec.GetY() );
	} 
	bool operator != (Vector &vec){
	    if( this->x == vec.GetX() && this->y == vec.GetY() ){
		return false;
	    }
	    else { return true; }
	} 
	Vector operator + (Vector &vec){
	     int newX = this->x + vec.GetX() ;
	     int newY = this->y + vec.GetY() ;	
	     return Vector(newX,newY);
	} 
	friend ostream& operator << ( ostream& os, Vector &vec){
	     return os << "Vector(" << vec.GetX() << ", "  << vec.GetY() << ")";
	}

	double GetX(){ return x;};
	double GetY(){ return y;};
        void SetX(int argX){ x = argX; }
        void SetY(int argY){ y = argY; }
	double GetRadius(){ return Radius(x,y) ; };
	double GetTheta(){ return Theta(x,y) ; };

   private:
	int x;
	int y;

	double Radius(double x, double y){
		double rad;
		rad = sqrt((pow(x,2))+(pow(y,2)));
		return rad;
	}	
	double Theta(double x, double y){
		double tht;
		tht = atan(y/x);
		return tht;
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

    // end test

    std::cout << "Radius of " << v3 << " is " << v3.GetRadius() << std::endl;
    std::cout << "Theta (\u03d1) of " << v3 << " is " << v3.GetTheta() << std::endl;

    Vector testVec;
    std::cout << "Radius of instantiated but unassigned vector " << testVec << " is " << testVec.GetRadius() << std::endl;
    testVec.GetTheta();
    Vector testVec2;
    std::cout << "Radius of a 2nd instantiated but unassigned vector " << testVec2 << " is " << testVec2.GetRadius() << std::endl;
    std::cout << "The value of X and the radius match on my machine despite values for Y that make that impossible. "<< std::endl;
    
}
