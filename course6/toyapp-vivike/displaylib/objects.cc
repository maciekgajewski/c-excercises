#include "objects.h"
#include "matrix.h"

#include <SDL2/SDL.h>

namespace Display {

void Color::redder(int amount)
{
	if(R + amount <= 255)
	{
		R = R + amount;
	}
};

Pixel Camera::project2D(Vector3D original)
{
	Pixel newVector({int(original[0]/original[2]), int(original[1]/original[2])});

	return newVector;
}

Square::Square(float edge_length, Vector3D center_location, Vector3D orientation) {
	len = edge_length;
	loc_center = center_location;
	orient = orientation;

	Vector3D corner1({-0.5, -0.5, 0});
	Vector3D corner2({0.5, -0.5, 0});
	Vector3D corner3({-0.5, 0.5, 0});
	Vector3D corner4({0.5, 0.5, 0});
	base_square = std::array<Vector3D, 4>{corner1, corner2, corner3, corner4};
}

Vector3D Square::transformCorner(Vector3D corner)
{
	Matrix44 scaleMatrix = Matrix44::Scale(len);
	Matrix44 moveMatrix = Matrix44::Translate(loc_center);

	// todo: rotation
	return moveMatrix * scaleMatrix * corner;
}

void Square::move(Vector3D move)
{
	loc_center = loc_center + move;
}

std::array<std::array<Vector3D, 2>, 4> Square::edges()
{	
	Vector3D corner1 = transformCorner(base_square[0]);
	Vector3D corner2 = transformCorner(base_square[1]);
	Vector3D corner3 = transformCorner(base_square[2]);
	Vector3D corner4 = transformCorner(base_square[3]);

	std::array<Vector3D, 2> line1{corner1, corner2};
	std::array<Vector3D, 2> line2{corner1, corner3};
	std::array<Vector3D, 2> line3{corner2, corner4};
	std::array<Vector3D, 2> line4{corner3, corner4};

	std::array<std::array<Vector3D, 2>, 4> result{line1, line2, line3, line4};

	return result;
}

}
