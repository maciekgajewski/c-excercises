#include <memory>
#include <cstring>
#include <iostream>

class String
{
public:
    String() { }

    String(const String& other)
        : buffer_(std::make_unique<char[]>(sizeof(other.buffer_)))
        , size_(other.size_)
    {
        std::uninitialized_copy_n(other.buffer_.get(), size_, buffer_.get());
    }

    String(const char* str)
        : buffer_(std::make_unique<char[]>(sizeof(str)))
        , size_(std::strlen(str))
    {
        std::uninitialized_copy_n(str, size_, buffer_.get());
    }

    String(String&& other)
        : buffer_(std::move(other.buffer_))
        , size_(other.size_)
    {
        other.size_ = 0;
    }

    String& operator=(const String& other) = default;
    String& operator=(const char* str) // I have no idea why =default doesn't compile
    {
        *this = String(str);
        return *this;
    }
    String& operator=(String&& other) = default;

    size_t length() const
    {
        return size_;
    }

    const char& operator[](size_t ind) const
    {
        if (ind >= size_) {
            throw std::runtime_error("Index is out of bounds");
        }
        return buffer_[ind];
    }

    char& operator[](size_t ind)
    {
        return const_cast<char&>(const_cast<const String*>(this)->operator[](ind)); // I strongly believe that it's the ligitimate usage of const_cast
    }

    String& operator+=(const String& other)
    {
        std::unique_ptr<char[]> new_buffer = std::make_unique<char[]>(sizeof(buffer_.get()) + sizeof(other.buffer_.get()));
        std::uninitialized_copy_n(buffer_.get(), size_, new_buffer.get());
        std::strcat(new_buffer.get(), other.buffer_.get());
        buffer_ = std::move(new_buffer);
        size_ = std::strlen(buffer_.get());
        return *this;
    }

    String operator+(const String& other) const
    {
        String res(*this);
        res += other;
        return res;
    }

    const char* c_str() const
    {
        return buffer_.get();
    }

private:
    std::unique_ptr<char[]> buffer_;
    size_t size_ = 0;
};

std::ostream& operator<<(std::ostream& os, const String& str)
{
    if (str.length()) {
        return os << str.c_str();
    } else {
        return os;
    }
}

int main()
{
    String a;
    a = "aaa";
    std::cout << a << ", len " << a.length() << " " << std::endl;
    String b = a;
    b[1] = 'b';
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    String c = std::move(a);
    c[1] = 'c';
    std::cout << "a (moved out): " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "c: " << c << std::endl;

    String d = b + c;
    std::cout << "b + c: " << d << std::endl;
    d += "ddd";
    std::cout << "d: " << d << std::endl;

    const String& dd = d;
    std::cout << dd[0] << dd[1] << dd[2] << std::endl;

    return 0;
}
