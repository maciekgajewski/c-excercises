#pragma once

#include <iostream>
#include <memory>

#include "vector3d.h"
#include "color.h"

namespace Draw {

struct Vertex;

struct Vertex {
	// Ctor and Dtor
	Vertex(): vector{0,0,0}, color(Draw::Colors::Green) {}
	Vertex(VCoord x, VCoord y, VCoord z): vector{x,y,z}, color(Draw::Colors::Green) {}
	Vertex(VCoord x, VCoord y, VCoord z, Color color): vector{x,y,z}, color(color) {}
//	Vertex(const Vertex& v);
//	~Vertex();

	// Data
	Vector3D vector;
	Color color;

	friend std::ostream& operator<<(std::ostream& s, const Vector3D& v);
};

std::ostream& operator<<(std::ostream& s , const Vertex& v);

}
