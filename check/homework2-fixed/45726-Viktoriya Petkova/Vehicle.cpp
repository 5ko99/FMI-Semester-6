#include "Vehicle.h"

Vehicle::Vehicle(Registration reg_num, string description, Person* owner):
	reg_num(reg_num), description(description) , owner(owner)
{
}

ostream& operator<<(ostream& ofs, const Vehicle& r) {

	return ofs << r.reg_num << '/'
		<< r.description ;
}


