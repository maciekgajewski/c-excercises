#include "camera.h"

namespace Display {

namespace {
	const auto DEFAULT_FOV_DEGREES = 60.0f;
}

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
