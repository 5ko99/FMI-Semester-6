#include "Database.h"

#include "Utils.h"
#include "DatabaseSerializer.h"

#include <iostream>
#include <iomanip>
#include <fstream>

Database::Database(const std::string& filepath)
{
    try {
        DatabaseDeserializer dbDeserializer(filepath);
        uint32_t len;
        dbDeserializer >> len;
        for (uint32_t i = 0; i < len; i++)
        {
            uint32_t id;
            dbDeserializer >> id;
            std::string registration, desc;
            dbDeserializer >> registration >> desc;
            m_Vehicles.insert({ id, Vehicle({registration}, desc, id) });
        }
        
        dbDeserializer >> len;
        for (uint32_t i = 0; i < len; i++)
        {
            uint32_t id;
            std::string name;
            dbDeserializer >> id >> name;
            m_People.insert({ id, Person(name, id)});
        }
        
        dbDeserializer >> len;
        for (uint32_t i = 0; i < len; i++)
        {
            uint32_t id1, id2;
            dbDeserializer >> id1 >> id2;
            m_VehicleOwners[id1] = id2;
        }
        
        dbDeserializer >> len;
        for (uint32_t i = 0; i < len; i++)
        {
            std::unordered_set<uint32_t> temp;
            uint32_t len2, id;
            dbDeserializer >> len2 >> id;
            for (uint32_t i = 0; i < len2; i++)
            {
                uint32_t id2;
                dbDeserializer >> id2;
                temp.insert(id2);
            }
            m_OwnedVehicles[id] = temp;
        }
    } catch (std::exception& exception) {
        throw;
    }
    
}

Person* Database::FindPersonById(uint32_t id)
{
    auto iter = m_People.find(id);
    if (iter != m_People.end())
        return &iter->second;
    return nullptr;
}
   
Vehicle* Database::FindVehicleById(uint32_t id)
{
    auto iter = m_Vehicles.find(id);
    if (iter != m_Vehicles.end())
        return &iter->second;
    return nullptr;
}

void Database::InsertPerson(const std::string& name, uint32_t id)
{
    if (m_People.find(id) != m_People.end())
        throw std::runtime_error("Duplicate person ids");
    m_People.insert({ id, Person(name, id)});
}

void Database::InsertVehicle(const std::string& registration, const std::string& desc)
{
    if (!Utils::ValidateCarId(registration))
        throw std::runtime_error("Invalid car registration");
    
    uint32_t id = Utils::Fnv1a(registration);
    if (m_Vehicles.find(id) != m_Vehicles.end())
        throw std::runtime_error("Duplicate vehicle ids");
    
    m_Vehicles.insert({ id, Vehicle({registration}, desc, id) });
}

void Database::Acquire(uint32_t owner, const std::string& vehicleReg)
{
    auto personIter = m_People.find(owner);
    if (personIter == m_People.end())
        throw std::runtime_error("Person does not exist");
    
    uint32_t vehicle = Utils::Fnv1a(vehicleReg);
    auto vehicleIter = m_Vehicles.find(vehicle);
    if (vehicleIter == m_Vehicles.end())
        throw std::runtime_error("Vehicle does not exist");
    
    m_VehicleOwners[vehicle] = owner;
    m_OwnedVehicles[owner].insert(vehicle);
}

void Database::Release(uint32_t owner, const std::string& vehicleReg)
{
    auto personIter = m_OwnedVehicles.find(owner);
    if (personIter == m_OwnedVehicles.end())
        throw std::runtime_error("Person does not exist");
    
    uint32_t vehicle = Utils::Fnv1a(vehicleReg);
    auto vehicleIter = m_VehicleOwners.find(vehicle);
    if (vehicleIter == m_VehicleOwners.end())
        throw std::runtime_error("Vehicle does not exist");
    
    personIter->second.erase(vehicle);
    m_VehicleOwners.erase(vehicleIter);
}

void Database::RemovePerson(uint32_t person)
{
    auto iter = m_People.find(person);
    if (iter == m_People.end())
        throw std::runtime_error("Person does not exist");
    
    m_People.erase(iter);
    auto personVehiclesIter = m_OwnedVehicles.find(person);
    auto& vehicles = personVehiclesIter->second;
    for (uint32_t vehicleId : vehicles)
        m_VehicleOwners.erase(m_VehicleOwners.find(vehicleId));
    m_OwnedVehicles.erase(personVehiclesIter);
}

void Database::RemoveVehicle(const std::string& vehicleReg)
{
    uint32_t vehicle = Utils::Fnv1a(vehicleReg);
    auto iter = m_Vehicles.find(vehicle);
    if (iter == m_Vehicles.end())
        throw std::runtime_error("Vehicle does not exist");
    
    m_Vehicles.erase(iter);
    uint32_t ownerId = m_VehicleOwners.find(vehicle)->second;
    auto& vehicleSet = m_OwnedVehicles.find(ownerId)->second;
    vehicleSet.erase(vehicleSet.find(vehicle));
    m_VehicleOwners.erase(m_VehicleOwners.find(vehicle));
}

