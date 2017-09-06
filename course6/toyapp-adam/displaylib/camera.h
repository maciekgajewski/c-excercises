#pragma once

#include "math/matrix.h"
#include "math/transform.h"
#include "util/pixel.h"

namespace Display {

using Math::Matrix44;
using Math::Transform;
using Util::Pixel;

class Camera
{
public:
	Transform transform;

	Camera();

	void SetScreenSize(Pixel dimensions);
	const Matrix44& GetProjectionMatrix() const { return mProjection; }
private:
	static constexpr auto DEFAULT_FOV_DEGREES = 60.0f;

	Matrix44 mProjection;
	float mFieldOfView;
	float mAspectRatio;

	Matrix44 CreateProjectionMatrix() { return Matrix44::Perspective(mFieldOfView, mAspectRatio); }
};

}
