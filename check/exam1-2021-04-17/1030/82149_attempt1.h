// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име:Димитър Стефанов
// ФН:82149
// Специалност:КН
// Курс:1
// Административна група:група 2
// Ден, в който се явявате на контролното:събота 17.04.2021г.
// Начален час на контролното: 10:30
// Кой компилатор използвате: <посочете едно от Visual C++, GCC или Clang>
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cstdint>

#pragma once
class RegistrationList
{
    private:
    size_t used;
    size_t capacity;

    public:
    RegistrationList(std::size_t _capacity);
    void insert(const std::string& id, const Date& date);
    const Registration& at(std::size_t index) const;
    const Registration& operator[](std::size_t index) const;
    bool empty() const;
    std::size_t capacity() const;
    std::size_t size() const;

}
















