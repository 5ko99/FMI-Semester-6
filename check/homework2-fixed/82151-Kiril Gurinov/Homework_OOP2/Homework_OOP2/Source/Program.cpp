#include "Program.h"
#include <chrono>
#include <thread>

//--------------------------------------------------------------
//Helping functions
//--------------------------------------------------------------
int charArrayToInt(const char *arr)
{
    int i, value, r, flag;
    flag = 1;
    i = value = 0;
    for (i = 0; i < strlen(arr); i++)
    {

        if (i == 0 && arr[i] == '-')
        {
            flag = -1;
            continue;
        }

        r = arr[i] - '0';
        value = value * 10 + r;
    }
    value = value * flag;

    return value;
}

bool checkString(const char *arr)
{
    const int string_len = strlen(arr);
    int i = 0;
    if (arr[0] == '-')
        i++;
    for (; i < string_len; i++)
        if (!isdigit(arr[i]))
            return false;
    return true;
}

std::string toLower(std::string str)
{
    for (std::string::size_type i = 0; i < str.length(); i++)
        std::tolower(str[i]);
    return str;
}

void toUpper(char *arr)
{
    for (int i = 0; i < strlen(arr); i++)
    {
        std::toupper(arr[i]);
    }
}

bool confirm()
{
    std::cout << "Are you sure: Y/N\n";
    std::string input;
    std::cin >> input;
    input = toLower(input);
    if (input == "y" || input == "yes")
        return true;
    return false;
}

void clearCharArray(char *arr)
{
    for (int i = 0; i < strlen(arr); i++)
        arr[i] = '\0';
}
//--------------------------------------------------------------
//Helping functions
//--------------------------------------------------------------

void Program::addOption(std::string str)
{
    options.push_back(str);
}

void Program::getInput(const char *arr)
{
    char temp[30], firstInput[20], secondInput[30], thirdInput[20];
    bool flag1 = true, flag2 = false, flag3 = true;
    int j = 0;
    for (int i = 0; i < strlen(arr); i++)
    {
        if (arr[i] == ' ')
        {
            if (flag1)
            {
                std::strcpy(firstInput, temp);
                flag1 = false;
                flag2 = true;
                clearCharArray(temp);
                j = 0; //trying to skip this v here
                i++;   // skipping one because " symbol (EX: COMMAND "COMMAND")
            }
            else if (flag2)
            {
                if (arr[i - 1] == '"')
                {
                    temp[j - 1] == '\0';
                    std::strcpy(secondInput, temp);
                    clearCharArray(temp);
                    j = 0;
                    flag2 = false;
                }
                else
                {
                    temp[j] = arr[i];
                    j++;
                }
            }
            else
            {
                std::strcpy(thirdInput, temp);
                clearCharArray(temp);
                j = 0;
                break;
            }
        }
        else
        {
            temp[j] = arr[i];
            j++;
        }
    }

    toUpper(firstInput);

    if (std::strcmp(firstInput, "VEHICLE") == 0)
    {
        addVehicle(secondInput, thirdInput);
    }
    else if (std::strcmp(firstInput, "PERSON") == 0)
    {
        if (checkString(thirdInput))
        {
            int tempN = charArrayToInt(thirdInput);
            addPerson(secondInput, tempN);
        }
        else
        {
            throw std::exception("Failed parsing char array to int!");
        }
    }
    else if (std::strcmp(firstInput, "ACQUIRE") == 0)
    {
        if (checkString(secondInput))
        {
            int tempN = charArrayToInt(secondInput);
            addVehicleOwner(tempN, thirdInput);
        }
        else
        {
            throw std::exception("Failed parsing char array to int!");
        }
    }
    else if (std::strcmp(firstInput, "RELEASE") == 0)
    {
        if (checkString(secondInput))
        {
            int tempN = charArrayToInt(secondInput);
            releaseVehicle(tempN, thirdInput);
        }
        else
        {
            throw std::exception("Failed parsing char array to int!");
        }
    }
    else if (std::strcmp(firstInput, "REMOVE") == 0)
    {
        remove(secondInput);
    }
    else if (std::strcmp(firstInput, "SAVE") == 0)
    {
        save(secondInput);
    }
    else if (std::strcmp(firstInput, "SHOW") == 0)
    {
        show(secondInput);
    }
    else if (std::strcmp(firstInput, "QUIT") == 0)
    {
        running = false;
    }
    else
    {
        throw std::exception("Error 422: Bad string");
    }
}

