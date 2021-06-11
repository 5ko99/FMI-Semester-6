#ifndef _REGISTRATION_HPP_
#define _REGISTRATION_HPP_

#include <string>

class Registration {

  public:
    explicit Registration(const std::string &reg);

    static bool validate(const std::string &reg);
    std::string to_string() const;

  private:
    std::string m_reg;
};

#endif // _REGISTRATION_HPP_
