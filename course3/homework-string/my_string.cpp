#include "my_string.h"
#include <memory>

        MyString::MyString()
        {
            mBuffer=nullptr;
        }

        MyString::MyString(const char* other)
        {
            mBuffer = std::make_unique<char[]>(std::strlen(other) + 1);
            std::strcpy(mBuffer.get(), other);
        }

        MyString::MyString(const MyString& other)
        {
            mBuffer = std::make_unique<char[]>(other.size() + 1);
            std::strcpy(mBuffer.get(), other.mBuffer.get());
        }

        std::size_t MyString::size() const
        {
            if(!mBuffer)
                return 0;

            return std::strlen(mBuffer.get());
        }

        bool MyString::empty() const
        {
            return mBuffer == nullptr || mBuffer.get()[0] == 0;
        }

        const char* MyString::c_str() const
        {
            if(!mBuffer)
                return "";

            return mBuffer.get();
        }

        char MyString::operator[](std::size_t index) const
        {
            return mBuffer.get()[index];
        }
        char& MyString::operator[](std::size_t index)
        {
            return mBuffer.get()[index];
        }

        bool MyString::operator==(const MyString& other) const
        {
            if(this -> empty() && other.empty())
                //TODO: this is not completely right just yet. we need nullptr checks for later on.
                return true;

            return std::strcmp(mBuffer.get(), other.mBuffer.get()) == 0;
        }
        bool MyString::operator!=(const MyString& other) const
        {
            return !(*this==other);
        }

        bool MyString::operator<(const MyString& other) const
        {
            if(this->empty() && other.empty())
                return false;

            return std::strcmp(this->c_str(), other.c_str()) < 0;
        }

        bool MyString::operator<=(const MyString& other) const
        {
            if(this->empty() && other.empty())
                return true;

            return std::strcmp(this->c_str(), other.c_str()) <= 0;
        }

        bool MyString::operator>(const MyString& other) const
        {
            if(this->empty() && other.empty())
                return true;

            return std::strcmp(this->c_str(), other.c_str()) > 0;
        }

        bool MyString::operator>=(const MyString& other) const
        {
            if(this->empty() && other.empty())
                return true;

            return std::strcmp(this->c_str(), other.c_str()) >= 0;
        }

        MyString& MyString::operator=(const MyString& other)
        {
            if(!other.mBuffer)
            {
                clearBuffer();
            }
            else
            {
                auto newSize = other.size() + 1;
                auto newBuffer = std::make_unique<char[]>(newSize);
                std::strcpy(newBuffer.get(), other.mBuffer.get());
                mBuffer.swap(newBuffer);
            }

            return *this;
        }

        MyString& MyString::operator=(const char* other)
        {
            if(other == nullptr)
            {
                clearBuffer();
            }
            else
            {
                auto newSize =std::strlen(other) + 1;
                auto newBuffer = std::make_unique<char[]>(newSize);

                std::strcpy(newBuffer.get(), other);
                mBuffer.swap(newBuffer);
            }

            return *this;
        }

        MyString& MyString::operator+=(const char* other)
        {
            if(other != nullptr && other[0] != '\0')
            {
                auto newSize = this->size() + std::strlen(other) + 1;
                auto copyStartIndex = this->size();

                auto newBuffer = std::make_unique<char[]>(newSize);
                std::strcpy(newBuffer.get(), this->c_str());
                std::strcpy(newBuffer.get() + copyStartIndex, other);

                mBuffer.swap(newBuffer);
            }

            return *this;
        }

        MyString& MyString::operator+=(const MyString& other)
        {
            if(!other.empty())
            {
                auto newSize = this->size() + other.size() + 1;
                auto copyStartIndex = this->size();

                auto newBuffer = std::make_unique<char[]>(newSize);
                std::strcpy(newBuffer.get(),this->c_str());
                std::strcpy(newBuffer.get() + copyStartIndex, other.c_str());
                mBuffer.swap(newBuffer);
            }

            return *this;
        }

        MyString MyString::operator+(const char* other) const
        {
            if(other == nullptr || other[0] == 0)
            {
                return MyString(*this);
            }
            else
            {
                auto newSize = this->size() + std::strlen(other) + 1;
                auto copyStartIndex = this->size();
                auto newBuffer = std::make_unique<char[]>(newSize);
                std::strcpy(newBuffer.get(), mBuffer.get());
                std::strcpy(newBuffer.get() + copyStartIndex, other);

                auto result = MyString(newBuffer.get());
                return result;
            }
        }

        MyString MyString::operator+(const MyString& other) const
        {
            if(other.empty())
            {
                return MyString(*this);
            }
            else
            {
                auto newSize = this->size() + other.size() + 1;
                auto copyStartIndex = this->size();

                auto newBuffer = std::make_unique<char[]>(newSize);
                std::strcpy(newBuffer.get(), mBuffer.get());
                std::strcpy(newBuffer.get() + copyStartIndex, other.mBuffer.get());

                return MyString(newBuffer.get());
            }
        }


        void MyString::clearBuffer()
        {
            //TODO: what happens with the previous pointer?
            mBuffer = nullptr;
        }


