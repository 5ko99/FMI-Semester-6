//
// Created by pgpetrov on 4.05.21 Рі..
//

#include <iostream>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <iterator>
#include "Registration.h"

std::ostream &operator<<(std::ostream &os, const Registration &registration) {
  os << registration.characters[0];
  if (registration.characters[1]) {
    os << registration.characters[1];
    std::copy(registration.characters+2, registration.characters+8, std::ostream_iterator<char>(os));
  } else {
    std::copy(registration.characters+1, registration.characters+8, std::ostream_iterator<char>(os));
  }
  return os;
}

Registration::operator std::string() const {
  std::ostringstream ss;
  ss << *this;
  return ss.str();
}

Registration::Registration(const std::string &s) {
  bool ok = s.size() == 8 || s.size() == 7;
  ok = ok && isupper(s[0]);
  if (s.size() == 8) {
    ok = ok && isupper(s[1]);
  } else {
    ok = ok && isdigit(s[1]);
  }
  ok = ok && isdigit(s[2]) && isdigit(s[3]) && isdigit(s[4]);
  if (s.size() == 8) {
    ok = ok && isdigit(s[5]);
    ok = ok && isupper(s[6]) && isupper(s[7]);
  } else {
    ok = ok && isupper(s[5]) && isupper(s[6]);
  }
  if (!ok)
    throw std::invalid_argument("Invalid format for registration plate \"" + s + "\".");

  characters[0] = s[0];
  if (s.size() == 8) {
    characters[1] = s[1];
    std::copy(s.begin()+2, s.end(), characters+2);
  } else {
    characters[1] = '\0'; // that's how we identify that only one letter is used for city id
    std::copy(s.begin()+1, s.end(), characters+2);
  }
}

bool Registration::operator==(const Registration &other) {
  return std::equal(characters, characters+8, other.characters);
}