void Database::ShowPeople()
{
    uint32_t maxIdLength = 2; // len("Id")
    uint32_t maxNameLength = 4; // len("Name")
    for (auto& person : m_People)
    {
        maxNameLength = std::max(maxNameLength, (uint32_t)person.second.m_Name.size());
        maxIdLength = std::max(maxIdLength, Utils::GetNumberLength(person.second.m_Id));
    }
    uint32_t maxRowLength = maxNameLength + maxIdLength + 7 /* |, padding */;
    for (uint32_t i = 0; i < maxRowLength; i++)
        std::cout << '-';
    std::cout << std::endl;
    
    std::cout << "| " << std::right << std::setw(maxIdLength) << "Id";
    std::cout << " | " << std::right << std::setw(maxNameLength) << "Name";
    std::cout << " |" << std::endl;
    for (uint32_t i = 0; i < maxRowLength; i++)
        std::cout << '-';
    std::cout << std::endl;
    for (auto& person : m_People)
    {
        std::cout << "| " << std::setw(maxIdLength) <<
            std::right << person.second.m_Id;
        std::cout << " | " << std::setw(maxNameLength) <<
            std::right << person.second.m_Name;
        std::cout << " |" << std::endl;
    }
    for (uint32_t i = 0; i < maxRowLength; i++)
        std::cout << '-';
    std::cout << std::endl;
}

void Database::ShowVehicles()
{
    // 0 <= len(id) <= 6
    uint32_t maxIdLength = 2; // len("Id");
    uint32_t maxRegistrationLength = 12; // len("Registration")
    uint32_t maxDescriptionLength = 11; // len("Description")
    for (auto& vehicle : m_Vehicles)
    {
        maxRegistrationLength = std::max(maxRegistrationLength, (uint32_t)vehicle.second.m_Registration.GetRegistrationText().size());
        maxDescriptionLength = std::max(maxDescriptionLength, (uint32_t)vehicle.second.m_Description.size());
        maxIdLength = std::max(maxIdLength, Utils::GetNumberLength(vehicle.second.m_Id));
    }
    
    uint32_t maxRowLength = maxRegistrationLength + maxDescriptionLength + maxIdLength + 10 /* |, padding */;
    for (uint32_t i = 0; i < maxRowLength; i++)
        std::cout << '-';
    std::cout << std::endl;
    
    std::cout << "| " << std::right << std::setw(maxIdLength) << "Id";
    std::cout << " | " << std::right << std::setw(maxRegistrationLength) << "Registration";
    std::cout << " | " << std::right << std::setw(maxDescriptionLength) << "Description";
    std::cout << " |" << std::endl;
    for (uint32_t i = 0; i < maxRowLength; i++)
        std::cout << '-';
    std::cout << std::endl;
    for (auto& vehicle : m_Vehicles)
    {
        std::cout << "| " << std::setw(maxIdLength) <<
            std::right << vehicle.second.m_Id;
        std::cout << " | " << std::setw(maxRegistrationLength) <<
            std::right << vehicle.second.m_Registration.GetRegistrationText();
        std::cout << " | " << std::setw(maxDescriptionLength) <<
            std::right << vehicle.second.m_Description;
        std::cout << " |" << std::endl;
    }
    for (uint32_t i = 0; i < maxRowLength; i++)
        std::cout << '-';
    std::cout << std::endl;
}

void Database::ShowPerson(uint32_t id)
{
    auto iter = m_People.find(id);
    if (iter == m_People.end())
        throw std::runtime_error("Person does not exist");
    std::cout << iter->second.m_Name << "#" << iter->second.m_Id << std::endl;
    for (uint32_t vehicle : m_OwnedVehicles[id])
    {
        std::cout << "  " << "|-" << m_Vehicles[vehicle].m_Registration.GetRegistrationText() <<
            "#" << m_Vehicles[vehicle].m_Id << std::endl;
    }
    std::cout << std::endl;
}

void Database::ShowVehicle(const std::string& registration)
{
    uint32_t vehicleId = Utils::Fnv1a(registration);
    auto iter = m_Vehicles.find(vehicleId);
    if (iter == m_Vehicles.end())
        throw std::runtime_error("Vehicle does not exist");
    
    const auto& vehicle = m_Vehicles[vehicleId];
    std::cout << "Vehicle[" << vehicle.m_Registration.GetRegistrationText() <<
        " - (" << vehicle.m_Description << ")" << "]";
    std::cout << " is owned by " << m_People[m_VehicleOwners[vehicleId]].m_Name << std::endl;
}

void Database::Save(const std::string& filepath)
{
    try {
        DatabaseSerializer dbSerializer(filepath);
    
        dbSerializer << (uint32_t)m_Vehicles.size();
         // reverse fors?
        for (auto& vehicle : m_Vehicles)
            dbSerializer << vehicle.second.m_Id << vehicle.second.m_Registration.GetRegistrationText() << vehicle.second.m_Description;
        
        dbSerializer << (uint32_t)m_People.size();
        for (auto& person : m_People)
            dbSerializer << person.second.m_Id << person.second.m_Name;
        
        dbSerializer << (uint32_t)m_VehicleOwners.size();
        for (auto& vo : m_VehicleOwners)
            dbSerializer << vo.first << vo.second;
        
        dbSerializer << (uint32_t)m_OwnedVehicles.size();
        for (auto& ov : m_OwnedVehicles)
        {
            dbSerializer << (uint32_t)ov.second.size() << ov.first;
            for (uint32_t id : ov.second)
                dbSerializer << id;
        }
    } catch(const std::exception& ex) {
        throw;
    }
}
