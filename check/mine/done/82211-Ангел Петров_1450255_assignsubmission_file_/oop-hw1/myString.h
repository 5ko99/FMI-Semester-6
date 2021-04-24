#ifndef MYSTRING_H
#define MYSTRING_H

class MyString {

    private: 

    char* string;
    std::size_t sizeOfString;

    void setSize();

    public:

    MyString ();
    MyString (const char* other);
    
    ~MyString ();
    MyString(const MyString& other);
    MyString& operator=(const MyString& other);
    
    char& at(std::size_t pos);
    const char& at(std::size_t pos) const; 
 
    char& operator[](std::size_t pos);
    const char& operator[](std::size_t pos) const;

    char& front();
    const char& front() const;

    char& back();
    const char& back() const;

    bool empty () const;
    std::size_t size() const;
    void clear ();
    void push_back(char c);
    void pop_back();

    MyString& operator+=(char c);
    MyString& operator+=(const MyString& rhs);
    MyString operator+(char c) const;
    MyString operator+(const MyString& rhs) const;

    const char* c_str() const;
    bool operator==(const MyString &rhs) const;
    bool operator<(const MyString &rhs) const;
};

#endif