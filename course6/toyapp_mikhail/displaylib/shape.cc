#include "shape.h"

#include "vector_common.h"

#include <algorithm>
#include <fstream>
#include <sstream>

namespace Display {

Shape Shape::LoadFromFile(const std::string& filePath)
{
	Shape shape;

	std::ifstream file(filePath);
	if (file.fail())
		return shape;

	std::vector<Vector3D> vertices;

	std::string line;
	while (std::getline(file, line))
	{
		if (line.length() < 2)
			continue;

		std::stringstream stream(line);
		if (line[0] == 'v')
		{
			stream.ignore(2);

			Vector3D vertex;
			stream >> vertex.x() >> vertex.y() >> vertex.z();
			vertex.y() *= -1;
			vertices.push_back(vertex);
		}
		else if (line[0] == 'f')
		{
			stream.ignore(2);

			Vector3<unsigned> indices;
			stream >> indices.x() >> indices.y() >> indices.z();

			shape.mSides.push_back({
				vertices[indices.x()-1],
				vertices[indices.y()-1],
				vertices[indices.z()-1]
			});
		}
	}
	return shape;
}
}
