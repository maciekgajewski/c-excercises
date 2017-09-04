#pragma once

#include "math/matrix.h"
#include "math/transform.h"
#include "pixel.h"

namespace Display {

using Math::Matrix44;
using Math::Transform;

class Camera
{
public:
	Transform transform;

	Camera();

	void SetScreenSize(Pixel dimensions);
	const Matrix44& GetProjectionMatrix() const { return mProjection; }
private:
	static constexpr auto DEFAULT_FOV_DEGREES = 90.0f;

	Matrix44 mProjection;
	float mFieldOfView = DEFAULT_FOV_DEGREES;
	float mAspectRatio = 1.0f;

	Matrix44 CreateProjectionMatrix();
};

}
