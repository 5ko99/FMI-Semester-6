/*Registration
РџСЂРµРґСЃС‚Р°РІСЏ СЂРµРіРёСЃС‚СЂР°С†РёРѕРЅРµРЅ РЅРѕРјРµСЂ РЅР° РїСЂРµРІРѕР·РЅРѕ СЃСЂРµРґСЃС‚РІРѕ. Р—Р° С†РµР»РёС‚Рµ РЅР° Р·Р°РґР°С‡Р°С‚Р°
С‰Рµ СЃС‡РёС‚Р°РјРµ, С‡Рµ РІСЃРµРєРё РЅРѕРјРµСЂ Рµ РїРѕСЂРµРґРёС†Р° РѕС‚ СЃРёРјРІРѕР»Рё, РїРѕРґСЂРµРґРµРЅРё РєР°РєС‚Рѕ СЃР»РµРґРІР°:
1. Р•РґРёРЅ РёР»Рё РґРІР° СЃРёРјРІРѕР»Р° РѕС‚ Р»Р°С‚РёРЅСЃРєР°С‚Р° Р°Р·Р±СѓРєР°, РєРѕРёС‚Рѕ СѓРєР°Р·РІР°С‚ РЅР°СЃРµР»РµРЅРѕ РјСЏСЃС‚Рѕ;
2. Р§РµС‚РёСЂРё С†РёС„СЂРё;
3. Р”РІР° СЃРёРјРІРѕР»Р° РѕС‚ Р»Р°С‚РёРЅСЃРєР°С‚Р° Р°Р·Р±СѓРєР°.
РќР°РїСЂРёРјРµСЂ C1234AB, XY1111YX СЃР° РІР°Р»РёРґРЅРё СЂРµРіРёСЃС‚СЂР°С†РёРѕРЅРЅРё РЅРѕРјРµСЂР°, Р° 111145,
ABC34DEF, ABCDEF Рё C11D РЅРµ СЃР°.
*/
#ifndef Registration_h
#define Registration_h

class Registration{

   private:
    char *city[2]; ///yes
    char *reg[4]; ///yes
    char *symbol[2]; ///yes

   public:
       Registration();
    Registration(const char* city, const char* reg, const char *symbol );
    Registation(const Registration& reg);
    //Registration& operator=(const Registration& reg);
    ~Registration();

    const char *getCity() const;
    const char *getReg() const;
    const char *getSymbol() const;

    void setCity(const char *city);
    void setReg(const char *reg);
    void setSymbol(const char *symbol);
// в—Џ РќРµ РјРѕР¶Рµ РґР° РёРјР° РґРІРµ РїСЂРµРІРѕР·РЅРё СЃСЂРµРґСЃС‚РІР° СЃ РµРґРЅР°РєСЉРІ СЂРµРіРёСЃС‚СЂР°С†РёРѕРЅРµРЅ РЅРѕРјРµСЂ
    void impossibleReg(const char* city, const char* reg, unsigned int *symbol);



};
#endif // Registration_h
