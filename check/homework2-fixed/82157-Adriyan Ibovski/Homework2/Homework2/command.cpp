#include "Command.h"
#include <iostream>
#include <unistd.h>

Command *Command::getInstance() {
    if(!instance) instance = new Command;
    return instance;
}
Command::~Command() {
    m_person.clear();
    m_vehicle.clear();
}

void Command::addVehicle(const Registration &reg, const string &desc) {
    if(findVehicle(reg)) throw std::invalid_argument("There is already vehicle with this registration");
    m_vehicle.emplace_back(reg,desc);
}

void Command::addPerson(const string &name, unsigned int ID) {
    if(findPerson(ID)) throw std::invalid_argument("There is already a person with this ID");
    m_person.emplace_back(name,ID);
}

void Command::setVehicleOwner(unsigned int ID, const Registration &reg) {
    for(Person &p : m_person){
        if(p.getID() == ID){
            Vehicle* v = findVehicle(reg);
            if(v->getOwner()) releaseVehicleOwner(v->getOwner()->getID(),reg);
            p.addVehicle(v);

        }
    }
}

void Command::releaseVehicleOwner(unsigned int ID, const Registration& reg) {
    for(Person &p : m_person)
        if(p.getID() == ID)  p.removeVehicle(reg);
}
bool Command::remove(unsigned int ID) {
    for(int it = 0; it < m_person.size(); it++){
        Person& p = m_person[it];
        if(p.getID() == ID){
            if(p.hasVehicles()){
                std::cout<<"The person with ID= "<<ID<<" own vehicles. Are you sure you want to delete it?"<<std::endl;
                std::cout<<"Enter Y / N: ";
                std::string input;
                do {
                    std::getline(std::cin,input);
                } while (input!="Y" && input!="N");
                if(input == "Y"){
                    p.releaseAllVehicles();
                    m_person[it] = m_person.back();
                    m_person.pop_back();
                }
            }
            else{
                m_person[it] = m_person.back();
                m_person.pop_back();
            }
            return true;
        }
    }
    return false;
}

bool Command::remove(const Registration &reg) {
    for(int it = 0; it < m_vehicle.size(); it++){
        Vehicle& v = m_vehicle[it];
        if(v.getReg() == reg){
            if(v.getOwner()){
                std::cout<<"The vehicle with REG = "<<reg.getString()<<" has an owner. Are you sure you want to delete it?"<<std::endl;
                std::cout<<"Enter Y / N: \n";
                std::string input;
                do {
                    std::cout<<"Input= ";
                    std::getline(std::cin,input);
                } while (input!="Y" && input!="N");
                if(input == "Y"){
                    v.getOwner()->removeVehicle(reg);
                    m_vehicle[it] = m_vehicle.back();
                    m_vehicle.pop_back();
                }
            }
            else{
                m_vehicle[it] = m_vehicle.back();
                m_vehicle.pop_back();
            }
            return true;
        }
    }
    return false;
}

void Command::showPeople() {
    for(Person &p : m_person){
        std::cout<<p.getName()<< " "<<p.getID()<<std::endl;
    }
}

void Command::showVehicles() {
    std::cout<<"Registration | Description | OwnerID\n";
    for(Vehicle &v: m_vehicle){
        std::cout<<v.getReg().getString()<<" "<<v.getDesc()<<" ";
        if(v.getOwner()) std::cout<<v.getOwner()->getID()<<std::endl;
        else std::cout<<"None\n";
    }
}


void Command::showVehicle(const string &reg) {
    std::cout<<"Registration | Description | OwnerID\n";
    for(Vehicle &v : m_vehicle){
        if(v.getReg().getString() == reg){
            std::cout<<v.getReg().getString()<<" "<<v.getDesc()<<" ";
            if(v.getOwner()) std::cout<<v.getOwner()->getID()<<std::endl;
            else std::cout<<"None\n";
            break;
        }
    }
}


void Command::showPersonbyID(unsigned int ID) {

    for(Person &p : m_person){
        if(p.getID() == ID) {
            std::cout << p.getName() << " " << p.getID() << std::endl;
            std::cout<<p.getName()<<"'s vehicles' registration and description: \n";
            p.showAllVehicles();
            break;
        }
    }
}


Vehicle* Command::findVehicle(const Registration &reg) {
    for(Vehicle &v : m_vehicle){
        if(v.getReg() == reg)
            return &v;
    }
    return nullptr;
}

Person *Command::findPerson(unsigned int ID) {
    for(Person &p : m_person){
        if(p.getID() == ID)
            return &p;
    }
    return nullptr;
}


bool Command::findCommand(string t) {
    if(t.size() > 8) return true;
    if(t == "VEHICLE ") return true;
    if(t == "PERSON ") return true;
    if(t == "ACQUIRE ") return true;
    if(t == "RELEASE ") return true;
    if(t == "REMOVE ") return true;
    if(t == "SAVE ") return true;
    if(t == "SHOW ") return true;

    return false;
}

