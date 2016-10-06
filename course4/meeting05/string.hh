#include <memory>

namespace maciek {

class string
{
public:

	string() = default;
	string(const char* data);
	
	std::size_t length() const { return mLength; }
	
private:
	
	std::unique_ptr<char[]> mData;
	std::size_t mLength = 0;
};

}
