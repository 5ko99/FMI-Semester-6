#include "Database.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
Database::Database(std::istream& in, std::ostream &out): Base(in, out) {}

void Database::processInput(const std::vector<std::string>& arg)
{
    std::string arg0 = arg[0];
    std::string print = "print";
    std::string open = "open";
    std::string person = "person";
    std::string save = "save";
    std::string aquire = "aquire";
    std::string add = "add";
    std::string vehicle = "vehicle";
    std::string release = "release";
    std::string show = "show";
    std::string _remove = "remove";

    /// tuk shte si opiswam interface komandite
    if(caseInSensitive(arg0, open)) openFromFile(arg);
    else if(caseInSensitive(arg0, print)) printAll(arg);
    else if(caseInSensitive(arg0, person)) addPerson(arg);
    else if(caseInSensitive(arg0, vehicle)) addVehicle(arg);
    else if(caseInSensitive(arg0, save)) saveToFile(arg);
    else if(caseInSensitive(arg0, aquire)) aquireVehicle(arg);
    else if(caseInSensitive(arg0, release)) releaseVehicle(arg);
    else if(caseInSensitive(arg0, show)) showData(arg);
    else if(caseInSensitive(arg0, _remove)) removeData(arg);

    //else if(arg[0] == "addVehicle") setOwner(getVehicle(arg[1]), getPerson(arg[2]));
    else out<<"Invalid command\n";
}

Database* Database::fromStream(std::istream& in)
{
    //Base* datab = new Database(in, std::cout);
    try
    {
        std::string Line;
        std::vector<std::string> vsplitLine;
        /// read line by line from a file and check if it is a Person or a Vehicle
        while(getline(in, Line))
        {
            vsplitLine=splitLine(Line);
            ///datab->vehicles.. breaks
            if(vsplitLine.size() == 2)
            {
                Registration r(vsplitLine[0]);
                Vehicle v(r, vsplitLine[1]);
                vehicles.push_back(v);
            }
            if(vsplitLine.size() == 3)
            {
                Person a(vsplitLine[0]+vsplitLine[1],std::stoi(vsplitLine[2]));
                persons.push_back(a);
            }
        }
        return this;
    }
    catch(...)
    {
        //delete datab;
        throw;
    }
}

void Database::toStream(std::ostream &out) const
{
    /// need to add some more
    for(auto it : persons)
    {
        out << it.getName() << " " << std::to_string(it.getId()) << std::endl;
    }
    for(auto it : vehicles)
    {
        out << it.getReg().getReg() << " " << it.getDescription() << std::endl;
    }
}
void Database::checkCommand(unsigned int expectedArg, const std::vector<std::string>& vSplitline)
{
    if ( vSplitline.size() != expectedArg )
    {
        std::cout << "Incorrect number of arguments! \n";
        throw std::invalid_argument("Invalid number of arguments!");
    }
}

void Database::openFromFile(const std::vector<std::string>& vsplitLine)
{
    checkCommand(2, vsplitLine);
    std::ifstream inputFile(vsplitLine[1]);
    if(!inputFile.is_open())
    {
        std::cerr<<"An error occured while accessing the file!\n";
    }
    else
    {
        fromStream(inputFile);
        std::cout<<"File successfully opened!\n";
    }
}

void Database::saveToFile(const std::vector<std::string>& vsplitLine)
{
    /// I dont know what it does if I give it an existing file
    checkCommand(2, vsplitLine);
    try
    {
        std::ofstream fileOutput("bin/Data/"+vsplitLine[1], std::ios_base::out | std::ios_base::trunc);
        if(fileOutput.is_open())
        {
            std::cout <<"File already exist\n";
            std::string answer;
            std::string no = "no";
            std::string yes = "yes";
            std::cout << "Do you want to override it?\nYES/NO\n";
            std::cin >> answer;
            if(caseInSensitive(no,answer))
            {
                return;
            }
            else if(caseInSensitive(yes,answer))
            {

            }
        }

        if (!fileOutput.is_open())
        {
            throw std::invalid_argument("An error occured while opening the file.");
        }
        toStream(fileOutput);
        out << "Successfully saved Database to " << vsplitLine[1] << ".\n";
    }
    catch (std::ios_base::failure)
    {
        throw std::invalid_argument("An error occured while accessing the file.");
    }
}

