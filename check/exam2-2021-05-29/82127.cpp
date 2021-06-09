//
// �� "��. ������� ��������"
// �������� �� ���������� � �����������
// ���� �������-����������� ������������ 2020/21
// ��������� 2
//
// ���: ������� ��������� �������
// ��: 82127
// �����������: ��������� �����
// ����:1
// ��������������� �����:1
// ���, � ����� �� ������� �� �����������: 29.05.2021
// ������� ��� �� �����������: 9:00
// ��� ���������� ����������: MinG
//

// (������ �� �������� ���� �������� ���� ���� �� ���������)
// ����� ��-���� � ���������� �� Visual C++.
// ��� ���������� ���� ����������, ������ �� �� ��������.
// ��� ���� strlen, strcmp � �.�. �� ���������� ���� deprecated,
// ����� ��� �����������:
//
// * �� ���������� ����������� ������ �� ���� �������
//   (strlen_s, strcmp_s � �.�.). � ���� ������ ������ ��
//   �������� �������� ��-���� #define ���������.
//
// * �� ���������� _CRT_SECURE_NO_WARNINGS ����� ��
//   �������� ����������� header ������� �� ������������
//   ����������.
//
#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


class comand{

    char* cm;
public:
    comand(char* str){
         strcpy(this->cm,str);
     }

     std::size_t size() const{

         std::size_t br=0;
         bool f=1;

         for(int i=0;i<sizeof(this->cm);i++){
            if(cm[i]==' '){
                f=1;
            }
            else{
                if(f==1){
                    br++;
                    f=0;
                }

            }
         }

     return br;
     }

     char* operator[](std::size_t t){
        char* s;
        if(t>=this->size()){
            throw std::invalid_argument("Invalid argument");
        }

        std::size_t br=0;
         bool f=1;

         for(int i=0;i<sizeof(this->cm);i++){
            if(cm[i]==' '){
                f=1;
            }
            else{
                if(f==1){
                    br++;
                    if(t==br-1){
                        int j=0;
                        while(cm[i]!=' '&&cm[i]!='\0'){
                             s[j]=cm[i];
                        j++;
                        }
                        break;
                    }
                    f=0;
                }

            }
         }

         return s;


    }
};

class editor:public comand{



};

class processor:public comand{
    bool is_valid(){
    if(this->cm[0]=="EDIT"||this->cm[0]=="SHOW"||this->cm[0]=="SIZE"){
        return true;
    }
    else{
        return false;
    }
    }

    void execute(){
        editor e(this->cm[0]);
        if(this->cm[0]=="EDIT"){
        e.EDIT();
    }
    if(this->cm[0]=="SHOW"){
        e.SHOW();
    }
    if(this->cm[0]=="SIZE"){
        e.SIZE();
    }

    }
};

int main(int argc,char** argv)
{
    try{
    char* f=argv[1];
    editor f;
    }
    catch{std::cout<<"Invalid argument. Program terminated"<<"\n"; return 0;}

    char* c;
        std::cin.getline(c);
    while(c!="EXIT"){
        std::cin.getline(c);
    comand com(c);
    processor p(com);
    }


	return 0;
}
