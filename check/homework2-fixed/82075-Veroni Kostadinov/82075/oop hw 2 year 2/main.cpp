
#include "Database.h"
using namespace std;


int main()
{
     Database database;
    Person* person = new Person("Ivan", 1234);
     Registration* reg = new Registration("AA2222BB");
     Vehicle* vehicle = new Vehicle(reg, "Ebalo si e mamata");
     database.person_command("Ivan", 1234);
     database.vehicle_command("AA2222BB", "dasdasd");
    

    return 0;
}
