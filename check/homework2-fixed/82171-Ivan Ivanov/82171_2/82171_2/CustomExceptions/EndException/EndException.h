#ifndef END_EXCEPTION_H
#define END_EXCEPTION_H

#include <string>

class EndException : public std::exception {
    private:
        std::string message;
    public:
        EndException(const std::string& message);
        const char* what() const throw();
};

#endif
