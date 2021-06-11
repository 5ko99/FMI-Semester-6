#include "Database.h"

std::size_t Database::Get_Size_of_Persons() const
{
    return this->AllPerson.size();
}

Person& Database::Get_Person_At_Index(const std::size_t& index) 
{
    return *AllPerson[index];
}

void Database::AddPerson(const Person& per)
{
    this->AllPerson.push_back(new Person(per));

}

void Database::RemovePerson(std::size_t index)
{
    this->AllPerson.erase(AllPerson.begin() + index);

}

std::size_t Database::Get_Size_of_Vehicles() const
{
    return this->AllVehicles.size();
}

Vehicle& Database::Get_Vehicle_At_Index(const std::size_t index)
{
    return *AllVehicles[index];
}

void Database::AddVehicle(const Vehicle& veh)
{
    this->AllVehicles.push_back(new Vehicle(veh));
}

void Database::RemoveVehicle(std::size_t index)
{

    this->AllVehicles.erase(AllVehicles.begin() + index);



}

void Database::SaveText(std::ofstream& file)
{

    

    //first prints to the file those who own cars also prints this person's cars
    for (std::size_t i = 0; i < this->Get_Size_of_Persons(); i++) {

        if (this->Get_Person_At_Index(i).GetOwnVehs().size() > 0) {
            file << this->Get_Person_At_Index(i);
        }
    }


    //then prints to the file all the person without their cars
    for (std::size_t i = 0; i < this->Get_Size_of_Persons(); i++) {
        if (this->Get_Person_At_Index(i).GetOwnVehs().size() == 0) {
            file << Get_Person_At_Index(i);
        }
    }

    //then prints the vehicles that dont have owner
    for (std::size_t i = 0; i < this->Get_Size_of_Vehicles(); i++) {
        if (!this->Get_Vehicle_At_Index(i).Is_Taken()) {
            file << Get_Vehicle_At_Index(i);
        }
    }

    //finally prints the stop on the file
    file << "stop|";
}

void Database::LoadText(std::ifstream& file)
{

    while (true) {

        //strings to contain given line
        std::string str1, str2;

        
        getline(file, str1, '|');
        getline(file, str2, '\n');

        if (str1[0] == 'p') {

            //erasing the first "p" indicating that this is a person
            str1.erase(str1.begin()+0);
            unsigned num = stoi(str2);
            Person per(str1, num);
            this->AddPerson(per);

        }

        if (str1[0] == '-') {

            //erasing the first "-" indicating that this is a Vehicles that is owned
            str1.erase(str1.begin()+0);
            Vehicle veh(str1, str2);
            veh.SetOwner(*this->AllPerson.back());
            this->AddVehicle(veh);
            this->AllPerson.back()->GetOwnVehs().push_back(&veh);


        }

        if (str1[0] == 'v') {

            //erasing the first "v" indicating that this is a Vehicles that doesnt have owner
            str1.erase(str1.begin() + 0);
            Vehicle veh(str1, str2);
            this->AddVehicle(veh);
        }

        //if it reach stop or there is nothing on the file breaking the cycle
        if (str1 == "stop" || file.eof()) break;

    }


}

Database::~Database()
{

    for (std::size_t i = 0; i < this->AllPerson.size(); i++) {

        delete AllPerson.at(i);

    }

    this->AllPerson.clear();


    for (std::size_t i = 0; i < this->AllVehicles.size(); i++) {

        delete AllVehicles.at(i);

    }

    this->AllVehicles.clear();

}

