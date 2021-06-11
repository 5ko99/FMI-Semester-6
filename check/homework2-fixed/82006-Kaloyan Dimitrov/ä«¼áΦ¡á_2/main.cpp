#include <iostream>
#include <fstream>
#include <algorithm>
//#include "Registration.h"
#include "Person.h"
#include "Vehicle.h"
bool case_insensitive_match(std::string s1, std::string s2);
bool id_check(std::string& what);
bool registration_check(std::string& what);
void remove_person(int &id);
void remove_vehicle(std::string& reg);
Person* find_person(int& id);
Vehicle* find_vehicle(std::string& reg);
int vehicles_without_owner();
void read_from_file();
void write_to_file();
void menu();




int main() {
    std::string choice;
    std::cout<<"Would you like to start with clear file. type:..(yes/no) ";
    while (!(case_insensitive_match(choice,"YES") || case_insensitive_match(choice,"NO"))) {
        std::cin >> choice;
        if (case_insensitive_match(choice, "Yes")) {
            read_from_file();
            menu();
            write_to_file();
        } else if (case_insensitive_match(choice, "NO")) {
            menu();
            write_to_file();
        }else{
            std::cout<<"invalid input";
        }
    }
//
//    read_from_file();
//    menu();
//    write_to_file();

    return 0;
}





