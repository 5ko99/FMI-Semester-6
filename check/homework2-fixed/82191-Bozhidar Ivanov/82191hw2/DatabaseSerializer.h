#include <fstream>
#include <ostream>

class DatabaseSerializer
{
public:
    DatabaseSerializer(const std::string& filepath);
    ~DatabaseSerializer();
    
    DatabaseSerializer& operator<<(const std::string& value);
    DatabaseSerializer& operator<<(uint32_t value);
private:
    std::ofstream m_Stream;
};

class DatabaseDeserializer
{
public:
    DatabaseDeserializer(const std::string& filepath);
    ~DatabaseDeserializer();
    
    DatabaseDeserializer& operator>>(std::string& value);
    DatabaseDeserializer& operator>>(uint32_t& value);
private:
    std::ifstream m_Stream;
};
