//
// Created by Yani Drenchev on 6.05.21.
//

/*
 * РўСѓРє "РјР°РіРёСЏС‚Р°" СЃРµ СЃР»СѓС‡РІР° РІ checkRegistration(),
 * С‚РѕР·Рё РјРµС‚РѕРґ РґРѕСЃС‚Р° С‚СЂРѕРјР°РІРѕ СЃСЉРј РіРѕ СЂРµР°Р»РёР·РёСЂР°Р» Рё СЃ РґРѕСЃС‚Р° РєРѕРґ, РЅРѕ
 * СЂР°Р±РѕС‚Рё :). If it works - don't touch it. РўРѕРІР° РјРѕР¶Рµ Р±Рё Рµ РµРґРёРЅСЃС‚РІРµРЅРёСЏС‚
 * "Р°Р»РіРѕСЂРёС‚СЉРј" РІ РїСЂРѕРіСЂР°РјР°С‚Р° Рё СЃРµ РёР·РІРёРЅСЏРІР°Рј, Р°РєРѕ СЃС‚Рµ РѕС‡Р°РєРІР°Р»Рё РїРѕРІРµС‡Рµ :D.
 *
 * РљРѕРЅСЃС‚СЂСѓРєС‚РѕСЂСЉС‚ С…РІСЉСЂР»СЏ РёР·РєР»СЋС‡РµРЅРёРµ, Р°РєРѕ Рµ РїРѕРґР°РґРµРЅ РЅРµРІР°Р»РёРґРµРЅ СЂРµРіРёСЃС‚СЂР°С†РёРѕРЅРµРЅ РЅРѕРјРµСЂ,
 * РЅРѕ РёР·РєР»СЋС‡РµРЅРёРµС‚Рѕ СЃРµ С…РІР°С‰Р°. Р’ С‚РµСЃС‚РѕРІРµС‚Рµ РїСЂРѕРІРµСЂСЏРІР°Рј РґР°Р»Рё РїСЂРё РіСЂРµС€РµРЅ РЅРѕРјРµСЂ СЃРµ С…РІСЉСЂР»СЏ РёР·РєР»СЋС‡РµРЅРёРµ.
 *
 * */
#include <iostream>
#include <string>

#ifndef HOMEWORK2_REGISTRATION_H
#define HOMEWORK2_REGISTRATION_H

class Registration {
private:
    std::string registration;

public:
    static bool checkRegistration(const std::string &);

    Registration(const std::string &);

    Registration();

    std::string getRegistration() const;

    bool operator==(const Registration &oth) const;
};

#endif //HOMEWORK2_REGISTRATION_H