void Database::printAll(const std::vector<std::string>& vsplitLine)
{
    checkCommand(1, vsplitLine);
    std::cout << "Vehicles: \n";
    for (auto it : vehicles)
    {
        std::cout << "Registration: "<< it.getReg() << " " << "description: "
                  << it.getDescription() << " "  << "ownerId: " << it.getPersonId() << std::endl;
    }
    std::cout << std::endl<< "Persons: \n";
    for (auto it : persons)
    {
        std::cout << "Name: " << it.getName() << " " <<"Id: " << it.getId() << " ";
        std::cout << "Owned cars: ";
        for( auto j : it.getCarRegs() )
        {
            std::cout << j << ", ";
        }
        std::cout << std::endl;
    }
}
void Database::addPerson(const std::vector<std::string>& vsplitLine)
{
    checkCommand(4, vsplitLine);
    /// dobawqme chovek s vectora persons vsplitLine[0] e imeto na komandata
    /// pri samoto dobawqne na chowek trqbwa da podsigurim che nqma chowek sys syhtoto id
    if(personExists(std::stoi(vsplitLine[3])))
    {
        std::cout << "Person with the same id already exists!\n";
    }
    else
    {
        Person p(vsplitLine[1]+vsplitLine[2], std::stoi(vsplitLine[3]));
        persons.push_back(p);
        std::cout << "Successfully added person!\n";
    }
}

