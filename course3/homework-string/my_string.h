#pragma once

#include <memory>

namespace Maciek {

class String
{
public:

	String() = default;
	String(const char*);
	
	std::size_t size() const;
	
	bool empty() const;
	
private:

	std::unique_ptr<char[]> mBuffer;
};

}