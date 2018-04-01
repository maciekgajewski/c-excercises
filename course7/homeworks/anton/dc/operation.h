#pragma once

#include "complex.h"
#include "stack.h"
#include <stack>


using Stack = std::stack<Complex, MyComplexLinkedList>;

namespace complex {
extern "C" char get_command_name();
extern "C" void invoke_command(Stack&);
}
