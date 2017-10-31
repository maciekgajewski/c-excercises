#include "matrix.h"

namespace Display {

Matrix4by4::Matrix4by4()
{
	for (auto& ar: mArray)
		for (auto& a: ar)
			a = 0.0;
}

//Guess we shouldn't do this yet, but! :D
template<typename M1, typename M2, typename M3>
M3 MultiplyMatrices(M1 m1, M2 m2)
{
	static_assert(m1.COL_COUNT == m2.ROW_COUNT, "Cannot multiply these matrices");
	static_assert(M3::ROW_COUNT == M1::ROW_COUNT && M3::COL_COUNT == M2::COL_COUNT, "M3 is of wrong type");
	M3 res;
	for (int i = 0; i < m1.ROW_COUNT; ++i)
	{
		for (int j = 0; j < m2.COL_COUNT; ++j)
		{
			for (int k = 0; k < m1.COL_COUNT; ++k)
			{
				res.mArray[i][j] += m1.mArray[i][k] * m2.mArray[k][j];
			}
		}
	}
	return res;
}

Matrix4by4 operator*(const Matrix4by4 &m1, Matrix4by4 m2)
{
	return MultiplyMatrices<Matrix4by4, Matrix4by4, Matrix4by4>(m1, m2);
}

Vector3D operator*(const Matrix4by4 &m, Vector3D v)
{
	Matrix4by1 mv = Vector3DToMatrix(v);
	Matrix4by1 res = MultiplyMatrices<Matrix4by4, Matrix4by1, Matrix4by1>(m, mv);
	return MatrixToVector3D(res);
}

Matrix4by1::Matrix4by1()
{
	for (auto& ar: mArray)
		for (auto& a: ar)
			a = 0.0;
}

Matrix4by1 Vector3DToMatrix(Vector3D v)
{
	Matrix4by1 m;
	m.mArray[0][0] = v.mX;
	m.mArray[1][0] = v.mY;
	m.mArray[2][0] = v.mZ;
	m.mArray[3][0] = 1.0;
}

Vector3D MatrixToVector3D(Matrix4by1 m)
{
	return {m.mArray[0][0], m.mArray[1][0], m.mArray[2][0]};
}

}
