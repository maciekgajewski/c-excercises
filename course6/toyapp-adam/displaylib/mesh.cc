#include "mesh.h"

namespace Display {

void Mesh::NormalizeSize()
{
	auto maxDimension = 0.0f;

	for (auto& triangle : triangles)
	{
		for (unsigned vector = 0; vector < 3; ++vector)
		{
			for (unsigned vertex = 0; vertex < 3; ++vertex)
			{
				auto dimension = std::fabs(triangle[vector][vertex]);
				if (dimension > maxDimension)
					maxDimension = dimension;
			}
		}
	}

	if (maxDimension == 0.0f)
		return;

	auto scale = 1.0f / maxDimension;

	for (auto& triangle : triangles)
		for (unsigned vector = 0; vector < 3; ++vector)
			for (unsigned vertex = 0; vertex < 3; ++vertex)
				triangle[vector][vertex] *= scale;
}

}
