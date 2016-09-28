#pragma once

#include <ostream>
#include <cmath>

bool double_eq(double x, double y)
//check whether two doubles are approximately equal. This assumes that they are neither both very large or very small
{
	return std::abs(x-y) < 1e-10;
}

struct PolarCoords2d;

struct CartesianCoords2d
{
	double x, y;
		
	PolarCoords2d get_polar_coords() const;
	
	bool operator==(const CartesianCoords2d& other_coords) const{
		return double_eq(x, other_coords.x) && double_eq(y, other_coords.y);
	}

	CartesianCoords2d operator+(const CartesianCoords2d& other_coords) const{
		return CartesianCoords2d{x+other_coords.x, y+other_coords.y};
	}
};

struct PolarCoords2d
{
	double r, phi;
		
	CartesianCoords2d get_cartesian_coords() const{
		return CartesianCoords2d{r * std::cos(phi), r * std::sin(phi)};
	}
};

PolarCoords2d CartesianCoords2d::get_polar_coords() const{
	return PolarCoords2d{std::sqrt(x*x + y*y), std::atan2(x, y)};
}

struct Vector2d
{
	Vector2d(CartesianCoords2d cart_coords) : coords(cart_coords) {}
	Vector2d(double x, double y) : coords(CartesianCoords2d{x, y}) {}
	Vector2d(PolarCoords2d polar_coords): coords(polar_coords.get_cartesian_coords()) {}

	Vector2d operator+(const Vector2d& other_vec) const{
		return Vector2d(coords + other_vec.coords);
	}

	bool operator==(const Vector2d& other_vec) const{
		return coords==(other_vec.coords);
	}
	
	CartesianCoords2d get_cartesian_coords() const{
		return coords;
	}

	PolarCoords2d get_polar_coords() const{
		return coords.get_polar_coords();
	}

	private:
		CartesianCoords2d coords;
};

std::ostream& operator<<(std::ostream& s, const Vector2d& vector){
	CartesianCoords2d coords = vector.get_cartesian_coords();
	return s << '(' << coords.x << ", " << coords.y << ')';
}