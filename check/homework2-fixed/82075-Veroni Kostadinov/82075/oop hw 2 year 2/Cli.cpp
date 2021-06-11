#include "Cli.h"
using namespace std;

bool Cli::checkString(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (isdigit(str[i]) == false)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

vector<string> split(const string &s, char delim)
{
    vector<string> result;
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim))
    {
        result.push_back(item);
    }

    return result;
}

void Cli::handleInput(string input, bool isRunning)
{
    vector<string> splitString = split(input, ' ');

    if (splitString[0] == "VEHICLE")
    {
        if (checkString(splitString[1]) && checkString(splitString[2]) && this->dbase.validateRegNum(splitString[1]))
        {
            this->dbase.vehicle_command(splitString[1], splitString[2]);
        }
        else
        {
            cout << "wrong input\n";
        }
    }
    else if (splitString[0] == "PERSON")
    {
        if (checkString(splitString[1]) && !checkString(splitString[2]))
        {
            this->dbase.person_command(splitString[1], stoi(splitString[2]));
        }
        else
        {
            cout << "wrong input\n";
        }
    }
    else if (splitString[0] == "ACQUIRE")
    {
        if (!checkString(splitString[1]) && this->dbase.validateRegNum(splitString[1]))
        {
            this->dbase.acquire_command(stoi(splitString[1]), splitString[2]);
        }
        else
        {
            cout << "wrong input\n";
        }
    }
    else if (splitString[0] == "RELEASE")
    {
        if (!checkString(splitString[1]) && !checkString(splitString[2]))
        {
            this->dbase.release_command(stoi(splitString[1]), splitString[2]);
        }
        else
        {
            cout << "wrong input\n";
        }
    }
    else if (splitString[0] == "REMOVE")
    {

        this->dbase.remove_command(splitString[1]);
    }
}
