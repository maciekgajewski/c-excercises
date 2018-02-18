#include <iostream>
#define MACIEK std::cout
#define BEGIN {
#define END }

#ifdef ENDX
#warning bracket redefined
#endif

int main(int argc, char** argv)
BEGIN
	MACIEK << "Hello, world!" << std::endl;
END
