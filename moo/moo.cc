#include <iostream>
#include <iomanip>
#include <set>
#include <unordered_set>
#include <random>

const int MAX_TURNS = 12;
const int CODE_LENGH = 4;
const std::string ALPHABET = "123456789";
const std::unordered_set<char> ALPHABET_SET(ALPHABET.begin(), ALPHABET.end());

struct Answer
{
	int bulls = 0;
	int cows = 0;

	Answer() = default;
	Answer(int bulls, int cows): bulls(bulls), cows(cows) {}
};

Answer check(const std::string & secret, const std::string & guess)
{
	Answer answer;

	auto s = secret.begin();
	auto g = guess.begin();

	std::unordered_set<char> unmatched;

	for (int i = 0; i < CODE_LENGH; i++, s++, g++)
	{
		if (*s == *g)
			answer.bulls++;
		else
		{
			unmatched.insert(*s);
			unmatched.insert(*g);
		}
	}

	answer.cows = (CODE_LENGH - answer.bulls) * 2 - unmatched.size();

	return answer;
}

std::string generate()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, ALPHABET.size() - 1);

    std::unordered_set<char> s; // Using set for simplicity

    while (s.size() < CODE_LENGH){
    	s.insert(*(ALPHABET.begin() + dis(gen)));
    }

    return std::string(s.begin(), s.end());
}

bool is_valid(const std::string & guess)
{
	if (guess.size() != CODE_LENGH) return false;

	for (char c : guess)
		if (ALPHABET_SET.count(c) == 0) return false;

	std::unordered_set<char> s(guess.begin(), guess.end());

	return s.size() == CODE_LENGH;
}

void read_guess(int i, std::string & guess)
{
	std::cout << std::setw(2) << i << " ";
	std::cin >> guess;
}

void print_invalid()
{
	std::cout << "\033[1A"; // Move cursor one line up
	std::cout << "\033[K"; // Delete till end of line
}

void print_answer(int i, const std::string &  guess, const Answer & answer)
{
	std::cout << "\033[1A" << std::setw(2) << i << " " << guess << " "<< answer.bulls << " " << answer.cows << std::endl;
}

void print_win()
{
	 std::cout << "You win!" << std::endl;
}

void print_loose()
{
	std::cout << "You loose!" << std::endl;
}

int main()
{
	std::string secret = generate();
	std::string guess;
	Answer answer;

	int i = 1;

	while (i <= MAX_TURNS)
	{
		read_guess(i, guess);

		if  (not is_valid(guess))
		{
			print_invalid();
			continue;
		}

		answer = check(secret, guess);

		print_answer(i, guess, answer);

		if (answer.bulls == CODE_LENGH)
		{
			print_win();
			return 0;
		}

		i++;
	}
	print_loose();
}
