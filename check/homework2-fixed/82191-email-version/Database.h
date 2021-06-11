#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>

#include "Person.h"
#include "Vehicle.h"

class Database
{
public:
    Database() = default;
    Database(const std::string& filepath);
    void InsertPerson(const std::string& name, uint32_t id);
    void InsertVehicle(const std::string& registration, const std::string& description);
    void Acquire(uint32_t owner, const std::string& vehicleReg);
    void Release(uint32_t owner, const std::string& vehicleReg);
    void RemovePerson(uint32_t person);
    void RemoveVehicle(const std::string& vehicleReg);
    void ShowPeople();
    void ShowVehicles();
    void ShowPerson(uint32_t id);
    void ShowVehicle(const std::string& registration);
    void Save(const std::string& path);

private:
    Person* FindPersonById(uint32_t id);
    Vehicle* FindVehicleById(uint32_t id);
private:
    // Relationships
    //                 VehicleId,Person
    std::unordered_map<uint32_t, uint32_t> m_VehicleOwners;
    //                 PersonId, Vehicles
    std::unordered_map<uint32_t, std::unordered_set<uint32_t>> m_OwnedVehicles;
    
    std::unordered_map<uint32_t, Person> m_People; // people "table"
    std::unordered_map<uint32_t, Vehicle> m_Vehicles; // vehicles "table"
    std::hash<std::string> m_StringHasher;
};
