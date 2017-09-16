#include <iostream>

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
	shapes.push_back(shape);
}

std::ostream& operator<<(std::ostream& s , const Scene& scene)
{
	s << "Scene: (shapes:" << scene.GetShapes().size() << ")\n";
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

	Shape squarePoints = ShapeFactory::GetSquarePoints(); 
	scene1.Add(squarePoints);

	// Scene2
	Scene scene1;

	Shape squarePoints = ShapeFactory::GetSquarePoints(); 
	scene1.Add(squarePoints);


	// Push all scenes
	scenes.push_back(std::move(scene1))
	scenes.push_back(std::move(scene2))
}

}
