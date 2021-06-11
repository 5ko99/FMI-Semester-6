#include "Commander.hpp"
#include <fstream>

Commander::Commander()
{
}

Commander& Commander::getInstance() 
{
    static Commander instance;
    return instance;
}

std::string Commander::splitWords(std::string input)
{
    bool hadLetters = false; //or a number
    bool openedQuotes = false;
    std::size_t from = 0;
    std::size_t cnt = 0;
    std::string word;

    std::size_t i = 0;
    for(i; i<input.size(); ++i) 
    {
        if(openedQuotes)
        {
            if(input[i] == '\"')
            {
                openedQuotes = false;
                word = input.substr(from, cnt);
                return word;
            }
            else
            {
                ++cnt;
            }
        }
        if(!openedQuotes && input[i] == '\"')
        {
            openedQuotes = true;
            ++from;
        }
        if(!openedQuotes && input[i] != '\"')
        {
            if((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z') 
                                                    || (input[i] >= '0' && input[i] <= '9'))
            {
                hadLetters = true;
            }
            if(!hadLetters)
            {
                from += 1;
            }
            if(hadLetters && input[i] != ' ')   
            {
                ++cnt;
            }
            if(hadLetters && input[i] == ' ') 
            {
                word = input.substr(from, cnt);
                return word;
            }
        }
    }
    if(i == input.size())
    {
        word = input.substr(from, cnt);
        return word;
    }
}

Command Commander::recognizeCommand(std::string word)               
{
    for(std::size_t i = 0; i<word.size(); ++i)
    {
        char c = word[i];
        word[i] = toupper(c);
    }
    if(word == "VEHICLE")
    {
        return VEHICLE;
    }
    if(word == "PERSON")
    {
        return PERSON;
    }
    if(word == "ACQUIRE")
    {
        return ACQUIRE;
    }
    if(word == "RELEASE")
    {
        return RELEASE;
    }
    if(word == "REMOVE")
    {
        return REMOVE;
    }
    if(word == "SAVE")
    {
        return SAVE;
    }
    if(word == "SHOW")
    {
        return SHOW;
    }

    throw std::runtime_error("Unrecognized command.");
}

void Commander::execute(std::string word, std::string arg1, std::string arg2)
{
    Command com = NONE;
    com = recognizeCommand(word);

    switch (com)
    {
    case VEHICLE:
    {
        organizer.addVehicle(arg1, arg2);
        break;
    }
    case PERSON:
    {
        unsigned tempId = stoul(arg2,nullptr,0);
        organizer.addPerson(arg1, tempId);
        break;
    }
    case ACQUIRE:   
    {
        unsigned tempId1 = stoul(arg1,nullptr,0);
        organizer.acquire(tempId1, arg2);
        break;
    }
    case RELEASE:
    {
        unsigned tempId2 = stoul(arg1,nullptr,0);
        organizer.release(tempId2, arg2);
        break; 
    }
    default:
        throw std::runtime_error("Unrecognized command.");     
        break;
    }

    std::string temp(word +" "+ arg1 +" "+ arg2);
    commandsMemory.push_back(temp);
}

void Commander::execute(std::string word, std::string arg1) 
{
    Command com = NONE;
    com = recognizeCommand(word);

    switch (com)
    {      
    case REMOVE:
    {
        if(Verify::isValidRegistration(arg1))
        {
            if(organizer.getVehicle(arg1).getOwnerId())
            {
                std::cout<<"This vehicle has an owner. Do you really want to remove it? Y/N\n";
                if(userConfirmation())
                {
                    organizer.remove(arg1);
                }
            }
            if(!organizer.getVehicle(arg1).getOwnerId())
            {
                organizer.remove(arg1);
            }
        }
        else
        {
            unsigned tempId = stoul(arg1,nullptr,0);
            if(organizer.getPerson(tempId)->numberOfVehicles())
            {
                std::cout<<"This person owns vehicles. Do you really want to remove it? Y/N\n";
                if(userConfirmation())
                {
                    organizer.remove(tempId);
                }
            }
            else
            {
                organizer.remove(tempId);
            }
        }
        break;
    }
    case SAVE:
    {
        save(arg1);
        break;
    }
    case SHOW: 
        break;
    default:
        throw std::runtime_error("Unrecognized command.");  
        break;
    }

    std::string temp(word +" "+ arg1);
    commandsMemory.push_back(temp);
}

bool Commander::userConfirmation()
{
    std::string input;
    std::cin>>input;
    if(input == "Y")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Commander::save(std::string file)  
{
    bool flag = true;
    std::ifstream exists(file);
    if(exists)
    {
        std::cout<<"Do you want to overwrite this file? Y/N\n";
        flag = userConfirmation();
        
        exists.close();
    }

    if(flag)
    {
        std::ofstream out(file);
        if(!out)
        {
            throw std::runtime_error("Unable to open this log file.");
        }

        for(std::size_t i = 0; i<commandsMemory.size(); ++i)
        {
            out << commandsMemory[i] << std::endl;
        }
        out.close();
    }
}

void Commander::read(std::string file)
{
    std::ifstream in(file);
    if(in)
    {

        in.close();
    }
    else
    {
        throw std::runtime_error("Unable to open this log file.");
    }
}

std::string Commander::userInput()
{
    char* temp = new char[MAX_INPUT];
    std::cin.getline(temp, MAX_INPUT);
    std::string input = temp;

    delete[] temp;
    temp = nullptr;

    return input;
}

void Commander::comunicator()
{
    std::cout<<"What would you like to do?\n";
    std::string input;
 
    input = userInput();

    std::string word1 = splitWords(input);
    std::string temp = input.substr(word1.size(), input.size() - word1.size());
    input =  temp;

    std::string word2 = splitWords(input);
    temp = input.substr(word2.size(), input.size() - word2.size());
    input =  temp;

    std::string word3 = splitWords(input);
    temp = input.substr(word3.size(), input.size() - word3.size());
    input =  temp;

    if(word1 != "" && word2 != "" && word3 != "")
    {
        execute(word1, word2, word3);
    }
    else
    {
        if(word1 != "" && word2 != "")
        {
            execute(word1, word2);
        }
        else
        {
            throw std::runtime_error("Unknown command.");
        }
    }
}
