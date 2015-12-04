#include <iostream>
#include <set>

const int CODE_LENGTH = 4;

bool isvalid(const std::string &input)
{
    if (input.size() == CODE_LENGTH)
    {
        for (auto c : input)
            if (c < 'A' or c > 'H') return false;
        
        std::set<char> s(input.begin(), input.end());
        
        return (s.size() == CODE_LENGTH);
    }

    return false;
}

struct answer
{
    int r;
    int w;
};

answer check_input(const std::string &code, const std::string &user_input)
{
    return answer {0,0};
}

int main(int, char**)
{
    std::string code ="ABCD";
    
    std::cout << "Hello, Mastermind!" << std::endl;
    //generate code
    
    //start loop for i<12
        //ask user for his guess
    std::string user_input;
    int current_attempt = 1;
    
    while (current_attempt <= 12)
    {
        std::cout << "User, enter your guess. The current attempt is "
            << current_attempt<< std::endl;
        std::cin >> user_input;
        
        if (code == user_input)
        {
            std::cout << "You are right!" << std::endl;
            return 0;
        }
        
        if (isvalid(user_input))
        {
            answer ans = check_input(code, user_input);
            std::cout << "whites: " << ans.w << "; reds: " << ans.r << std::endl;
            
            current_attempt++;
            
        }
        else
        {
            std::cout << "Your input is invalid, human" << std::endl;
            
        }
            //calculate result from guess
            //compare result and code
            //print user's guess and result and win statement if win condition
            //print lose condition if loop end
        
    }  
  
}
