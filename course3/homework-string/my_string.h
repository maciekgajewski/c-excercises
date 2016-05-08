#pragma once

class MyString
{
private:
    int length;
    char * buff;

    int strlen(const char *data) {
        int i = 0;
        while (*data++ != '\0')
            i++;

        return i;
    }

public:
    MyString() {
        length = 0;
    }

    MyString(const char *data) {
        length = strlen(data);

        buff = new char[length];

        for (int i = 0; i < length; i++)
            buff[i] = data[i];
    }

    MyString(const MyString& rhs) {
        length = rhs.size();
        buff = new char[length];
        for (int i = 0; i < length; i++)
            buff[i] = rhs[i];
    }

    bool empty() const {
       return length == 0 ? true : false;
    }

    bool empty() {
        return length == 0 ? true : false;
    }

    int size() const {
        return length;
    }

    int size() {
        return length;
    }

    bool operator!=(const MyString& rhs) {
        return !(*this == rhs);
    }

    bool operator==(const MyString& rhs) {
        if (length != rhs.size())
            return false;
        for (int i = 0; i < length; i++)
            if (buff[i] != rhs[i])
                return false;
        return true;
    }

    char& operator[](int index) {
        return buff[index];
    }

    char& operator[](int index) const {
        return buff[index];
    }
};
