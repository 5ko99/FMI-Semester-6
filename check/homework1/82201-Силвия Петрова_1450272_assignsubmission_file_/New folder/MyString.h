#pragma once
#include <iostream>

/*! My String - представя символен низ */
class MyString
{

public:
    MyString(); //!< Default constructor.
    //Всички функции от rule of 3 (бонус: всички от rule of 5)
    ~MyString();                                //!< *Destructor
    MyString(const MyString &other);            //!< *Copy Constructor  //не е инициализиран
    MyString &operator=(const MyString &other); //!< *Copy Assignment Operator   //вече е инициализира

    MyString(const char *str); //!< създава нов обект и копира в него съдържанието на str.

    //at; []
    char &at(std::size_t pos);                     //!< достъп до елемента намиращ се на позиция pos. Ако такъв няма, да се хвърля изключение std::out_of_range.
    const char &at(std::size_t pos) const;         //!< Като по-горното, но за константи.
    char &operator[](std::size_t pos);             //!< достъп до елемента на+миращ се на позиция pos. Функцията да не прави проверка за коректност дали pos е валидна позиция. (В debug режим assert-вайте дали pos е валидна позиция).
    const char &operator[](std::size_t pos) const; //!< Като по-горното, но за константи.

    //front; back
    char &front();             //!< достъп до първия символ в низа. Да НЕ СЕ прави проверка за коректност дали такъв символ има. (В debug режим assert-вайте че низът не е празен).
    const char &front() const; //!< Като по-горното, но за константи.
    char &back();              //!< достъп до последния символ в низа. Да не се прави проверка за коректност дали такъв символ има. (В debug режим assert-вайте че низът не е празен).
    const char &back() const;  //!< Като по-горното, но за константи.

    //mischevous
    bool empty() const;       //!< Проверява дали низът е празен.
    std::size_t size() const; //!< дължина на низа.
    void clear();             //!< изчиства съдържанието на низа.

    // //add; delete last char
    void push_back(char c); //!< добавя символа c в края на низа. Операцията да дава strong exception guarantee.
    void pop_back();        //!< премахва последния символ от низа. Да не се прави проверка за коректност дали такъв символ има. (В debug режим assert-вайте че низът не е празен).

    //printing
    void print();                                                           //!< * prints string
    friend std::ostream &operator<<(std::ostream &os, const MyString &str); //!<* prints string
    friend std::istream &operator>>(std::istream &is, MyString &str);       //<* inputs string

    //operators
    MyString &operator+=(char c);                  //!< добавя символа c в края на низа. Операцията да дава strong exception guarantee. Връща *this.
    MyString &operator+=(const MyString &rhs);     //!< конкатенира съдържанието на str към текущия низ. Операцията да дава strong exception guarantee. Връща *this.
    MyString operator+(char c) const;              //!< Връща нов символен низ, който се получава от текущия, конкатениран със символа c.
    MyString operator+(const MyString &rhs) const; //!< Връща нов символен низ, който се получава от текущия, конкатениран с низа rhs.
    const char *c_str() const;                     //!< връща указател към null-terminated масив от тип char, който има съдържание идентично с това на низа.
    bool operator==(const MyString &rhs) const;    //!< Проверява дали два символни низа са еднакви.
    bool operator!=(const MyString &rhs) const;    //!<* Проверява дали два символни низа не са еднакви.
    bool operator<(const MyString &rhs) const;     //!< Проверява дали текущият низ предхожда лексикографски rhs.
    bool operator>(const MyString &rhs) const;     //!< *Проверява дали текущият низ задхожда лексикографски rhs.

private:
    char *str = nullptr;               //указател към първи елемент
    std::size_t length = 0;            // размер на масива
    std::size_t allocatedCapacity = 0; // the amount of space allocated at the moment

    void expand();                        // *increase allocated space
    void copyFrom(const MyString &other); //* from lecture
};