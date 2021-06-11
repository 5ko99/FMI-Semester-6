#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <assert.h>


#include "Registration.h"
#include "Person.h"
#include "Vehicle.h"


std::ostream& operator<<(std::ostream& out, const Person& person)
{
    if (person.cars.empty())
    {
        out << "The person: " << person.getName() << " with id: " << person.getId() << " has no cars!" << '\n';
    }
    else
    {
        out << "The person: " << person.getName() << " with id: " << person.getId() << " has the following cars: " << '\n';
        for (const auto& car : person.cars)
        {
            out << "Registration: " << car.get().getRegistration() << "; Description: " << car.get().getDescription() << '\n';
        }
    }

    return out;
}

std::ostream& operator<<(std::ostream& out, const Vehicle& vehicle)
{
    if (vehicle.owner.empty())
    {
        out << "The car: " << vehicle.getDescription() << " with registration: " << vehicle.getRegistration()
            << " has no owner." << '\n';
    }
    else
    {
        out << "The car: " << vehicle.getDescription() << " with registration: " << vehicle.getRegistration()
            << " has an owner: " << '\n' << "Name:" << vehicle.owner.front().get().getName() << "; Id:" << vehicle.owner.front().get().getId() << '\n';
    }

    return out;

}

///Validate registration number
bool validateRegistration(std::string num)
{
    bool answer;
    if (num.length() == 7)
    {
        //
        if (num[0] < 'A' || num[0] > 'Z')
        {
            answer = false;
        }
        else
        {
            bool flag = true;
            for (int i = 1; i < 5; i++)
            {
                if (num[i] < '0' || num[i] > '9')
                {
                    flag = false;
                    answer = false;
                }

            }

            ///TODO
            if (flag)
            {
                if (num[5] < 'A' || num[5] > 'Z' || num[6] < 'A' || num[6] > 'Z')
                {
                    answer = false;
                }
                else
                {
                    answer = true;
                }
            }
            else
            {
                answer = false;
            }

        }

    }
    else if (num.length() == 8)
    {
        if (num[0] < 'A' || num[0] > 'Z' || num[1] < 'A' || num[1] > 'Z')
        {
            answer = false;
        }
        else
        {
            bool flag = true;
            for (int i = 2; i < 6; i++)
            {
                if (num[i] < '0' || num[i] > '9')
                {
                    flag = false;
                    answer = false;
                }

            }

            if (flag)
            {
                if (num[6] < 'A' || num[6] > 'Z' || num[7] < 'A' || num[7] > 'Z')
                {
                    answer = false;
                }
                else
                {
                    answer = true;
                }
            }
            else
            {
                answer = false;
            }
        }
    }
    else
    {
        answer = false;
    }

    return answer;
}

///Split the command
void splitCommand(std::string str, std::vector<std::string>& output)
{
    std::istringstream stream(str);
    bool flag = false;
    std::string temp_str = "";
    while (stream >> str)
    {
        if (flag)
        {
            temp_str.append(" ");
            temp_str.append(str);
            if (str.back() == '"')
            {
                flag = false;
                output.push_back(temp_str);
                temp_str = "";
            }
        }
        else if (str.front() == '"')
        {
            flag = true;
            temp_str.append(str);
        }
        else
        {
            output.push_back(str);
        }

    }
}

///Working only with numbers
unsigned int convertStringToNumber(std::string str)
{
    unsigned int number;
    if (!(std::istringstream(str) >> number))
        number = 0;

    assert(number != 0);
    return number;
}




///CreatingVehicle
void createVehicle(std::vector<std::string>& command_words, std::vector<Registration>& registrations, std::vector<Vehicle>& vehicles)
{
    ///Validate reg number
    if (validateRegistration(command_words.at(1)))
    {
        ///Validate
        bool identical_registration = false;
        for (std::vector<Vehicle>::iterator it = vehicles.begin(); it != vehicles.end(); it++)
        {
            if (it->getRegistration().compare(command_words.at(1)) == 0)
            {
                identical_registration = true;
            }
        }

        ///Create
        if (!identical_registration)
        {
            Registration temp_reg(command_words.at(1));

            registrations.push_back(temp_reg);


            Vehicle temp_veh(&registrations.back(), command_words.at(2));

            vehicles.push_back(temp_veh);
        }
        else
        {
            std::cout << "Identical registration! Cannot insert the vehicle!" << std::endl;
        }
    }
    else
    {
        std::cout << "Invalid registration number!" << std::endl;
    }

}

