#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::string;
using std::ostream;
using std::ifstream;
using std::vector;
#include "Common.h"
#include "Command.h"
using std::cout;
using std::cin; 

vector<string> readFileToVector(const string& fileName)
{
    vector<string> lines;
    ifstream source;
    source.open(fileName);
    if (!source) {
        cout << "File failed to open!\n";
        return lines;
    }
    string line;
    while (getline(source, line))
    {
        lines.push_back(line);
    }
    source.close();
    return lines;
}

vector<string> split(const string& s)
{
    vector<string> ret;
    typedef string::size_type string_size;
    string_size i = 0;

    while (i != s.size()) {
        while (i != s.size() && isspace(s[i]))
            ++i;

        string_size j = i;
        
        while (j != s.size() && !isspace(s[j]))
            j++;

        if (i != j) {
            ret.push_back(s.substr(i, j - i));
            i = j;
        }
    }
    return ret;
}

void parseFile(vector<string> input, Command* driver);
void parseInput(vector<string> input, Command* driver);

int main(int argc, char** argv)
{
    Command driver;
    if (argc > 2) {
        cout << "Invalid arguments!\n";
        return 0;
    }
    if (argc == 2) {
        string fileName(argv[1]);
        vector<string> input = readFileToVector(fileName);
        parseFile(input, &driver);
    }
    
   do {
        cout << "Type CLOSE and press enter to exit program\n";
        cout << "Type LIST and press enter to view available commands\n";
        string input;
        std::getline(std::cin, input);
        if (input == "CLOSE") break;
        if (input == "LIST") {
            cout << "VEHICLE <registration> <description>\n";
            cout << "PERSON <name> <id>\n";
            cout << "ACQUIRE <owner-id> <vehicle-id>\n";
            cout << "RELEASE <owner-id> <vehicle-id\n";
            cout << "REMOVE <what>\n";
            cout << "SHOW [PEOPLE|VEHICLES|<id>]\n";
        }
        for (size_t i = 0; i < input.size(); ++i) {
            if (input[i] != ' ') {
                input[i] = toupper(input[i]);
            }
        }
        vector<string> args = split(input);
        parseInput(args, &driver);
    }     
    while (1);
    
    return 0;
}

void parseFile(vector<string> input, Command* driver)
{
    string tempCmd;
    string arg1;
    string arg2;
    for (size_t i = 0; i < input.size(); ++i) {
        unsigned cntr = 0;
        while (input[i].at(cntr) != ' ' && cntr < input[i].size()) {
            tempCmd.push_back(input[i].at(cntr));
            cntr++;
        }
        if (tempCmd != "PERSON" && tempCmd != "VEHICLE") {
            cout << "Invalid data format!";
            return;
        }
        unsigned argCnt = 0;
        // if command is PERSON
        if (tempCmd == "PERSON") {
            while (input[i].at(cntr) == ' ' && cntr < input[i].size()) {
                cntr++;
            }
            // if person name has spaces
            if (input[i].at(cntr) == '"') {
                cntr++;
                while (input[i].at(cntr) != '"' && cntr < input[i].size()) {
                    arg1.push_back(input[i].at(cntr));
                    cntr++;
                }
                cntr++;
                while (input[i].at(cntr) == ' ' && cntr < input[i].size()) {
                    cntr++;
                }
                while (cntr < input[i].size()) {
                    if (input[i].at(cntr) < '0' || input[i].at(cntr) > '9') {
                        cout << "Invalid data format!\n";
                        return;
                    }
                    arg2.push_back(input[i].at(cntr));
                    cntr++;
                }
                unsigned int temp = std::stoul(arg2, nullptr, 0);
                driver->addPerson(arg1, temp);
                tempCmd.clear();
                arg1.clear();
                arg2.clear();
                continue;
            }
            // if person name doesn't have spaces
            if (input[i].at(cntr) != '"') {
                while (input[i].at(cntr) != ' ' && cntr < input[i].size()) {
                    arg1.push_back(input[i].at(cntr));
                    cntr++;
                }
                while (input[i].at(cntr) == ' ' && cntr < input[i].size()) {
                    cntr++;
                }
                while (cntr < input[i].size()) {
                    if (input[i].at(cntr) < '0' || input[i].at(cntr) > '9') {
                        cout << "Invalid data format!\n";
                        return;
                    }
                    arg2.push_back(input[i].at(cntr));
                    cntr++;
                }
                unsigned int temp = std::stoul(arg2, nullptr, 0);
                driver->addPerson(arg1, temp);
                tempCmd.clear();
                arg1.clear();
                arg2.clear();
                continue;
            }
        }
        // if command is VEHICLE
        if (tempCmd == "VEHICLE") {
            while (input[i].at(cntr) == ' ' && cntr < input[i].size()) {
                cntr++;
            }
            while (input[i].at(cntr) != ' ' && cntr < input[i].size()) {
                arg1.push_back(input[i].at(cntr));
                cntr++;
            }
            while (input[i].at(cntr) == ' ' && cntr < input[i].size()) {
                cntr++;
            }

            // if vehicle description has spaces
            if (input[i].at(cntr) == '"') {
                cntr++;
                while (input[i].at(cntr) != '"' && cntr < input[i].size()) {
                    arg2.push_back(input[i].at(cntr));
                    cntr++;
                }
                Registration temp = arg1;
                driver->addVehicle(temp, arg2);
                tempCmd.clear();
                arg1.clear();
                arg2.clear();
                continue;
            }
            // if vehicle description has no spaces
            if (input[i].at(cntr) != '"') {
                while (cntr < input[i].size()) {
                    arg2.push_back(input[i].at(cntr));
                    cntr++;
                }
                Registration temp = arg1;
                driver->addVehicle(temp, arg2);
                tempCmd.clear();
                arg1.clear();
                arg2.clear();
            }
        }
    }
}

