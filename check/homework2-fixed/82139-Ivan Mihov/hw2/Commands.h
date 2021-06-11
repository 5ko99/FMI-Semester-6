

#ifndef HW2_COMANDS_H
#define HW2_COMANDS_H
# include "Person.h"
# include "Vehicle.h"
# include <string>
# include <vector>
class Commands {
private:
   
    std::vector<Person> person;
    std::vector<Vehicle> vehicles;
public:

    void newVehicle(const Registration&, const std::string&);
    void newPerson(const std::string&, unsigned int);
    void Aquire(unsigned int, const Registration&);
    void Release(unsigned int, const Registration&);
    void remove(unsigned int);
    void remove(const Registration&);
    void Save(const std::string &)const;
    void display(const std::string&)const;
    void display(unsigned int)const;
    Person getPersonAt(unsigned int)const;
    Vehicle getVehicleAt(unsigned int)const;
};

#endif //HW2_COMANDS_H
