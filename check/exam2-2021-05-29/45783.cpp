//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
//
// Име: Веселин Христов Пенев
// ФН: 45783
// Специалност: Информатика
// Курс: 1
// Административна група: 3
// Ден, в който се явявате на контролното: 29.05
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//


#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class command{
private:
    vector<string> commandArguments;

    vector<string>& breakCommand(const string& str){
        vector<string> cl;
        string currentStr = "";
        for(size_t  i = 0; i < str.size(); i++){
            if(str[i] == ' '){
                if(currentStr != ""){
                    cl.push_back(currentStr);
                    currentStr = "";
                    continue;
                }
                currentStr += str[i];
            }
        }
        return cl;
    }

public:
    command(const string& str){
        commandArguments = breakCommand(str);
    }
    size_t size() const{
        return commandArguments.size();
    }
    string& operator[](size_t pos){
        if(pos >= size()){
            throw out_of_range("Index out of range");
        }
        return commandArguments[pos];
    }

};

class editor{
private:
    size_t size_;
    fstream currentStream;
    size_t getStreamSize(ifstream& in){
        size_t size = 0;
        while(!in.eof()){
            char re;
            in.read((char*) &re, sizeof(char));
            size++;
        }
        return size;
    }
public:

    editor(){

    }

    editor(const string& path){
        open(path);
    }

    void open(const string& path){
        if(path == ""){
            throw invalid_argument("File path was not entered");
        }
        currentStream.open(path, ios::binary);
        if(!currentStream.is_open()){
            throw invalid_argument("File was not found");
        }
    }

    void close(){
        if(!currentStream.is_open()){
            currentStream.close();
        }
    }

    void edit(std::size_t offset, std::uint8_t value){
        currentStream.seekp(offset);


    }

    void display(std::ostream& out, std::size_t offset, std::size_t limit){

    }

    size_t size(){
        return size_;
    }

};

class processor{
private:
    editor currentEditor;

    size_t convertStringToUInt(string& str){
        size_t num = 0;
        for(size_t  i = 0; i < str.size(); i++){
            num*= 10;
            if('0' < str[i] || str[i] > '9'){
                throw invalid_argument("given string was not a number");
            }
            num += (str[i] - '0');
        }
    }

public:
    processor(){

    }
    void open(const string& str){
        currentEditor.open(str);
    }
    bool is_valid(command& command){

        if(command.size() == 0){
            return false;
        }

        if(command[0] == "SIZE"){
            if(command.size() != 1){
                return false;
            }
        }

        if(command[0] == "EDIT"){
            if(command.size() != 3){
                return false;
            }
        }

        if(command[0] == "SHOW"){
            if(command.size() != 3){
                return false;
            }
        }

        return true;

    }

    void execute(command& exeCommand){
        if(exeCommand[0] == "SIZE"){
            cout << currentEditor.size();
        }
        if(exeCommand[0] == "EDIT"){
            try{
                size_t c1 = convertStringToUInt(exeCommand[1]);
                size_t c2 = convertStringToUInt(exeCommand[2]);
                currentEditor.edit(c1, c2);
            }catch(invalid_argument& e){
                cout << "Edit was not successful. Reason: " << e.what();
            }
        }
        if(exeCommand[0] == "SHOW"){
            try{
                size_t c1 = convertStringToUInt(exeCommand[1]);
                size_t c2 = convertStringToUInt(exeCommand[2]);
                currentEditor.display(cout, c1, c2);
            }catch(invalid_argument& e){
                cout << "Show was not successful. Reason: " << e.what();
            }
        }
    }

};

int main(int argv, char** argc)
{
    string input;

    getline(cin, input);

    processor proc;

    try{
        proc.open(input);
    }catch(invalid_argument& e){
        cout << "Open was not successful. Reason: " << e.what();
    }

    getline(cin, input);

    while(input != "EXIT"){

        command currentCommand(input);

        if(!proc.is_valid(currentCommand)){
           // proc.execute(input);
        }else{
            cout << "Invalid count of command arguments";
        }

        getline(cin, input);

    }

	return 0;
}
