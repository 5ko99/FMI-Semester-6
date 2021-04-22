#include <cassert>
#include <iostream>
#include <cstring>
#include "MyString.h"

using std::cin;
using std::cout;
using std::endl;
//using std::exception;
//TODO bad::alocate

//*******************************************************************/
// +
MyString::MyString()
{
    // constructor
}

// +
MyString::~MyString()
{
    // destructor
    delete[] str;
}

// +
MyString::MyString(const MyString &other)
{
    //Copy Constructor
    copyFrom(other);
}

// +
MyString &MyString::operator=(const MyString &other)
{
    // Copy Assignment Operator
    if (this != &other) //x = x
    {
        copyFrom(other);
    }
    return *this;
}

// i think there might be a better implementation
MyString::MyString(const char *str)
{
    // създава нов обект и копира в него съдържанието на str.

    this->str = new char[1];
    length = 1;
    allocatedCapacity = 1;
    this->str[0] = str[0];

    size_t i = 1;
    while (true)
    {
        if (str[i] == '\0')
            break;
        this->push_back(str[i]);
        i++;
    }
}

//**********************************************************************************************
//at; []

//+l
char &MyString::at(std::size_t pos)
{
    // достъп до елемента намиращ се на позиция pos. Ако такъв няма, да се хвърля изключение std::out_of_range.
    if (pos >= length || pos < 0)
    {
        throw std::out_of_range("index is out of range");
    }

    return str[pos];
}

//+l
const char &MyString::at(std::size_t pos) const
{
    // Като по-горното, но за константи.
    if (pos >= length || pos < 0)
    {
        throw std::out_of_range("index out of range");
    }

    return str[pos];
}

//+l
char &MyString::operator[](std::size_t pos)
{
    // достъп до елемента намиращ се на позиция pos. Функцията да не прави проверка за коректност дали pos е валидна позиция. (В debug режим assert-вайте дали pos е валидна позиция).
    assert(pos < length);
    return str[pos];
}

//+l
const char &MyString::operator[](std::size_t pos) const
{
    // Като по-горното, но за константи.
    assert(pos < length);
    return str[pos];
}

//**********************************************************************************************
//front; back
// +
char &MyString::front()
{
    // достъп до първия символ в низа. Да НЕ СЕ прави проверка за коректност дали такъв символ има. (В debug режим assert-вайте че низът не е празен).
    assert(length);
    return str[0];
}
// +
const char &MyString::front() const
{
    // Като по-горното, но за константи.
    assert(length);
    return str[0];
}
// +
char &MyString::back()
{
    // достъп до последния символ в низа. Да не се прави проверка за коректност дали такъв символ има. (В debug режим assert-вайте че низът не е празен).
    assert(length);
    return str[length - 1];
}
// +
const char &MyString::back() const
{
    // Като по-горното, но за константи.
    assert(length);
    return str[length - 1];
}

// //**********************************************************************************************
//mischevous
// +
bool MyString::empty() const
{
    // Проверява дали низът е празен.
    return !length;
}
// +
std::size_t MyString::size() const
{
    // дължина на низа.
    return length;
}
// +
void MyString::clear()
{
    // изчиства съдържанието на низа.
    delete[] str;
    str = nullptr;
    length = 0;
    allocatedCapacity = 0;
}

//**********************************************************************************************
//add; delete last char
// +
void MyString::push_back(char c)
{
    // добавя символа c в края на низа. Операцията да дава strong exception guarantee.

    if (length + 1 > allocatedCapacity)
    {
        expand();
    }
    try
    {
        str[length] = c;
        length++;
    }
    catch (std::bad_alloc())
    {
    }
}

//+
void MyString::pop_back()
{
    // премахва последния символ от низа. Да не се прави проверка за коректност дали такъв символ има. (В debug режим assert-вайте че низът не е празен).
    assert(length);
    length--;
}

//**********************************************************************************************
//+
void MyString::print()
{
    //printing
    for (size_t i = 0; i < length; ++i)
    {
        std::cout << str[i];
    }
}

