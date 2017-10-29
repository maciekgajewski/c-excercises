#pragma once

#include "color.h"
#include "math/triangle.h"
#include "math/vector.h"
#include "sdlobject.h"
#include "util/pixel.h"
#include <memory>
#include <SDL2/SDL.h>
#include <vector>

namespace Display {

using Math::Triangle2D;
using Math::Triangle3D;
using Math::Vector2D;
using Math::Vector3D;
using Util::Pixel;

class Surface2D : private SDLObject
{
	friend class Window;
public:
	Surface2D(Pixel dimensions);
	~Surface2D();

	Pixel GetDimensions() const { return {mSurface->w, mSurface->h}; }

	void Clear(Color color);
	void SetPixel(Pixel position, Color color);
	void DrawLine(Pixel start, Pixel end, Color color);
	void DrawLine(Pixel start, float startDepth, Pixel end, float endDepth, Color color);
	void DrawTriangle(Pixel a, Pixel b, Pixel c, Color color);
	void DrawTriangle(Pixel a, float aDepth, Pixel b, float bDepth, Pixel c, float cDepth, Color color);
	void SetPixel(Vector2D position, Color color);
	void SetPixel(Vector3D position, Color color);
	void DrawLine(Vector2D start, Vector2D end, Color color);
	void DrawLine(Vector3D start, Vector3D end, Color color);
	void DrawTriangle(const Triangle2D& triangle, Color color);
	void DrawTriangle(const Triangle3D& triangle, Color color);
private:
	SDL_Surface* mSurface;
	std::unique_ptr<float[]> mDepthBuffer;
	Pixel mHalfDimensions;

	void SetDepth(Pixel position, float depth);
	bool CheckSetDepth(Pixel position, float depth);
	Pixel ToPixel(Vector3D logicalCoordinates);
};

inline void Surface2D::DrawLine(Pixel start, Pixel end, Color color)
{
	DrawLine(start, 0.0f, end, 0.0f, color);
}

inline void Surface2D::DrawTriangle(Pixel a, Pixel b, Pixel c, Color color)
{
	DrawTriangle(a, 0.0f, b, 0.0f, c, 0.0f, color);
}

inline void Surface2D::SetPixel(Vector2D position, Color color)
{
	SetPixel(Vector3D{position, 0.0f}, color);
}

inline void Surface2D::DrawLine(Vector2D start, Vector2D end, Color color)
{
	DrawLine(Vector3D{start, 0.0f}, Vector3D{end, 0.0f}, color);
}

inline void Surface2D::DrawTriangle(const Triangle2D& triangle, Color color)
{
	Triangle3D triangle3D = {
		{triangle[0], 0.0f},
		{triangle[1], 0.0f},
		{triangle[2], 0.0f}
	};

	DrawTriangle(triangle3D, color);
}

}
