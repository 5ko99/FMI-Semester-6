#ifndef REGISTRATION_H_INCLUDED
#define REGISTRATION_H_INCLUDED

bool is_valid(const char *reg_number)
{
    size_t sz=strsize(reg_number);

    if(reg_number[0]>='A'&&reg_number[0]<='Z')
    {
        if(reg_number[1]>='A'&&reg_number[1]<='Z')
        {
            if(sz!=8) return false;
            if((reg_number[2]>='0'&&reg_number[2]<='9')&&
               (reg_number[3]>='0'&&reg_number[3]<='9')&&
               (reg_number[4]>='0'&&reg_number[4]<='9')&&
               (reg_number[5]>='0'&&reg_number[5]<='9')&&
               (reg_number[6]>='A'&&reg_number[6]<='Z')&&
               (reg_number[7]>='A'&&reg_number[7]<='Z')) return true;
        }
        if(reg_number[1]>='0'&&reg_number[1]<='9')
        {
            if(sz!=7) return false;
             if((reg_number[2]>='0'&&reg_number[2]<='9')&&
               (reg_number[3]>='0'&&reg_number[3]<='9')&&
               (reg_number[4]>='0'&&reg_number[4]<='9')&&
               (reg_number[5]>='A'&&reg_number[5]<='Z')&&
               (reg_number[6]>='A'&&reg_number[6]<='Z')) return true;
        }
    }
    return false;
}

class Registration
{
public:
    Registration(const char *str);
    Registration();
   ~Registration();

    void operator= (Registration &rhs);
    void operator= (const char *str);
    const char *getRegNumber() const;
    void printRegNumber() const;
    bool isEmpty() const;
    void setRegistration(const char *str);

private:
    char reg_number[9];
};

Registration::Registration(const char *str)
{
    strcpy(reg_number, str);
    if(!is_valid(reg_number))
    {
        std::cout<<"WRONG REGISTRATION NUMBER "<<reg_number<<'!'<<std::endl;
    }
}

Registration::Registration()
{
    reg_number[0]='\0';
}

Registration::~Registration() {}

const char *Registration::getRegNumber() const
{
    return reg_number;
}

void Registration::printRegNumber() const
{
    std::cout<<"Registration number: "<<reg_number<<std::endl;
}

void Registration::operator=(Registration &rhs)
{
    if(!is_valid(rhs.getRegNumber()))
    {
        std::cout<<"WRONG REGISTRATION NUMBER "<<reg_number<<'!'<<std::endl;
        return;
    }
    strcpy_safemode(reg_number, rhs.getRegNumber(), strsize(rhs.getRegNumber()));
}

void Registration::operator=(const char *str)
{
    if(!is_valid(str))
    {
        std::cout<<"WRONG REGISTRATION NUMBER "<<reg_number<<'!'<<std::endl;
        return;
    }
    strcpy_safemode(reg_number, str, strsize(str));
}

bool Registration::isEmpty() const
{
    std::cout<<reg_number<<" SIZE:"<<strsize(reg_number)<<std::endl;
    return (strsize(reg_number)==0);
}

void Registration::setRegistration(const char *str)
{
    strcpy_safemode(reg_number, str, strsize(str));
}

#endif // REGISTRATION_H_INCLUDED
