#include <string>

class Database;

class Person
{
public:
    Person() = default;
    Person(const std::string& name, uint32_t id);
    
private:
    friend class Database;
    uint32_t m_Id;
    std::string m_Name;
};
