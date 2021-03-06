/*Vehicle
РџСЂРµРґСЃС‚Р°РІСЏ РїСЂРµРІРѕР·РЅРѕ СЃСЂРµРґСЃС‚РІРѕ. РўРѕ РёРјР° СЃР»РµРґРЅРёС‚Рµ СЃРІРѕР№СЃС‚РІР°:
в—Џ РЈРЅРёРєР°Р»РµРЅ СЂРµРіРёСЃС‚СЂР°С†РёРѕРЅРµРЅ РЅРѕРјРµСЂ (Registration)
в—Џ РћРїРёСЃР°РЅРёРµ (std::string)
в—Џ РЎРѕР±СЃС‚РІРµРЅРёРє.
*/
#ifndef Vehicle_h
#define Vehicle_h
#include <Registration.h>
#include <Person.h>
class Vehicle:Registration {
private:

    Registration(const char* city, const char* reg, const char *symbol );
    std::string Description;
    char owner(Person name);

    public:

    // в—Џ РќРµ РјРѕР¶Рµ РґР° РёРјР° РґРІРµ РїСЂРµРІРѕР·РЅРё СЃСЂРµРґСЃС‚РІР° СЃ РµРґРЅР°РєСЉРІ СЂРµРіРёСЃС‚СЂР°С†РёРѕРЅРµРЅ РЅРѕРјРµСЂ

    //в—Џ Р•РґРЅРѕ РїСЂРµРІРѕР·РЅРѕ СЃСЂРµРґСЃС‚РІРѕ РјРѕР¶Рµ РґР° РёРјР° РёР»Рё РЅСѓР»Р°, РёР»Рё РµРґРёРЅ СЃРѕР±СЃС‚РІРµРЅРёРє.
    void OwnVehicle();
    //в—Џ Р•РґРёРЅ С‡РѕРІРµРє РјРѕР¶Рµ РґР° РїСЂРёС‚РµР¶Р°РІР° РЅСѓР»Р°, РµРґРЅРѕ РёР»Рё РїРѕРІРµС‡Рµ РїСЂРµРІРѕР·РЅРё СЃСЂРµРґСЃС‚РІР°.
    //Р’СЃРµРєРё РѕР±РµРєС‚ РѕС‚ С‚РёРї Vehicle РёРјР° РїСЂРµРїСЂР°С‚РєР° РєСЉРј СЃРѕР±СЃС‚РІРµРЅРёРєР° РјСѓ (Р°РєРѕ РёРјР°
    //С‚Р°РєСЉРІ). РўРѕРµСЃС‚ РїРѕ РѕР±РµРєС‚ РѕС‚ С‚РёРї Vehicle С‚СЂСЏР±РІР° РґР° РјРѕР¶Рµ РґР° СЃРµ РЅР°РјРµСЂРё РѕР±РµРєС‚СЉС‚,
    //РєРѕР№С‚Рѕ РїСЂРµРґСЃС‚Р°РІСЏ СЃРѕР±СЃС‚РІРµРЅРёРєР° РјСѓ.
    //в—ЏРћР±РµРєС‚РёС‚Рµ РѕС‚ С‚РёРї Person Рё/РёР»Рё Vehicle СЃСЉС‰РµСЃС‚РІСѓРІР°С‚ РЅРµР·Р°РІРёСЃРёРјРѕ РµРґРЅРё РѕС‚ РґСЂСѓРіРё.
     //РќР°РїСЂРёРјРµСЂ РґР°РґРµРЅРѕ РїСЂРµРІРѕР·РЅРѕ СЃСЂРµРґСЃС‚РІРѕ РјРѕР¶Рµ РґР° СЃС‚Р°РЅРµ СЃРѕР±СЃС‚РІРµРЅРѕСЃС‚ РЅР° РґР°РґРµРЅ
       //С‡РѕРІРµРє, Р° РїРѕ-РєСЉСЃРЅРѕ РґР° СЃРµ СѓРєР°Р¶Рµ, С‡Рµ С‚Рѕ РЅРµ РїСЂРёРЅР°РґР»РµР¶Рё РЅР° РЅРёРєРѕРіРѕ. РўРѕРІР° РѕР±Р°С‡Рµ РЅРµ
        //РґРѕРІРµР¶РґР° РґРѕ СѓРЅРёС‰РѕР¶Р°РІР°РЅРµ РЅР° РїСЂРµРІРѕР·РЅРѕС‚Рѕ СЃСЂРµРґСЃС‚РІРѕ




#endif // Vehicle_h
