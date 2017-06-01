#include <boost/optional.hpp>

#include <iostream>
#include <map>
#include <string>

/*
template<typename T>
class optional
{
private:
	char[sizeof(T)] buffer;
	bool valid = false;
public:
	// ...
};
*/
class Config {...};

class Users
{
private:

	std::map<int, std::string> mUsers;

	/*
	// 1
	std::unique_ptr<Config> mConfg;
	void SetConf(const std::string& xml) { mConfig = std::make_unique<Config>(xml); }
	User(const User& other)
	{
		if (other.mConfig)
			mConfig = std::make_unique<Config>(*other.mConfig); 
	}

	// 2
	boost::optional<Config> mCofig;
	void SetConf(const std::string& xml) { mConfig.emplace(xml); }
	*/
	
public:
	
	
	Users()
	{
		mUsers[0] = "Alosza";
		mUsers[1] = "Sophia";
	}
	
	boost::optional<std::string> Name(int id) const
	{
		auto it = mUsers.find(id);
		if ( it == mUsers.end())
		{
			return boost::none;
		}
		return it->second;
	}
};

int main(int argc, char** argv)
{
	Users users;
	
	int id = std::stoi(argv[1]);
	
	auto name = users.Name(id);
	
	if (name)
	{
		std::cout << "name of id=" << id << " is " << *name << std::endl;
	}
	else
	{
		std::cout << "no user with id=" << id << std::endl;
	}
	
	name = boost::none;
	assert(!name);
}

