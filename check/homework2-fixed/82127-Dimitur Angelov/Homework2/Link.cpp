
#include "Link.h"


Link::Link(Vehicle veh,Person p){
    this->veh=veh;
    this->p=p;
}

Link::Link(){


}

Vehicle& Link::getVehLink(){
    return this->veh;
}

Person& Link::getPerLink(){
    return this->p;
}
