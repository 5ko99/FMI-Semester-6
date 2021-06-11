#include "Data.h"


vector<Person> Data::list_of_created_people;
vector<Vehicle> Data::list_of_created_vehicles;

Data::Data(string first_cmd, string second_cmd) {
	this->id = 0;
	this->first_cmd = first_cmd;
	this->second_cmd = second_cmd;
}

Data::Data(string fist_cmd, size_t second_cmd) {
	this->first_cmd = fist_cmd;
	this->id = second_cmd;
}

Data::Data(size_t first_cmd, string second_cmd) {
	this->id = first_cmd;
	this->second_cmd = second_cmd;
}

Data::~Data() {
	this->id = 0;
	this->first_cmd.clear();
	this->second_cmd.clear();
}

//create a vehicle
void Data::create_veh() {
	if (check_if_veh_is_already_created(this->first_cmd)) {
		throw std::invalid_argument("The vehicle you are trying to create has already been created!");
	}
	Registration rg(this->first_cmd);
	Vehicle a(rg, this->second_cmd);	
	list_of_created_vehicles.push_back(a);
}

//check if the vehicle was already created... 1 if the vehicle has already been created, 0 if it hasn't
bool Data::check_if_veh_is_already_created(const string reg) {
	for (size_t i = 0; i < this->list_of_created_vehicles.size(); i++) {
		if (this->list_of_created_vehicles[i].show_reg() == reg) {
			return 1;
		}
	}
	return 0;
}
// create a person
void Data::create_person() {
	if (check_if_person_is_already_created(this->id)) {
		throw std::invalid_argument("The person you are trying to create has already been created!");
	}
	Person a(this->first_cmd, this->id);
	list_of_created_people.push_back(a);
}

//check if the person was already created... 1 if the person has already been created, 0 if he/she hasn't
bool Data::check_if_person_is_already_created(const size_t id) {
	for (size_t i = 0; i < this->list_of_created_people.size(); i++) {
		if (this->list_of_created_people[i].show_id() == id) {
			return 1;
		}
	}
	return 0;
}

void Data::acquire(const size_t id, const string registration) {
	size_t place_of_person = find_place_in_people_list(id);
	size_t place_of_veh = find_place_in_veh_list(registration);
	size_t var_if_the_veh_already_has_owner = list_of_created_vehicles[place_of_veh].does_it_have_an_owner();
	if (var_if_the_veh_already_has_owner == id) {
		throw std::invalid_argument("This person already owns this vehicle!");
	}
	if (var_if_the_veh_already_has_owner) {
		list_of_created_vehicles[place_of_veh].assign_owner(id);
		size_t place_of_old_owner = find_place_in_people_list(var_if_the_veh_already_has_owner);
		list_of_created_people[place_of_old_owner].remove_vehicle(registration);
		list_of_created_people[place_of_person].add_vehicle(registration);
	}
	else {
		list_of_created_vehicles[place_of_veh].assign_owner(id);
		list_of_created_people[place_of_person].add_vehicle(registration);
	}
}

// return the place of the given person in the id list
size_t Data::find_place_in_people_list(const size_t id) {
	for (size_t i = 0; i < this->list_of_created_people.size(); i++) {
		if (this->list_of_created_people[i].show_id() == id) {
			return i;
		}
	}
	throw std::invalid_argument("This person hasn't been created yet!");
}

//return the place of the given registration in the veh id list
size_t Data::find_place_in_veh_list(const string reg) {
	for (size_t i = 0; i < this->list_of_created_vehicles.size(); i++) {
		if (!list_of_created_vehicles[i].show_reg().compare(reg)) {
			return i;
		}
	}
	throw std::invalid_argument("This vehicle hasn't been created yet!");
}

void Data::release(const size_t id, const string registration) {
	size_t place_of_person = find_place_in_people_list(id);
	size_t place_of_veh = find_place_in_veh_list(registration);
	list_of_created_vehicles[place_of_veh].remove_owner();
	list_of_created_people[place_of_person].remove_vehicle(registration);
}

