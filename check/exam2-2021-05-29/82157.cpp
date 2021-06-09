// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Адриян Ибовски
// ФН: 82157
// Специалност: КН
// Курс: 1
// Административна група: 2
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 9.00
// Кой компилатор използвате: GCC
//
//#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::size_t;
using std::ifstream;
using std::ofstream;

class Command{
private:
    vector<string> args;
    size_t size = 0;
public:
    Command(const string& cm){
        string curr;
        size_t i = 0, j = cm.size();
        while(i < j){
            curr = "";
            while(cm[i] != ' ' && i < j) curr += cm[i++];
            args.push_back(curr);
            size++;
            i++;
        }
    }
    ~Command(){
        args.clear();
        size = 0;
    }
    size_t getSize() const{
        return size;
    }
    string operator[](size_t pos) const{
        if(pos >= size) return "";
        return args[pos];
    }

};

class Editor{
private:
    std::fstream File;
    size_t size = 0;

    size_t findSizeofFile(){
      size_t cur = File.tellp();
      File.seekp(0,std::ios::end);
      size_t sz = File.tellp();
      File.seekp(cur,std::ios::beg);
      return sz;
  }
public:
    Editor() = default;
    Editor(const string& path){
        open(path);
    }

    void open(const string& path){
      File.open(path, std::ios::ate | std::ios::binary | std::ios::out | std::ios::in);
      size = findSizeofFile();
      if(!File.good()) throw std::invalid_argument("Could not open the file");
  }
  void close(){
      File.close();
  }
  size_t getSize() const{
      return size;
  }
  void edit(size_t offset, uint8_t value){
      if(offset >= size) throw std::invalid_argument("Offset is out of range in edit function");
      File.seekp(offset,std::ios::beg);
      File.write((const char*)&value, sizeof(uint8_t));
      if(!File.good()) throw std::exception();
  }
  void display(std::ostream& out, size_t offset, size_t limit){
      if(offset > size) throw std::invalid_argument("Offset is out of range in display function");
    //cout<<File.tellg()<<endl;
      File.seekg(offset,std::ios::beg);
      char byte;
      File.read((char*)&byte,sizeof(uint8_t));
      std::cout << std::setfill('0') << std::setw(8) << std::hex << (unsigned int)byte;
      for(size_t i = offset; i < std::min(offset+limit,this->size); i++){
          File.read((char*)&byte,sizeof(uint8_t));
          if(((i-offset+1)%16 == 0)) cout<<endl;
          std::cout <<" "<< std::setfill('0') << std::setw(2) << std::hex << (unsigned int)byte;

      }
     cout<<endl;
        File.seekg(0,std::ios::beg);
    }
  bool isOpen(){
        return File.is_open();
    }

};


class Processor{
public:
    bool is_valid(const Command& cm){
        for(int i = 0; i < cm.getSize(); i++){
            if(cm[i] == "EXIT") continue;
            if(cm[i] == "SIZE") continue;
            if(cm[i] == "EDIT" || cm[i] == "SHOW"){
                for(int j = i+1; j <= i + 2; j++){
                    int k = 0;
                    while('0'<=cm[j][k] && cm[j][k]<='9' && k<cm[j].size()) k++;
                    if(k != cm[j].size()) return false;
                }
                i+=2;
                continue;
            }
            return false;
        }
        return true;
    }
    void execute(const Command& cm, Editor* ed){
        for(int i = 0; i < cm.getSize(); i++){
            if(cm[i] == "EXIT") {ed->close(); return;}
            if(cm[i] == "SIZE") cout<<ed->getSize()<<" byte(s)\n";
            if(cm[i] == "EDIT" || cm[i] == "SHOW"){
                int k = 0;
                int j =i+1;
                size_t offset = 0;
                while('0'<=cm[j][k] && cm[j][k]<='9' && k<cm[j].size()) {
                    offset = offset * 10 + (cm[j][k]-'0');
                    k++;
                }
                j++;
                if(cm[i] == "EDIT"){
                    uint8_t value = 0;
                    k = 0;
                    while('0'<=cm[j][k] && cm[j][k]<='9' && k<cm[j].size()) {
                        value = value * 10 + (cm[j][k]-'0');
                        k++;
                    }

                    ed->edit(offset,value);
                }
                else{
                    size_t limit = 0;
                    k = 0;
                    while('0'<=cm[j][k] && cm[j][k]<='9' && k<cm[j].size()) {
                        limit = limit * 10 + (cm[j][k]-'0');
                        k++;
                    }
                   // cout<<ed->isOpen()<<endl;
                    ed->display(cout,offset,limit);
                }
                i+=2;
            }
        }
    }
};


int main(int argc, char* argv[])
{
    bool f = true;
    Processor* pr;
    Editor ed;
    try{
        ed.open(argv[1]);
    }catch(std::exception& e){
        cout<<e.what()<<endl;
        return 1;
    }
    while(f){
        string command;
        std::getline(cin,command);
        Command cm(command);
        if(!pr->is_valid(cm)) {cout<<"Invalid Command"<<endl; continue;}
        pr->execute(cm,&ed);
        if(!ed.isOpen()) f = false;
    }

    return 0;
}