#ifndef Person_h
#define Person_h
#include <cstring>
/*Person
РџСЂРµРґСЃС‚Р°РІСЏ РёРЅС„РѕСЂРјР°С†РёСЏ Р·Р° С‡РѕРІРµРє. Р’СЃРµРєРё РѕР±РµРєС‚ РѕС‚ С‚РёРї Person С‚СЂСЏР±РІР° РґР° РёРјР°
СЃР»РµРґРЅРёС‚Рµ СЃРІРѕР№СЃС‚РІР°:
в—Џ РРјРµ (std::string)
в—Џ РЈРЅРёРєР°Р»РµРЅ РёРґРµРЅС‚РёС„РёРєР°С‚РѕСЂ (unsigned int)
в—Џ РџСЂРµРІРѕР·РЅРё СЃСЂРµРґСЃС‚РІР°, РєРѕРёС‚Рѕ РїСЂРёС‚РµР¶Р°РІР°.
*/
class Person{


private:
    string name;
    static unsigned int *id;
    int *numCars;

public:

Person();
    Person(const string* name, const int* id, const int *numCars);
    Person(const Person& id);
    //Person& operator=(const Person& id);
    ~Person();

    //в—Џ РќРµ РјРѕР¶Рµ РґР° РёРјР° РґРІР°РјР° С‡РѕРІРµРєР° СЃ РµРґРЅР°РєСЉРІ РёРґРµРЅС‚РёС„РёРєР°С‚РѕСЂ.
    void impossibleID(const char *id);

     const string *name() const;
    const int *id() const;
    const int *numCars() const;

    void setName(const string *name);
    void setId(const int *id);
    void setnumCars(const char *numCars);
    //в—Џ Р’СЃРµРєРё РѕР±РµРєС‚ РѕС‚ С‚РёРї Person СЃСЉРґСЉСЂР¶Р° РїСЂРµРїСЂР°С‚РєРё РєСЉРј РїСЂРµРІРѕР·РЅРёС‚Рµ СЃСЂРµРґСЃС‚РІР°,
    //РєРѕРёС‚Рѕ С‡РѕРІРµРєСЉС‚ РїСЂРёС‚РµР¶Р°РІР° (Р°РєРѕ РёРјР° С‚Р°РєРёРІР°). РўРѕРµСЃС‚ РїРѕ РѕР±РµРєС‚ РѕС‚ С‚РёРї Person РјРѕР¶Рµ
    //РґР° СЃРµ РЅР°РјРµСЂСЏС‚ РѕР±РµРєС‚РёС‚Рµ, РєРѕРёС‚Рѕ РїСЂРµРґСЃС‚Р°РІСЏС‚ РїСЂРµРІРѕР·РЅРёС‚Рµ СЃСЂРµРґСЃС‚РІР°, РєРѕРёС‚Рѕ С‚РѕР№
    //РїСЂРёС‚РµР¶Р°РІР°;
};
#endif // Person_h
