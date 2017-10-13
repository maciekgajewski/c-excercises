#include "mesh_util.h"

#include <fstream>

namespace Display {

Mesh CreateMeshFromFile(const std::string& filePath)
{
	Mesh mesh;

	std::ifstream file(filePath);
	if (file.fail())
		return mesh;

	std::string line;
	while (std::getline(file, line))
	{
		Math::Triangle3D triangle;
		for (unsigned vertex = 0; vertex < 3; ++vertex)
			for (unsigned coordinate = 0; coordinate < 3; ++coordinate)
				file >> triangle[vertex][coordinate];

		mesh.triangles.push_back(triangle);
	}

	return mesh;
}

}
