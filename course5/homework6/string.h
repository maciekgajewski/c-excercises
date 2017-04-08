#include <memory>
#include <iostream>

namespace course{
    class string
    {
    public:
            string();
            string(const string&);
            string(string&&);
            string(const char*);
            string& operator=(const string&);
            string& operator=(const char*);
            string& operator=(string&&);
            int length() const;
            char* getchars() const;
            string operator+(const string&);
            string& operator+=(const string&);
            char& operator[](const int);
            char operator[](const int) const;
            bool operator==(const string&);
            bool operator==(const char*);
            char* c_str() const;
            char* begin();
            char* begin() const;
            char* end();
            char* end() const;
//            class iterator
//            {
//            public:
                    
//            private:
//                    char* point;
//            };
//            iterator& operator++(const iterator&);

    private:
            std::unique_ptr<char[]> string_pointer;
            int len;

    };

    std::ostream& operator<<(std::ostream&, const string&);

}