///Creating person
void createPerson(std::vector<std::string>& command_words, std::vector<Person>& people)
{
    ///Validate
    bool identical_id = false;
    unsigned int id_num = convertStringToNumber(command_words.at(2));

    for (std::vector<Person>::iterator it = people.begin(); it != people.end(); it++)
    {
        if (it->getId() == id_num)
        {
            identical_id = true;
        }
    }
    ///Create
    if (!identical_id)
    {
        Person temp_per(command_words.at(1), id_num);
        people.push_back(temp_per);
    }
    else
    {
        std::cout << "Identical identification number! Cannot insert the person!" << std::endl;
    }
}

void acquireRelation(std::vector<std::string>& command_words, std::vector<Person>& people, std::vector<Vehicle>& vehicles)
{
    ///Validate if there is such a person
    unsigned int index_person = 0;
    unsigned int i = 0;
    bool identical_id = false;
    unsigned int j = 0;
    unsigned int id_num = convertStringToNumber(command_words.at(1));
    for (std::vector<Person>::iterator it = people.begin(); it != people.end(); it++, i++)
    {
        if (it->getId() == id_num)
        {
            identical_id = true;
            index_person = i;
        }

    }

    if (identical_id)
    {

        unsigned int index_vehicle = 0;
        ///Validate if there is such registration number
        bool identical_registration = false;
        for (std::vector<Vehicle>::iterator it = vehicles.begin(); it != vehicles.end(); it++, j++)
        {
            if (it->getRegistration().compare(command_words.at(2)) == 0)
            {
                identical_registration = true;
                index_vehicle = j;
            }
        }

        if (identical_registration)
        {
            vehicles.at(index_vehicle).addOwner(people.at(index_person));

            /*!std::cout << "ACQUIRED:" << std::endl;
            std::cout << vehicles.at(index_vehicle) << std::endl;
            std::cout << people.at(index_person) << std::endl;*/
        }
        else
        {
            std::cout << "There is no car with registration number: " << command_words.at(1) << std::endl;
        }
    }
    else
    {
        std::cout << "There is no person with id: " << id_num << std::endl;
    }
}

void releasePersonFromCars(unsigned int index_person, std::vector<Person>& people, std::vector<Vehicle>& vehicles)
{
    std::vector<std::string> regs = people.at(index_person).getAllRegistrations();

    if (regs.empty())
    {
        std::cout << "Owner has no cars!" << std::endl;
    }
    else
    {
        for (std::vector<std::string>::iterator it = regs.begin(); it != regs.end(); it++)
        {
            for (std::vector<Vehicle>::iterator iter = vehicles.begin(); iter != vehicles.end(); iter++)
            {
                if (iter->getRegistration().compare(*it) == 0)
                {
                    iter->releaseOwner(people.at(index_person));
                }
            }
        }
    }

}

void showPeople(std::vector<Person>& people)
{
    std::cout << "People:" << std::endl;
    for (std::vector<Person>::iterator it = people.begin(); it != people.end(); it++)
    {
        std::cout << "Id: " << it->getId() << ", ";
        std::cout << "Name: " << it->getName() << std::endl;
    }
}

void showVehicles(std::vector<Vehicle>& vehicles)
{
    std::cout << "Vehicles:" << std::endl;
    for (std::vector<Vehicle>::iterator it = vehicles.begin(); it != vehicles.end(); it++)
    {
        std::cout << "Registration: " << it->getRegistration() << ", ";
        std::cout << "Description: " << it->getDescription() << std::endl;
    }
}

bool isRegistrationId(std::string id)
{
    bool answer;

    if (id.front() >= 'A' && id.front() <= 'Z')
    {
        answer = true;
    }
    else
    {
        answer = false;
    }

    return answer;
}

void showObject(std::string id, std::vector<Person>& people, std::vector<Vehicle>& vehicles)
{
    if (isRegistrationId(id))
    {
        bool flag = false;
        unsigned int index;
        unsigned int i = 0;
        for (std::vector<Vehicle>::iterator it = vehicles.begin(); it != vehicles.end(); it++, i++)
        {
            if (it->getRegistration().compare(id) == 0)
            {
                flag = true;
                index = i;
            }
        }

        if (flag)
        {
            std::cout << vehicles.at(index);
        }
        else
        {
            std::cout << "There is no such car!" << '\n';
        }
    }
    else
    {
        bool flag = false;
        unsigned int index;
        unsigned int i = 0;
        for (std::vector<Person>::iterator it = people.begin(); it != people.end(); it++, i++)
        {
            if (it->getId() == convertStringToNumber(id))
            {
                flag = true;
                index = i;
            }
        }

        if (flag)
        {
            std::cout << people.at(index);
        }
        else
        {
            std::cout << "There is no such person!" << '\n';
        }
    }

}