void Data::remove_if_person(const size_t id) {
	if (!check_if_person_is_already_created(id)) {
		throw std::invalid_argument("The person you are trying to remove doesn't exist");
	}
	else {
		size_t pos_of_person = find_place_in_people_list(id);
		if (!list_of_created_people[pos_of_person].list_of_owned_vehicles.size()) {
			list_of_created_people.erase(list_of_created_people.begin() + pos_of_person);
		}
		else {
			string answer;
			std::cout << "This person has vehicles. If you remove the person, the vehicles will lose their owner. Are you sure you want to proceed?:\n";
			std::cout << "Type \" YES\"  or \"NO\"\n";
			std::cin >> answer;
			std::cin.ignore();

			if (!answer.compare("YES")) {
				for (size_t i = 0; i < list_of_created_people[pos_of_person].list_of_owned_vehicles.size(); i++) {
					string reg_to_remove = list_of_created_people[pos_of_person].list_of_owned_vehicles[i];
					size_t pos_of_veh = find_place_in_veh_list(reg_to_remove);
					list_of_created_vehicles[pos_of_veh].remove_owner();
				}
				list_of_created_people.erase(list_of_created_people.begin() + pos_of_person);
			}
		}
	}
}

void Data::remove_if_veh(const string registration) {
	if (!check_if_veh_is_already_created(registration)) {
		throw std::invalid_argument("The vehicle you are trying to remove doesn't exist");
	}
	else {
		size_t pos_of_veh = find_place_in_veh_list(registration);
		size_t does_it_have_owner = list_of_created_vehicles[pos_of_veh].does_it_have_an_owner();
		if (!does_it_have_owner) {
			list_of_created_vehicles.erase(list_of_created_vehicles.begin() + pos_of_veh);
		}
		else {
			string answer;
			size_t pos_of_owner = find_place_in_people_list(does_it_have_owner);
			std::cout << "This vehicle has an owner. Are you sure you want to proceed?:\n";
			std::cout << "Type \" YES\"  or \"NO\"\n";
			std::cin >> answer;
			std::cin.ignore();
			if (!answer.compare("YES")) {
				list_of_created_people[pos_of_owner].remove_vehicle(registration);
				list_of_created_vehicles.erase(list_of_created_vehicles.begin() + pos_of_veh);
			}
				
		}
	}
}

void Data::show_people() {
	if (this->list_of_created_people.size() == 0) {
		throw std::invalid_argument("There aren't any people to show.");
	}
	for (size_t i = 0; i < this->list_of_created_people.size(); i++) {
		std::cout << "Name: " << list_of_created_people[i].show_name() << ", id: " << list_of_created_people[i].show_id() << std::endl;
	}
}

void Data::show_vehicles() {
	if (this->list_of_created_vehicles.size() == 0) {
		throw std::invalid_argument("There aren't any vehicles to show.");
	}
	for (size_t i = 0; i < this->list_of_created_vehicles.size(); i++) {
		std::cout << "Registration: " << this->list_of_created_vehicles [i].show_reg() << 
			", description: " << this->list_of_created_vehicles[i].show_descr() << std::endl;
	}
}

void Data::show_owner_of_veh(string reg) {
	size_t pos_of_veh = find_place_in_veh_list(reg);
	size_t id_of_owner = this->list_of_created_vehicles[pos_of_veh].does_it_have_an_owner();
	if (id_of_owner) {
		size_t pos_of_owner = find_place_in_people_list(id_of_owner);
		std::cout << "Name of owner: " << this->list_of_created_people[pos_of_owner].show_name() <<
			", id of owner: " << this->list_of_created_people[pos_of_owner].show_id() << std::endl;
	}
	else {
		std::cout << "This vehicle doesn't have an owner." << std::endl;
	}
}

void Data::show_owned_vehicles(size_t id) {
	size_t pos_of_person = find_place_in_people_list(id);
	size_t size_of_owned_veh_list = this->list_of_created_people[pos_of_person].list_of_owned_vehicles.size();

	if (size_of_owned_veh_list) {
		for (size_t i = 0; i < size_of_owned_veh_list; i++) {
			size_t pos_of_vehicle = find_place_in_veh_list(list_of_created_people[pos_of_person].list_of_owned_vehicles[i]);
			std::cout << "Registration: " << this->list_of_created_vehicles[pos_of_vehicle].show_reg() <<
				", description: " << this->list_of_created_vehicles[pos_of_vehicle].show_descr() << std::endl;
		}
	}
	else {
		std::cout << "This person doesn't own any vehicles." << std::endl;
	}
}
