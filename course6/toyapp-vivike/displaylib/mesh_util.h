#pragma once

#include "mesh.h"
#include <string>

namespace Display {

Mesh CreateMeshFromObjFile(const std::string& filePath);

}