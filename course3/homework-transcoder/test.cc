#include "transcoder.h"

#include <iostream>


int main()
{
	std::cout << "Transcoding input.json to output.xml..." << std::endl;
	Karun::Transcoder t("../input.json");
	t.WriteXML("output.xml");
	std::cout << "Done :)" << std::endl;
	
	std::cout << "Transcoding input.xml to output.json..." << std::endl;
	Karun::Transcoder t2("../input.xml");
	t2.WriteJSON("output.json");
	std::cout << "Done :)" << std::endl;
}
