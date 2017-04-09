#include <algorithm>
#include <cassert>
#include <iostream>

#include "string.h"

int main(int, char**)
{
	jds::String s = "Hello world";
	std::sort(s.begin(), s.end());
	assert(s == " Hdellloorw");
	std::reverse(s.begin(), s.end());
	assert(s == "wroollledH ");
	assert(*std::max_element(s.begin(), s.end()) == 'w');
	assert(*std::min_element(s.begin(), s.end()) == ' ');
}