void Program::addPerson(const char *name, unsigned int id)
{
    bool flag = true;
    for (int i = 0; i <= people.size(); i++)
        if (people[i].getId() == id)
            flag = false;

    if (flag)
    {
        Person newPerson = Person(name, id);
        people.push_back(newPerson);
        std::string str = "PERSON \"";
        str.append(name);
        str.append("\" ");
        str.append(std::to_string(id));
        addOption(str);
    }
    else
    {
        throw std::exception("Person with such ID already exists!");
    }
}

void Program::addVehicle(const char *registration, const char *description)
{
    bool flag = true;
    for (int i = 0; i <= cars.size(); i++)
        if (std::strcmp(cars[i].getRegistration(), registration) == 0)
            flag = false;

    if (flag)
    {
        Vehicle newVehicle = Vehicle(registration, description);
        cars.push_back(newVehicle);
        std::string str = "VEHICLE ";
        str.append(registration);
        str.append(" ");
        str.append(description);
        addOption(str);
    }
    else
    {
        throw std::exception("Vehicle with such registration already exists!");
    }
}

void Program::addVehicleOwner(unsigned int id, const char *registration)
{
    int pos = -1;
    bool flag = false;
    for (int i = 0; i <= cars.size(); i++)
        if (std::strcmp(cars[i].getRegistration(), registration) == 0)
            pos = i;

    if (pos == -1)
    {
        throw std::exception("No vehicle with such registration found!");
    }

    for (int i = 0; i <= people.size(); i++)
        if (people[i].getId() == id)
        {
            if (cars.at(pos).isOwned())
                releaseVehicle(id, registration);
            people[i].addVehicle(cars.at(pos));
            flag = true;
        }

    if (flag)
    {
        std::string str = "ACQUIRE ";
        str.append(std::to_string(id));
        str.append(" ");
        str.append(registration);
        addOption(str);
    }
    else
    {
        throw std::exception("New vehicle owner not found!");
    }
}

void Program::releaseVehicle(unsigned int id, const char *registration)
{
    int pos = -1;
    bool flag = false;
    for (int i = 0; i <= cars.size(); i++)
        if (std::strcmp(cars[i].getRegistration(), registration) == 0)
            pos = i;

    if (pos == -1)
    {
        throw std::exception("No vehicle with such registration found!");
    }

    for (int i = 0; i <= people.size(); i++)
        if (people[i].getId() == id)
        {
            people[i].removeVehicle(cars.at(pos));
            flag = true;
        }

    if (flag)
    {
        std::string str = "RELEASE ";
        str.append(std::to_string(id));
        str.append(" ");
        str.append(registration);
        addOption(str);
    }
    else
    {
        throw std::exception("Vehicle owner not found!");
    }
}

void Program::remove(const char *what)
{

    Registration temp = Registration(what);
    if (temp.isEmpty())
    {
        Vehicle temp;
        bool flag = false;
        int pos = -1;
        for (int i = 0; i <= cars.size(); i++)
        {
            if (std::strcmp(what, cars[i].getRegistration()) == 0)
            {
                temp = cars[i];
                pos = i;
                flag = true;
                break;
            }
        }
        if (flag)
        {
            if (temp.isOwned())
            {
                if (confirm())
                {
                    temp.getOwner().removeVehicle(temp);
                    temp.removeOwner();
                    cars.erase(cars.begin() + pos);
                    std::string str = "REMOVE ";
                    str.append(what);
                    addOption(str);
                }
            }
            else
            {
                cars.erase(cars.begin() + pos);
                std::string str = "REMOVE ";
                str.append(what);
                addOption(str);
            }
        }
        else
            throw std::exception("No car with such registration found!");
    }
    else if (checkString(what))
    {
        int tempNumber = charArrayToInt(what);
        if (tempNumber >= 0)
        {
            Person temp;
            bool flag = false;
            int pos = -1;
            for (int i = 0; i <= people.size(); i++)
            {
                if (people[i].getId() == tempNumber)
                {
                    temp = people[i];
                    flag = true;
                    pos = i;
                    break;
                }
            }
            if (flag)
            {
                if (tempNumber >= 0)
                {
                    Person temp;
                    if (temp.hasVehicle())
                    {
                        if (confirm())
                        {
                            temp.removeAllVehicles();
                            people.erase(people.begin() + pos);
                            std::string str = "REMOVE ";
                            str.append(what);
                            addOption(str);
                        }
                    }
                    else
                    {
                        people.erase(people.begin() + pos);
                        std::string str = "REMOVE ";
                        str.append(what);
                        addOption(str);
                    }
                }
            }
            else
            {
                throw std::exception("No person with such ID exists!");
            }
        }
        else
            throw std::exception("ID can't be negative!");
    }
    else
        throw std::exception("No such ID/Registration exists in database!");
}

