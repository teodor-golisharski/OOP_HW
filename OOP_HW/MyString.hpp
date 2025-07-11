// Teodor Golisharski 6MI0600367
#pragma once
#include <iostream>
#include "OutputMessages.h"
#include "MyVector.hpp"

class MyString
{
    char* data;
    size_t len;

    void copyFrom(const MyString& other);
    void free();

    explicit MyString(size_t capacity);
public:

    MyString();
    MyString(const char* data);
    MyString(const MyString& other);
    MyString& operator=(const MyString& other);
    ~MyString();

    MyString(MyString&& other) noexcept;
    MyString& operator=(MyString&& other) noexcept;

    size_t length() const;
    MyString& operator+=(const MyString& other);
    MyVector<MyString> split(char delimiter) const;
    int toInt() const;
    double toDouble() const;

    MyString substr(size_t begin, size_t howMany) const;

    char& operator[](size_t index);
    char operator[](size_t index) const;

    const char* c_str() const;

    friend inline MyString operator+(const MyString& lhs, const MyString& rhs);
    friend inline std::istream& operator>>(std::istream&, MyString& str);
    friend inline std::ostream& operator<<(std::ostream& os, const MyString& str);

    friend inline bool operator<(const MyString& lhs, const MyString& rhs);
    friend inline bool operator<=(const MyString& lhs, const MyString& rhs);
    friend inline bool operator>=(const MyString& lhs, const MyString& rhs);
    friend inline bool operator>(const MyString& lhs, const MyString& rhs);
    friend inline bool operator==(const MyString& lhs, const MyString& rhs);
    friend inline bool operator!=(const MyString& lhs, const MyString& rhs);
};


inline void MyString::copyFrom(const MyString& other)
{
    len = other.len;
    data = new char[len + 1];
    if (other.data)
    {
        strcpy_s(data, len + 1, other.data);
    }
    else
    {
        data[0] = '\0';
    }
}

inline void MyString::free()
{
    delete[] data;
    data = nullptr;
}

inline MyString::MyString() : MyString(1)
{
    data[0] = '\0';
}

inline MyString::MyString(size_t capacity)
{
    len = capacity - 1;
    data = new char[capacity];
}

inline MyString::MyString(const char* str) : MyString(std::strlen(str) + 1)
{
    if (!str)
        throw std::invalid_argument(ErrorMessages::NULL_POINTER);
    strcpy_s(data, len + 1, str);
}

inline MyString::MyString(const MyString& other)
{
    copyFrom(other);
}

inline MyString& MyString::operator=(const MyString& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

inline MyString::~MyString()
{
    free();
}

inline MyString::MyString(MyString&& other) noexcept
{
    data = other.data;
    len = other.len;
    other.data = nullptr;
    other.len = 0;
}

inline MyString& MyString::operator=(MyString&& other) noexcept
{
    if (this != &other)
    {
        free();
        data = other.data;
        len = other.len;
        other.data = nullptr;
        other.len = 0;
    }
    return *this;
}

inline size_t MyString::length() const
{
    return len;
}

inline MyString& MyString::operator+=(const MyString& other)
{
    size_t newLength = len + other.len;
    char* newData = new char[newLength + 1];
    strcpy_s(newData, newLength + 1, data);
    strcat_s(newData, newLength + 1, other.data);
    delete[] data;
    data = newData;
    len = newLength;
    return *this;
}

inline MyVector<MyString> MyString::split(char delimiter) const
{
    MyVector<MyString> tokens;
    size_t start = 0;
    size_t len = length();

    for (size_t i = 0; i <= len; ++i)
    {
        if (i == len || data[i] == delimiter)
        {
            size_t tokenLen = i - start;
            if (tokenLen > 0)
            {
                tokens.push(substr(start, tokenLen));
            }
            start = i + 1;
        }
    }

    return tokens;
}

inline int MyString::toInt() const
{
    int result = 0;
    bool isNegative = false;
    size_t i = 0;

    if (data[0] == '-')
    {
        isNegative = true;
        i++;
    }

    while (data[i] >= '0' && data[i] <= '9')
    {
        result = result * 10 + (data[i] - '0');
        i++;
    }

    return isNegative ? -result : result;
}

inline double MyString::toDouble() const
{
    double result = 0.0;
    double fraction = 0.0;
    bool isNegative = false;
    bool inFraction = false;
    double divisor = 10.0;

    size_t i = 0;
    if (data[0] == '-')
    {
        isNegative = true;
        i++;
    }

    for (; data[i] != '\0'; i++)
    {
        if (data[i] == '.')
        {
            inFraction = true;
            continue;
        }

        if (data[i] >= '0' && data[i] <= '9')
        {
            if (inFraction)
            {
                fraction += (data[i] - '0') / divisor;
                divisor *= 10.0;
            }
            else
            {
                result = result * 10 + (data[i] - '0');
            }
        }
        else break;
    }

    return isNegative ? -(result + fraction) : (result + fraction);
}

inline MyString MyString::substr(size_t begin, size_t howMany) const
{
    if (begin + howMany > len)
        throw std::out_of_range(ErrorMessages::SUBSTR_OUT_OF_RANGE);

    MyString result(howMany + 1);
    for (size_t i = 0; i < howMany; i++)
        result.data[i] = data[begin + i];
    result.data[howMany] = '\0';
    return result;
}

inline char& MyString::operator[](size_t index)
{
    if (index >= len)
        throw std::out_of_range(ErrorMessages::INDEX_OUT_OF_RANGE);
    return data[index];
}

inline char MyString::operator[](size_t index) const
{
    if (index >= len)
        throw std::out_of_range(ErrorMessages::INDEX_OUT_OF_RANGE);
    return data[index];
}

inline const char* MyString::c_str() const
{
    return data;
}

inline MyString operator+(const MyString& lhs, const MyString& rhs)
{
    MyString result(lhs);
    result += rhs;
    return result;
}

inline std::istream& operator>>(std::istream& is, MyString& str)
{
    char buffer[1024];
    is >> buffer;

    delete[] str.data;
    str.len = std::strlen(buffer);
    str.data = new char[str.len + 1];
    strcpy_s(str.data, str.len + 1, buffer);
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const MyString& str)
{
    return os << str.c_str();
}

inline bool operator<(const MyString& lhs, const MyString& rhs)
{
    return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

inline bool operator<=(const MyString& lhs, const MyString& rhs)
{
    return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

inline bool operator>=(const MyString& lhs, const MyString& rhs)
{
    return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}

inline bool operator>(const MyString& lhs, const MyString& rhs)
{
    return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

inline bool operator==(const MyString& lhs, const MyString& rhs)
{
    return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

inline bool operator!=(const MyString& lhs, const MyString& rhs)
{
    return strcmp(lhs.c_str(), rhs.c_str()) != 0;
}