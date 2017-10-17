#include "matrix.h"

#include <SDL2/SDL.h>

namespace Display {


Matrix44 Matrix44::Zero()
{
	Matrix44 m;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			m[i][j] = 0.0f;
		}
	}

	return m;
}


}