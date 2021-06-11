#include <iostream>

void skipWhitespaces(std::istream& in)
{
    char c;

    do{
        c = in.get();
    }
    while (c == ' ' || c == '\n' || c == '\t');

    in.unget();
}

bool getConfirmation()
{
    skipWhitespaces(std::cin);
    char c = std::cin.get();

    return (c == 'Y' || c == 'y');
}

std::string inputString(std::istream& in)
{
    std::string name;

    skipWhitespaces(in);

    char c = in.get();

    if( (c != '\'') && (c != '\"') )
    {
        in.unget();
        in >> name;
    }
    else{
        while(1)
        {
            c = in.get();

            if( c == '\'' || c == '\"' )
            {
                break;
            }

            name += c;
        }
    }

    return name;
}

bool isNumber(const std::string& s)
{
    for (size_t i = 0; i < s.size(); i++)
    {
        if(s[i] < '0' || s[i] > '9')
        {
            return false;
        }
    }
    return true;
}
