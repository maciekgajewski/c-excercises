#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <locale>
#include <set>
#include <map>
#include <boost/tokenizer.hpp>

class Dictionary {
public:
	Dictionary(const std::string& path);
	bool InDictionary(const std::string& word) const;

private:
	std::set<std::string> mWords;
};

Dictionary::Dictionary(const std::string& path) {
	std::ifstream file(path);
	std::string word;
	while(std::getline(file, word))
		mWords.insert(word);
	std::cerr << "Loaded " << mWords.size() << " words into dictionary" << std::endl;
}

bool Dictionary::InDictionary(const std::string& word) const {
	return mWords.find(word) != mWords.end();
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
	std::map<std::string, int> errors;
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
					errors[word]++;
				}
			}
		}
		lineNumber++;
	}

	int numErrors = std::accumulate(errors.begin(), errors.end(), 0,
		[](int a, const std::pair<std::string, int>& b)
		{
			return a + b.second;
		});
	std::cout << "Errors found: " << numErrors << ", " << errors.size() << " invalid words" << std::endl;
}
 