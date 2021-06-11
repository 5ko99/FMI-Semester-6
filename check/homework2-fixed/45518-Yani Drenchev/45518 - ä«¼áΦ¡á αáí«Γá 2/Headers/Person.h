//
// Created by Yani Drenchev on 6.05.21.
//
/* РўСѓРє Р±РёС… РєР°Р·Р°Р», С‡Рµ РјРѕР¶Рµ Р±Рё РЅРµ РѕС‡Р°РєРІР°С‚Рµ С‚РѕС‡РЅРѕ С‚Р°РєР°РІР° СЂРµР°Р»РёР·Р°С†РёСЏ РјРµР¶РґСѓ С…РѕСЂР°С‚Р° Рё
 * РїСЂРµРІРѕР·РЅРёС‚Рµ СЃСЂРµРґСЃС‚РІР°, РЅРѕ Р·Р° РјРµРЅ С‚РѕРІР° Рµ РЅР°Р№-СѓРґР°С‡РЅРѕ РІ СЃР»СѓС‡Р°СЏ. РўР°РєР° РїР°Р·РёРј СЃР°РјРѕ
 * СѓРЅРёРєР°Р»РЅРёС‚Рµ РёРЅРґРµРЅС‚РёС„РёРєР°С‚РѕСЂРё РЅР° РїСЂРµРІРѕР·РЅРё СЃСЂРµРґСЃС‚РІР°, РєР°РєС‚Рѕ РІ РµРґРЅР° РёСЃС‚РёРЅСЃРєР°
 * Р±Р°Р·Р° РѕС‚ РґР°РЅРЅРё Р±Рё СЃРµ СЃР»СѓС‡РёР»Р° СЂРµР°Р»РёР·Р°С†РёСЏС‚Р°. РўР°Рј РІ С‚Р°Р±Р»РёС†Р°С‚Р° РЅР° С…РѕСЂР° С‰Рµ РёРјР°
 * РёРґ - С‚Р° РЅР° РїСЂРµРІРѕР·РЅРёС‚Рµ СЃСЂРµРґСЃС‚РІР° Рё РІСЂСЉР·РєР°С‚Р° С‰Рµ Рµ one to many.
 *
 * РћРїРµСЂР°С‚РѕСЂСЉС‚ == РјРё С‚СЂСЏР±РІР° РїСЂРё С‚СЉСЂСЃРµРЅРµ РЅР° С…РѕСЂР° РІ СЃРїРёСЃСЉРєР° РІ DataBase.
 * */

#include <vector>
#include <string>
#include "Registration.h"

#ifndef HOMEWORK2_PERSON_H
#define HOMEWORK2_PERSON_H

class Person {
private:
    unsigned int id;
    std::string name;
    std::vector<Registration> vehicles;
public:
    unsigned int getId() const;

    std::string getName() const;

    std::vector<Registration> getVehicles() const;

    Person(const std::string &, const unsigned int);

    bool operator==(const Person &) const;

    bool addVehicle(const Registration &);

    bool removeVehicle(const Registration &);

    void print() const;
};

#endif //HOMEWORK2_PERSON_H
