#include "Garage.h"
#include <new>
#include <cstring>
#include <stdexcept>
#include <cassert>


Garage::Garage(){
    this->space=0;
    this->freespace=0;
    this->vehiclecount=0;
    this->veh=new Vehicle*[0];
}

Garage::Garage(std::size_t space){
    this->space=0;
    this->freespace=space;
    this->vehiclecount=0;
    this->veh=new Vehicle*[0];
}

Garage& Garage::operator=(const Garage& other){
    this->space=other.space;
    this->freespace=other.freespace;
    this->vehiclecount=other.vehiclecount;
    for(size_t i=0;i<other.vehiclecount;i++){

        this->veh[i]=other.veh[i];
    }
    return *this;
}

Garage::~Garage(){
    delete[] this->veh;
}

void Garage::insert(Vehicle& v){


    if(this->freespace<v.space()){throw std::exception();}

    for(std::size_t i=0;i<this->vehiclecount;i++){

        if((*this->veh[i]).registration()==v.registration()){throw std::exception();}
    }

    Vehicle** a = new Vehicle* [this->vehiclecount+1];

    for(size_t i=0;i<vehiclecount;i++){

        a[i]=this->veh[i];

    }

    a[vehiclecount]=&v;
    this->space=this->space+v.space();
    this->freespace=this->freespace-v.space();
    this->vehiclecount=this->vehiclecount+1;

    delete[] this->veh;
    for(size_t i=0;i<vehiclecount;i++){
        this->veh[i]=a[i];
    }
}

void Garage::erase(const char* registration){
    for(std::size_t i=0;i<this->vehiclecount;i++){
        if(registration==(*this->veh[i]).registration()){

            Vehicle** a = new Vehicle* [this->vehiclecount-1];

            a[i]=veh[vehiclecount-1];

            for(size_t j=0;j<vehiclecount-1;j++){
                if(j==i){continue;}
                a[j]=this->veh[j];

            }
            this->space=this->space-(*this->veh[i]).space();
            this->freespace=this->freespace+(*this->veh[i]).space();
            this->vehiclecount=this->vehiclecount-1;

            delete[] this->veh;

            for(size_t j=0;j<vehiclecount;j++){

                this->veh[j]=a[j];
            }

            break;
        }
    }
}

const Vehicle& Garage::at(std::size_t pos) const{

        if(pos==0||pos>=this->vehiclecount) {
        throw std::out_of_range("Wrong index");
        }
        return *this->veh[pos-1];

}

const Vehicle& Garage::operator[](std::size_t pos) const{

    assert(pos>0&&pos<=this->vehiclecount);
    return *this->veh[pos-1];

}

bool Garage::empty() const{

    if(this->vehiclecount==0){
        return true;
    }
    else {return false;}

}

std::size_t Garage::size() const{

    return this->vehiclecount;

}

void Garage::clear(){

    delete[] this->veh;
    this->vehiclecount=0;
    this->veh=new Vehicle*[0];

}

const Vehicle* Garage::find(const char* registration) const{

        for(size_t i=0;i<this->vehiclecount;i++){
            if(strcmp(registration,(*this->veh[i]).registration())==0){
                return veh[i];
            }
        }

        return nullptr;

}


