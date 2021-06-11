//
// Created by Yani Drenchev on 6.05.21.
//

/*РўРѕР·Рё С„Р°Р№Р» РёРјР° С‚РѕС‡РЅРѕ РґРІРµ С„СѓРЅРєС†РёРё, РєРѕРёС‚Рѕ СЃР° СЂРµР°Р»РёР·РёСЂР°РЅРё СЃСЉРѕС‚РІРµС‚РЅРѕ РІ Command.cpp
 * РџРѕРІРµС‡Рµ Р·Р° РјРµРЅ РЅРµ СЃР° РЅСѓР¶РЅРё. РР·РїРѕР»Р·РІР°Рј pair, Р·Р°С‰РѕС‚Рѕ С‚Р°РєР° СЂРµС€РµРЅРёРµС‚Рѕ РёР·Р»РёР·Р° РЅР°Р№-С‡РёСЃС‚Рѕ.
 * Р РµС€РёС… РґР° РЅРµ РёР·РїРѕР»Р·РІР°Рј РјРЅРѕРіРѕ РЅРµСѓС‡РµРЅРё Рё РЅРµРїРѕРєР°Р·РІР°РЅРё РЅРµС‰Р° Рё Р·Р°С‚РѕРІР° С‚Р°Р·Рё СЃС‚СЂСѓРєС‚СѓСЂР° Рµ РµРґРёРЅСЃС‚РІРµРЅР°С‚Р°,
 * РєРѕСЏС‚Рѕ РЅРµ Рµ РїРѕРєР°Р·РІР°РЅР° РЅР° Р»РµРєС†РёРё.
 *
 * Using СЃРїРµСЃС‚СЏРІР° РґРѕСЃС‚Р° РјСЏСЃС‚Рѕ, Р·Р°С‚РѕРІР° СЃРё РїРѕР·РІРѕР»РёС… РґР° РіРѕ РёР·РїРѕР»Р·РІР°Рј С‚СѓРє.
 * РћРїРёСЃР°РЅРёРµС‚Рѕ РЅР° СЂРµР°Р»РёР·РёСЂР°РЅРёС‚Рµ С„СѓРЅРєС†РёРё РѕС‚ РјРµРЅ С‰Рµ РѕС‚РєСЂРёРµС‚Рµ РІ .cpp С„Р°Р№Р»Р°.
 *
 * */
#include <string>
#include <iostream>
#include <vector>
#include <utility>

#include "CommandCode.h"

#ifndef HOMEWORK2_COMMAND_H
#define HOMEWORK2_COMMAND_H

using CommandArguments = std::vector<std::string>;
using Command = std::pair<CommandCode, CommandArguments>;

Command parseCommand(const std::string &);
void printAllCommands();

#endif //HOMEWORK2_COMMAND_H
