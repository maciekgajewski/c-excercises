#include <iostream>

class SimpleString
{
  public:
    SimpleString()
    {
    	mBuffer[0] = 0;
    }

    SimpleString(SimpleString& that):SimpleString(that.mBuffer)
    {
    }

    SimpleString(const char* ascii)
    {
      int lastCharacterIndex = BUFFER_SIZE - 1;

      int i;
      for (i=0; i < lastCharacterIndex && ascii[i] != 0; ++i)
      {
        mBuffer[i] = ascii[i];
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
  SimpleString defaultConstructed;
  std::cout << defaultConstructed;
  defaultConstructed = "---------";
  std::cout << defaultConstructed << std::endl;
  
  std::cout << "Hi There" << std::endl;
  SimpleString s("Hi Back");
  std::cout << s << std::endl;

    SimpleString name;
    std::cout << "Whats your name? > ";
    std::cin >> name;
    std::cout << "Hello, " << name << std::endl;
    std::cout << "size of SimpleString is: " << sizeof(name) << std::endl;
    
    SimpleString a("hello");
    SimpleString b = a;
    SimpleString c;
    c = a;
    std::cout << b << "   " << c << std::endl;
}
