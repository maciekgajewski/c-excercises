#pragma once

#include <array>

namespace Display {

template<std::size_t A, std::size_t B, class T = double>
class Matrix
{
public:
	Matrix() {}
	Matrix(std::array<std::array<T, B>, A> data): mMatrix(data) {}

	std::array<T, B>& operator [](int i)
	{
		return mMatrix[i];
	}

	const std::array<T, B>& operator [](int i) const
	{
		return mMatrix[i];
	}

	template<std::size_t C>
	Matrix<A, C, T> operator*(const Matrix<B, C, T> matrix) const
	{
		Matrix<A, C, T> result;

		for (int i = 0; i < A; i++)
		{
			for (int j = 0; j < C; j++)
			{
				T value = 0;
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
	std::array<std::array<T, B>, A> mMatrix;
};

}
