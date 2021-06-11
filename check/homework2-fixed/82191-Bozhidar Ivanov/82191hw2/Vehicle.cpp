#include "Vehicle.h"

Registration::Registration(const std::string& name) : m_RegistrationText(name) {}

Vehicle::Vehicle(const Registration& registration, const std::string& desc, uint32_t id)
    : m_Registration(registration), m_Description(desc), m_Id(id) {}