void Database::addVehicle(const std::vector<std::string>& vsplitLine)
{
    checkCommand(3, vsplitLine);
    if(vehicleExists(vsplitLine[1]))
    {
        std::cout << "Vehicle with the same reg already exists!\n";
    }
    else
    {
        Vehicle p(Registration(vsplitLine[1]), vsplitLine[2]);
        vehicles.push_back(p);
        std::cout << "Successfully added vehicle!\n";
    }
}
void Database::aquireVehicle(const std::vector<std::string>& vsplitLine)
{
    checkCommand(3, vsplitLine);
    if(!vehicleExists(vsplitLine[2]))
    {
        std::cout << "Vehicle with given Registration does not exist! \n";
        return;
    }
    if(!personExists(std::stoi(vsplitLine[1])))
    {
        std::cout << "Person with given id does not exist! \n";
        return;
    }
    /// I must check if the vehicle is already owned by someone else if it is I must release it and add the new owner!
    if(isOwned(getPerson(vsplitLine[1]), getVehicle(vsplitLine[2])))
    {
        std::cout << "Vehicle is already owned by this person.\n";
        return;
    }

    for(auto it = persons.begin(); it != persons.end(); ++it )
    {
        /// if somebody owns the given car
        if( isOwned ( getPerson(std::to_string(it->getId())), getVehicle(vsplitLine[2])))
        {
            std::cout << "Vehicle is already owned by another Person(with id: " << it->getId() << ")\nDo you wish to proceed?\nType YES/NO\n";
            std::string answer;
            std::string no = "no";
            std::string yes = "yes";
            std::cin >> answer;
            if( caseInSensitive(answer, no) )
            {
                std::cout << "Operation canceled!\n";
                return;
            }
            else if( caseInSensitive(answer,yes ))
            {
                /// aquire 123 CA1234KA ; CA1234KA is already owned by another person
                /// iskam za getPerson(CA1234LA.getPersonId()).
                releaseVehicle({"release", std::to_string(it->getId()), vsplitLine[2] });
            }
        }
        /// we get into the next if when the given vehicle is unowned
        if(it->getId() == std::stoi(vsplitLine[1]))
        {
            Registration r(vsplitLine[2]);
            it->p_addVehicle(r);
            std::cout << "Person with id " << it->getId() << " aquired a car with Registration " << r.getReg() << std::endl;
        }
    }
    for(auto it = vehicles.begin(); it != vehicles.end(); ++it )
    {
        if(it->getReg() == vsplitLine[2])
        {
            it->setPersonId(std::stoi(vsplitLine[1]));
        }
    }
}
void Database::releaseVehicle(const std::vector<std::string>& vsplitLine)
{
    checkCommand(3, vsplitLine);
    /// vsplitLine[1] - ownerId veche ne e sobstwenik na vsplitLine[2] -> regNomer
    unsigned int ownerId = std::stoi(vsplitLine[1]);
    Registration reg = vsplitLine[2];
    if(!vehicleExists(vsplitLine[2]))
    {
        std::cout << "Vehicle with given Registration does not exist! \n";
        return;
    }
    if(!personExists(std::stoi(vsplitLine[1])))
    {
        std::cout << "Person with given id does not exist! \n";
        return;
    }
    if(!isOwned(getPerson(vsplitLine[1]), getVehicle(vsplitLine[2])))
    {
        std::cout << "Vehicle is not owned by the given person!\n";
        return;
    }
    /// Here we remove the ownership PERSON -> VEHICLE
    /// iskam da magna ot person.getCarRegs() dadenata kola -> vsplitLine[2] (promenliwata reg)

    for(auto it = persons.begin(); it != persons.end(); ++it )
    {
        if( it->getId() == ownerId )
        {
            /// iskame tozi chowek weche da ne e sobstwenik na dadenata kola
            /// towa trqbwwa da go izmisliq
            int index = 0;
            for(auto j = it->getCarRegs().begin(); j != it->getCarRegs().end(); ++j,++index  )
            {
                ///string   == string
                if(j->getReg() == reg.getReg())
                {
                    /// iskame da mahnem j ot it->getCarRegs()
                    /// next row break the program if we try to erase the last element from getCarRegs
                    if(it->getCarRegs().size() == 1)
                    {
                        it->getCarRegs().clear();
                    }
                    else
                    {
                        it->getCarRegs().erase(it->getCarRegs().begin() + index);
                    }
                    break;
                }
            }
        }
    }
    /// towa bachka ok
    /// Here we remove the ownership VEHICLE -> PERSON
    for(auto it = vehicles.begin(); it != vehicles.end(); ++it )
    {
        if( it->getReg() == reg )
        {
            it->setPersonId(0);
        }
    }
}
void Database::showData(const std::vector<std::string>& vsplitLine)
{
    checkCommand(2, vsplitLine);
    std::string people = "people";
    std::string vehicle = "vehicles";
    std::string arg0 = vsplitLine[1];

    if(caseInSensitive(people, arg0))
    {
        std::cout << std::endl<< "People: \n";
        for (auto it : persons)
        {
            std::cout << "Name: " << it.getName() << " " <<"Id: " << it.getId() << "\n" << "Owned cars: ";

            for( auto j : it.getCarRegs() )
            {
                std::cout << j << " ";
            }
            std::cout << std::endl << std::endl;
        }
    }
    else if(caseInSensitive(vehicle, arg0))
    {
        std::cout << "Vehicles: \n";
        for (auto it : vehicles)
        {
            std::cout << "Registration: "<< it.getReg() << " " << "description: "
                      << it.getDescription() << " "  << "ownerId: " << it.getPersonId() << std::endl;
        }
    }

    else if( isdigit(vsplitLine[1][0]) )
    {
        bool flag = false;
        unsigned int tmpId = std::stoi(vsplitLine[1]);
        for(auto it = persons.begin(); it != persons.end(); ++it)
        {
            if(it->getId() == tmpId)
            {
                std::cout << "Owned cars: ";
                flag = true;
                for(auto j = it->getCarRegs().begin(); j != it->getCarRegs().end(); ++j)
                {
                    std::cout << j->getReg() << " ";
                }
                std::cout << std::endl;
            }
        }
        if(!flag) std::cout << "Incorrect input!\n";

    }

    else if (Registration(vsplitLine[1]).isValid(vsplitLine[1]))
    {
        for(auto it = vehicles.begin(); it != vehicles.end(); ++it)
        {
            if(it->getReg() == vsplitLine[1])
            {
                if(it->getPersonId() == 0)
                {
                    std::cout << "The vehicle with registration " << it->getReg() << " is unowned! \n";
                }
                else std::cout << "Vehicle with registration " << it->getReg() <<" is owned by the person with id " << it->getPersonId() << " \n";
            }
        }
    }
    else
    {
        std::cout << "Incorrect input \n";
    }
}

