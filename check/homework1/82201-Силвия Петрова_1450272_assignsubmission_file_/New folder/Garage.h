#pragma once

#include "Vehicle.h"

/*! Garage - гараж */
class Garage
{

public:
    //constructors
    Garage(std::size_t size); //!< създава гараж с максимално място за паркиране size.
    //Всички функции от rule of 3 (бонус: всички от rule of 5)
    ~Garage(); //!< *Destructor
    //Garage(const Garage& str); //!< *Copy Constructor
    //Garage& operator=(const Garage& other); //!< *Copy Assignment Operator

    // add delete
    void insert(Vehicle &v);              //!< добавя превозното средство v в гаража. Ако операцията не успее (например няма достатъчно памет, в гаража няма повече място за паркиране, вече има кола със същия регистрационен номер), да се хвърля изключение. Операцията да дава strong exception guarantee.
    void erase(const char *registration); //!< премахва колата с регистрационен номер registration от гаража. Ако такава няма, да не се прави нищо. При премахването на кола от гаража е допустимо да се промени редът на останалите в гаража. Това условие ще ви позволи при премахване на елемент да поставите последния елемент от масива на мястото на премахнатия, вместо да правите left shift.

    // at []
    const Vehicle &at(std::size_t pos) const;         //!< достъп до елемента намиращ се на позиция pos. Ако такъв няма, да се хвърля изключение std::out_of_range.
    const Vehicle &operator[](std::size_t pos) const; //!< достъп до елемента намиращ се на позиция pos. Функцията да не прави проверка за коректност дали pos е валидна позиция. (В debug режим assert-вайте дали pos е валидна позиция)

    //mischevous
    bool empty() const;       //!< Проверява дали гаражът е празен
    std::size_t size() const; //!< брой елементи (превозни средства) в гаража
    void clear();             //!< изчиства съдържанието на гаража. Това означава, че в него не се съдържа нито една кола. Капацитетът му обаче остава непроменен. Така в него могат отново да се добавят нови коли

    //find
    const Vehicle *find(const char *registration) const; //!< намира и връща превозното средство с регистрационен номер registration в гаража. Ако такова няма, да се върне nullptr.

    //print
    void print(); //!< *prints out contents of Garage

private:
    Vehicle **vehicle = nullptr;
    int numCars = 0;
    std::size_t capacity;

    // уточнение за това, че не трябва да се държи отчет на
    // паркоместата в гаража, а само на заетия обем.
    bool valid(Vehicle &v); //!< *Трябва да се отчита капацитетa и броят на вече добавните превозни средства. & Освен това, в един гараж не може да има две коли с еднакви регистрационни номера.
};