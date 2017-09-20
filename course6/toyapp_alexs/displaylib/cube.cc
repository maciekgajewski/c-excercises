#include "vector2d.h"
#include "surface.h"
#include "shape3d.h"
#include "cube.h"

namespace Display {

Cube::Cube(Vector3D position, Color color, float size) : Shape3D(position, color)
{
    this->size = size;
}

void Cube::Draw(Surface& surface)
{
    auto half = size / 2;

    surface.SetPixel(surface.getProjection({this->position.x - half, this->position.y - half, this->position.z - half}), this->color);
    surface.SetPixel(surface.getProjection({this->position.x + half, this->position.y - half, this->position.z - half}), this->color);
    surface.SetPixel(surface.getProjection({this->position.x + half, this->position.y + half, this->position.z + half}), this->color);
    surface.SetPixel(surface.getProjection({this->position.x - half, this->position.y + half, this->position.z - half}), this->color);
    surface.SetPixel(surface.getProjection({this->position.x - half, this->position.y + half, this->position.z + half}), this->color);
    surface.SetPixel(surface.getProjection({this->position.x - half, this->position.y - half, this->position.z + half}), this->color);
    surface.SetPixel(surface.getProjection({this->position.x + half, this->position.y - half, this->position.z + half}), this->color);
    surface.SetPixel(surface.getProjection({this->position.x + half, this->position.y + half, this->position.z - half}), this->color);
}

}
