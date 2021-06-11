//
// Created by pgpetrov on 4.05.21 Рі..
//

#ifndef HWUNI2_SRC_REGISTRATION_H_
#define HWUNI2_SRC_REGISTRATION_H_
#include <string>

class Registration {
 public:
  Registration(const std::string &s);
  operator std::string() const;
  friend std::ostream& operator<<(std::ostream& os, const Registration& registration);
  bool operator==(const Registration& other);
 private:
  char characters[8];
};

#endif //HWUNI2_SRC_REGISTRATION_H_
