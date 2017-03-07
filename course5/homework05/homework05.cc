#include "vector2d.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <cassert>


void test_operators();
void test_basics();
void test_polars();
void test_literals();

using namespace vector2D;

void test_basics()
{
	std::cout << "====== Testing basics ======" << std::endl;
	std::cout << "Testing creation" << std::endl;
	Vector2D	v(3.0, 4.0);
	Vector2D	v2 = {8.0, 1.5};

	std::cout << "Testing printing. Created "<< v  << "and (" << v2.GetX() << ", " << v2.GetY() << ")" << std::endl;


	std::cout << "Testing setters and getters" << std::endl;
	v.SetX(v2.GetX());
	v.SetY(v2.GetY());
	assert(v.GetX() == v2.GetX() && v.GetY() == v2.GetY());
	std::cout << "~~~~~ inished Testing basics " << std::endl;
}

void test_polars()
{
	Vector2D v(3, 4);

	std::cout << "====== Testing Polars ======" << std::endl;
	std::cout <<  v << "in polar coordinates is " << v.GetPolarR() << ", "<< v.GetPolarPhi() << std::endl;

	Vector2D v2 =  0.927295_tocart * v.GetPolarR();
	std::cout << "Recreated in carterians " <<  v2 << std::endl;
	
	std::cout << "~~~~~~Finished Testing Polars" << std::endl;
}


void test_operators()
{
	const int arr_size = 4;
	Vector2D	v0;	// default construction
	Vector2D	v1(10.0, 1.4); // user define construction
	Vector2D	v2 = {3.14, 2.71}; // user defined construction
	Vector2D	v3 = v2; // copy construction
	Vector2D	v_arr[arr_size] = {v0, v1, v2, v3};
	
	std::cout << "====== Testing operators ======" << std::endl;
	std::cout << "CReating vectors... "<< std::endl;
	for (int i=1; i <arr_size ; i++)
	{
		std::cout << "v" << i << " = " << v_arr[i-1] << std::endl;
	}
	std::cout << "Testing (in)equality" << std::endl;
	assert(v1 != v2);
	assert(v3 == v2 && v2 == v3);

	std::cout << "Testing Addition" << std::endl;
	Vector2D v4 = v1 + v2;
	std::cout << "adding v1: " << v1 << " +  v2 " << v2 << "= " << v4 << std::endl;
	std::cout << "v1 should be unchanged: "<< v1 << std::endl; 
	assert (v1 == Vector2D(10.0, 1.4)); // should be unchanged

	std::cout << "Testing Inline Addition (v1 += v1)" << std::endl;
	v1 += v1;
	std::cout << "After inline adding, v1 :  "<< v1 << std::endl;
	assert (v1 == Vector2D(20.0, 2.8));

	std::cout << "Testing Subtracting" << std::endl;
	Vector2D v5 = v2 -v1;
	std::cout << "subtracting v2: " << v2 << " -  v1 " << v1 << "= " << v5 << std::endl;
	std::cout << "v2 should be unchanged: "<< v3 << std::endl; 
	assert (v2 == Vector2D(3.14, 2.71)); // should be unchanged

	std::cout << "Testing Inline Subtracting (v3 -= v1)" << std::endl;
	std::cout << "v3: " << v4 << " -  v1 " << v1  << "= ";
	v3 = v1;
	v3 -= v1;
	std::cout << v3 << std::endl;
	assert (v3 == v0); // v3 was equal to v1, so should be 0 vector now

	std::cout << "Testing Negation" << std::endl;
	v3 = -v2;
	std::cout << "Assigning v3 = -v2. -" << v2 << "= " << v3 << std::endl;
	std::cout << "But v2 should be unchanged: " << v2 << std::endl;
	assert(v2 == Vector2D(3.14, 2.71)); // should be unchanged

	std::cout << "Testing Idempotency of + operator" << std::endl;
	assert(+v3 == v3);
	
	std::cout << "Extra's with anonymous objects" << std::endl;
	v1 = {1.0, 2.0}; 
	v2 = {0.5, 0.5};

	std::cout << v1 << " + " << v2 << "= " << v1+v2 << std::endl;
	assert(v1 == Vector2D(1.0, 2.0));

	std::cout << v1 << " - " << v2 << "= " << v1-v2 << std::endl;
	assert(v1 == Vector2D(1.0, 2.0));

	std::cout << "~~~~~ Finished Testing operators" << std::endl;
}
	
void test_literals()
{
	Vector2D v = {1.0, 3.14};
	Vector2D v2 = 1.0_x + 3.14_y;
	Vector2D v3 = 1.0_x + 0.5_y;

	std::cout << "====== Testing literals ======" << std::endl;
	std::cout << "created v " << v << "and literals v2 " << v2 << "abnd v3" << v3 << std::endl;
	assert(v == v2);
	assert(v != v3);

	auto vec = 3.3_x + 0.7_y; assert(vec==Vector2D(3.3, 0.7));

	std::cout << "~~~~~~Finished Testing literals" << std::endl;
}

int main()
{
	std::cout << "Start of tests"<< std::endl;

	test_basics();
	test_polars();
	test_operators();
	test_literals();

	std::cout << "End of tests" << std::endl;
}
