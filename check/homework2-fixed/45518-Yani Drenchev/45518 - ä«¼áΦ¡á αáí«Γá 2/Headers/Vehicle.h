//
// Created by Yani Drenchev on 6.05.21.
//


/* РћС‚РЅРѕРІРѕ РјРѕР¶Рµ Р±Рё РЅРµ С‚РѕРІР°, РєРѕРµС‚Рѕ СЃС‚Рµ РёСЃРєР°Р»Рё, РЅРѕ Р·Р° РјРЅРµ РёР·РіР»РµР¶РґР° РїРѕ-РЅРѕСЂРјР°Р»РЅРѕ
 * РґР° СЃРµ РїР°Р·Рё РµРґРЅРѕ РР” РІ С‚РѕР·Рё РєР»Р°СЃ РІРјРµСЃС‚Рѕ РїСЂРµРїСЂР°С‚РєР° РєСЉРј СЃРѕР±СЃС‚РІРµРЅРёРєР°.
 * РЎ РµРґРЅРѕ РїСЂРµРјСЏС‚Р°РЅРµ РЅР° РјР°СЃРёРІ С‚РѕР·Рё СЃРѕР±СЃС‚РІРµРЅРёРє РІРµС‡Рµ СЃРїРёСЂР° РґР° РїСЂРёС‚РµР¶Р°РІР° С‚Р°Р·Рё РєРѕР»Р°,
 * Р° Рё СЃРё СЃРїРµСЃС‚СЏРІР°Рј РјСЉРєРё.
 *
 * РЎР°РјРѕ РЅРµ СЂР°Р·Р±РёСЂР°Рј Р·Р°С‰Рѕ РІ Р·Р°РґР°С‡Р°С‚Р° РёР·РѕР±С‰Рѕ СЃСЉС‰РµСЃС‚РІСѓРІР° С‚РѕРІР° description, РєР°С‚Рѕ Р·Р° РЅРµРіРѕ
 * СЃРµ РѕРєР°Р·Р°, С‡Рµ РЅРµ РјРё С‚СЂСЏР±РІР° Рё getter, РЅРѕ СЃСЉРј РіРѕ СЃР»РѕР¶РёР». РџСЂРёРЅС‚РёСЂР°Рј РіРѕ РїСЂРё РїСЂРёРЅС‚РёСЂР°РЅРµС‚Рѕ РЅР° Р°РІС‚РѕРјРѕР±РёР»Р°.
 *
 * РћРїРµСЂР°С‚РѕСЂ == РјРё С‚СЂСЏРІР±Р° РїСЂРё С‚СЉСЂСЃРµРЅРµ РЅР° РєРѕР»Р° РІ РјР°СЃРёРІ.
 * */
#include "Registration.h"
#include "Person.h"

#ifndef HOMEWORK2_VEHICLE_H
#define HOMEWORK2_VEHICLE_H


class Vehicle {
private:
    Registration registration;
    std::string description;
    unsigned int person;
public:
    Vehicle(const std::string &, const std::string &);

    Registration getRegistration() const;

    unsigned int getPerson() const;

    void print() const;

    void setPerson(unsigned int);

    bool operator == (const Vehicle &) const;

};

#endif //HOMEWORK2_VEHICLE_H
