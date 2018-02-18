#pragma once

#include "complex.h"
#include <stack>

namespace complex {
extern "C" char get_operation_symbol();
extern "C" void operation(std::stack<Complex>&);
}
