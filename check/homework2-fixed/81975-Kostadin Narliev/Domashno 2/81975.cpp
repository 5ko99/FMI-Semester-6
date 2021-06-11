#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

class Person;
class Vehicle;

class Registration
{
	string reg_num;
	bool valid;
public:

	Registration()
    {
		valid = false;
	}

	Registration(string regnum)
    {
		set_num(regnum);
	}

	void set_num(string regnum)
    {
		if(regnum.size() == 7)
        {
			if((regnum[0] >= 'A' && regnum[0] <= 'Z'))
            {
				for (int i = 1; i <= 4; ++i)
				{
					if(regnum[i] >= '0' && regnum[i] <= '9')
                    {

					}
                    else
                    {
						valid = false;
						break;
					}
				}
				if((regnum[5] >= 'A' && regnum[5] <= 'Z') && (regnum[6] >= 'A' && regnum[6] <= 'Z'))
                {
					this->reg_num = regnum;
					valid = true;
				}
                else
                {
					valid = false;
				}
			}
            else
            {
				valid = false;
			}
		}
        else if(regnum.size() == 8)
        {
			if((regnum[0] >= 'A' && regnum[0] <= 'Z') && (regnum[1] >= 'A' && regnum[1] <= 'Z'))
            {
				for(int i = 2; i <= 5; ++i)
				{
					if(regnum[i] >= '0' && regnum[i] <= '9')
                    {

					}
                    else
                    {
						valid = false;
						break;
					}
				}
				if((regnum[6] >= 'A' && regnum[6] <= 'Z') && (regnum[7] >= 'A' && regnum[7] <= 'Z'))
                {
					this->reg_num = regnum;
					valid = true;
				}
                else
                {
					valid = false;
				}
			}
            else
            {
				valid = false;
			}
		}
        else
        {
			valid = false;
		}
	}

	bool get_valid()
    {
		return this->valid;
	}

	string get_num()
    {
		return this->reg_num;
	}

	~Registration()
    {

	}
};

class Vehicle
{
	Registration reg_num;
	string description;
	Person* owner;
public:

	Vehicle()
    {
		this->owner = nullptr;
	}

	Registration get_reg_num()
    {
		return reg_num;
	}

	string get_description()
    {
		return this->description;
	}

	bool set_reg_num(string regnum)
    {
		reg_num.set_num(regnum);
		return reg_num.get_valid();
	}

	void set_owner(Person* _owner)
    {
		this->owner = _owner;
	}

	Person* get_owner()
    {
		return this->owner;
	}

	bool has_owner()
    {
		if(owner!=nullptr)
        {
			return true;
		}else{
			return false;
		}
	}

	void set_description(string _description)
    {
		this->description = _description;
	}

	~Vehicle()
    {

	}

};

class Person
{
	string name;
	unsigned int id;
	std::vector<Vehicle*> vehicle_owned;
public:
	Person()
    {
		this->id = 0;
	}

	void add_vehicle(Vehicle* v)
    {
		vehicle_owned.push_back(v);
	}

	void remove_vehicle(string reg_num)
    {
		for (int i = 0; i < vehicle_owned.size(); ++i)
		{
			if(vehicle_owned[i]->get_reg_num().get_num() == reg_num)
            {
				vehicle_owned.erase(vehicle_owned.begin() + i);
			}
		}
	}

	void release_all()
    {
		for (int i = 0; i < vehicle_owned.size(); ++i)
		{
			vehicle_owned[i]->set_owner(nullptr);
		}
	}

	int num_of_vehicles_owned()
    {
		return vehicle_owned.size();
	}

	void set_name(string _name)
    {
		this->name = _name;
	}

	void set_id(unsigned int _id)
    {
		this->id = _id;
	}

	unsigned int get_id()
    {
		return this->id;
	}

	void print_vehicles()
    {
		cout << "Owned vehicles:" << endl;
		if(vehicle_owned.size() == 0)
        {
			cout << "No owned vehicles!" << endl;
		}
		for (int i = 0; i < vehicle_owned.size(); ++i)
        {
			cout << "~~~~~~~~~~~~~" << endl;
			cout << "Vehicle registration number: "<< vehicle_owned[i]->get_reg_num().get_num() << endl;
			cout << "Vehicle description: "<< vehicle_owned[i]->get_description() << endl;
		}
	}

	string get_name()
    {
		return this->name;
	}

