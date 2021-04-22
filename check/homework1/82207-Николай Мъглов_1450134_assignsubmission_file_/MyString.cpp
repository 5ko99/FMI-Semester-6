#include "MyString.h"
#include <cassert>
#include <stdexcept>
MyString::MyString()
{
    m_size = 0;
    m_capacity = 0;
    m_string = nullptr;
}
MyString::MyString(const char *str)
{
    m_size = 0;
    while (str[m_size] != '\0')
        m_size++;
    m_string = new char[m_size];
    m_capacity = m_size;
    int i = 0;
    while (str[i] != '\0')
    {
        m_string[i] = str[i];
        i++;
    }
}
MyString::MyString(const MyString &mstr)
{
    m_size = mstr.size();
    m_capacity = mstr.size();
    m_string = new char[m_capacity];
    for (int i = 0; i < m_size; ++i)
    {
        (*this).at(i) = mstr.at(i);
    }
}
char &MyString::at(std::size_t pos)
{
    if (pos < 0 || pos >= m_size)
        throw std::out_of_range("");
    return m_string[pos];
}
const char &MyString::at(std::size_t pos) const
{
    return m_string[pos];
}
char &MyString::operator[](std::size_t pos)
{
#ifdef _DEBUG
    assert(pos >= 0 && pos < m_size);
#endif
    return m_string[pos];
}
const char &MyString::operator[](std::size_t pos) const
{
#ifdef _DEBUG
    assert(pos >= 0 && pos < m_size);
#endif
    return m_string[pos];
}
char &MyString::front()
{
#ifdef _DEBUG
    assert(m_size > 0);
#endif
    return m_string[0];
}
const char &MyString::front() const
{
#ifdef _DEBUG
    assert(m_size > 0);
#endif
    return m_string[0];
}
char &MyString::back()
{
#ifdef _DEBUG
    assert(m_size > 0);
#endif
    return m_string[m_size - 1];
}
const char &MyString::back() const
{
#ifdef _DEBUG
    assert(m_size > 0);
#endif
    return m_string[m_size - 1];
}
bool MyString::empty() const
{
    return m_size == 0;
}
size_t MyString::size() const
{
    return m_size;
}
void MyString::clear()
{
    delete[] m_string;
    m_string = nullptr;
    m_size = 0;
    m_capacity = 0;
}

void MyString::push_back(char c)
{
    if (m_size >= m_capacity)
    {
        if (m_capacity == 0)
            m_capacity = 1;
        else
            m_capacity *= 2;
        char *tmp = new char[m_capacity];
        for (int i = 0; i < m_size; ++i)
        {
            tmp[i] = m_string[i];
        }
        delete[] m_string;
        m_string = tmp;
    }
    m_string[m_size] = c;
    m_size++;
}
void MyString::pop_back()
{
#ifdef _DEBUG
    assert(m_size > 0);
#endif
    m_size--;
}
MyString &MyString::operator=(const MyString &other)
{
    if (this != &other)
    {
        clear();
        m_size = other.size();
        m_capacity = other.size();
        m_string = new char[m_capacity];
        for (int i = 0; i < m_size; ++i)
        {
            (*this).at(i) = other[i];
        }
    }
    return *this;
}
MyString &MyString::operator+=(char c)
{
    this->push_back(c);
    return *this;
}
MyString &MyString::operator+=(const MyString &rhs)
{
    std::size_t newCapacity = m_size + rhs.m_size;
    char *newstr = new char[newCapacity];
    std::size_t i = 0;
    for (i = 0; i < m_size; ++i)
    {
        newstr[i] = m_string[i];
    }
    for (int j = 0; j < rhs.m_size; ++j)
    {
        newstr[i] = rhs[j];
        i++;
    }
    delete[] m_string;
    m_string = newstr;
    m_size = newCapacity;
    m_capacity = newCapacity;
    return *this;
}

MyString MyString::operator+(char c) const
{
    MyString res;
    res = (*this);
    res.push_back(c);
    return res;
}
MyString MyString::operator+(const MyString &rhs) const
{
    MyString res;
    res = (*this);
    for (int i = 0; i < rhs.size(); ++i)
    {
        res.push_back(rhs[i]);
    }
    return res;
}
const char *MyString::c_str() const
{
    char *str = new char[m_size + 1];
    for (int i = 0; i < m_size; ++i)
    {
        str[i] = m_string[i];
    }
    str[m_size] = '\0';
    return str;
}
bool MyString::operator==(const MyString &rhs) const
{
    if (m_size != rhs.size())
        return false;
    for (int i = 0; i < m_size; ++i)
    {
        if (m_string[i] != rhs[i])
            return false;
    }
    return true;
}
bool MyString::operator<(const MyString &rhs) const
{
    int i;
    for (i = 0; i < m_size && i < rhs.size(); ++i)
    {
        if (rhs[i] > m_string[i])
            return true;
        if (rhs[i] < m_string[i])
            return false;
    }
    if (i == m_size)
        return false;
    return true;
}
MyString::~MyString()
{
    clear();
}
