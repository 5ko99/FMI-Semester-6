#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include "../include/input.hpp"
//#include "../include/manager.hpp"

bool Input::readLine(std::istream& in)
{
    input = '\0';

    while(input[0] == '\0' && in.good())
    {
        std::getline(in, input);
    }    
    return true;
}

void Input::toLower()
{
    for (size_t i = 0; i < arguments[0].size(); i++)
    {
        if(arguments[0][i] >= 'A' && arguments[0][i] <= 'Z')
        {
            arguments[0][i] += 'a' - 'A';
        }
    }
    
}

const char* Input::INSTRUCTIONS[] = {
    "vehicle",
    "person",
    "acquire",
    "release",
    "remove",
    "save",
    "show"
};

const int Input::REQUIRED_ARGUMENTS[] = {3, 3, 3, 3, 2, 2, 2};

void Input::callFunction()
{
    for (size_t i = 0; i < INSTRUCTIONS_COUNT; i++)
    {
        if(arguments[0].compare(INSTRUCTIONS[i]) == 0){
            if(arguments.size() != REQUIRED_ARGUMENTS[i]){
                cout<<"Invalid arguments count! Try again!\n";
                break;
            }

            try
            {
                ((*this).*(commands[i]))();
            }
            catch(const std::invalid_argument& e)
            {
                cout << e.what() << '\n';
            }
            catch(const std::exception& e){
                cout << "Error! Please try again!\n";
            }
            break;
        }
    }
}

bool Input::handleInput()
{
    splitInput();
    toLower();

    if(arguments[0].compare("quit") == 0){
        return false;
    }

    callFunction();
    arguments.clear();

    return true;
}

void Input::splitInput()
{
    int length = input.size();
    int spaceCnt = 0;
    int from = 0;

    for (size_t i = 0; i < length; i++)
    {
        if(isspace(input[i])){
            input[i] = ' ';
           ++spaceCnt;
        }
        else
        {
            if(spaceCnt && i == spaceCnt){
                input.erase(0, spaceCnt);
                i = 0;
                length -=spaceCnt;
                spaceCnt = 0;
            }
            else if(spaceCnt)
            {
                if(spaceCnt > 1){
                    --spaceCnt;
                    i -= spaceCnt;
                    length -= spaceCnt;
                    input.erase(i, spaceCnt);
                    input[i-1] = ' ';
                }
                if(from > -1){
                    arguments.push_back(input.substr(from, i - 1 - from));
                }
                from = i;
                spaceCnt = 0;
            }

            if(input[i] == '"'){
                from = i + 1;
                i = input.find('"', from);

                if(i == string::npos){
                    throw std::invalid_argument("Missing second \"");
                }

                arguments.push_back(input.substr(from, i - from));
                from = -1;
            }
        }
    }

    if(from > -1 && from < input.size()){
        arguments.push_back(input.substr(from, input.size() - from - spaceCnt));
    }
}

bool Input::read(std::istream& in)
{
    quit = false;

    readLine(in);
    return handleInput();
}

void Input::loadFromFile(const char* path)
{
    std::fstream in(path, std::ios::in);

    if(!in.is_open()){
        in.clear();
        in.close();
        cout<<"Invalid file path! Starting with an empty database!\n";
        return;
    }

    while(!in.eof() && read(in))
    {}
    in.close();
}

void Input::vehicle()
{
    data.addVehicle(arguments[1].c_str(), arguments[2]);
}
void Input::person()
{   
    data.addPerson(arguments[1], Manager::convertToULong(arguments[2].c_str()));
}
void Input::acquire()
{
    data.aquire(Manager::convertToULong(arguments[1].c_str()), arguments[2].c_str());
}
void Input::release()
{
    data.release(Manager::convertToULong(arguments[1].c_str()), arguments[2].c_str());
}
void Input::remove()
{
    data.remove(arguments[1].c_str());
}
void Input::save()
{
    std::ifstream file;
    file.open(arguments[1]);
    
    if(file && !Manager::takePermission("The file already exists!")){
        file.close();
        return;
    }
    
    file.close();

    data.save(arguments[1].c_str());
}
void Input::show()
{
    data.show(arguments[1].c_str());
}
