#pragma once

#include <string>
#include <iostream>

class Fred
{
public:
	Fred(const std::string& name)
	: mName(name)
	{
		std::cout << "Fred " << mName << " created" << std::endl;
	}
	
	~Fred()
	{
		std::cout << "Fred " << mName << " destroyed" << std::endl;
	}

private:
	std::string mName;
};