	~Person()
    {

	}
};

void System(std::vector<Person*> &people, std::vector<Vehicle*> &vehicles)
{
	string input;
	string token;
	while(true){
		getline(cin,input);
		stringstream command(input);
		command >> token;
		for (int i = 0; i < token.size(); ++i)
        {
			token[i] = toupper(token[i]);
		}
		if(token.compare("VEHICLE") == 0)
        {
			string reg_num;
			string description;
			string additional_token;
			command >> reg_num;
			command >> description;
			if(description[0] == '"')
            {
				while(command >> additional_token)
                {
					description += ' ';
					description += additional_token;
					if(additional_token[additional_token.size()-1] == '"')
                    {
						break;
					}
				}
			}

			bool unique = true;
			for (int i = 0; i < vehicles.size(); ++i)
			{
				if(vehicles[i]->get_reg_num().get_num().compare(reg_num) == 0)
                {
					cout << "Vehicle with that Registration number is already registered!" << endl;
					unique = false;
					break;
				}
			}

			if(unique)
            {
				Vehicle* new_vehicle = new Vehicle();
				new_vehicle->set_reg_num(reg_num);
				if(new_vehicle->get_reg_num().get_valid() == false)
                {
					cout << "Bad registration number!" << endl;
					delete new_vehicle;
				}
                else
                {
					new_vehicle->set_description(description);
					vehicles.push_back(new_vehicle);
					cout << "Added new vehicle with registration num: " << new_vehicle->get_reg_num().get_num()
					<< " and description: " << new_vehicle->get_description() << endl;
				}
			}	
		}else if(token.compare("PERSON") == 0)
        {
			string name;
			unsigned int id;
			string additional_token;
			command >> name;
			if(name[0] == '"')
            {
				while(command >> additional_token)
                {
					name += ' ';
					name += additional_token;
					if(additional_token[additional_token.size()-1] == '"')
                    {
						break;
					}
				}
			}
			command >> id;

			bool unique = true;
			for (int i = 0; i < people.size(); ++i)
			{
				if(people[i]->get_id() == id)
                {
					cout << "Person with that ID is already registered!" << endl;
					unique = false;
				}
			}

			if(unique)
            {
				Person* new_person = new Person();
				new_person->set_name(name);
				new_person->set_id(id);
				people.push_back(new_person);
				cout << "Added new person with name: " << new_person->get_name()
				<< " and id: " << new_person->get_id() << endl;
			}	
		}
        else if(token.compare("ACQUIRE") == 0)
        {
			unsigned int owner_id;
			string vehicle_id;
			command >> owner_id;
			command >> vehicle_id;
			Person* new_owner;
			Vehicle* v;
			bool check_for_existance_p = false;
			bool check_for_existance_v = false;
			for (int i = 0; i < people.size(); ++i)
			{
				if(people[i]->get_id() == owner_id)
                {
					check_for_existance_p = true;
				}
			}
			for (int i = 0; i < vehicles.size(); ++i)
			{
				if(vehicles[i]->get_reg_num().get_num().compare(vehicle_id) == 0){
					check_for_existance_v = true;
				}
			}

			if(check_for_existance_v == false)
            {
				cout << "No such vehicle!" << endl;
			}
            else if(check_for_existance_p == false)
            {
				cout << "No such person!" << endl;
			}
            else
            {
				for (int i = 0; i < people.size(); ++i)
				{
					if(people[i]->get_id() == owner_id)
                    {
						new_owner = people[i];
					}
				}
				for (int i = 0; i < vehicles.size(); ++i)
				{
					if(vehicles[i]->get_reg_num().get_num().compare(vehicle_id) == 0)
                    {
						v = vehicles[i];
					}
				}
				if(v->has_owner())
                {
					v->get_owner()->remove_vehicle(v->get_reg_num().get_num());
				}
				v->set_owner(new_owner);
				new_owner->add_vehicle(v);
				cout << "Person: " << new_owner->get_name() << " acquired new car: " << v->get_reg_num().get_num() << endl;
			}		
		}
        else if(token.compare("RELEASE") == 0)
        {
			unsigned int owner_id;
			string vehicle_id;
			command >> owner_id;
			command >> vehicle_id;
			bool check_for_existance_p = false;
			bool check_for_existance_v = false;
			for (int i = 0; i < people.size(); ++i)
			{
				if(people[i]->get_id() == owner_id)
                {
					check_for_existance_p = true;
				}
			}
			for (int i = 0; i < vehicles.size(); ++i)
			{
				if(vehicles[i]->get_reg_num().get_num().compare(vehicle_id) == 0)
                {
					check_for_existance_v = true;
				}
			}

			if(check_for_existance_v == false)
            {
				cout << "No such vehicle!" << endl;
			}
            else if(check_for_existance_p == false)
            {
				cout << "No such person!" << endl;
			}
            else
            {
				for (int i = 0; i < people.size(); ++i)
				{
					if(people[i]->get_id() == owner_id)
                    {
						people[i]->remove_vehicle(vehicle_id);
					}
				}
				for (int i = 0; i < vehicles.size(); ++i)
				{
					if(vehicles[i]->get_reg_num().get_num().compare(vehicle_id) == 0)
                    {
						vehicles[i]->set_owner(nullptr);
					}
				}
				cout << "Vehicle: " << vehicle_id << " is released!" << endl;
			}
		}
        else if(token.compare("REMOVE") == 0)
        {
			bool finded = false;
			command >> token;
			if(isdigit(token[0]))
            {
				for (int i = 0; i < people.size(); ++i){
					if(people[i]->get_id() == stoi(token))
                    {
						finded = true;
						if(people[i]->num_of_vehicles_owned() == 0)
                        {
							delete people[i];
							people.erase(people.begin() + i);	
							cout << "Person deleted!" << endl;
						}
                        else
                        {
							cout << "This person owns vehicles, are you sure you want to delete him? y/n" << endl;
							string answer;
							getline(cin,answer);
							if(answer.compare("y") == 0)
                            {
								people[i]->release_all();
								delete people[i];
								people.erase(people.begin() + i);
								cout << "Person deleted!" << endl;
							}
						}
						break;
					}
				}
				if(!finded)
                {
					cout << "No such person exists in the database!" << endl;
				}
			}
            else
            {
				for (int i = 0; i < vehicles.size(); ++i)
                {
					if(vehicles[i]->get_reg_num().get_num() == token)
                    {
						finded = true;
						if(vehicles[i]->has_owner())
                        {
							cout << "This vehicle has owner, are you sure you want to delete it? y/n" << endl;
							string answer;
							getline(cin,answer);
							if(answer.compare("y") == 0)
                            {
								vehicles[i]->get_owner()->remove_vehicle(vehicles[i]->get_reg_num().get_num());
								delete vehicles[i];
								vehicles.erase(vehicles.begin() + i);
								cout << "Vehicle deleted!" << endl;
							}
						}
                        else
                        {
							delete vehicles[i];
							vehicles.erase(vehicles.begin() + i);
							cout << "Vehicle deleted!" << endl;
						}
						break;
					}
				}
				if(!finded)
                {
					cout << "No such vehicle exists in the database!" << endl;
				}
			} 
		}
        else if(token.compare("SAVE") == 0)
        {
			string path;
			command >> path;
			ifstream file(path);
			if(file.fail())
            {
				ofstream mysavefile(path);
				if(mysavefile.is_open())
                {
					for (int i = 0; i < people.size(); ++i)
					{
						mysavefile << "PERSON " << people[i]->get_name() << " " << people[i]->get_id() << endl;
					}
					for (int i = 0; i < vehicles.size(); ++i)
					{
						mysavefile << "VEHICLE " << vehicles[i]->get_reg_num().get_num() << " " << vehicles[i]->get_description() << endl;
					}
					for (int i = 0; i < vehicles.size(); ++i)
					{
						if(vehicles[i]->has_owner())
                        {
							mysavefile << "ACQUIRE " << vehicles[i]->get_owner()->get_id() << " " << vehicles[i]->get_reg_num().get_num() << endl;
						}			
					}
					mysavefile.close();
				}
				cout << "Database saved!" << endl;
			}
            else
            {
				cout << "the file exist do you really want to overwrite it? y/n" << endl;
				string answer;
				getline(cin,answer);
				if(answer.compare("y") == 0)
                {
					ofstream mysavefile(path);
					if(mysavefile.is_open())
                    {
						for (int i = 0; i < people.size(); ++i)
						{
							mysavefile << "PERSON " << people[i]->get_name() << " " << people[i]->get_id() << endl;
						}
						for (int i = 0; i < vehicles.size(); ++i)
						{
							mysavefile << "VEHICLE " << vehicles[i]->get_reg_num().get_num() << " " << vehicles[i]->get_description() << endl;
						}
						for (int i = 0; i < vehicles.size(); ++i)
						{
							if(vehicles[i]->has_owner())
                            {
								mysavefile << "ACQUIRE " << vehicles[i]->get_owner()->get_id() << " " << vehicles[i]->get_reg_num().get_num() << endl;
							}			
						}
						mysavefile.close();
					}
					cout << "Database saved!" << endl;
				}
			}
		}
        else if(token.compare("SHOW") == 0)
        {
			command >> token;
			Registration test_token;
			test_token.set_num(token);
			if(isdigit(token[0]))
            {
				cout << "searching for person with id: " << token << " in th database" << endl;
				bool finded = false;
				for (int i = 0; i < people.size(); ++i)
				{
					if(people[i]->get_id() == stoi(token))
                    {
						finded = true;
						cout << "FOUND" << endl;
						cout << "Person name: " << people[i]->get_name() << endl;
						cout << "Person id: " << people[i]->get_id() << endl;
						people[i]->print_vehicles();
					}
				}
				if(!finded)
                {
					cout << "No such person in the database" << endl;
				}
			}
            else if(test_token.get_valid())
            {
				cout << "searching for vehicle with registration number: " << token << " in th database" << endl;
				bool finded = false;
				for (int i = 0; i < vehicles.size(); ++i)
				{
					if(vehicles[i]->get_reg_num().get_num() == token)
                    {
						finded = true;
						cout << "FOUND" << endl;
						cout << "Vehicle registration number: "<< vehicles[i]->get_reg_num().get_num() << endl;
						cout << "Vehicle description: "<< vehicles[i]->get_description() << endl;
						if(vehicles[i]->has_owner())
                        {
							cout << "Vehicle owner: "<< vehicles[i]->get_owner()->get_name() << endl;
							cout << "Vehicle owner id: "<< vehicles[i]->get_owner()->get_id() << endl;
						}
                        else
                        {
							cout << "Vehicle doesn't have owner" << endl;
						}		
					}
				}
				if(!finded)
                {
					cout << "No such vehicle in the database" << endl;
				}
			}
            else
            {
				for (int i = 0; i < token.size(); ++i)
                {
					token[i] = toupper(token[i]);
				}
				if(token.compare("PEOPLE") == 0)
                {
					cout << "---------------PEOPLE-----------------" << endl;
					cout << "Number of people registered: "<< people.size() << endl;
					for (int i = 0; i < people.size(); ++i)
					{
						cout << "===================" << endl;
						cout << "Person name: " << people[i]->get_name() << endl;
						cout << "Person id: " << people[i]->get_id() << endl;
						people[i]->print_vehicles();
					}
					cout << "--------------------------------------" << endl;
				}
                else if(token.compare("VEHICLES") == 0)
                {
					cout << "--------------VEHICLES----------------" << endl;
					cout << "Number of vehicles registered: "<< vehicles.size() << endl;
					for (int i = 0; i < vehicles.size(); ++i)
					{
						cout << "===================" << endl;
						cout << "Vehicle registration number: "<< vehicles[i]->get_reg_num().get_num() << endl;
						cout << "Vehicle description: "<< vehicles[i]->get_description() << endl;
						if(vehicles[i]->has_owner())
                        {
							cout << "Vehicle owner: "<< vehicles[i]->get_owner()->get_name() << endl;
							cout << "Vehicle owner id: "<< vehicles[i]->get_owner()->get_id() << endl;
						}
                        else
                        {
							cout << "Vehicle doesn't have owner" << endl;
						}		
					}
					cout << "--------------------------------------" << endl;
				}
                else
                {
					cout << "Invalid argument to SHOW!" << endl;
				}
			}
		}
        else if(token.compare("EXIT") == 0)
        {
			for (int i = 0; i < vehicles.size(); ++i)
			{
				delete vehicles[i];
			}
			for (int i = 0; i < people.size(); ++i)
			{
				delete people[i];
			}
			break;
		}
        else
        {
			cout << "Invalid command!" << endl;
		}
	}
}

