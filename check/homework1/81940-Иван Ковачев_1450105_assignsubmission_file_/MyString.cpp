
#include "MyString.h"

MyString::MyString()
{
    str = nullptr;
    my_size = 0;
    /// my default capacity is 16 chars
    my_capacity = 16;
}
MyString::MyString(const char* str)
{
    setStr(str);
    my_size = strlen(str) ;
    my_capacity = my_size * 2;
}

MyString::MyString(const MyString& other)
{
	setStr(other.getStr());
	my_size = other.my_size;
	my_capacity = other.my_capacity;
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		Free();
		setStr(other.getStr());
		my_size = other.my_size;
		my_capacity = other.my_capacity;
	}
	return *this;
}

char& MyString::at(std::size_t pos)
{
	if (pos > my_size - 1 || pos < 0)
        throw std::out_of_range("Invalid position");
    return str[pos];
}

const char& MyString::at(std::size_t pos) const
{
	if (pos > my_size - 1 || pos < 0)
        throw std::out_of_range("Invalid position");
    return str[pos];
}


char& MyString::operator[](std::size_t pos)
{
	return str[pos];
}

const char& MyString::operator[](std::size_t pos) const
{
	return str[pos];
}

char& MyString::front()
{
    return str[0];
}

const char& MyString:: front() const
{
    return str[0];
}

char& MyString::back()
{
    return str[my_size-1];
}
const char& MyString::back() const
{
    return str[my_size-1];
}
std::size_t MyString::size() const
{
    return my_size;
}

void MyString::push_back(char c)
{
    /// kakwo znachi strong exception guarantee
    if(this == nullptr) std::cout << "Nullptr exception\n";

    if(my_size >= my_capacity)
        expand();
    str[ my_size++ ] = c;
}

void MyString::pop_back()
{
    //if(this == nullptr) std::cout << "Nullptr exception\n";
    if(my_size == 0) std::cout << "Empty string\n";

    str[my_size-1] = 0;
    my_size--;

}
MyString& MyString :: operator+=(char c)
{
    if(str==nullptr){
        str = new char[1];
        str[0] = c;


        return *this;
    }
    if(my_size >= my_capacity)
        expand();
    str[my_size] = c;
    my_size++;
    return *this;
}
MyString& MyString:: operator+=(const MyString& rhs)
{
    if(str==nullptr){
        str = new char[rhs.getCapacity()];
        for(int i=0;i<rhs.getSize();i++){
                str[i] = rhs[i];
        }
        return *this;
    }
    std::size_t bdmTss = my_size + rhs.my_size;
    while( bdmTss > my_size )
        expand();
    for(size_t i = my_size, j = 0; i < rhs.getSize(); i++, j++)
    {
        str[i] = rhs.getStr()[j];
    }
    my_size += rhs.getSize();
    return *this;
}
MyString MyString::operator+(char c) const
{
    char* temp = str;
    temp += c;
    return temp;
}
//check again
MyString MyString::operator+(const MyString& rhs) const
{

    MyString tmp(*this);
    tmp += rhs.getStr();
    return tmp;
}
const char* MyString :: c_str() const
{
    /// does that count as nullterminated string?
    str[my_size] = 0;
    return str;
}
bool MyString::operator==(const MyString &rhs) const
{
    return !strcmp(getStr(), rhs.getStr());
}
bool MyString::operator<(const MyString &rhs) const
{
    int result = strcmp(getStr(), rhs.getStr());
    return result > 0;
}

void MyString::Free()
{
    delete[] str;
}


char* MyString::getStr() const{	return str;}
size_t MyString::getSize() const { return my_size; }
size_t MyString::getCapacity() const { return my_capacity; }

void MyString::setStr(const char* str)
{
    delete[] this->str;
    int length = strlen(str) + 1;
    this->str = new char[length];
    strcpy_s(this->str, length, str);
}

MyString::~MyString()
{
    Free();
}

void MyString::expand()
{
    my_capacity *= 2;
    char *temp = new char[my_capacity];
    for(std::size_t i=0; i<my_size; i++)
        temp[i] = str[i];
    delete[] str;
    str = temp;
}

