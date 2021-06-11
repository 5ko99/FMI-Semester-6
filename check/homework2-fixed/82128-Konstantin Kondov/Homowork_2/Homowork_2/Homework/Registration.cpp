#include "Registration.h"


 bool Registration::operator==(const Registration& other) const
 {

     if (this->RegNum == other.RegNum) return true;
     return false;

 }

bool Registration::IsStringValid(const std::string& str) const
{
    //get size of given argument str
    std::size_t size = str.size();


    //chekcs the number of the ASCII symbols of the argument, if there dont correcsponds to ASCII code of A-Z OR 1-9 return false and later exception
    for (std::size_t i = 0; i < size; i++) {
        if (((unsigned int)str[i] < 48 || (unsigned int)str[i]>57) && ((unsigned int)str[i] < 65 || (unsigned int)str[i]>90)) {
            return false;
        }
    }

    //If the lenght of the string is bigger than 7 or 8 throws exception
    if (size > 8 || size < 7) { throw std::invalid_argument("You have entered too long or too short registration number"); }


    //Goes to the private case to validate argument with lenght seven , not being valid return false and later exception
    if (size == 7) { CheckValidnessWith7(str); }


    //Goes to the private case to validate argument with lenght eight , not being valid return false and later exception
    if (size == 8) { CheckValidnessWith8(str); }
    
}

bool Registration::CheckValidnessWith7(const std::string& str) const
{
    //Checks the first and the last two symbols of the argument are their ASCII code between A-Z, not being between A-Z return false and later exception
    if ((int)str[0] < 65 || (int)str[0] > 95) return false;
    if ((int)str[5] < 65 || (int)str[5] > 95) return false;
    if ((int)str[6] < 65 || (int)str[6] > 95) return false;

    //Checks the middle symbols of the argument are their ASCII code's between 1-9, , not being between A-Z return false and later exception
    for (int i = 1; i < 5; i++) {
        if ((int)str[i] < 48 || (int)str[i]>57) {
            return false;
        }
    }

    return true;

}

bool Registration::CheckValidnessWith8(const std::string& str) const
{
    //Checks the first, the second and the last two symbols of the argument are their ASCII code between A-Z, not being between A-Z return false and later exception
    if ((int)str[0] < 65 || (int)str[0] > 95) return false;
    if ((int)str[1] < 65 || (int)str[1] > 95) return false;

    if ((int)str[6] < 65 || (int)str[6] > 95) return false;
    if ((int)str[7] < 65 || (int)str[7] > 95) return false;

    //Checks the middle symbols of the argument are their ASCII code's between 1-9, , not being between A-Z return false and later exception
    for (int i = 2; i < 6; i++) {
        if ((int)str[i] < 48 || (int)str[i]>57) {
            return false;
        }
    }

    return true;

}



Registration::Registration(std::string& str)
{
    // if the argument is not valid throws exceptipn
    if (!IsStringValid(str)) { (throw std::invalid_argument("You have entered a different character from 1-9 or A-Z in your code")); }

    //assaing member to argument
    this->RegNum = str;

}

std::string& Registration::GetRegNum()
{
    return this->RegNum;
}

std::ostream& operator<<(std::ostream& out, const Registration& reg)
{
    out << reg.RegNum;
    return out;
}