void load_from_database(std::vector<Person*> &people, std::vector<Vehicle*> &vehicles, string fileforreading)
{
	ifstream input_file(fileforreading);
	if(input_file.is_open())
    {
		string input;
		string token;
		while(getline(input_file,input))
        {
			stringstream command(input);
			command >> token;
			for (int i = 0; i < token.size(); ++i)
            {
				token[i] = toupper(token[i]);
			}
			if(token.compare("VEHICLE") == 0)
            {
				string reg_num;
				string description;
				string additional_token;
				command >> reg_num;
				command >> description;
				if(description[0] == '"')
                {
					while(command >> additional_token)
                    {
						description += ' ';
						description += additional_token;
						if(additional_token[additional_token.size()-1] == '"')
                        {
							break;
						}
					}
				}

				bool unique = true;
				for (int i = 0; i < vehicles.size(); ++i)
				{
					if(vehicles[i]->get_reg_num().get_num().compare(reg_num) == 0)
                    {
						cout << "Vehicle with that Registration number is already registered!" << endl;
						unique = false;
						break;
					}
				}

				if(unique)
                {
					Vehicle* new_vehicle = new Vehicle();
					new_vehicle->set_reg_num(reg_num);
					if(new_vehicle->get_reg_num().get_valid() == false)
                    {
						cout << "Bad registration number!" << endl;
						delete new_vehicle;
					}
                    else
                    {
						new_vehicle->set_description(description);
						vehicles.push_back(new_vehicle);
						cout << "Added new vehicle with registration num: " << new_vehicle->get_reg_num().get_num()
						<< " and description: " << new_vehicle->get_description() << endl;
					}
				}	
			}
            else if(token.compare("PERSON") == 0)
            {
				string name;
				unsigned int id;
				string additional_token;
				command >> name;
				if(name[0] == '"')
                {
					while(command >> additional_token)
                    {
						name += ' ';
						name += additional_token;
						if(additional_token[additional_token.size()-1] == '"')
                        {
							break;
						}
					}
				}
				command >> id;

				bool unique = true;
				for (int i = 0; i < people.size(); ++i)
				{
					if(people[i]->get_id() == id)
                    {
						cout << "Person with that ID is already registered!" << endl;
						unique = false;
					}
				}

				if(unique)
                {
					Person* new_person = new Person();
					new_person->set_name(name);
					new_person->set_id(id);
					people.push_back(new_person);
					cout << "Added new person with name: " << new_person->get_name()
					<< " and id: " << new_person->get_id() << endl;
				}	
			}
            else if(token.compare("ACQUIRE") == 0)
            {
				unsigned int owner_id;
				string vehicle_id;
				command >> owner_id;
				command >> vehicle_id;
				Person* new_owner;
				Vehicle* v;
				bool check_for_existance_p = false;
				bool check_for_existance_v = false;
				for (int i = 0; i < people.size(); ++i)
				{
					if(people[i]->get_id() == owner_id)
                    {
						check_for_existance_p = true;
					}
				}
				for (int i = 0; i < vehicles.size(); ++i)
				{
					if(vehicles[i]->get_reg_num().get_num().compare(vehicle_id) == 0)
                    {
						check_for_existance_v = true;
					}
				}
				if(check_for_existance_v == false)
                {
					cout << "No such vehicle!" << endl;
				}
                else if(check_for_existance_p == false)
                {
					cout << "No such person!" << endl;
				}
                else
                {
					for (int i = 0; i < people.size(); ++i)
					{
						if(people[i]->get_id() == owner_id)
                        {
							new_owner = people[i];
						}
					}
					for (int i = 0; i < vehicles.size(); ++i)
					{
						if(vehicles[i]->get_reg_num().get_num().compare(vehicle_id) == 0)
                        {
							v = vehicles[i];
						}
					}
					if(v->has_owner())
                    {
						v->get_owner()->remove_vehicle(v->get_reg_num().get_num());
					}
					v->set_owner(new_owner);
					new_owner->add_vehicle(v);
					cout << "Person: " << new_owner->get_name() << " acquired new car: " << v->get_reg_num().get_num() << endl;
				}		
			}
		}
		input_file.close();
	}
	
}

int main(int argc,char** argv)
{
	std::vector<Person*> people;
	std::vector<Vehicle*> vehicles;
	string filename;
	if(argc == 2)
    {
		for (int i = 0; i < strlen(argv[1]); ++i)
		{
			filename+= argv[1][i];
		}
		load_from_database(people,vehicles,filename);
	}
	System(people,vehicles);
}
