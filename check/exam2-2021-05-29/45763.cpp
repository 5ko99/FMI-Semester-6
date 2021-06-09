//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
//
// Име: Ивайло Атанасов
// ФН: 45763
// Специалност: Информатика
// Курс: 1
// Административна група: 2
// Ден, в който се явявате на контролното: 29.5
// Начален час на контролното: 9:00
// Кой компилатор използвате: Clang


#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#include <vector>
#include <iomanip>
#include <cmath>

class Command{
private:
    std::vector<std::string> commandArr;
public:
    Command(std::string rawCommand){
        std::string buffer;
        for(int i=0; i<rawCommand.size(); i++){
            if(rawCommand[i] == ' ' || rawCommand[i] == '\0'){
                if(i!=0)
                    commandArr.push_back(buffer);
                buffer.clear();
                while(rawCommand[i] == ' ' && i<rawCommand.size()) i++;
                i--;
            } else {
                buffer.push_back(rawCommand[i]);
            }
        }
        if(strcmp(buffer.c_str(), ""))
            commandArr.push_back(buffer);
    }
    
    const std::string& operator[](const std::size_t pos) const{
        return commandArr[pos];
    }
    
    std::size_t size() const{
        return commandArr.size();
    }
};


class Editor{
private:
    std::fstream file;
    std::size_t p_size;
public:
    Editor() = default;
    Editor(const char* path, std::ios::openmode mode):file(path, std::ios::binary | std::ios::ate | mode){
        //p_size = file.tellp();
        //file.seekp(std::ios::beg);
    }
    
    void edit(std::size_t offset, std::uint8_t value){
        if(offset > p_size) throw std::invalid_argument("offset reaches out of file");
        file.seekp(offset * sizeof(value));
        file.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }
    
    void display(std::ostream& out, std::size_t offset, std::size_t limit){
        file.seekg(offset);
        
        for(std::size_t i=0; i<limit; i++){
            uint8_t val{};
            file.read((char*)(&val), sizeof(val));
            if(!file) break;
            //out<<(std::size_t)val<<" ";
            out << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)val << " ";
        }
        
    }
    
    void open(const char* path, std::ios::openmode mode){
        file.open(path, mode | std::ios::binary | std::ios::ate);
        //p_size = file.tellp();
        //file.seekp(std::ios::beg);
    }
    
    void close(){
        file.close();
    }
    
    std::size_t size(){
        if(file){
            p_size = file.tellp();
            file.seekp(std::ios::beg);
        }
        return p_size;
    }
    
};


class Processor{
private:
    Editor ed;
    std::string path;
    
    int strToInt(std::string str){
        int res = 0;
        for(int i=0;i<str.size(); i++){
            res += str[i] * pow(10,i);
        }
        return res;
    }
    
public:
    Processor(const char* path){
        this->path = path;
    }
    
    bool isValid(Command& cmd){
        // logic
        return true;
    }
    
    void execute(Command& cmd) try{
        if(!strcmp(cmd[0].c_str(), "SIZE")){
            ed.open(path.c_str(), std::ios::in);
            std::cout<<ed.size();
            ed.close();
        }
        if(!strcmp(cmd[0].c_str(), "EDIT")){
            ed.open(path.c_str(), std::ios::out);
            ed.edit(strToInt(cmd[1]), strToInt(cmd[2]));
            ed.close();
        }
        if(!strcmp(cmd[0].c_str(), "SHOW")){
            ed.open(path.c_str(), std::ios::in);
            ed.display(std::cout, strToInt(cmd[1]), strToInt(cmd[2]));
            ed.close();
        }
    } catch(const std::exception& e){
        std::cout<<e.what()<<std::endl;
    }
    
    Command getNextCmd(){
        std::string buffer;
        getline(std::cin, buffer);
        Command cmd(buffer);
        return cmd;
    }
    
};


int main(int argc, char** args) {
    
    if(argc == 2){
        char* path = args[1];
        
        Processor p(path);
        
        Command cmd = p.getNextCmd();
        while(!strcmp(cmd[0].c_str(), "STOP")){
            
            cmd = p.getNextCmd();
            if(p.isValid(cmd)){
                p.execute(cmd);
            }
            
        }
        
        
        return 0;
    } else {
        std::cout<<"wrong arguments\n";
        return 0;
    }
    
    
    /*
    Editor ed;
    ed.open("asd.bin", std::ios::out);
    ed.edit(0, 77);
    ed.edit(1, 22);
    ed.edit(2, 11);
    ed.edit(3, 89);
    ed.close();
    
    ed.open("asd.bin", std::ios::in);
    ed.display(std::cout, 0, 3);
    std::cout<<"\n";
    ed.display(std::cout, 1, 2);
    ed.close();
    */
   
}
