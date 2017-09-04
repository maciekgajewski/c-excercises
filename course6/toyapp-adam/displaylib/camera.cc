#include "camera.h"

namespace Display {

Camera::Camera()
:	mProjection(CreateProjectionMatrix())
{}

void Camera::SetScreenSize(Pixel dimensions)
{
	mAspectRatio = dimensions.x / static_cast<float>(dimensions.y);
	mProjection = CreateProjectionMatrix();
}

Matrix44 Camera::CreateProjectionMatrix()
{
	return Matrix44::Perspective(mFieldOfView, mAspectRatio);
}

}
