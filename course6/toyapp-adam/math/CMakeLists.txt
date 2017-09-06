add_library(math
	matrix.cc
	transform.cc
	vector.cc)

set_property(TARGET math PROPERTY CXX_STANDARD 14)
