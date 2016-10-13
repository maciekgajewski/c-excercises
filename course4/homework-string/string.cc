#include "string.hh"

namespace course {

std::ostream& operator<<(std::ostream& s, const string& strng){
	return s << strng.c_str();
}

}