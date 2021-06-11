#include <fstream>
#include "Commands.h"

Commands::Commands() {}

Commands::Commands(std::vector<Vehicle> allVehicles, std::vector<Person> allPersons) {
    for (int i = 0; i < allVehicles.size(); ++i) {
        listOfAllVehicles.push_back(allVehicles.at(i));
    }
    for (int i = 0; i < allPersons.size(); ++i) {
        listOfAllPeople.push_back(allPersons.at(i));
    }
}

void Commands::Command(std::string& command) {
    int size = 0;
    for (; size < command.size() && command[size] != ' '; ++size) {
        command[size] = tolower(command[size]);
    }
    if (command.find("vehicle") == 0){
        std::string registration = "";
        for (++size; size < command.size() && command[size] != ' '; ++size) {
            registration += command[size];
        }
        std::string description = "";
        for (++size; size < command.size(); ++size) {
            description += command[size];
        }
        Registration newRegistration(registration);
        Vehicle newVehicle (newRegistration, description);

        bool IsThereSuchVehicle = false;
        for (int i = 0; i < listOfAllVehicles.size(); ++i) {
            if(listOfAllVehicles.at(i) == newVehicle){
                IsThereSuchVehicle = true;
            }
        }
        if (!IsThereSuchVehicle){
            AddVehicle(newVehicle);
        } else {
            throw std::invalid_argument("You cannot add vehicle which is already added");
        }
    } else if (command.find("person") == 0){
        std::string name = "";
        if (command[size + 1] == '"') {
            size +=2;
            for (; size < command.size() && command[size] != '"'; ++size) {
                name += command[size];
            }
            size++;
        } else {
            for (++size; size < command.size() && command[size] != ' ' ; ++size) {
                name += command[size];
            }
        }
        std::string id = "";
        for (++size; size < command.size(); ++size) {
            if(command[size] >= '0' && command[size] <= '9'){
                id += command[size];
            } else {
                throw std::invalid_argument("wrong id");
            }
        }
        int idNum = stoi(id);
        Person newPerson (name, idNum);
        AddPerson(newPerson);
    } else if (command.find("acquire") == 0){
        std::string id = "";
        for (++size; size < command.size() && command[size] != ' '; ++size) {
            if(command[size] >= '0' && command[size] <= '9'){
                id += command[size];
            } else {
                throw std::invalid_argument("wrong id");
            }
        }
        unsigned int idNum = stoi(id);
        std::string reg = "";
        for (++size; size < command.size(); ++size) {
            reg+= command[size];
        }
        Registration registration(reg);
        Acquire(idNum, registration);
    } else if (command.find("release") == 0){
        std::string id = "";
        for (++size; size < command.size() && command[size] != ' '; ++size) {
            if(command[size] >= '0' && command[size] <= '9'){
                id += command[size];
            } else {
                throw std::invalid_argument("wrong id");
            }
        }
        unsigned int idNum = stoi(id);
        std::string reg = "";
        for (++size; size < command.size(); ++size) {
            reg+= command[size];
        }
        Registration registration(reg);
        Release(idNum, registration);
    } else if (command.find("remove") == 0){
        std::string what = "";
        for (++size; size < command.size(); ++size) {
            what += command[size];
        }
        bool IsItReg = IsItRegisration(what);
        if (IsItReg){
            Registration newRegistration (what);
            RemoveVehicle(newRegistration);
        } else {
            unsigned int id = stoi(what);
            RemovePerson(id);
        }
    } else if (command.find("save") == 0){
        std::string path = "";
        for (++size; size < command.size(); ++size) {
            path += command[size];
        }
        Save(path);
    } else if (command.find("show") == 0){
        std::string what = "";
        for (++size; size < command.size(); ++size) {
            what += command[size];
        }
        bool IsItReg = IsItRegisration(what);
        if (IsItReg == true) {
            Registration newReg(what);
            ShowACar(newReg);
        } else {
            for (int i = 0; i < what.size(); ++i) {
                what[i] += tolower(what[i]);
            }

            if(what == "people"){
                ShowAllPeople();
            } else if (what == "vehicles"){
                ShowAllVehicles();
            } else {
                unsigned int id = stoi(what);
                ShowAPerson(id);
            }
        }
    } else {
        throw std::invalid_argument("There is no such command");
    }

}

void Commands::AddVehicle(const Vehicle &vehicle) {
    for (int i = 0; i < listOfAllVehicles.size(); ++i) {
        if (listOfAllVehicles[i].getRegistration() == vehicle.getRegistration()){
            throw std::invalid_argument("there is existing vehicle with this registration");
        }
    }
    listOfAllVehicles.push_back(vehicle);
}

void Commands::AddPerson(const Person &person) {
    for (int i = 0; i < listOfAllPeople.size(); ++i) {
        if (listOfAllPeople[i].getId() == person.getId()){
            throw std::invalid_argument("there is existing person with this id");
        }
    }
    listOfAllPeople.push_back(person);
}

void Commands::Acquire(unsigned int id, const Registration &registration) {
    int i = 0;
    for (; i < listOfAllPeople.size(); ++i) {
        if (listOfAllPeople[i].getId() == id)break;
    }
    for (int j = 0; j < listOfAllVehicles.size(); ++j) {
        if (listOfAllVehicles[j].getRegistration() == registration){
            if (listOfAllVehicles[j].getOwner() != nullptr) {
                listOfAllVehicles[j].getOwner()->RemoveVehicle(listOfAllVehicles[j]);
            }
            listOfAllPeople[i].AddVehicle(listOfAllVehicles[j]);
            break;
        }
    }
}