void Command::execute(string command) {
    string cm = "";
    int i = 0;
    while(!findCommand(cm)){
        cm += toupper(command[i]);
        i++;
    }
    if(i > 8) {std::cout<<"No such command found \n"; return;}
    if(cm == "VEHICLE "){
        string reg = "";
        while(command[i] != ' '){
            reg += command[i];
            i++;
        }
        string desc = "";
        i++;
        while(i < command.size()){
            desc += command[i];
            i++;
        }
        addVehicle(Registration(reg),desc);
        return;
    }
    if(cm == "PERSON "){
        string name = "";
        if(command[i] == '"'){
            i++;
            while(command[i] != '"'){
                name += command[i];
                i++;
            }
            i+=2;
        }else {
            while (command[i] != ' ') {
                name += command[i];
                i++;
            }
            i++;
        }
        unsigned int ID = 0;
        while('0'<= command[i] && command[i] <= '9'){
            ID = ID * 10 + (command[i] - '0');
            i++;
        }
        if(i < command.size()) throw std::invalid_argument("The ID is invalid");
        addPerson(name,ID);
        return;
    }
    if(cm == "ACQUIRE "){
        unsigned int ID = 0;
        while('0'<= command[i] && command[i] <= '9'){
            ID = ID * 10 + (command[i] - '0');;
            i++;
        }
        i++;
        string reg = "";
        while(i < command.size()){
            reg += command[i];
            i++;
        }
        setVehicleOwner(ID,Registration(reg));
        return;
    }
    if(cm == "RELEASE "){
        unsigned int ID = 0;
        while('0'<= command[i] && command[i] <= '9'){
            ID = ID * 10 + (command[i] - '0');;
            i++;
        }
        i++;
        string reg = "";
        while(i < command.size()){
            reg += command[i];
            i++;
        }
        releaseVehicleOwner(ID,Registration(reg));
        return;
    }
    if(cm == "REMOVE "){
        if('0'<=command[i] && command[i] <= '9'){
            unsigned int ID = 0;
            while('0'<= command[i] && command[i] <= '9'){
                ID = ID * 10 + (command[i] - '0');;
                i++;
            }
            if(!remove(ID)) std::cout<<"There is no person with ID= "<<ID<<"\n";
        }
        else{
            string reg = "";
            while(i < command.size()){
                reg += command[i];
                i++;
            }
            if(!remove(Registration(reg))) std::cout<<"There is no car with REGISTRATION= "<<reg<<"\n";
        }
        return;
    }
    if(cm == "SAVE ") {
        string path = "";
        while(i < command.size()){
            path += command[i];
            i++;
        }
        save(path);
        return;
    }
    if(cm == "SHOW "){
        string obj = "";
        bool isID = true;
        while(i < command.size()){
            obj += command[i];
            if(!('0'<=command[i] && command[i] <= '9')) isID = false;
            i++;
        }
        if(isID){
            unsigned int ID = 0;
            int j = 0;
            while(j < obj.size()){
                ID = ID * 10 + (obj[j] - '0');;
                j++;
            }
            showPersonbyID(ID);
            return;
        }
        if(obj == "PEOPLE") {showPeople(); return;}
        if(obj == "VEHICLES") {showVehicles(); return;}
        if(Registration::checkReg(obj)) {showVehicle(obj); return;}


    }
}

void Command::save(const string &path) {
    if(access(path.c_str(), F_OK) != -1){
        std::cout<<"Are you sure you want to safe here\n";
        std::cout<<"Enter Y / N: ";
        std::string input;
        do {
            std::getline(std::cin,input);
        } while (input!="Y" && input!="N");
        if(input == "N") return;
    }
    std::ofstream file;
    file.open(path,std::ios::out);
    for(Person& p : m_person) {
        file <<"PERSON : "<<p.getName()<<"; "<<p.getID()<<"\n";
    }
    for(Vehicle& v : m_vehicle) {
        file <<"VEHICLE: "<<v.getReg().getString() << "; " << v.getDesc() <<"; ";
        if(v.getOwner()) file<<v.getOwner()->getID()<<"\n";
        else file<<"NONE\n";
    }
    file.close();
}

void Command::readLine(const string &line) {
    int it = 0;
    string obj = "";
    while (it < 8) obj = obj + line[it++];
    it++;
    if (obj == "PERSON :") {
        string name = "";
        while (line[it] != ';') {
            name += line[it];
            it++;
        }
        it+=2;

        unsigned int ID = 0;
        while ('0' <= line[it] && line[it] <= '9') {
            ID = ID * 10 + (line[it] - '0');
            it++;
        }
        addPerson(name,ID);
    }
    else{
        string reg = "";
        while (line[it] != ';') {
            reg += line[it];
            it++;
        }
        it+=2;
        string desc = "";
        while (line[it] != ';') {
            desc += line[it];
            it++;
        }
        it+=2;
        Registration REG(reg);
        addVehicle(REG,desc);
        if('0'<=line[it] && line[it]<='9'){
            unsigned int ID = 0;
            while ('0' <= line[it] && line[it] <= '9') {
                ID = ID * 10 + (line[it] - '0');
                it++;
            }
            setVehicleOwner(ID,REG);
        }
    }
}




