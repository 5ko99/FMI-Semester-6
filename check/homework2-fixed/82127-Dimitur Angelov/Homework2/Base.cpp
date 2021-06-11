
#include "Base.h"
#include <iostream>
#include <fstream>
#include <cmath>


Base::Base(){
    this->persons.resize(0);
    this->vehicles.resize(0);
    this->links.resize(0);
}

std::vector<Vehicle> Base::getV(){
    return this->vehicles;
}

std::vector<Person> Base::getP(){
    return this->persons;
}

std::vector<Link> Base::getL(){
    return this->links;
}

bool Base::existReg(Registration r){
    std::vector<Vehicle> c;
    c=this->vehicles;
    for(int i=0;i<(this->vehicles).size();i++){
        if(c[i].getRegVehStr()==r.getReg()){
            return false;
        }

    }
    return true;

}

bool Base::existVeh(Vehicle v){
    return this->existReg(v.getRegVeh());
}

bool Base::existPer(Person p){
    std::vector<Person> c;
    c=this->persons;
    for(int i=0;i<(this->persons).size();i++){
        if(c[i].getId()==p.getId()){
            return false;
        }

    }
    return true;
}

void Base::VEHICLE (Registration reg,std::string descr){
    Person p0;
    Vehicle a(reg,descr,p0);
    if(this->existVeh(a)){
        this->vehicles.push_back(a);

    }
    else{std::cout<<"There is a vehicle with the same registration"<<"\n";}
}


void Base::PERSON (std::string name, unsigned int id){
    Person p(name,id);
    if(this->existPer(p)){
        this->persons.push_back(p);
    }
    else{std::cout<<"There is a person with the same Id"<<"\n";}
}


void Base::ACQUIRE (unsigned id, Registration reg){
    bool flag=0;
    for(int i=0;i<this->persons.size();i++){
        if(this->persons[i].getId()==id){
            for(int j=0;j<this->vehicles.size();j++){
                if(this->vehicles[j].getRegVehStr()==reg.getReg()){
                    Link l(this->vehicles[j],this->persons[i]);
                    this->links.push_back(l);
                    flag=1;

                    this->persons[i].getRegs().push_back(this->vehicles[j].getRegVeh());
                    for(int h=0;h<this->vehicles[j].getPerVeh().getRegs().size();h++){
                        if(this->vehicles[j].getPerVeh().getRegs()[h].getReg()==reg.getReg()){
                            std::swap(this->vehicles[j].getPerVeh().getRegs()[h],this->vehicles[j].getPerVeh().getRegs()[this->vehicles[j].getPerVeh().getRegs().size()-1]);
                            this->links.resize(links.size()-1);
                        }
                    }


                }

            }


            break;
        }
    }
    if(flag==0){std::cout<<"There is not a person or a vehicle in the database"<<"\n";}

}


void Base::RELEASE (unsigned id, Registration reg){
    bool flag=0;
    for(int i=0;i<this->links.size();i++){
            if(this->links[i].getPerLink().getId()==id&&this->links[i].getVehLink().getRegVehStr()==reg.getReg()){

                flag=1;
                std::swap(this->links[i],this->links[this->links.size()-1]);
                this->links.resize(links.size()-1);

                for(int j=0;j<this->persons.size();j++){
                    if(this->persons[j].getId()==id){
                        for(int f=0;f<this->persons[j].getRegs().size();f++){
                            if(this->persons[j].getRegs()[f].getReg()==reg.getReg()){
                                std::swap(this->persons[j].getRegs()[f],this->persons[j].getRegs()[this->persons[j].getRegs().size()-1]);
                                this->persons[j].getRegs().resize(this->persons[j].getRegs().size()-1);
                                break;
                            }
                        }
                        break;
                    }
                }

                for(int j=0;j<this->vehicles.size();j++){
                    if(this->vehicles[j].getRegVehStr()==reg.getReg()){

                        this->vehicles[j].getPerVeh().getId()=0;
                        this->vehicles[j].getPerVeh().getName()="No car";
                        this->vehicles[j].getPerVeh().getRegs().resize(0);
                    }
                }

                break;
            }

        }

    if(flag==0){std::cout<<"There is not a link between this person and vehicle in the database"<<"\n";}
}

void Base::REMOVE_VEH (std::string s){
    bool flag=0;
    for(int i=0;i<this->vehicles.size();i++){
           if(this->vehicles[i].getRegVehStr()==s){
                flag=1;
                this->RELEASE(this->vehicles[i].getPerVeh().getId(),this->vehicles[i].getRegVeh());
                std::swap(this->vehicles[i],this->vehicles[this->vehicles.size()-1]);
                this->vehicles.resize(this->vehicles.size()-1);
                break;
           }
        }

    if(flag==0){std::cout<<"There is not such a vehicle in the database"<<"\n";}
}

void Base::REMOVE_PER (unsigned int a){
    bool flag=0;
    for(int i=0;i<this->persons.size();i++){
           if(this->persons[i].getId()==a){
                for(int j=0;j<this->persons[i].getRegs().size();j++){
                    this->RELEASE(this->persons[i].getId(),this->persons[i].getRegs()[j]);
                }
                flag=1;
                std::swap(this->persons[i],this->persons[this->persons.size()-1]);
                this->persons.resize(this->persons.size()-1);
                break;
           }
        }

    if(flag==0){std::cout<<"There is not such a person in the database"<<"\n";}
}

