#pragma once

#include "math/matrix.h"
#include "math/transform.h"

namespace Display {

using Math::Matrix44;
using Math::Transform;

class Camera
{
public:
	Transform transform;

	Camera();

	void SetAspectRatio(float aspectRatio);
	const Matrix44& GetProjectionMatrix() const { return mProjection; }
private:
	Matrix44 mProjection;
	float mFieldOfView;
	float mAspectRatio;

	Matrix44 CreateProjectionMatrix() { return Matrix44::Perspective(mFieldOfView, mAspectRatio); }
};

}
