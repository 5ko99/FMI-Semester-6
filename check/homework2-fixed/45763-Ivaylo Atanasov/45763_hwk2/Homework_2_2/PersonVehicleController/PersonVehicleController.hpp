#ifndef PersonVehicleController_hpp
#define PersonVehicleController_hpp

#include "../Person/Person.hpp"
#include "../Utils/Utils.hpp"

class PersonVehicleController{
private:
    std::vector<Person*> personPointerArr;
    std::vector<Vehicle*> vehiPointerArr;
public:
    ~PersonVehicleController();
    void clear();
    
    void createPerson(std::string nameStr, std::string uidStr);
    void createVehicle(std::string regStr, std::string descStr);
    void acquire(std::string personIdStr, std::string vehiRegStr);
    void release(std::string personIdStr, std::string vehiRegStr);
    void remove(std::string whatStr);
    void show(std::string whatStr);

    bool personExists(const unsigned int& uid);
    bool vehicleExists(Registration& reg);
    
    std::size_t getIdentificatorType(std::string whatStr);
    Vehicle* getVehicleById(const Registration& reg);
    Person* getPersonById(const unsigned int id);
    
    void printPersons() const;
    void printVehicles() const;
    void printAll() const;
};

#endif
