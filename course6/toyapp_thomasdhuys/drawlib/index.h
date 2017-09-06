#pragma once

#include <iostream>
#include <memory>

#include "rgb.h"
#include "colors.h"
#include "vector3d.h"

namespace Draw {

struct Vertex;
using Index = std::shared_ptr<Vertex>;

struct Vertex {
	// Ctor and Dtor
	Vertex(): vector{0,0,0}, color(Draw::Colors::Red) {}
	Vertex(VCoord x, VCoord y, VCoord z): vector{x,y,z}, color(Draw::Colors::Red) {}
	Vertex(VCoord x, VCoord y, VCoord z, RGB color): vector{x,y,z}, color(color) {}
	Vertex(const Vertex& v) = delete;
	~Vertex();

	// Data
	Vector3D vector;
	RGB color;

	friend std::ostream& operator<<(std::ostream& s, const Vector3D& v);
};

std::ostream& operator<<(std::ostream& s , const Vertex& v);

}
