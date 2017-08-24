#pragma once

namespace Display {

struct Vector2D
{
	float x = 0.0f;
	float y = 0.0f;
};

struct Vector3D
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	/**
	 * Assumes eye is at {0,0,0} looking at {0,0,1}
	 */
	Vector2D project() const;
};

}
