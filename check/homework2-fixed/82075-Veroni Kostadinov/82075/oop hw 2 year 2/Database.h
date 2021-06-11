#ifndef DATABASE_HH
#define DATABASE_HH

#include "Vehicle.h"
#include <cmath>
using namespace std;



class Database
{   
    vector<Vehicle*> allVehicles;
    vector<Person*> people; 

    Person* findById (const unsigned int& _id);
    Vehicle* findById (const string& _id);

    void copy (vector<Vehicle*> _allVehicles, vector<Person*> _people);

    bool isStringNumber(string str);
    void deletePersonFromDB(Person* person);
    void deleteVehicleFromDB(Vehicle* vehicle);

    public:
    ~Database();

    bool validateRegNum(string);


    void vehicle_command(const string registration, const string description); 
    void person_command (const string _name, const unsigned int _id);
    void acquire_command (const unsigned int& owner_id, const string& vehicle_id); 
    void release_command (const unsigned int& owner_id, const string& vehicle_id);
    void remove_command (string what);
    void save_command();
    void show_command();
};

#endif


