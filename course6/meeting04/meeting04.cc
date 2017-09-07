#include <iostream>
#include <string>


struct Point2D {};
class Surface2D
{
public:
	void Draw(Point2D p) {} 
};

Surface2D globalSurface;

struct Point3D {};
class Surface3D
{
public:
	void Draw(Point3D p)
	{
		surface2d.Draw(Project(p));
	}

	Surface3D(Surface2D& s) : surface2d(s)
	{
		surface2d = s;
	}

	Surface3D() : surface2d(globalSurface)
	{
	}

private:
	Point2D Project(Point3D) const { return {}; }
	Surface2D& surface2d;
};

int main(int argc, char** argv)
{
	Surface2D surface;
	Surface3D td(surface);

	Surface3D td2;
}

