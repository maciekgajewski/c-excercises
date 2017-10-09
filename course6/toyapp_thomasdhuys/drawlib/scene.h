#pragma once

#include <vector>
#include <memory>
#include <string>

#include "primitives.h"
#include "shape.h"

namespace Draw {

using SceneShapes = std::vector<Shape>;

class Scene {
public:
	SceneShapes& GetShapes();
	const SceneShapes& GetShapes() const;
	void Add(const Shape& shape);
	void Add(Shape&& shape);
private:
	SceneShapes shapes;
	int orientation;

	friend std::ostream& operator<<(std::ostream& s , const Scene& scene);
};

std::ostream& operator<<(std::ostream& s , const Scene& ro);

using Scenes = std::vector<Scene>;

class SceneFactory {
public:
	static Scenes GetScenes();
};

}
