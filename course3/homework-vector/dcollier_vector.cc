#include <iostream>
#include <cassert>

using namespace std;

class Vector
{
    // TODO
    public:
	// default constructor
        Vector(){
	     cout << "Default constructor, this=" << this << endl;
	};
	//constructor
	Vector(int argX, int argY) { 
    	     std::cout << "Constructor(x,y), this=" << this << std::endl; 
    	     x = argX;
             y = argY;
	};
        //destructor
	~Vector(){
             cout << "Freeing memory this=" << this << endl;
	};

	bool operator == ( Vector &vec){
	    return ( this->x == vec.GetX() && this->y == vec.GetY() );
	} 

	bool operator != ( Vector &vec){
	    if( this->x == vec.GetX() && this->y == vec.GetY() ){
		return false;
	    }
	    else { return true; }
	} 

	Vector operator + ( Vector &vec){
	     int newX = this->x + vec.GetX() ;
	     int newY = this->y + vec.GetY() ;	
	     return Vector(newX,newY);
	} 

	friend ostream& operator<<( ostream& os, Vector &vec){
	     return os << "Vector(" << vec.GetX() << ", "  << vec.GetY() << ")";
	}

	int GetX(){ return x;};
	int GetY(){ return y;};
        void SetX(int argX){ x = argX; }
        void SetY(int argY){ y =argY; }

   private:
	int x;
	int y;

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
