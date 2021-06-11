#include <iostream>
#include <fstream>
#include "commands.h"
#include "Data.h"
using namespace std;

void if_vehicle_create(string registration, string description) {
	Data veh(registration, description);
	veh.create_veh();
}

void if_person_create(string name, size_t id) {
	Data human(name, id);
	human.create_person();
}

void if_acquire(size_t id, string registration) {
	Data acquire(id, registration);
	acquire.acquire(id, registration);
}

void if_release(size_t id, string registration) {
	Data release(id, registration);
	release.release(id, registration);
}

void if_person_remove(size_t id) {
	Data a(id, "");
	a.remove_if_person(id);
}

void if_vehicle_remove(string registration) {
	Data a(registration, "");
	a.remove_if_veh(registration);
}

void if_show_people() {
	Data a("", "");
	a.show_people();
}

void if_show_vehicles() {
	Data a("", "");
	a.show_vehicles();
}

void if_show_owner_of_veh(string reg) {
	Data a(reg, "");
	a.show_owner_of_veh(reg);
}

void if_show_vehicles_of_owner(size_t id) {
	Data a("", id);
	a.show_owned_vehicles(id);
}

void process_commands(char command[100]) {
	Commands new_cmd(command);
	string main_command = new_cmd.main_cmd();



	if (main_command == "VEHICLE") {
		if (new_cmd.split_command.size() == 4) {
			string description = new_cmd.split_command[2] + ' ' + new_cmd.split_command[3];
			try
			{
				if_vehicle_create(new_cmd.split_command[1], description);
			}
			catch (const invalid_argument& e)
			{
				cout << e.what() << endl;
			}
		}
		else {
			try
			{
				if_vehicle_create(new_cmd.split_command[1], new_cmd.split_command[2]);

			}
			catch (const invalid_argument& e)
			{
				cout << e.what() << endl;
			}
		}
	}
	else if (main_command == "PERSON") {
		if (new_cmd.split_command.size() == 4) {
			string name = new_cmd.split_command[1] + ' ' + new_cmd.split_command[2];
			size_t id = stoi(new_cmd.split_command[3]);
			try
			{
				if (id == 0) {
					cout << "0 is not a valid ID. Try again!" << endl;
				}
				else {
					if_person_create(name, id);
				}
			}
			catch (const invalid_argument& e)
			{
				cout << e.what() << endl;
			}

			
		}
		else {
			string name = new_cmd.split_command[1];
			size_t id = stoi(new_cmd.split_command[2]);
			try
			{
				if (id == 0) {
					cout << "0 is not a valid ID. Try again!" << endl;
				}
				else {
					if_person_create(name, id);
				}
			}
			catch (const invalid_argument& e)
			{
				cout << e.what() << endl;
			}
		}
	}
	else if (main_command == "ACQUIRE") {
		size_t id = std::stoi(new_cmd.split_command[1]);
		string registration = new_cmd.split_command[2];
		try
		{
			if_acquire(id, registration);
		}
		catch (const invalid_argument& e)
		{
			cout << e.what() << endl;
		}
	}
	else if (main_command == "RELEASE") {
		size_t id = stoi(new_cmd.split_command[1]);
		string registration = new_cmd.split_command[2];
		try
		{
			if_release(id, registration);
		}
		catch (const invalid_argument& e)
		{
			cout << e.what() << endl;
		}
	}
	else if (main_command == "REMOVE") {
		if (isdigit(new_cmd.split_command[1][0])) {
			size_t id = stoi(new_cmd.split_command[1]);
			try
			{
				if_person_remove(id);
			}
			catch (const invalid_argument& e)
			{
				cout << e.what() << endl;
			}
		}
		else {
			string registration = new_cmd.split_command[1];
			try
			{
				if_vehicle_remove(registration);
			}
			catch (const invalid_argument& e)
			{
				cout << e.what() << endl;
			}
		}
	}
	else if (main_command == "SAVE") {
		ofstream file_to_save;
		string path = new_cmd.split_command[1];
		file_to_save.open(path);
		if (file_to_save.fail()) {
			cerr << "Error opening file" << endl;
			exit(1);
		}
		for (size_t i = 0; i < new_cmd.list_of_used_commands.size() -1; i++) {
			file_to_save << new_cmd.list_of_used_commands[i] << endl;
		}
		file_to_save.close();
	}
	else if (main_command == "SHOW") {
		if (new_cmd.split_command[1] == "PEOPLE") {
			try
			{
				if_show_people();
			}
			catch (const invalid_argument& e)
			{
				cout << e.what() << endl;
			}
		}
		else if (new_cmd.split_command[1] == "VEHICLES") {
			try
			{
				if_show_vehicles();
			}
			catch (const invalid_argument& e)
			{
				cout << e.what() << endl;
			}
		}
		else {
			string id_or_reg = new_cmd.split_command[1];
			//regs
			if (isalpha(id_or_reg[0])) {
				try
				{
					if_show_owner_of_veh(id_or_reg);
				}
				catch (const invalid_argument& e)
				{
					cout << e.what() << endl;
				}
			}
			//id's
			else {
				size_t id = stoi(id_or_reg);
				try
				{
					if_show_vehicles_of_owner(id);
				}
				catch (const invalid_argument& e)
				{
					cout << e.what() << endl;
				}
			}
		}
	}
}


int main(int argc, char* argv[]) {

	if (argc > 1) {
		ifstream given_file;
		string filepath = argv[1];
		given_file.open(filepath);

		if (given_file.fail()) {
			std::cerr << "Error Opening file";
			exit(1);
		}
		string command;
		char cmd[100];
		while (getline(given_file, command)) {
			strcpy(cmd, command.c_str());
			process_commands(cmd);
		}
		given_file.close();
	}
	char command[100];


	cout << "Enter a command:\n \n";
	cout << "To stop the program, enter \"STOP\"\n \n";

	std::cin.getline(command, 100);

	while (strcmp(command, "STOP")){
		process_commands(command);
		cout << "Enter a command:\n";
		std::cin.getline(command, 100);
	}
	}
