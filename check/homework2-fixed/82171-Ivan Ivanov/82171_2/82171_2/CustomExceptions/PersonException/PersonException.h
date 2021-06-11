#ifndef PERSON_EXCEPTION_H
#define PERSON_EXCEPTION_H

#include <string>

class PersonException : public std::exception {
    private:
        std::string message;
    public:
        PersonException(const std::string& message);
        const char* what() const throw();
};

#endif