void Database::removeData(const std::vector<std::string>& vsplitLine)
{
    checkCommand(2, vsplitLine);

    int inputSize = vsplitLine[1].size();
    /// If we are given a person id
    if( personExists(std::stoi(vsplitLine[1])) )
    {
        if( personExists(std::stoi(vsplitLine[1])) )
        {
            int index = 0;
            for ( auto it = persons.begin(); it != persons.end(); ++it, index++ )
            {
                if ( it-> getId() == std::stoi(vsplitLine[1]) )
                {
                    if( it->getCarRegs().size() == 0 ) /// if the person with the given id does not own any cars
                    {
                        persons.erase(persons.begin() + index);
                    }
                    else if ( it->getCarRegs().size() > 0 )
                    {
                        /// remove the person from persons & remove the person from the vehicle
                        persons.erase(persons.begin() + index);
                        for ( auto j = vehicles.begin(); j != vehicles.end(); ++j )
                        {
                            if( j->getPersonId() == std::stoi(vsplitLine[1]) )
                            {
                                j->setPersonId(0);
                            }
                        }
                    }
                }
            }
        }
        else
        {
            std::cout << "Person with given id does not exist!\n";
        }
    }
    /// if we are given a Registration
    else if ( inputSize == 7 || inputSize == 8 )                  ///Registration(vsplitLine[1]).isValid(vsplitLine[1]) )
    {
        std::cout << "vehicle!";
        if(!vehicleExists(vsplitLine[1]))
        {
            std::cout << "Vehicle with given Registration does not exist! \n";
            return;
        }
        int index = 0;
        for( auto it = vehicles.begin() ; it != vehicles.end(); ++it, ++index )
        {
            if(it->getReg().getReg() == vsplitLine[1])
            {
                if( it->getPersonId() != 0 )/// if the car is already owned by someone
                {
                    std::cout << "Vehicle is owned! Do you wish to proceed?\n";
                    std::string answer;
                    std::cin >> answer;
                    if( answer == "no" || answer == "No" || answer == "nO" || answer == "NO" )
                    {
                        std::cout<<"Removal operation aborted!\n";
                        break;
                    }
                    /// the following if doesnt work if we want to remove the last vehicle from vector<Vehicle> vehicles
                    /// otherwise it does what it is supposed to
                    else if ( answer == "yes"  || answer == "Yes"  || answer == "YEs"  || answer == "YES"  || answer == "yES" || answer == "yeS" || answer == "YeS" || answer == "yEs" )
                    {
                        vehicles.erase(vehicles.begin() + index);
                        std::cout << "Vehicle deleted\n";
                        for( auto j = persons.begin(); j != persons.end(); ++j )
                        {
                            int ind = 0;
                            for ( auto p = j->getCarRegs().begin(); p != j->getCarRegs().end(); ++p )
                            {
                                if( p->getReg() == vsplitLine[1] )
                                {
                                    j->getCarRegs().erase( j->getCarRegs().begin() + ind );
                                    break;
                                }
                                ind++;
                            }
                        }
                    }
                    else out << "Incorrect answer!\n";
                }
                else if ( it->getPersonId() == 0 ) /// if the vehicle is unowned
                {
                    std::cout << "Vehicle deleted\n";
                    vehicles.erase(vehicles.begin() + index);
                }
            }
        }
    }

    else std::cout << "Object with given id " << vsplitLine[1] << " does not exist!\n";
}

bool Database::caseInSensitive(std::string & str1, std::string &str2)
{
    return ((str1.size() == str2.size()) && std::equal(str1.begin(), str1.end(), str2.begin(), [](char & c1, char & c2)
    {
        return (c1 == c2 || std::toupper(c1) == std::toupper(c2));
    }));
}

bool Database::personExists(const unsigned int& id) const
{
    bool flag = false;
    for(auto it : persons)
    {
        if(it.getId() == id)
            flag = true;
    }
    return flag;
}
bool Database::vehicleExists(const std::string& reg) const
{
    bool flag = false;
    for(auto it : vehicles)
    {
        if(it.getReg().getReg() == reg)
            flag = true;
    }
    return flag;
}
Vehicle Database::getVehicle(std::string str) const
{
    for(auto it: vehicles)
    {
        if (it.getReg() == str)
        {
            return it;
        }
    }
    std::cerr<<"Vehicle with given reg doesn't exist\n";
}

Person Database::getPerson(std::string str) const
{
    for(auto it: persons)
    {
        if (it.getId() == std::stoi(str))
        {
            return it;
        }
    }
    std::cerr<<"Person with given Id doesn't exist\n";
}


int Database::countPeople() const
{
    return persons.size();
}
int Database::countVehicles() const
{
    return vehicles.size();
}
bool Database::isOwned(Person p, Vehicle v)
{
    bool flag = false;
    for(auto it = p.getCarRegs().begin(); it != p.getCarRegs().end(); ++it )
    {
        if(*it == v.getReg())
            flag = true;
    }
    return flag;
}
