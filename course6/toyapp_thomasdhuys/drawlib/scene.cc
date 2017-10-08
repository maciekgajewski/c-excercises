#include <iostream>
#include <cassert>

#include "scene.h"
#include "shape.h"

namespace Draw {

SceneShapes& Scene::GetShapes() { return shapes; }
const SceneShapes& Scene::GetShapes() const { return shapes; }

void Scene::Add(const Shape& shape)
{
	shapes.push_back(shape);
}

void Scene::Add(Shape&& shape)
{
	shapes.push_back(std::move(shape));
}

std::ostream& operator<<(std::ostream& s , const Scene& scene)
{
	s << "(shapes:" << scene.GetShapes().size() << ")\n";
	for(const auto& shape : scene.GetShapes())
	{
		s << "\t" << shape << "\n";
	}
	return s;
}

Scenes SceneFactory::GetScenes()
{
	Scenes scenes;

	// Scene1
	Scene scene1;

	Shape squarePoints1 = ShapeFactory::GetSquarePoints();
	scene1.Add(std::move(squarePoints1));

	// Scene2
	Scene scene2;

	Shape squarePoints2 = ShapeFactory::GetSquareLines();
	scene2.Add(std::move(squarePoints2));


	// Push all scenes
	scenes.push_back(std::move(scene1));
	//scenes.push_back(std::move(scene2));
	return scenes;
}

}
