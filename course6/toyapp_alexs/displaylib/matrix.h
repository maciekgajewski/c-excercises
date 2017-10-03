#pragma once

#include <array>

namespace Display {

template<std::size_t A, std::size_t B>
class Matrix
{
public:
	Matrix() {}
	Matrix(std::array<std::array<double, B>, A> data): mMatrix(data) {}

	std::array<double, B>& operator [](int i)
	{
		return mMatrix[i];
	}

	const std::array<double, B>& operator [](int i) const
	{
		return mMatrix[i];
	}

	template<std::size_t C>
	Matrix<A, C> operator*(const Matrix<B, C> matrix) const
	{
		Matrix<A, C> result;

		for (int i = 0; i < A; i++)
		{
			for (int j = 0; j < C; j++)
			{
				double value = 0;
				for (int k = 0; k < B; k++)
				{
					value += (*this)[i][k] * matrix[k][j];
				}
				result[i][j] = value;
			}
		}

		return result;
	}

private:
	std::array<std::array<double, B>, A> mMatrix;
};

}