void Program::save(const char *path)
{
    std::ofstream saveFile(path);

    for (int i = 0; i <= people.size(); i++)
    {
        Person temp = people[i];
        std::string str = "PERSON \"";
        str.append(temp.getName());
        str.append("\" ");
        str.append(std::to_string(temp.getId()));
        str.append("\n");
        saveFile << str;
    }

    for (int i = 0; i <= cars.size(); i++)
    {
        Vehicle temp = cars[i];
        std::string str = "VEHICLE \"";
        str.append(temp.getRegistration());
        str.append(" ");
        str.append(temp.getDescription());
        str.append("\n");
        saveFile << str;
    }

    for (int i = 0; i <= people.size(); i++)
    {
        if (people[i].hasVehicle())
        {
            int id = people[i].getId();
            std::vector temp = people[i].getVehicles();
            for (int j = 0; j <= temp.size(); j++)
            {
                std::string str = "ACQUIRE \"";
                str.append(std::to_string(id));
                str.append(" ");
                str.append(temp[j].getRegistration());
                str.append("\n");
                saveFile << str;
            }
        }
    }

    saveFile.close();
}

void Program::show(char *option)
{
    Registration temp;
    if (checkString(option))
    {
        bool flag = true;
        int id = charArrayToInt(option);
        for (int i = 0; i <= people.size(); i++)
        {
            if (people[i].getId() == id)
            {
                std::vector tempCars = people[i].getVehicles();
                people[i].print();
                std::cout << "Cars\n";
                for (int j = 0; j < tempCars.size(); j++)
                {
                    std::cout << "#" << j << " ";
                    tempCars[j].print();
                }
                std::cout << std::endl;
                flag = false;
                break;
            }
        }
        if (flag)
        {
            throw std::exception("No such ID exist in the database! (show command)");
        }
    }
    else if (temp.isValid(option))
    {
        bool flag = true;
        for (int i = 0; i <= cars.size(); i++)
        {
            if (std::strcmp(cars[i].getRegistration(), option) == 0)
            {
                cars[i].print();
                std::cout << "Owner info:\n";
                Person owner = cars[i].getOwner();
                owner.print();
                flag = false;
            }
        }
        if (flag)
        {
            throw std::exception("No such car registration exist in the database! (show command)");
        }
    }
    toUpper(option);
    if (std::strcmp(option, "PEOPLE"))
    {
        for (int i = 0; i <= people.size(); i++)
        {
            people[i].print();
        }
    }
    else if (std::strcmp(option, "VEHICLES"))
    {
        for (int i = 0; i <= cars.size(); i++)
        {
            cars[i].print();
        }
    }
    else
    {
        throw std::exception("Incorrect input for show command");
    }
}

void Program::load(const char *path)
{
    std::ifstream myFile(path);
    std::string line;
    if (myFile)
    {
        while (std::getline(myFile, line))
        {
            getInput(line.c_str());
        }
        myFile.close();
    }
    std::cout << "Loaded file successfuly\n";
}

std::vector<std::string> Program::getOptions()
{
    return options;
}

void Program::run()
{
    running = true;
    std::string input;
    std::cout << "Do you want to load a database from a file? Y/N";
    std::cin >> input;
    input = toLower(input);
    if (input == "y" || input == "yes")
    {
        std::cout << "Enter file path: ";
        std::cin >> input;
        load(input.c_str());
    }
    while (running)
    {
        showCommands();
        std::cin >> input;
        try
        {
            getInput(input.c_str());
        }
        catch (std::exception e)
        {
            std::cout << e.what();
        }
    }

    std::cout << "Do you want to save the database to a file? Y/N";
    std::cin >> input;
    input = toLower(input);
    if (input == "y" || input == "yes")
    {
        std::cout << "Enter file path: ";
        std::cin >> input;
        save(input.c_str());
    }

    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono;      // nanoseconds, system_clock, seconds
    std::cout << "Goodbye\n";
    sleep_for(nanoseconds(10));
}

bool Program::isRunning()
{
    return running;
}

void showCommands()
{
    std::cout << "VEHICLE <registration> <description> to register a vehicle\n";
    std::cout << "PERSON <name> <id> to register a person\n";
    std::cout << "ACQUIRE <owner-id> <vehicle-id> to register a vehicle to a person\n";
    std::cout << "RELEASE <owner-id> <vehicle-id> to remove a vehicle from a person\n";
    std::cout << "REMOVE <what> to remove a vehicle or a person in the database (what needs to be id or registration)\n";
    std::cout << "SAVE <path> to save the database in a file\n";
    std::cout << "SHOW [PEOPLE|VEHICLES|<id>] to show all people or vehicles or specific entity\n";
}