// +
std::ostream &operator<<(std::ostream &os, const MyString &str)
{
    for (size_t i = 0; i < str.length; ++i)
    {
        os << str[i];
    }
    return os;
}

// std::istream& operator>> (std::istream& is, MyString& str){

//     size_t i = 0;
//     while(true){
//         if(str[i] == '\0') break;
//         str.push_back(str[i]);
//     }

//     is >> str;
//     return is;
// }

//**********************************************************************************************
//operators
//+
MyString &MyString::operator+=(char c)
{
    // добавя символа c в края на низа. Операцията да дава strong exception guarantee. Връща *this.
    push_back(c);
    return *this;
}

// +
MyString &MyString::operator+=(const MyString &rhs)
{
    // конкатенира съдържанието на str към текущия низ. Операцията да дава strong exception guarantee. Връща *this.

    for (size_t i = 0; i < rhs.length; ++i)
    {
        push_back(rhs[i]);
    }
    return *this;
}

// +
MyString MyString::operator+(char c) const
{
    // Връща нов символен низ, който се получава от текущия, конкатениран със символа c.

    MyString newStr;
    //newStr.str = str;
    newStr = *this; //ддз и двете работят
    newStr.push_back(c);

    return newStr;
}

//+
MyString MyString::operator+(const MyString &rhs) const
{
    // Връща нов символен низ, който се получава от текущия, конкатениран с низа rhs.
    MyString newStr;
    //newStr.str = str;
    newStr = *this;
    newStr += rhs;

    return newStr;
}

// +
const char *MyString::c_str() const
{
    // връща указател към null-terminated масив от тип char, който има съдържание идентично с това на низа.
    if (length == 0)
        return nullptr;

    char *newStr = new char[length + 1];
    for (size_t i = 0; i < length; ++i)
    {
        newStr[i] = str[i];
    }
    newStr[length] = '\0';

    return newStr;
}

// +
bool MyString::operator==(const MyString &rhs) const
{
    // Проверява дали два символни низа са еднакви.
    if (length != rhs.length)
        return false;

    for (int i = 0; i < length; i++)
    {
        if (str[i] != rhs.str[i])
            return false;
    }
    return true;
}

// +
bool MyString::operator!=(const MyString &rhs) const
{
    // *Проверява дали два символни низа не са еднакви.
    return !operator==(rhs);
}

// +
bool MyString::operator<(const MyString &rhs) const
{
    // Проверява дали текущият низ предхожда лексикографски rhs.

    size_t shorter = this->length;
    if (this->length > rhs.length)
        shorter = rhs.length;

    for (size_t i = 0; i < shorter; ++i)
    {

        if (this->str[i] < rhs.str[i])
        {
            return true;
        }
        else if (this->str[i] > rhs.str[i])
        {
            return false;
        }
    }

    if (this->length > rhs.length)
        return false;

    return true;
}

// +
bool MyString::operator>(const MyString &rhs) const
{
    // *Проверява дали текущият низ задхожда лексикографски rhs.
    return !operator<(rhs);
}

//**********************************************************************************************
//**********************************************************************************************
// private mathods

//+
void MyString::expand()
{

    // 1. allocated a new array with more capacity
    char *newStr = new char[2 * allocatedCapacity];

    if (newStr)
    {

        // 2. copy all data
        for (size_t i = 0; i < length; i++)
        {
            newStr[i] = str[i];
        }

        // 3. delete old array
        delete[] str;

        // 4. update pointer
        str = newStr;

        // 5. update allocatedCapacity
        allocatedCapacity *= 2;
    }
    else
    {
        throw std::bad_alloc();
    }
}

// +
void MyString::copyFrom(const MyString &other)
{

    char *buffer = new char[other.allocatedCapacity];
    if (buffer)
    {
        for (size_t i = 0; i < other.length; ++i)
        {
            buffer[i] = other.str[i];
        }
        delete[] str;

        str = buffer;
        allocatedCapacity = other.allocatedCapacity;
        length = other.length;
    }
    else
    {
        throw std::bad_alloc();
    }
}