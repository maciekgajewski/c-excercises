#include "camera.h"

namespace Display {

Camera::Camera()
:	mProjection(CreateProjectionMatrix()),
	mFieldOfView(DEFAULT_FOV_DEGREES),
	mAspectRatio(1.0f)
{}

void Camera::SetScreenSize(Pixel dimensions)
{
	mAspectRatio = dimensions.x / static_cast<float>(dimensions.y);
	mProjection = CreateProjectionMatrix();
}

}
