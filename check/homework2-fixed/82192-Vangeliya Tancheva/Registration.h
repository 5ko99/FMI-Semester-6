#ifndef REGISTRATION_H_INCLUDED
#define REGISTRATION_H_INCLUDED

class Registration
{
private:
    std::string number;

public:
    Registration();

    Registration(std::string num);


    Registration& operator=(const Registration& source);

    const std::string getNumber() const;

    ~Registration();
};

#endif // REGISTRATION_H_INCLUDED
