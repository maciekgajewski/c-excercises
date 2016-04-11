#include <iostream>

class SimpleString
{
  public:
    SimpleString()
    {
    }

    SimpleString(const char* ascii)
    {
      int lastCharacterIndex = BUFFER_SIZE - 1;

      int i = 0;
      while(i < lastCharacterIndex
            && ascii[i] != 0)
      {
        mBuffer[i] = ascii[i];
	++i;
      }
      mBuffer[i] = 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const SimpleString& that);
    friend std::istream& operator>>(std::istream& is, SimpleString& target);

  private:
    static const int BUFFER_SIZE = 64;
    char mBuffer[BUFFER_SIZE];
};

std::ostream& operator<<(std::ostream& os, const SimpleString& that)
{
  os << that.mBuffer;
  return os;
}

std::istream& operator>>(std::istream& is, SimpleString& target)
{
  is.getline(target.mBuffer, target.BUFFER_SIZE - 1);
  target.mBuffer[is.gcount()] = 0;
  return is;
}

int main(int argc, char** argv)
{
//  std::cout << "Hi There" << std::endl;
//  SimpleString s("Hi Back");
//  std::cout << s << std::endl;

    SimpleString name;
    std::cout << "Whats your name? > ";
    std::cin >> name;
    std::cout << "Hello, " << name << std::endl;
    std::cout << "size of SimpleString is: " << sizeof(name) << std::endl;
}