void Commands::Release(unsigned int id, const Registration &registration) {
    int i = 0;
    for (; i < listOfAllPeople.size(); ++i) {
        if (listOfAllPeople[i].getId() == id)break;
    }
    for (int j = 0; j < listOfAllVehicles.size(); ++j) {
        if (listOfAllVehicles[j].getRegistration() == registration){
            listOfAllPeople[i].RemoveVehicle(listOfAllVehicles[j]);
            break;
        }
    }
}

void Commands::RemoveVehicle(const Registration &registration) {
    for (int i = 0; i < listOfAllVehicles.size(); ++i) {
        if (listOfAllVehicles[i].getRegistration() == registration){
            if (listOfAllVehicles[i].getOwner() != nullptr) {
                listOfAllVehicles[i].getOwner()->RemoveVehicle(listOfAllVehicles[i]);
            }
            listOfAllVehicles.erase(listOfAllVehicles.begin()+i);
            break;
        }
    }
}

void Commands::RemovePerson(unsigned int id) {
    for (int i = 0; i < listOfAllPeople.size(); ++i) {
        if (listOfAllPeople[i].getId() == id) {
            listOfAllPeople[i].RemoveAllVehicles();
            listOfAllPeople.erase(listOfAllPeople.begin()+i);
            break;
        }
    }
}

void Commands::Save(const std::string &path) {
    bool writeInTheFile = true;
    std::ifstream ifile;
    ifile.open(path);
    if(ifile) {
        std::cout << "this is existing file. Do you want to rewrite the information in it? (\"Yes\"/\"No\") ";
        std::string YesOrNo;
        std::getline(std::cin, YesOrNo);
        for (int i = 0; i < YesOrNo.size(); ++i) {
            YesOrNo[i] = tolower(YesOrNo[i]);
        }
        if (YesOrNo == "no"){
            writeInTheFile = false;
        }
    }
    ifile.close();

    std::ofstream newFile;
    newFile.open (path);


    if (writeInTheFile){
        for (int i = 0; i < listOfAllPeople.size(); ++i) {
            newFile << "person " << listOfAllPeople[i].getName() << " " << listOfAllPeople[i].getId() << std::endl;
        }
        for (int i = 0; i < listOfAllVehicles.size(); ++i) {
            newFile << "vehicle " << listOfAllVehicles[i].getRegistration().getRegistration()
                    << " " << listOfAllVehicles[i].getDescription() << std::endl;
            if (listOfAllVehicles[i].getOwner() != nullptr){
                newFile << "acquire " << listOfAllVehicles[i].getOwner()->getId() << " "
                        << listOfAllVehicles[i].getRegistration().getRegistration()  << std::endl;
            }
        }
    }
    newFile.close();
}

void Commands::ShowAllPeople() const {
    for (int i = 0; i < listOfAllPeople.size(); ++i) {
        listOfAllPeople[i].Print();
    }
}

void Commands::ShowAllVehicles() const {
    for (int i = 0; i < listOfAllVehicles.size(); ++i) {
        listOfAllVehicles[i].printRegistration();
        std::cout << " ";
        listOfAllVehicles[i].printDescription();
        std::cout << std::endl;
    }
}

void Commands::ShowACar(const Registration &registration) const {
    for (int i = 0; i < listOfAllVehicles.size(); ++i) {
        if (listOfAllVehicles[i].getRegistration() == registration){
            listOfAllVehicles[i].printRegistration();
            std::cout << " ";
            listOfAllVehicles[i].printDescription();
            std::cout << std::endl;
            break;
        }
    }
}

void Commands::ShowAPerson(unsigned int id) {
    for (int i = 0; i < listOfAllPeople.size(); ++i) {
        if (listOfAllPeople[i].getId() == id){
            listOfAllPeople[i].Print();
            listOfAllPeople[i].PrintAllVehicles();
            break;
        }
    }
}

bool Commands::IsItRegisration(const std::string what) {
    bool IsItReg = 1;
    if (what.size() == 7){
        if ((what[0] >= 'A' && what[0] <= 'Z')&&
            (what[1] >= '0' && what[1] <= '9') &&
            (what[2] >= '0' && what[2] <= '9') &&
            (what[3] >= '0' && what[3] <= '9') &&
            (what[4] >= '0' && what[4] <= '9') &&
            (what[5] >= 'A' && what[5] <= 'Z')&&
            (what[6] >= 'A' && what[6] <= 'Z')){
        } else {
            IsItReg = 0;
        }
    } else if (what.size() == 8){
        if ((what[0] >= 'A' && what[0] <= 'Z')&&
            (what[1] >= 'A' && what[1] <= 'Z')&&
            (what[2] >= '0' && what[2] <= '9') &&
            (what[3] >= '0' && what[3] <= '9') &&
            (what[4] >= '0' && what[4] <= '9') &&
            (what[5] >= '0' && what[5] <= '9') &&
            (what[6] >= 'A' && what[6] <= 'Z')&&
            (what[7] >= 'A' && what[7] <= 'Z')){
        } else {
            IsItReg = 0;
        }
    } else {
        IsItReg = 0;
    }
    return IsItReg;
}
