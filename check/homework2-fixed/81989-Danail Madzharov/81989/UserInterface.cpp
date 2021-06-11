#include "UserInterface.h"
#include <string>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void UserInterface::start()
{
    cout << "Hello and welcome!" << endl;
    interactive();
}

void UserInterface::interactive()
{
    while (true)
    {
        printMenu();
        cout << endl;
        string command;
        std::getline(cin, command);
        int counter = 0;
        string words[999];

        for (int i = 0; i < command.length(); i++)
        {
            if (command[i] == ' ')
            {
                counter++;
            }
            else
            {
                words[counter] += command[i];
            }
        }

        transform(words[0].begin(), words[0].end(), words[0].begin(), ::tolower);

        if (words[0] == "vehicle")
        {
            transform(words[1].begin(), words[1].end(), words[1].begin(), ::toupper);

            if (!database.validateRegNumber(words[1]))
            {
                cout << "Registration number is not valid";
                continue;
            }

            if (database.doesVehicleExistAlready(words[1]))
            {
                cout << "Vehicle already in database";
                continue;
            }

            string description;
            for (int i = 2; i <= counter; i++)
            {
                description += words[i];
            }

            Registration *reg = new Registration(words[1]);
            Vehicle *newVehicle = new Vehicle(reg, description);
            this->database.addVehicle(newVehicle);
            continue;
        }

        else if (words[0] == "person")
        {
            string personName;

            if (words[1].at(0) == '"' && words[1].at(words[1].length() - 1) != '"')
            {
                words[1].erase(0, 1);
                for (int i = 1; i <= counter; i++)
                {
                    if (words[i].at(words[i].length() - 1) == '"')
                    {
                        words[i].erase(words[i].length() - 1);
                        personName += words[i];
                        break;
                    }
                    personName += words[i] + " ";
                }
            }
            else
            {
                personName = words[1];
            }

            if (words[counter].at(0) == '-')
            {
                cout << "The Id must be a positive number" << endl;
                continue;
            }

            try
            {
                unsigned int idNumber = stoi(words[counter]);

                if (this->database.doesPersonExistAlready(idNumber))
                {
                    cout << "Person is already in the database!";
                    continue;
                }

                Person *newPerson = new Person(personName, idNumber);
                this->database.addPerson(newPerson);
            }
            catch (const invalid_argument &e)
            {
                cout << "Invalid person ID" << endl;
            }
        }

        else if (words[0] == "acquire")
        {
            if (words[1].at(0) == '-')
            {
                cout << "The Id must be a positive number" << endl;
                continue;
            }

            try
            {
                unsigned int idNumber = stoi(words[1]);
                transform(words[2].begin(), words[2].end(), words[2].begin(), ::toupper);

                if (!database.validateRegNumber(words[2]))
                {
                    cout << "Registration number is not valid";
                    continue;
                }

                if (!database.doesVehicleExistAlready(words[2]) || !database.doesPersonExistAlready(idNumber))
                {
                    cout << "Vehicle or person is not in our database!";
                    continue;
                }

                Person *person = database.getPersonById(idNumber);
                Vehicle *vehicle = database.getVehicleByRegNumber(words[2]);

                database.setCarOwner(person, vehicle);
            }
            catch (invalid_argument &e)
            {
                cout << "Invalid person ID" << endl;
            }
        }
        else if (words[0] == "release")
        {

            if (words[1].at(0) == '-')
            {
                cout << "The Id must be a positive number" << endl;
                continue;
            }

            unsigned int idNumber = stoi(words[1]);
            transform(words[2].begin(), words[2].end(), words[2].begin(), ::toupper);

            if (!database.validateRegNumber(words[2]))
            {
                cout << "Registration number is not valid";
                continue;
            }

            if (!database.doesVehicleExistAlready(words[2]) || !database.doesPersonExistAlready(idNumber))
            {
                cout << "Vehicle or person is not in our database!";
                continue;
            }

            Person *person = database.getPersonById(idNumber);
            Vehicle *vehicle = database.getVehicleByRegNumber(words[2]);
            database.removeCarOwner(person, vehicle);
            continue;
        }

        else if (words[0] == "remove")
        {
            transform(words[1].begin(), words[1].end(), words[1].begin(), ::toupper);
            if (this->database.validateRegNumber(words[1]))
            {
                this->database.deleteCarFromDatabase(words[1]);
            }
            else if (words[1].at(0) != '-' || (words[1].at(0) >= '1' || words[1].at(0) <= '9'))
            {
                try
                {
                    unsigned int idNumber = stoi(words[1]);
                    this->database.deletePersonFromDatabase(idNumber);
                }
                catch (invalid_argument &e)
                {
                    cout << "Invalid person ID";
                    continue;
                }
            }
        }
        else if (words[0] == "show")
        {
            transform(words[1].begin(), words[1].end(), words[1].begin(), ::toupper);
            if (words[1] == "PEOPLE")
            {
                this->database.printAllPeople();
            }
            else if (words[1] == "VEHICLES")
            {
                this->database.printAllVehicles();
            }
            else if (this->database.validateRegNumber(words[1]))
            {
                this->database.printVehicleByRegNumber(words[1]);
                continue;
            }
            else
            {
                if (words[1].at(0) == '-' || (words[1].at(0) < '1' || words[1].at(0) > '9'))
                {
                    cout << "Invalid Person ID" << endl;
                    continue;
                }
                else
                {
                    unsigned int idNumber = stoi(words[1]);
                    this->database.printPersonById(idNumber);
                }
            }
        }
        else if (words[0] == "save")
        {
            this->database.saveInformationToFile(words[1]);
        }
        else if (words[0] == "quit")
        {
            return;
        }
    }
}

void UserInterface::printMenu()
{
    cout << endl;
    cout << "You have the following commands: " << endl
         << endl;
    cout << "\t 1. 'VEHICLE <registration> <description>' - creates a new vehicle" << endl;
    cout << "\t 2. 'PERSON <name> <id>' - creates a new person" << endl;
    cout << "\t 3. 'ACQUIRE <owner-id> <vehicle-id>' - The person with <owner-id> id will acquire the vehicle <vehicle-id>" << endl;
    cout << "\t 4. 'RELEASE <owner-id> <vehicle-id>' - The person with <owner-id> id releases the vehicle <vehicle-id>" << endl;
    cout << "\t 5. 'REMOVE <what>' - Removes the person/vehicle with ID/Reg.number <what>" << endl;
    cout << "\t 6. 'SAVE <path>' - Saves the database in a file with an absolute path <path>" << endl;
    cout << "\t 7. 'SHOW [PEOPLE|VEHICLES|<id>]' - Show information about a Person, vehicle or an object with ID/reg.number <id>" << endl;
    cout << "\t 8. 'quit' - quits the program" << endl;
}
