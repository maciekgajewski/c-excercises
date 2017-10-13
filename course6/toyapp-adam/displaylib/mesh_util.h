#pragma once

#include "mesh.h"
#include <string>

namespace Display {

Mesh CreateMeshFromTxtFile(const std::string& filePath);
Mesh CreateMeshFromObjFile(const std::string& filePath);

}
