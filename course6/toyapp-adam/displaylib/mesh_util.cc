#include "mesh_util.h"

#include <algorithm>
#include <fstream>
#include <sstream>

namespace Display {

static unsigned GetFaceIndex(unsigned index, unsigned vertexCount)
{
	return index > 0 ? index - 1 : vertexCount + index;
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
			stream.ignore(2);

			Math::Vector<unsigned, 3> indices;
			auto slashCount = std::count(line.begin(), line.end(), '/');
			if (slashCount < 3)
			{
				stream >> indices[0] >> indices[1] >> indices[2];
			}
			else if (slashCount < 6)
			{
				char slash;
				unsigned dummy;
				stream >> indices[0] >> slash >> dummy;
				stream >> indices[1] >> slash >> dummy;
				stream >> indices[2];
			}
			else
			{
				char slash;
				unsigned dummy;
				stream >> indices[0] >> slash >> dummy >> slash >> dummy;
				stream >> indices[1] >> slash >> dummy >> slash >> dummy;
				stream >> indices[2];
			}

			auto vertexCount = static_cast<unsigned>(vertices.size());
			mesh.triangles.push_back({
				vertices[GetFaceIndex(indices[0], vertexCount)],
				vertices[GetFaceIndex(indices[1], vertexCount)],
				vertices[GetFaceIndex(indices[2], vertexCount)]
			});
		}
	}

	return mesh;
}

}
