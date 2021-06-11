//
// Created by Yani Drenchev on 10.05.21.
//
#include <fstream>
#include "Vehicle.h"
#include "Person.h"
#include "Command.h"
/* РўСѓРє СЂРµР°Р»РёР·Р°С†РёСЏС‚Р° Рё РЅР° РјРµРЅ РЅРµ РјРё С…Р°СЂРµСЃРІР°. Р’СЉР·РјРѕР¶РЅРѕ Рµ С‚РѕР·Рё РєР»Р°СЃ РґР° СЃРµ СЂР°Р·Р±РёРµ РЅР° РїРѕ-РјР°Р»РєРё
 * РїР°СЂС‡РµС‚Р°, РЅРѕ С‚РѕРІР° СЃРїРѕСЂРµРґ РјРµРЅ РЅРµ СЃРµ РёР·РёСЃРєРІР° РІ Р·Р°РґР°С‡Р°С‚Р°. Р’ РјРѕРјРµРЅС‚Р° Рµ СЃСЉР·РґР°РґРµРЅ РµРґРёРЅ "РњР°СЃС‚СЉСЂ РєР»Р°СЃ",
 * РєРѕРµС‚Рѕ РїРѕ РїСЂРёРЅС†РёРї РЅРµ Рµ РґРѕР±СЂР° РїСЂР°РєС‚РёРєР°. Р’СЉР·РјРѕР¶РЅРѕ Рµ РґР° СЃРµ РЅР°РїСЂР°РІРё РѕС‚РґРµР»РЅР° СЂРµР°Р»РёР·Р°С†РёСЏ Р·Р°
 * РёР·РїСЉР»РЅРµРЅРёРµС‚Рѕ РЅР° РєРѕРјР°РЅРґРёС‚Рµ Рё С‚РѕР·Рё РєР»Р°СЃ РґР° РїР°Р·Рё РґР°РЅРЅРё Р·Р° DataBasePeople, DataBaseVehicle Рё С‚.РЅ, РЅРѕ
 * С‚РѕРІР° РІРµС‡Рµ СЃС‚Р°РІР° РЅРµ С‚РѕР»РєРѕРІР° "РїСЂРѕСЃС‚Р° РїСЂРѕРіСЂР°РјР°С‚Р°", РєР°РєС‚Рѕ Рµ РѕРїРёСЃР°РЅРѕ РІ Р·Р°РґР°РЅРёРµС‚Рѕ. Р”СЉСЂР¶Р° РґР° РѕС‚Р±РµР»РµР¶Р°, С‡Рµ
 * РЅРµ СЃСЉРј РіРѕ РЅР°РїСЂР°РІРёР» СѓРјРёС€Р»РµРЅРѕ :).
 *
 * Р”СЂСѓРі РІР°СЂРёР°РЅС‚ Р·Р° СЂРµР°Р»РёР·Р°С†РёСЏ РЅР° РєР»Р°СЃР° Рµ РґР° РёРјР°РјРµ map РѕС‚ С…РѕСЂР° Рё РїСЂРµРІРѕР·РЅРё СЃСЂРµРґСЃС‚РІР°, РЅРѕ СЂРµС€РёС… РґР°
 * РѕРіСЂР°РЅРёС‡Р° РёР·РїРѕР»Р·РІР°РЅРµС‚Рѕ РЅР° РЅРµРїРѕРєР°Р·РІР°РЅРёС‚Рµ СЃС‚СЂСѓРєС‚СѓСЂРё РЅР° Р»РµРєС†РёРё. РўСЉСЂСЃРµРЅРµС‚Рѕ РІ РјРѕРјРµРЅС‚Р° СЃРµ РѕСЃСЉС‰РµСЃС‚РІСЏРІР° РІ
 * РЅР°Р№-Р»РѕС€РёСЏ СЃР»СѓС‡Р°Р№ СЃ O(n), РєРѕРµС‚Рѕ РЅРµ Рµ С‚РѕР»РєРѕРІР° Р±Р°РІРЅРѕ. Р’СЉР·РјРѕР¶РЅРѕ Рµ СЃ map С‚СЉСЂСЃРµРЅРµС‚Рѕ РґР° СЃС‚Р°РЅРµ Р»РѕРіР°СЂРёС‚РјРёС‡РЅРѕ, РЅРѕ
 * РїСЂРµРґРїРѕР»Р°РіР°Рј, С‡Рµ С‚РѕРІР° РЅРµ СЃРµ РёР·РёСЃРєРІР°, Р·Р°С‰РѕС‚Рѕ РЅРµ Рµ РѕС‚Р±РµР»СЏР·Р°РЅРѕ, С‡Рµ РґР°РЅРЅРёС‚Рµ С‰Рµ Р±СЉРґР°С‚ РјРЅРѕРіРѕ РіРѕР»РµРјРё.
 *
 * РљР»Р°СЃСЉС‚ СЂРµС€РёС… РґР° РіРѕ РЅР°РїСЂР°РІСЏ, РєР°С‚Рѕ Singleton, Р·Р°С‰РѕС‚Рѕ Рµ РЅРµС‰Рѕ РЅРѕРІРѕ РІ РєСѓСЂСЃР° Рё РїСЂРµС†РµРЅРёС…, С‡Рµ С‚РѕР·Рё РєР»Р°СЃ
 * С‰Рµ РёРјР° РўРћР§РќРћ Рё РЎРђРњРћ РµРґРЅР° РёРЅСЃС‚Р°РЅС†РёСЏ РІ С†СЏР»Р°С‚Р° РїСЂРѕРіСЂР°РјР°.
 *
 * РђР±СЃРѕР»СЋС‚РЅРѕ С†СЏР»Р°С‚Р° "РјР°РіРёСЏ" СЃРµ СЃР»СѓС‡РІР° РІ РјРµС‚РѕРґР° executeCommand, РєРѕРµС‚Рѕ РґР°РІР° РЅРёРІРѕ РЅР° Р°Р±СЃС‚СЂР°РєС†РёСЏ, Р°РєРѕ
 * РЅСЏРєРѕР№ СЂРµС€Рё РґР° РїРѕР»Р·РІР° С‚РѕР·Рё РєР»Р°СЃ.
 *
 * РРјРїРѕСЂС‚Р° РѕС‚ С„Р°Р№Р» РїСЂРёРЅС‚РёСЂР° Рё СЂРµРґРѕРІРµС‚Рµ, РЅР° РєРѕРёС‚Рѕ РёРјР° РіСЂРµС€РЅР° РєРѕРјР°РЅРґР° Рё РёР·РїСЉР»РЅСЏРІР° РІРµСЂРЅРёС‚Рµ.
 * */



#ifndef HOMEWORK2_DATABASE_H
#define HOMEWORK2_DATABASE_H

class DataBase {
private:

    DataBase() = default;

    ~DataBase() = default;

    std::vector<Vehicle> vehicles;
    std::vector<Person> people;
    std::vector<std::string> commands;

private:

    Vehicle *findVehicle(const std::string &);

    Person *findPerson(unsigned int);

    bool extractToFile(const std::string &);

    void show(const std::string &);

    void printPeople();

    void printVehicles();

    bool addCommand(const std::string &);

    bool addPerson(const std::string &, unsigned int);

    bool addVehicle(const std::string &, const std::string &);

    bool acquire(const std::string &, unsigned int);

    bool release(const std::string &, unsigned int);

    bool removeVehicle(const std::string &);

    bool removePerson(unsigned int);

public:

    static bool importFromFile(const std::string &);

    static DataBase &get_instance() {
        static DataBase instance;
        return instance;
    }

    bool executeCommand(Command &, const std::string &);

    DataBase(const DataBase &) = delete;

    DataBase &operator=(const DataBase &) = delete;


};

#endif //HOMEWORK2_DATABASE_H