void saveToFile(std::string file_path, std::vector<Person>& people, std::vector<Vehicle>& vehicles)
{
    std::ofstream dest_file;
    dest_file.open(file_path.c_str());
    if (dest_file.is_open())
    {
        for (std::vector<Person>::iterator it = people.begin(); it != people.end(); it++)
        {
            dest_file << "PERSON " << it->getName() << " " << it->getId() << std::endl;
        }

        for (std::vector<Vehicle>::iterator it = vehicles.begin(); it != vehicles.end(); it++)
        {
            dest_file << "VEHICLE " << it->getRegistration() << " " << it->getDescription() << std::endl;
        }

        for (std::vector<Person>::iterator it = people.begin(); it != people.end(); it++)
        {
            std::vector<std::string> regs = it->getAllRegistrations();

            if (!regs.empty())
            {
                for (std::vector<std::string>::iterator iter = regs.begin(); iter != regs.end(); iter++)
                {
                    dest_file << "ACQUIRE " << it->getId() << " " << *iter << std::endl;
                }
            }
        }

    }
    else
    {
        std::cout << "There was a problem with opening the file." << std::endl;
    }

    dest_file.close();
}

void loadFile(std::string file_path, std::vector<Registration>& registrations, std::vector<Person>& people, std::vector<Vehicle>& vehicles)
{
    std::string line;
    std::vector<std::string> line_words;

    std::ifstream source_file;
    source_file.open(file_path.c_str());
    if (source_file.is_open())
    {
        while (getline(source_file, line))
        {
            line_words.clear();

            ///std::cout << line << std::endl;

            splitCommand(line, line_words);

            /*!for(int i = 0 ; i < line_words.size(); i++)
            {
                std::cout << line_words.at(i) << "; ";
            }*/

            ///std::cout << '\n';

            std::for_each(line_words.front().begin(), line_words.front().end(), [](char& c)
                {
                    c = std::toupper(c);
                });

            if (line_words.front().compare("VEHICLE") == 0)
            {
                createVehicle(line_words, registrations, vehicles);
            }

            if (line_words.front().compare("PERSON") == 0)
            {
                createPerson(line_words, people);
            }

            if (line_words.front().compare("ACQUIRE") == 0)
            {
                acquireRelation(line_words, people, vehicles);
            }
        }
    }
    else
    {
        std::cout << "There was a problem with opening the file." << std::endl;
    }
}