void Base::SAVE (std::string s){
    std::ofstream oFile(s);
    for(int i=0;i<this->persons.size();i++){
        oFile<<"Person "<<this->persons[i].getName()<<"-"<<this->persons[i].getId()<<"\n";
    }
    for(int i=0;i<this->vehicles.size();i++){
        oFile<<"Vehicle "<<this->vehicles[i].getRegVehStr()<<" "<<this->vehicles[i].getDescr()<<"\n";
    }
    for(int i=0;i<this->links.size();i++){
        oFile<<"Link "<<this->links[i].getPerLink().getId()<<" "<<this->links[i].getVehLink().getRegVehStr()<<"\n";
    }
    oFile.close();
}

Base::Base(std::string file){

    Person p0;
    std::ifstream iFile(file,std::ios_base::in);
    if(!iFile){
        std::cout<<"File faild to open"<<"\n";
    }
    while(iFile.eof()){
        std::string s;
        iFile>>s;
        if(s=="PERSON"){
            char ime[100];
            iFile.getline(ime,100,'-');
            std::string str=ime;
            char id1[100];
            iFile.getline(id1,100);
            std::string id=id1;
            unsigned int a;
                for(int i=0;i<id.size();i++){
                        if((int)id[i]>=48&&(int)id[i]<=57){
                    a=a+((int)id[i]-48)*pow(10,id.size()-1-i);
                }
                else{break;}
                }
                Person p(str,a);
                this->persons.push_back(p);


        }

        if(s=="VEHICLE"){
            std::string reg;
            char desc[100];
            iFile>>reg;
            iFile.getline(desc,100);
            std::string d=desc;
            Registration r(reg);
            Person p0;
            Vehicle v(r,d,p0);
            this->vehicles.push_back(v);

        }

        if(s=="LINK"){
            std::string id;
            std::string reg;
            iFile>>id;
            unsigned int a;
                for(int i=0;i<id.size();i++){
                        if((int)id[i]>=48&&(int)id[i]<=57){
                    a=a+((int)id[i]-48)*pow(10,id.size()-1-i);
                }

                else{break;}
                }
                int memp,memv;
             for(int i=0;i<this->getP().size();i++){
                if(this->persons[i].getId()==a){
                    memp=i;
                }
             }
             for(int i=0;i<this->getV().size();i++){
                if(this->vehicles[i].getRegVehStr()==reg){
                    memv=i;
                }
             }
               Link l(this->vehicles[memv],this->persons[memp]);
                this->links.push_back(l);



        }

        if(s!="PERSON"&&s!="VEHICLE"&&s!="LINK"){
            char t[50];
            iFile.getline(t,50);
        }

    }


}




void Base::SHOW_PER (){
    for(int i=0;i<this->persons.size();i++){
            std::cout<<this->persons[i].getName()<<"-"<<this->persons[i].getId()<<"\n"<<"Cars:"<<"\n";
        for(int j=0;j<this->persons[i].getRegs().size();j++){
            std::cout<<this->persons[i].getRegs()[j].getReg()<<"\n";
        }
    }
}


void Base::SHOW_VEH (){
    for(int i=0;i<this->vehicles.size();i++){
            if(this->vehicles[i].getPerVeh().getName()=="No car"){std::cout<<this->vehicles[i].getRegVehStr()<<"-"<<this->vehicles[i].getDescr()<<"-"<<"No one has this car"<<"\n";}
            else{;
        std::cout<<this->vehicles[i].getRegVehStr()<<" - "<<this->vehicles[i].getDescr()<<" - "<<this->vehicles[i].getPerVeh().getName()<<"-"<<this->vehicles[i].getPerVeh().getId()<<"\n";
    }
    }
}

void Base::SHOW_IDV(std::string s){
    bool f=0;
    for(int i=0;i<this->vehicles.size();i++){
        if(this->vehicles[i].getRegVehStr()==s){f=1;
            if(this->vehicles[i].getPerVeh().getName()=="No car"){std::cout<<this->vehicles[i].getRegVehStr()<<" - "<<this->vehicles[i].getDescr()<<" - "<<"No one has this car"<<"\n";}
            else{
        std::cout<<this->vehicles[i].getRegVehStr()<<" - "<<this->vehicles[i].getDescr()<<" - "<<this->vehicles[i].getPerVeh().getName()<<"-"<<this->vehicles[i].getPerVeh().getId()<<"\n";
    }
        }
    }
    if(f==0){std::cout<<"Missing or invalid ID"<<"\n";}
}

void Base::SHOW_IDP (unsigned int a){
    bool f=0;
    for(int i=0;i<this->persons.size();i++){
        if(this->persons[i].getId()==a){f=1;
            std::cout<<this->persons[i].getName()<<"-"<<this->persons[i].getId()<<"\n"<<"Cars:"<<"\n";
        for(int j=0;j<this->persons[i].getRegs().size();j++){
            std::cout<<this->persons[i].getRegs()[j].getReg()<<"\n";
        }
        }

    }
    if(f==0){std::cout<<"Missing or invalid ID"<<"\n";}
}

