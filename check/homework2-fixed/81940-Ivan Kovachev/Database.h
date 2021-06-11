#include "Person.h"
#include "Vehicle.h"
#include "Registration.h"
#include "Base.h"
#include <istream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
class Database: public Base
{
    std::vector<Person> persons;
    std::vector<Vehicle> vehicles;

    bool personExists(const unsigned int& id) const;
    bool vehicleExists(const std::string&) const;
    bool caseInSensitive(std::string & str1,std::string &str2);
    bool isOwned(Person p, Vehicle v);
protected:
    void processInput(const std::vector<std::string> &arg);
public:
    Database* fromStream(std::istream& in);
    void toStream(std::ostream &out) const;
    Database(std::istream &in, std::ostream& out);

    int countPeople() const;
    int countVehicles() const;


    Vehicle getVehicle(std::string) const; /// by reg
    Person getPerson(std::string) const; /// by id

    /* Commands only from here down */
    void checkCommand(unsigned int expectedArg, const std::vector<std::string>& vSplitline);
    void openFromFile(const std::vector<std::string>& vsplitLine);
    void saveToFile(const std::vector<std::string>& vsplitLine);
    void printAll(const std::vector<std::string>& vsplitLine);
    void addPerson(const std::vector<std::string>& vsplitLine);
    void addVehicle(const std::vector<std::string>& vsplitLine);
    void aquireVehicle(const std::vector<std::string>& vsplitLine);
    void releaseVehicle(const std::vector<std::string>& vsplitLine);
    void showData(const std::vector<std::string>& vsplitLine);

    void removeData(const std::vector<std::string>& vsplitLine);

};

