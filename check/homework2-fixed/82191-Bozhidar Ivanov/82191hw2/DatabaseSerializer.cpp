#include "DatabaseSerializer.h"

DatabaseSerializer::DatabaseSerializer(const std::string& filepath)
{
    m_Stream = std::ofstream(filepath, std::ios::binary);
    if (!m_Stream.is_open())
        throw std::runtime_error("Could not open save file");
}

DatabaseSerializer::~DatabaseSerializer()
{
    m_Stream.close();
}

DatabaseSerializer& DatabaseSerializer::operator<<(const std::string& value)
{
    operator<<((uint32_t)value.size());
    m_Stream.write(value.c_str(), value.size());
    return *this;
}

DatabaseSerializer& DatabaseSerializer::operator<<(uint32_t value)
{
    m_Stream.write(reinterpret_cast<const char*>(&value), sizeof(uint32_t));
    return *this;
}

DatabaseDeserializer::DatabaseDeserializer(const std::string& filepath)
{
    m_Stream = std::ifstream(filepath, std::ios::binary);
    if (!m_Stream.is_open())
        throw std::runtime_error("Could not open input file");
}

DatabaseDeserializer::~DatabaseDeserializer()
{
    m_Stream.close();
}

DatabaseDeserializer& DatabaseDeserializer::operator>>(std::string& value)
{
    uint32_t len;
    operator>>(len);
    value.resize(len);
    m_Stream.read(&value[0], len); // C++17 has non-const .data()
    return *this;
}

DatabaseDeserializer& DatabaseDeserializer::operator>>(uint32_t& value)
{
    m_Stream.read(reinterpret_cast<char*>(&value), sizeof(uint32_t));
    return *this;
}
