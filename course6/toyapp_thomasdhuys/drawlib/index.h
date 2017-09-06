#pragma once

#include <iostream>
#include <cstdint>
#include <memory>

#include "rgb.h"
#include "colors.h"
#include "vector3d.h"

namespace Draw {

struct Vertex;
using Index = std::shared_ptr<Vertex>;

struct Vertex {
	Vertex(): x(0), y(0), z(0), color(Draw::Colors::Red) {}
	Vertex(VCoord x, VCoord y, VCoord z): vector{x,y,z}, color(Draw::Colors::Red) {}
	Vertex(VCoord x, VCoord y, VCoord z, RGB color): vector{x,y,z}, color(color) {}
	Vertex(const Vertex& v) = delete;

	~Vertex() { std::cout << "Vtx Destructed: " << ToString() << std::endl; }

	Vector3D vector;
	VCoord x;
	VCoord y;
	VCoord z;

	RGB color;

	std::string ToString() { return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z)+")"; }
	void Print() { std::cout << "Idx" << ToString() << std::endl; }
};

}