void parseInput(vector<string> input, Command* driver)
{
    if (input[0] == "VEHICLE") {
        if (input.size() > 3) {
            cout << "Wrong command arguments for VEHICLE\n";
            return;
        }
        Registration temp = input[1];
        driver->addVehicle(temp, input[2]);
        return;
    }

    if (input[0] == "PERSON") {
        if (input.size() > 3) {
            cout << "Wrong command arguments for PERSON\n";
            return;
        }
        unsigned int temp = std::stoul(input[2], nullptr, 0);
        driver->addPerson(input[1], temp);
        return;
    }

    if (input[0] == "ACQUIRE") {
        if (input.size() > 3) {
            cout << "Wrong command arguments for ACQUIRE\n";
            return;
        }
        unsigned int temp = std::stoul(input[1], nullptr, 0);
        Registration tempReg = input[2];
        driver->acquire(temp, tempReg);
        return;
    }

    if (input[0] == "RELEASE") {
        if (input.size() > 3) {
            cout << "Wrong command arguments for RELEASE\n";
            return;
        }
        unsigned int temp = std::stoul(input[1], nullptr, 0);
        Registration tempReg = input[2];
        driver->release(temp, tempReg);
        return;
    }

    if (input[0] == "REMOVE") {
        if (input.size() > 2) {
            cout << "Wrong command arguments for REMOVE\n";
            return;
        }
        Registration temp = input[1];
        driver->remove(temp);
        return;
    }

    if (input[0] == "SAVE") {
        if (input.size() > 2) {
            cout << "Wrong command arguments for SAVE\n";
            return;
        }
        driver->save(input[1]);
        return;
    }

    if (input[0] == "SHOW") {
        if (input.size() > 2) {
            cout << "Wrong command arguments for SHOW\n";
            return;
        }
        if (input[1] == "PEOPLE") {
            driver->show(PEOPLE);
        }
        if (input[1] == "VEHICLES") {
            driver->show(VEHICLES);
        }
        Registration temp = input[1];
        if (temp.isValid()) {
            driver->showVehInfo(temp);
        }
        bool isValidId = true;
        for (size_t i = 0; i < input[1].size(); ++i) {
            if (input[1].at(i) < '0' || input[1].at(i) > '9') {
                isValidId = false;
            }
        }
        if (isValidId) {
            unsigned int temp = std::stoul(input[1], nullptr, 0);
            driver->showPerInfo(temp);
        }
        return;
    }
    if (input[0] == "LIST") {

    }
    else {
        cout << "Wrong command!\n";
    }
    return;
}
