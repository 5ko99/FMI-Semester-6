#ifndef CMDENGINE_H
#define CMDENGINE_H

#include<iostream>
#include<exception>
#include<string>
#include<fstream>
#include"main.h"
class VehicleManager;
class PersonManager;
class CMDEngine{
    public:
        bool ParseCMDToData(std::string& userCMD, std::string& firstArgument, std::string& secondArgument, std::string& commandOrderData, PersonManager& pManager, VehicleManager& vManager, bool isDataFromFile = false);
};

#endif