bool id_check(std::string& what){
    for(int i=0;i<what.size();i++)
    {
        if(what[i]<'1' || what[i]>'9')return false;
    }
    return true;
}
bool registration_check(std::string& what){
    if(what.size()<7 || what.size()>8)return false;
    if(what.size()==7)
    {
        bool valid=false;
        for(int i=0;i<3;i++) {
            if(i==0){
                if(what[0]>='A' && what[0]<='Z')valid=true;
                else break;
            }
            if(i==1){
                if((what[1]>='0' && what[1]<='9')  &&
                   (what[2]>='0' && what[2]<='9') &&
                   (what[3]>='0' && what[3]<='9') &&
                   (what[4]>='0' && what[4]<='9')) valid=true;
                else {
                    valid=false;
                    break;
                }
            }
            if(i==3)
            {
                if((what[5]>='A' && what[5]<='Z') && (what[6]>='A' && what[6]<='Z'))valid=true;
                else {
                    valid = false;
                    break;
                }
            }
        }
        if(valid)return true;
        else return false;
    }
    if (what.size()==8){
        bool valid=false;
        for(int i=0;i<3;i++) {
            if(i==0){
                if((what[0]>='A' && what[0]<='Z') && (what[1]>='A' && what[1]<='Z'))valid=true;
                else break;
            }
            if(i==1){
                if((what[2]>='0' && what[2]<='9')  &&
                   (what[3]>='0' && what[3]<='9') &&
                   (what[4]>='0' && what[4]<='9') &&
                   (what[5]>='0' && what[5]<='9')) valid=true;
                else {
                    valid=false;
                    break;
                }
            }
            if(i==2)
            {
                if((what[6]>='A' && what[6]<='Z') && (what[7]>='A' && what[7]<='Z'))valid=true;
                else {
                    valid = false;
                    break;
                }
            }
        }
        if(valid)return true;
        else return false;
    }

}
void remove_person(int &id){
    for(int i=0;i<allPersons.size();i++){
        if(id==allPersons[i]->get_egn()){
            int vehicles=allPersons[i]->vehicles_size();
            for(int j=0;j<vehicles;j++){
                allPersons[i]->remove_vehicle();
            }
            allPersons.erase(allPersons.begin()+i);
        }
    }
}
void remove_vehicle(std::string& reg){
    for(int i=0;i<allVehicles.size();i++){
        if(reg==allVehicles[i]->get_reg().get_registration()){
            allVehicles[i]->set_owner(nullptr);
            allVehicles.erase(allVehicles.begin()+i);
        }
    }
}
Person* find_person(int& id){
    for (int i=0;i<allPersons.size();i++) {
        if (id == allPersons[i]->get_egn()) {
            return allPersons[i];
        }
    }return nullptr;
}
Vehicle* find_vehicle(std::string& reg){
    for (int j = 0; j < allVehicles.size(); ++j) {
        if (reg == allVehicles[j]->get_reg().get_registration()) {
            return allVehicles[j];
        }
    }return nullptr;
}
int vehicles_without_owner(){
    int counter=0;
    for (int i=0;i<allVehicles.size();i++){
        if(allVehicles[i]->get_owner()== nullptr)counter++;
    }
    return counter;
}
void read_from_file(){
    std::ifstream read("vehicles.txt");
    if(!read.is_open())
    {
        std::cout<<"Error opening a file\n";
    }else{
        int allPersons_size;
        read >> allPersons_size;
        for(int i=0;i<allPersons_size;i++)
        {
            std::string first_name,second_name;
            int egn,vehicles_size;
            read >> first_name >> second_name >> egn >> vehicles_size;
            allPersons.push_back(new Person(first_name+' '+second_name,egn));
            for(int j=0;j<vehicles_size;j++)
            {
                std::string reg,description;
                read >> reg >> description;
                Registration registration(reg);
                allVehicles.push_back(new Vehicle(registration,description));
//                std::cout<<reg<<" "<<description<<"\n";
                allVehicles[allVehicles.size()-1]->set_owner(allPersons[i]);
//                std::cout<<allVehicles[allVehicles.size()-1]->get_reg().get_registration()<<" "<<allVehicles[allVehicles.size()-1]->get_owner()->get_name()<<"\n";
                allPersons[i]->add_vehicle(allVehicles[allVehicles.size()-1]);
            }

        }

        int vehicles_size;
        read >> vehicles_size;
        for(int i=0;i<vehicles_size;i++)
        {
            std::string reg,description;
            read >> reg >> description;
            allVehicles.push_back(new Vehicle(reg,description));
        }
        read.close();
    }
}
void write_to_file()
{
    std::ofstream file("vehicles.txt");
    if (!file.is_open())
    {
        std::cout<<"Error opening a file\n";
    }else
    {

        file << allPersons.size()<<" ";
        for(int i=0;i<allPersons.size();i++)
        {
            file    <<     allPersons[i]->get_name()
                    <<" "<<allPersons[i]->get_egn()
                    <<" "<<allPersons[i]->vehicles_size()<<" ";
            for(int j=0;j<allPersons[i]->vehicles_size();j++)
            {
                file    << allPersons[i]->vehicle_pos(j)->get_reg().get_registration()
                        <<" "<<allPersons[i]->vehicle_pos(j)->get_description()<<" ";
            }
            file << "\n";
        }
        int other_vehicles=vehicles_without_owner();
        file <<other_vehicles<<" ";
        for(int i=0;i<allVehicles.size();i++) {
            if (allVehicles[i]->get_owner()== nullptr){
                file << allVehicles[i]->get_reg().get_registration()
                     << " " << allVehicles[i]->get_description()<< "\n";
            }
        }
    }
    file.close();
}
void menu()
{

    std::string command;
    while(command!="exit")
    {

        std::cout<<"type command: ";
        std::cin>>command;

        if(case_insensitive_match(command,"VEHICLE"))
        {
            try {
                std::string reg, description;
//            std::cout<<"<";
                std::cin >> reg;//std::cout<<"> <";
                Registration registration_(reg);
                for (int i = 0; i < allVehicles.size(); i++) {
                    if (reg == allVehicles[i]->get_reg().get_registration())
                        throw std::out_of_range("Registration already existing");
                }
                std::cin >> description;
                std::cout << std::endl;
                allVehicles.push_back(new Vehicle(reg, description));
            } catch (std::out_of_range&) {
                std::cout<<"Registration already existing\n";
            }
        }
        if(case_insensitive_match(command,"PERSON")){
            try {
                std::string name1, name2;
                int id;
//            std::cout<<"<";
                std::cin >> name1 >> name2;
                std::cout << "> <";
                std::cin >> id;
                std::cout << std::endl;
                for (int i = 0; i < allPersons.size(); i++) {
                    if (id == allPersons[i]->get_egn()) throw std::out_of_range("EGN already existing");
                }
                std::string full_name = name1 + ' ' + name2;
                allPersons.push_back(new Person(full_name, id));
            } catch (std::out_of_range&) {
                std::cout<<"EGN already existing\n";
            }
        }
        if(case_insensitive_match(command,"ACQUIRE")){
            int id;
            std::string reg;
            std::cin>>id>>reg;
            bool flag_person=false;
            bool flag_vehicle=false;
            for (int i=0;i<allPersons.size();i++)
            {
                if(id==allPersons[i]->get_egn()){
                    flag_person=true;
                    for (int j = 0; j < allVehicles.size(); ++j) {
                        if (reg==allVehicles[j]->get_reg().get_registration()){

                            flag_vehicle= true;
                            if(allVehicles[j]->get_owner()== nullptr) {
                                allVehicles[j]->set_owner(allPersons[i]);
                                allPersons[i]->add_vehicle(allVehicles[j]);
                                break;
                            }else{
                                allVehicles[j]->get_owner()->remove_vehicle(allVehicles[j]->get_reg().get_registration());
                                allVehicles[j]->set_owner(allPersons[i]);
                                allPersons[i]->add_vehicle(allVehicles[j]);
                            }
                        }
                    }
                    break;
                }
            }
            if(!flag_person)std::cout<<"could not find person with this id\n";
            else if (!flag_vehicle)std::cout<<"could not find vehicle with this registration\n";
        }
        if(case_insensitive_match(command,"RELEASE")){
            int id;
            std::string reg;
            std::cin>>id>>reg;
            for (int i=0;i<allPersons.size();i++) {
                if (id == allPersons[i]->get_egn()) {
                    allPersons[i]->remove_vehicle(reg);
                }
            }
        }
        if(case_insensitive_match(command,"REMOVE")){
            std::string what;
            std::cin>>what;
            if(id_check(what))
            {
                int id=std::stoi(what);
                for (int i=0;i<allPersons.size();i++)
                {
                    if(id==allPersons[i]->get_egn())
                    {
                        if(allPersons[i]->vehicles_size()>0)
                        {
                            std::string choice;
                            std::cout<<"this person has "<<allPersons[i]->vehicles_size()<<" vehicles. Would you like to delete the person. (type: yes/no):..";
                            std::cin>>choice;std::cout<<"\n";
                            if(case_insensitive_match(choice,"YES"))
                            {
                                remove_person(id);
                            }else if (case_insensitive_match(choice,"NO")){
                                std::cout<<"exiting from operation\n";
                            }
                        }else{
                            remove_person(id);
                        }
                    }
                }
            }else if(registration_check(what)){
                for (int i=0;i<allVehicles.size();i++){
                    if(what==allVehicles[i]->get_reg().get_registration()){
                        if(allVehicles[i]->get_owner()!= nullptr){
                            std::cout<<"this vehicle has owner ["<<allVehicles[i]->get_owner()->get_name()<<"]. Would you like to erase this vehicle. (type: yes/no):..";
                            std::string choice;
                            std::cin>>choice;std::cout<<"\n";
                            if(case_insensitive_match(choice,"YES")){
                                remove_vehicle(what);
                            }else if (case_insensitive_match(choice,"NO")){
                                std::cout<<"exiting from operation\n";
                            }
                        }else{
                            remove_vehicle(what);
                        }
                    }
                }
            }
        }
        if(case_insensitive_match(command,"SHOW"))
        {
            std::string word;
            std::cin>>word;
            if(id_check(word)){
                int id=std::stoi(word);
                for (int i=0;i<allPersons.size();i++){
                    if(id==allPersons[i]->get_egn()){
                        std::cout<<"["<<allPersons[i]->get_name()<<"] ["<<allPersons[i]->get_egn()<<"]\n";
                        int vehiclesSize=allPersons[i]->vehicles_size();
                        if(vehiclesSize>0){
                            std::cout<<"this person has "<<vehiclesSize<<" vehicles:\n";
                            for (int j=0;j<vehiclesSize;j++){
                                std::cout<<j+1<<".["<<allPersons[i]->vehicle_pos(j)->get_reg().get_registration()<<"] ["<<allPersons[i]->vehicle_pos(j)->get_description()<<"]\n";
                            }
                        }
                        break;
                    }
                }
            }else if(registration_check(word)){
                for(int i=0;i<allVehicles.size();i++){
                    if (word==allVehicles[i]->get_reg().get_registration()){
                        std::cout<<"["<<allVehicles[i]->get_reg().get_registration()<<"] ["<<allVehicles[i]->get_description()<<"] ["<< allVehicles[i]->get_owner()->get_name() << "] \n";
                        break;
                    }
                }
            }
            else if(case_insensitive_match(word,"VEHICLES")) {
                for (int i = 0; i < allVehicles.size(); i++)
                    if (allVehicles[i]->get_owner() != nullptr) {
                        std::cout << i + 1 << ". [" << allVehicles[i]->get_reg().get_registration() << "] "
                                  << "[" << allVehicles[i]->get_description() << "] "
                                  << "[" << allVehicles[i]->get_owner()->get_name() << "] \n";
                    } else {
                        std::cout << i + 1 << ". [" << allVehicles[i]->get_reg().get_registration() << "] "
                                  << "[" << allVehicles[i]->get_description() << "] \n";
                    }
            }else if (case_insensitive_match(command,"SAVE")){
                std::string path;
                std::getline(std::cin,path);
//                write_to_file(path);

            }
            else if(case_insensitive_match(word,"PEOPLE")){
                for(int i=0;i<allPersons.size();i++){
                    std::cout<<i+1<<". ["<<allPersons[i]->get_name()<<"] ["<<allPersons[i]->get_egn()<<"] "<<std::endl;
                }
            }
        }

    }

}
bool case_insensitive_match(std::string s1, std::string s2) {
    std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    if(s1.compare(s2) == 0)
        return 1;
    return 0;
}
