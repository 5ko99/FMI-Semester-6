#include "registration.h"
#include <stdexcept>

Registration::Registration()
{}

Registration::Registration(const std::string& data)
{
    this->data = data;
}


std::string Registration::getData() const
{
    return data;
}

bool operator ==(const Registration& lhs, const Registration& rhs)
{
    return lhs.getData() == rhs.getData();
}

std::ostream& operator <<(std::ostream& out, const Registration& r)
{
    out << r.data;
    return out;
}

std::istream& operator >>(std::istream& in, Registration& r)
{
    in >> r.data;
    return in;
}
