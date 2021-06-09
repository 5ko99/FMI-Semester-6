// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име:Валери Добрев
// ФН:45807
// Специалност: Информатика
// Курс:1
// Административна група: 5
// Ден, в който се явявате на контролното: 29.05.2021 
// Начален час на контролното: 09:00
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include<vector>

class Command{
    std::string command;
    std::vector<std::string> args;

public:
    Command(const std::string& line){
        //Didn't manage to create the string stream so it is commented so that the program caould be compiled
        
        // std::stringstream ss(line);
        
        // getline(ss, command, ' ');
        // std::string arg;
        
        // while(getline(ss, arg, ' ')){
        //     args.push_back(arg);
        // }

    }
    ~Command(){
        args.clear();
    }

    Command(const Command& other) : command(other.command), args(other.args){
    }

    Command& operator=(const Command& other){
        if(this==&other){
            return *this;
        }


        this->command = other.command;
        this->args = other.args;
    }

    std::size_t size() const{ return this->args.size();}

    std::string& operator[](const std::size_t index){
        if(index>this->size()){
            throw std::invalid_argument("Index out of range");
        }

        return args[index];
    }
    std::string& getCommand(){return this->command;}
};


class Editor{
    std::fstream stream;
    std::size_t filesize;

public:
    Editor(){}
    Editor(const std::string& path){ 
        this->open(path);
    }
    Editor(const Editor& other) = delete;

    Editor& operator=(const Editor& other) = delete;

    void open(const std::string& path){
        if(!stream.is_open()){
            this->stream.open(path, std::ios::binary | std::ios::in | std::ios::out);
            if(!stream.is_open()){
                throw std::invalid_argument("Couldn't open the file specified!");
            }

            this->stream.seekg(0,std::ios::beg);
            size_t beg = this->stream.tellg();

            this->stream.seekg(0, std::ios::end);
            size_t end = this->stream.tellg();
            this->filesize = end - beg;
        }
    }

    int edit(std::size_t offset, std::uint8_t value){
        if(!stream.is_open()){
            throw std::invalid_argument("No file opened!");
        }
        if(offset > filesize){
            throw std::invalid_argument("ERROR: file size is " + std::to_string(filesize) + ".");
        }

        try{
            stream.seekg(offset);
            stream.write((char*) &value, sizeof(std::uint8_t));
        }catch(std::exception& e){
            return -1;
        }
        return 1;
    }
    void close(){
        if(this->stream.is_open()){
            this->stream.close();
        }
    }

    size_t size() const{ return this->filesize;}
    ~Editor(){
        this->close();
    }
};

class Processor{

    Editor* editor;
public:
    Processor(Editor& editor) {
        this->editor = &editor;
    };
    Processor(Processor& other) {
        this->editor = other.editor;
    };

    ~Processor(){
        editor->close();
        editor = nullptr;
    }
    Processor& operator=(const Processor& other){
        if(this == &other){
            return *this;
        }
        this->editor = other.editor;
    }
    bool is_valid(Command& command)const{ 
        std::string com = command.getCommand();
        return ((com == "EXIT" || com == "SIZE") && command.size() == 0) ||
                ((com == "EDIT" || com == "SHOW") && command.size() == 2);
    }

    int execute(Command& command) const {
        try{
            if(!is_valid(command)){
                return 1;
            }
            if(command.getCommand() == "EXIT"){
                throw std::invalid_argument("exit");
            }else if(command.getCommand()=="SIZE"){
                std::cout<< editor->size();
            }else if(command.getCommand() == "EDIT"){
                if(editor->edit(std::stoi(command[0]), std::stoi(command[1]))==1){
                    std::cout<<"OK"<<std::endl;
                }else{
                    std::cout<<"FAIL"<<std::endl;
                }
            }else{
                //TODO reading
            }
        }catch(std::exception& e){
            std::cout<<e.what()<<std::endl;
        }
        return 0;
    }
};


int main(int argc, char* argv[])
{
    Editor editor;
    if(argc<2){
        std::cout<< "Please enter file name when running the program!"<<std::endl;
    }else{
        try{
                editor.open(std::string(argv[1]));
        }catch(std::exception& e){
            std::cerr<< e.what() << std::endl;
            return -1;
        }
    }
    Processor p(editor);
    std::string s;
    while(getline(std::cin, s)){
        Command c(s);
        
        if(p.execute(c)==1)break;
        
    }

	return 0;
}