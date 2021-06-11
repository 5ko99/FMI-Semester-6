#ifndef PERSON_H
#define PERSON_H

#include "Vehicle.hpp"
#include <vector>

class Person
{
private:
    std::string name;
    unsigned int id; //make sure it is not 0!
    std::vector<Vehicle*> vehicles;
    
public:
    Person(std::string name, unsigned int id); //РїРѕ СЃСЉС‰РµСЃС‚РІРѕ РЅРµ Рµ РїСЂРѕР±Р»РµРј Р°РєРѕ СЃРµ СЃР»СѓС‡Рё РґР° СЃРµ СЃСЉР·РґР°РґРµ РёР·РІСЉРЅ РєР»Р°СЃР° 
    //Organizer, Р·Р°С‰РѕС‚Рѕ С‚Р°РєР° РёР»Рё РёРЅР°С‡Рµ РЅРµРіРѕРІРёС‚Рµ РјРµС‚РѕРґРё С‚СЉСЂСЃСЏС‚ СЃР°РјРѕ РІ РЅРµРіРѕРІР°С‚Р° СЃРё Р±Р°Р·Р° РґР°РЅРЅРё. Р’СЃРµ РїР°Рє Р°Р· РЅРµ РїСЂРµРґРІРёР¶РґР°Рј РґР° 
    //СЃРµ СЃСЉР·РґР°РІР°С‚ РѕР±РµРєС‚Рё РёР·РІСЉРЅ Organizer //na gornoto nivo proverka za id! 
    Person(const Person& other);
    ~Person();

    std::string getName() const;
    unsigned getId() const;
    std::size_t numberOfVehicles() const;
    Vehicle* getVehicle(std::size_t pos) const; // !doesn't return a pointer to prevent unwanted changes to the object

    bool addVehicle(Vehicle& veh); //bez proverki tuk; na gornoto nivo! //РґРѕР±Р°РІСЏ РљРћРџРР• РІСЉРІ РІРµРєС‚РѕСЂР° РЅР° person //vryshta dali e bilo usp
    bool releaseVehicle(Registration registration); //РїСЉСЂРІРѕ РїСЂРѕРІРµСЂСЏРІР° РґР°Р»Рё РёРјР° С‚Р°РєРѕРІР° РІСЉРІ РІРµРєС‚РѕСЂР° /РІСЂСЉС‰Р° РґР°Р»Рё РѕРїРµСЂР°С†РёСЏС‚Р° Рµ 
                                                    //Р±РёР»Р° СѓСЃРїРµС€РЅР° (С‚.Рє. СЃРµ Р±РѕСЂР°РІРё СЃ РєРѕРїРёСЏС‚Р°, СЃР°РјРѕС‚Рѕ vehicle РЅРµ СЃРїРёСЂР° РґР° СЃСЉС‰РµСЃС‚РІ)

};


#endif
