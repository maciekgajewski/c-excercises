#include "mesh_util.h"

#include <fstream>
#include <sstream>

namespace Display {

Mesh CreateMeshFromTxtFile(const std::string& filePath)
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

Mesh CreateMeshFromObjFile(const std::string& filePath)
{
	Mesh mesh;

	std::ifstream file(filePath);
	if (file.fail())
		return mesh;

	std::vector<Math::Vector3D> vertices;

	std::string line;
	while (std::getline(file, line))
	{
		if (line.length() < 2)
			continue;

		std::stringstream stream(line);
		if (line[0] == 'v')
		{
			if (line[1] != 't')
			{
				stream.ignore(2);

				Math::Vector3D vertex;
				stream >> vertex[0] >> vertex[1] >> vertex[2];
				vertices.push_back(vertex);
			}
		}
		else if (line[0] == 'f')
		{
			stream.ignore(1);

			Math::Vector<unsigned, 3> indices;
			stream >> indices[0] >> indices[1] >> indices[2];

			mesh.triangles.push_back({
				vertices[indices[0] - 1],
				vertices[indices[1] - 1],
				vertices[indices[2] - 1]
			});
		}
	}

	return mesh;
}

}
