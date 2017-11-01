#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <locale>

#include <boost/tokenizer.hpp>

class Dictionary {
public:
	Dictionary(const std::string& path);
	bool InDictionary(const std::string& word) const;

private:
	std::vector<std::string> mWords;
};

Dictionary::Dictionary(const std::string& path) {
	std::ifstream file(path);
	std::string word;
	while(std::getline(file, word))
		mWords.push_back(word);
	std::sort(mWords.begin(), mWords.end());
	std::cerr << "Loaded " << mWords.size() << " words into dictionary" << std::endl;
}

bool Dictionary::InDictionary(const std::string& word) const {
	//return std::find(mWords.begin(), mWords.end(), word) != mWords.end();
	auto it = std::lower_bound(mWords.begin(), mWords.end(), word);
	return it != mWords.end() && *it == word;
}

int main(int argc, char** argv)
{
	if (argc < 3)
		throw std::runtime_error("Usage: meeting12 DICTIONARY INPUT");

	// Load dictionary
	Dictionary dict(argv[1]);

	// Parse input file
	std::ifstream input(argv[2]);
	std::string line;
	int lineNumber = 1;
	int errors = 0;
	while(std::getline(input, line))
	{
		for(std::string word : boost::tokenizer<>(line))
		{
			if (!dict.InDictionary(word))
			{
				// convert to lower
				std::transform(word.begin(), word.end(), word.begin(), [](char c) { return std::tolower(c); });
				if (!dict.InDictionary(word))
				{
					//std::cout << "ERROR line " << lineNumber << " : " << word << std::endl;
					errors++;
				}
			}
		}
		lineNumber++;
	}
	std::cout << "Errors found: " << errors << std::endl;
}
 