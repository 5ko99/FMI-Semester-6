#include "Garage.h"
#include <cstring>
#include <stdexcept>
Garage::Garage(std::size_t size)
{
    m_max_size = size;
    m_cur_size = 0;
}
Garage::Garage(const Garage &g)
{
    m_max_size = g.m_max_size;
    m_cur_size = g.m_cur_size;
    m_v = g.m_v;
}
void Garage::insert(Vehicle &v)
{
    if (m_cur_size + v.space() <= m_max_size)
    {
        if (m_v.push_back(v))
            m_cur_size += v.space();
        else
            throw std::exception();
    }
    else
        throw std::exception();
}
void Garage::erase(const char *registration)
{
    m_cur_size -= m_v.erase(registration);
}
const Vehicle &Garage::at(std::size_t pos) const
{
    if (pos < 0 || pos >= m_v.size())
        throw std::out_of_range("");
    return m_v.at(pos);
}
const Vehicle &Garage::operator[](std::size_t pos) const
{
#ifdef _DEBUG
    assert(pos >= 0 && pos < m_v.size());
#endif
    return m_v.at(pos);
}
bool Garage::empty() const
{
    return m_cur_size == 0;
}
std::size_t Garage::size() const
{
    return m_v.size();
}
void Garage::clear()
{
    m_cur_size = 0;
    m_v.clear();
}
const Vehicle *Garage::find(const char *registration) const
{
    for (int i = 0; i < m_v.size(); ++i)
    {
        const char *curRegistration = m_v.at(i).registration();
        if (strcmp(curRegistration, registration) == 0)
        {
            return &m_v.at(i);
        }
    }
    return nullptr;
}
Garage &Garage::operator=(const Garage &other)
{
    if (this != &other)
    {
        m_cur_size = other.m_cur_size;
        m_max_size = other.m_max_size;
        m_v = other.m_v;
    }
    return *this;
}
Garage::~Garage()
{
    clear();
}