int main(int argc, char* argv[])
{


    std::string command;
    std::string delimiter = " ";
    std::string token;
    std::vector<std::string> command_words;

    std::vector<Registration> registrations;
    std::vector<Vehicle> vehicles;
    std::vector<Person> people;


    /*std::cout << "Argc: " << argc << '\n';
    for(int i = 0 ; i < argc; i++)
    {
        std::cout << argv[i] << '\n';
    }*/

    if (argc == 2)
    {
        loadFile(argv[1], registrations, people, vehicles);
    }


    /*Registration r("M1182BB");

    Registration r1;

    Registration r2("CB2030BB");

    r1 = r;*/

    /*!Person p("Pesho", 1);

    people.push_back(p);

    Vehicle v(&r1, "Mercedes");

    Vehicle v1(&r2, "VW");

    vehicles.push_back(v1);

    ///p.addCar(v);

    ///v1.addOwner(p);
    vehicles.at(0).addOwner(people.at(0));

    std::cout << vehicles.at(0) << '\n';

    std::cout << people.at(0) << '\n';

    std::cout << "Release..." << std::endl;
    people.at(0).releaseCar("CB2030BB");
    vehicles.at(0).releaseOwner();

    std::cout << vehicles.at(0) << '\n';

    std::cout << people.at(0) << '\n';*/

    ///Stop when "exit" is written
    for (bool flag = false; flag != true; )
    {
        command_words.clear();

        std::getline(std::cin, command);

        splitCommand(command, command_words);

        std::for_each(command_words.front().begin(), command_words.front().end(), [](char& c)
            {
                c = std::toupper(c);
            });

        if (command_words.front().compare("VEHICLE") == 0)
        {
            createVehicle(command_words, registrations, vehicles);
        }

        if (command_words.front().compare("PERSON") == 0)
        {
            createPerson(command_words, people);
        }

        if (command_words.front().compare("ACQUIRE") == 0)
        {
            acquireRelation(command_words, people, vehicles);
        }


        if (command_words.front().compare("RELEASE") == 0)
        {
            ///Validate if there is such a person
            unsigned int index_person = 0;
            unsigned int i = 0;
            bool identical_id = false;
            unsigned int id_num = convertStringToNumber(command_words.at(1));
            for (std::vector<Person>::iterator it = people.begin(); it != people.end(); it++, i++)
            {
                if (it->getId() == id_num)
                {
                    identical_id = true;
                    index_person = i;
                }

            }

            if (identical_id)
            {

                if (people.at(index_person).ownCar(command_words.at(2)))
                {
                    ///std::cout << "Found Car with: " << people.at(index_person).getName() << std::endl;

                    ///Releasing owner
                    for (std::vector<Vehicle>::iterator it = vehicles.begin(); it != vehicles.end(); it++)
                    {
                        if (it->getRegistration().compare(command_words.at(2)) == 0)
                        {
                            it->releaseOwner(people.at(index_person));
                            std::cout << "Association between Person with id: " << people.at(index_person).getId() << " and Vehicle with registration: "
                                << it->getRegistration() << " has been released!" << std::endl;
                        }
                    }
                }
                else
                {
                    std::cout << "There is no car to release!" << std::endl;
                }

            }
            else
            {
                std::cout << "There is no person with id: " << id_num << std::endl;
            }
        }


        if (command_words.front().compare("REMOVE") == 0)
        {
            ///Check the origin of the <what>
            if (command_words.at(1).front() >= 'A' && command_words.at(1).front() <= 'Z')
            {
                bool flag = false;
                unsigned int index_vehicle;
                unsigned int index_person;
                unsigned int i = 0;
                unsigned int j = 0;
                for (std::vector<Vehicle>::iterator it = vehicles.begin(); it != vehicles.end(); it++, i++)
                {
                    if (it->getRegistration().compare(command_words.at(1)) == 0)
                    {
                        flag = true;
                        index_vehicle = i;
                    }
                }
                if (flag)
                {
                    if (vehicles.at(index_vehicle).hasOwner())
                    {
                        std::string response;
                        std::cout << "The vehicle has an owner. Do you still want to proceed with removing the vehicle? (Y/N):";
                        std::getline(std::cin, response);

                        std::for_each(response.begin(), response.end(), [](char& c)
                            {
                                c = std::toupper(c);
                            });

                        if (response == "Y")
                        {
                            unsigned int id_num = vehicles.at(index_vehicle).getOwnerId();

                            for (std::vector<Person>::iterator it = people.begin(); it != people.end(); it++, j++)
                            {
                                if (it->getId() == id_num)
                                {
                                    index_person = j;
                                }

                            }

                            ///Release
                            vehicles.at(index_vehicle).releaseOwner(people.at(index_person));
                            vehicles.erase(vehicles.begin() + index_vehicle);
                        }
                        else
                        {
                            std::cout << "REMOVE aborted!" << std::endl;
                        }

                    }
                    else
                    {
                        vehicles.erase(vehicles.begin() + index_vehicle);
                    }
                }
                else
                {
                    std::cout << "Nothing to remove!" << std::endl;
                }

            }
            else
            {
                ///For person
                bool flag = false;
                unsigned int index_person;
                unsigned int i = 0;
                for (std::vector<Person>::iterator it = people.begin(); it != people.end(); it++, i++)
                {
                    if (it->getId() == convertStringToNumber(command_words.at(1)))
                    {
                        index_person = i;
                        flag = true;
                    }
                }

                if (flag)
                {
                    if (people.at(index_person).hasCar())
                    {
                        std::string response;
                        std::cout << "The person has a vehicle. Do you still want to proceed with removing the person? (Y/N):";
                        std::getline(std::cin, response);

                        std::for_each(response.begin(), response.end(), [](char& c)
                            {
                                c = std::toupper(c);
                            });

                        if (response == "Y")
                        {
                            releasePersonFromCars(index_person, people, vehicles);
                            people.erase(people.begin() + index_person);
                        }
                        else
                        {
                            std::cout << "REMOVE aborted!" << std::endl;
                        }
                    }
                    else
                    {
                        releasePersonFromCars(index_person, people, vehicles);
                        people.erase(people.begin() + index_person);
                    }
                }
                else
                {
                    std::cout << "There is no such person to remove!" << std::endl;
                }

            }
        }

        if (command_words.front().compare("SHOW") == 0)
        {
            std::for_each(command_words.back().begin(), command_words.back().end(), [](char& c)
                {
                    c = std::toupper(c);
                });

            if (command_words.back().compare("PEOPLE") == 0)
            {
                showPeople(people);
            }
            else if (command_words.back().compare("VEHICLES") == 0)
            {
                showVehicles(vehicles);
            }
            else
            {
                showObject(command_words.back(), people, vehicles);
            }

        }

         ///Трябва да е без кавички, защото в противен случай не работи open()
         ///Това не позволява да има в абсолютният път интервали!!!!

         ///Пример:
        ///save C:\temp\test
        if (command_words.front().compare("SAVE") == 0)
        {
            ///Saving to file
            saveToFile(command_words.back(), people, vehicles);
        }




        if (command_words.front().compare("EXIT") == 0)
        {
            flag = true;
        }

    }

    return 0;
}
