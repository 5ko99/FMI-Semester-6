 #ifndef ORGANIZER_H
#define ORGANIZER_H

#include "Person.hpp"

class Organizer //singleton
{
private:
    std::vector<Person> people; 
    std::vector<Vehicle> vehicles; 

    Organizer(); 

public:
    Organizer(const Organizer& other) = delete;
    void operator=(const Organizer& other) = delete;
    static Organizer& getInstance();

    //РїСЂРѕРІРµСЂРєРё С‚СѓРє!
    void addVehicle(std::string registration, std::string description); //should check if the reg is taken!
    void addPerson(std::string name, unsigned int id); //should check if the id is taken before adding the person!
    void acquire(unsigned int id, std::string registration); //griji se za Vehicle i Person 
    void release(unsigned int id, std::string registration); //griji se za Vehicle i Person
    
    void remove(unsigned int id); //removes a person 
    void remove(std::string registration); //removes a vehicle //NA GORNOTO NIVO РґР° СЃРµ РёСЃРєР° РїРѕС‚РІСЉСЂР¶Рґ РѕС‚ РїРѕС‚СЂРµР±РёС‚РµР»СЏ
    
    //The following functions are used only for the unit tests:
    unsigned getPersonId(std::size_t pos) const;
    std::string getVehicleReg(std::size_t pos) const;
    Person* getPerson(unsigned id);
    Vehicle getVehicle(std::string registration);
};

#endif


    //РђРєРѕ СЃРµ РѕРїРёС‚РІР° РґР° СЃРµ РїСЂРµРјР°С…РЅРµ РєРѕР»Р°, РєРѕСЏС‚Рѕ РёРјР° СЃРѕР±СЃС‚РІРµРЅРёРє РёР»Рё СЃРѕР±СЃС‚РІРµРЅРёРє, 
    // РєРѕР№С‚Рѕ РїСЂРёС‚РµР¶Р°РІР° РєРѕР»Рё, РґР° СЃРµ РёР·РІРµРґРµ СЃСЉРѕР±С‰РµРЅРёРµ Рё РґР° СЃРµ РїРѕРїРёС‚Р° РїРѕС‚СЂРµР±РёС‚РµР»СЏС‚ РґР°Р»Рё 
    // Рµ СЃРёРіСѓСЂРµРЅ. РђРєРѕ С‚РѕР№ РїРѕС‚РІСЉСЂРґРё, РѕР±РµРєС‚СЉС‚ РґР° СЃРµ РёР·С‚СЂРёРµ, РЅРѕ РґР° СЃРµ РєРѕСЂРёРіРёСЂР°С‚ РѕСЃС‚Р°РЅР°Р»РёС‚Рµ, 
    // РєРѕРёС‚Рѕ СЃР° СЃРІСЉСЂР·Р°РЅРё СЃ РЅРµРіРѕ.
