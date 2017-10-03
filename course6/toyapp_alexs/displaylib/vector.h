#pragma once

#include <array>

namespace Display
{
	template<class T, std::size_t S>
	struct Vector
	{
	};

	template<>
	struct Vector<int, 2>
	{
		int x;
		int y;
	};

	template<>
	struct Vector<double, 3>
	{
		double x;
		double y;
		double z;
	};

	using Pixel = Vector<int, 2>;
	using Vector3D = Vector<double, 3>;
}
