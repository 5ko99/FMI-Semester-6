#include <string>

class Database;

class Registration
{
public:
    Registration() = default;
    Registration(const std::string& name);
    const std::string& GetRegistrationText() const { return m_RegistrationText; }
private:
    std::string m_RegistrationText;
};

class Vehicle
{
public:
    Vehicle() = default;
    Vehicle(const Registration& registration, const std::string& desc, uint32_t id);
private:
    friend class Database;
    Registration m_Registration;
    std::string m_Description;
    uint32_t m_Id;
};
