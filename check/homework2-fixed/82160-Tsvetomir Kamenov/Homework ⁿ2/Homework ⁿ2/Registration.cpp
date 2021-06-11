#include "Registration.h"

#include <iostream>

Registration::Registration(const std::string& reg) : m_reg(reg) {}

const std::string& Registration::getReg() const
{
    return m_reg;
}

Registration& Registration::operator=(const Registration& reg)
{
    m_reg = reg.m_reg;
    m_length = reg.m_length;

    return *this;
}

void Registration::calculateLength()
{
    while(m_reg[m_length] != '\0') {
        ++m_length;
    }
}


bool Registration::isValidReg()
{
    calculateLength();

    if(m_length > MAX_LENGTH || m_length < MIN_LENGTH)
        return false;

    int index = 0;
    if(m_reg[index] < 'A' || m_reg[index] > 'Z')
        return false;
    else
        ++index;

    if(m_length == MIN_LENGTH) {
        int indexOfLastDigit = 4;
        for( ; index <= indexOfLastDigit; ++index) {
            if(m_reg[index] < '0' || m_reg[index] > '9')
                return false;
        }
        for( ; index < m_length; ++index) {
            if(m_reg[index] < 'A' || m_reg[index] > 'Z')
                return false;
        }
    }

    else {
        if(m_reg[index] < 'A' || m_reg[index] > 'Z')
            return false;
        else
            ++index;

        int indexOfLastDigit = 5;
        for( ; index <= indexOfLastDigit; ++index) {
            if(m_reg[index] < '0' || m_reg[index] > '9')
                return false;
        }
        for( ; index < m_length; ++index) {
            if(m_reg[index] < 'A' || m_reg[index] > 'Z')
                return false;
        }
    }

    return true;
}

std::ostream& operator<<(std::ostream& out, const Registration& reg)
{
    out << reg.m_reg;

    return out;
}

//returns true if 2 registrations are matching
bool Registration::operator==(const Registration& reg)
{
    return !(m_reg.compare(reg.getReg()));
}
