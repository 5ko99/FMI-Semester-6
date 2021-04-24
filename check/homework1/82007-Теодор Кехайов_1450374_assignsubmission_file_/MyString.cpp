#include "MyString.h"


    MyString::MyString()  /// default constructor
    {
        lenght=0;
        str = new char[lenght + 1];
        str[0] = '\0';
    }

    /// създава нов обект и копира в него съдържанието на str
    MyString::MyString(const char* str)
    {
        lenght=strlen(str);
        this->str = new char[lenght + 1];

        strcpy(this->str,str);
        this->str[lenght]='\0';
    }

    /// Rule Of Three
    /// destructor
    MyString::~MyString() { delete [] str; }

    /// copy constructor
    MyString::MyString(const MyString& str)
    {
        lenght = str.lenght;
        this->str = new char[lenght+1];
        strcpy(this->str,str.str);
    }

    /// copy assignment operator
    MyString& MyString::operator= (const MyString& str1)
    {
        if (this != &str1)
        {
            delete str;
            lenght = strlen(str1.str);
            str = new char[lenght+1];
            strcpy(str,str1.str);
            str[lenght]='\0';
        }

        return *this;
    }


    /// достъп до елемента намиращ се на позиция pos
    char& MyString::at(std::size_t pos)
    {
        if((pos>size() - 1) || pos < 0) throw std::out_of_range("Invalid position!");
        return str[pos];
    }
    const char& MyString::at(std::size_t pos) const
    {
        if((pos>size() - 1) || pos < 0) throw std::out_of_range("Invalid position!");
        return str[pos];
    }

    /// operator за достъп до елемент намиращ се на позиция pos
    char& MyString::operator[](std::size_t pos)
    {
        return str[pos];
    }
    const char& MyString::operator[](std::size_t pos) const
    {
        return str[pos];
    }

    /// достъп до първия символ в низа
    char& MyString::front() { return str[0]; }
    const char& MyString::front() const { return str[0]; }

    /// достъп до последния символ в низа
    char& MyString::back() { return str[strlen(str) - 1]; }
    const char& MyString::back() const { return str[strlen(str) - 1]; }

    /// проверява дали низът е празен
    bool MyString::empty() const
    {
        if(!strlen(str)) return true;
        return false;
    }

    /// дължина на низа
    std::size_t MyString::size() const
    {
        return lenght;
    }

    /// изчиства съдържанието на низа
    void MyString::clear()
    {
        delete this->str;
        this->str = nullptr;
    }

    /// добавя символа c в края на низа
    void MyString::push_back(char c)
    {
        int temp = size();
        char* newStr = new char[temp + 2];

        for (int i = 0; i < temp; i++)
        {
            newStr[i] = str[i];
        }

        newStr[temp]=c;
        newStr[temp + 1]='\0';

        *this = MyString(newStr);
        delete [] newStr;
    }

    /// премахва последния символ от низа
    void MyString::pop_back()
    {
        int temp = size();
        char* newStr = new char[temp];

        for (int i = 0; i < temp-1; i++)
        {
            newStr[i]=str[i];
        }
        newStr[temp - 1]='\0';

        *this = MyString(newStr);
        delete [] newStr;
    }

    /// operator , добавящ символа c в края на низа
    MyString& MyString::operator+=(char c)
    {
        int temp = size();
        char* newStr = new char[temp + 2];

        for (int i = 0; i < temp; i++)
        {
            newStr[i]=str[i];
        }
        newStr[temp]=c;
        newStr[temp + 1]='\0';

        *this = MyString(newStr);
        delete [] newStr;

        return *this;
    }

    MyString& MyString::operator+=(const MyString& rhs)
    {
        int temp = size() + rhs.size();
        char* newStr = new char[temp + 1];

        for (int i = 0; i < size(); i++)
        {
            newStr[i]=str[i];
        }
        int i,j=0;
        for (i = size(); i < temp; i++)
        {
            newStr[i]=rhs[j];
            j++;
        }

        newStr[temp]='\0';

        *this = MyString(newStr);
        delete [] newStr;

        return *this;
    }

    /// operator за конкатениране на низ със символа c
    MyString MyString::operator+(char c) const
    {
        int temp = size();
        char* newStr = new char[temp + 2];

        strcpy(newStr,str);
        newStr[temp]=c;
        newStr[temp + 1]='\0';

        MyString tempStr{newStr};

        delete [] newStr;
        return tempStr;
    }

    MyString MyString::operator+(const MyString& rhs) const
    {
        int temp = size() + rhs.size();
        char* newStr = new char[temp + 1];

        strcpy(newStr,str);
        strcat(newStr,rhs.str);
        newStr[temp]='\0';

        MyString tempStr{newStr};

        delete [] newStr;
        return tempStr;
    }

    /// проверява дали два символни низа са еднакви
    bool MyString::operator== (const MyString& rhs) const
    {
        if (strcmp(str, rhs.str) == 0)  return true;
        return false;
    }

    bool MyString::operator== (const char* rhs) const
    {
        if(strcmp(str,rhs) == 0) return true;
        return false;
    }

    /// проверява дали текущият низ предхожда лексикографски rhs
    bool MyString::operator<(const MyString &rhs) const
    {
        if (strcmp(this->str, rhs.str) < 0) { return true; }
        return false;
    }
    bool MyString::operator>(const MyString &rhs) const
    {
        if (strcmp(this->str, rhs.str) > 0) { return true; }
        return false;
    }

    /// връща указател към null-terminated масив, който има съдържание идентично с това на низа
    const char* MyString::c_str() const
    {
        return str;
    }


    std::ostream& operator<< (std::ostream& os, const MyString& str)
    {
        if (str.str)
        {
            for (int i = 0; i < str.lenght; ++i)
            {
                os<<str.str[i];
            }
        }
        return os;
    }



    std::istream & operator>> (std::istream & is, MyString &str)
    {
        char newStr[1024];
        is >> newStr;

        if (str.str) {
            delete str.str;
            str.str = nullptr;
        }

        str.str = new char[strlen(newStr) + 1];
        strcpy(str.str, newStr);
        str.str[strlen(newStr)]= '\0';

        return is;
    }
