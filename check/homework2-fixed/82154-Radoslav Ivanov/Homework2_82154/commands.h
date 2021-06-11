#pragma once
#include "allVehicles.h"
#include "People.h"

class Commands {

private:
    AllVehicles AV;
    People PPL;

public:
    Commands() = default;
    Commands (const Commands&) = delete;
    Commands& operator= (const Commands&) = delete;
    ~Commands() = default;

    void VEHICLE(const Registration& reg, const std::string& descript);
    void PERSON(const std::string& name, const unsigned id);
    void ACQUIRE(const unsigned id, const Registration& reg);
    void RELEASE(const unsigned id, const Registration& reg);
    void REMOVE(const std::string& arg);
    void SAVE(std::ofstream& file);
    void SHOW(std::string& arg);
    void HELP() const;
    
    static void toLowerCase(std::string& str);
    static int whatIsThis(const std::string& str);
    
    //The following 2 are only created for the unit tests
    AllVehicles& getAV();
    People& getPPL();

};
