#include "Commands.h"

std::string Command::Get_Argument_within_QuotationMark(std::string& args) { //done


	//creates two helpers variable that will theme from where one quoted string begins and ends
	size_t m = 0, n = 0;

	//here will store the string 
	std::string arg;

	for (size_t i = 0; i < args.size(); i++) {

		//if finds the first " and m is empthy stores them
		if (args[i] == '"' && !m) {
			m = i + 1;
			break;
		}
	}

	for(size_t i=m+1;i<args.size();i++){

		//if finds the second " and stores it in n
		if (args[i] == '"') {
			n = i - 1;
			break;
		}
	}

	// if m and n are not empty gets the substring
	if (m && n) { arg = args.substr(m, n - m + 1); }


	//erasing the substing from the bigger input
	args.erase(m - 1, n+2);

	//return arg
	return arg;
}

bool Command::Does_Arg_Contains_2_QuotationMarks(std::string& args)
{

	//one is used for the first " and second is used for the second "
	bool one=false, two=false;

	for (std::size_t i = 0; i < args.size(); i++) {

		//if finds " and one is false
		if (args[i] == '\"' && !one) one = true;

		//if finds " and the second is true
		if (args[i] == '\"' && one) two = true;
	}

	//if both are true returs true
	if (one && two) { return true; }

	//if two is false return false
	if (one && !two) { return false; }
	
}

std::string Command::Get_Other_Argument(std::string& args) // done
{
	//helper variable to tell me where is the end
	size_t m = 0;

	//searches for ' ' or till the end of the remaining string
	for (std::size_t i = 0; i < args.size(); i++) {
		if (args[i] == ' '){ m = i-1; break; }
		if (i + 1 == args.size()) { m = i; break; }
	}

	//stroring it
	std::string arg = args.substr(0, m+1);
	return arg;
}

void Command::Remove_Leading_Whitespaces(std::string& args) //done 
{
	//function to remove the leading whitespaces in the input
	std::size_t a = 0;

	for (std::size_t i = 0; i < args.size(); i++) {
		if (args[i] == ' ') a++;
		if (args[i] != ' ') break;
	}

	//erasing the white spaces
	args.erase(0, a);
}

std::string& Command::str_toupper(std::string& str) // done
{
	//converts the argument ot upper letter casses
	for (std::size_t i = 0; i < str.size(); i++) {
		str[i] = toupper(str[i]);
	}

	return str;
}

bool Command::Is_There_Duplicated_Person(unsigned int& per_id) // da se vurna posle
{
    
	//checks all person and if the argument is met in the database returns true
	for (std::size_t i = 0; i < this->database->Get_Size_of_Persons(); i++) {
		if (per_id == this->database->Get_Person_At_Index(i).GetUniNum()) return true;
	}
	return false;

}

bool Command::Is_There_Duplicated_Vehicle(std::string& arg) 
{
	
	// if arg1 isnt valid throw exception
	Registration reg(arg);

	//checks all vehicles and if the argument is met in the database return ture
	for (std::size_t i = 0; i < this->database->Get_Size_of_Vehicles(); i++) {
		if (reg == this->database->Get_Vehicle_At_Index(i).GetUniRegNum()) return true;
	}
	return false;
}



void Command::Execute_Person() 
{

		unsigned int num = stoi(this->arg2); 

		if (Is_There_Duplicated_Person(num)) throw std::invalid_argument("There is a Person with the same id your input!");
		Person per(this->arg1, num);
		this->database->AddPerson(per);
		std::cout << "Succesfully added Person"<< std::endl;
}



void Command::Execute_Vehicle()
{

	if (Is_There_Duplicated_Vehicle(this->arg1)) throw std::invalid_argument("There is a Vehicle with the same id in your input");

	
	Vehicle veh(this->arg1, this->arg2);
	this->database->AddVehicle(veh);
	std::cout << "Succesfully added Vehicle" << std::endl;
}

void Command::Execute_Acquire()
{
	//if the size of the database is zero throws exception
	if (this->database->Get_Size_of_Vehicles() == 0 || this->database->Get_Size_of_Persons() == 0) {
		throw std::runtime_error("There is nothing in our database!");
	}


	//Owner is argument with only numbers inside, changing it to unsigned int
	unsigned int owner_id = stoi(this->arg1);

	//if the person's id is not met in the database throws exception
	if (!Is_There_Duplicated_Person(owner_id)) throw std::invalid_argument("There isnt such person  in our database");

	//if the vehicle's Reg num is not met in the database throws exception
	if (!Is_There_Duplicated_Vehicle(this->arg2)) throw std::invalid_argument("There isnt such vehicle in our database");

	//finds the location of the vehicle in the database
	std::size_t v = 0;
	for (std::size_t j = 0; j < this->database->Get_Size_of_Vehicles(); j++) {
		if (this->arg2 == this->database->Get_Vehicle_At_Index(j).GetUniRegNum()) v = j; break;
	}

	//finds the location of the person in the database
	std::size_t p = 0;
	for (std::size_t i = 0; i < this->database->Get_Size_of_Persons(); i++) {
		if (owner_id == this->database->Get_Person_At_Index(i).GetUniNum()) p = i; break;
	}

	// if the vehicle is owned by someone it disown itself and removes itself from his past owner's vector
	if (this->database->Get_Vehicle_At_Index(v).Is_Taken()) {

		for (std::size_t i = 0; i < this->database->Get_Vehicle_At_Index(v).GetOwner().GetOwnVehs().size(); i++) {
			if (this->arg2 == this->database->Get_Vehicle_At_Index(v).GetOwner().GetOwnVehs().at(i)->GetUniRegNum()) {

				//erasing the vehicle from the previews owner
				this->database->Get_Vehicle_At_Index(v).GetOwner().GetOwnVehs().erase(this->database->Get_Vehicle_At_Index(v).GetOwner().GetOwnVehs().begin() + i);

				//disowning the veh
				this->database->Get_Vehicle_At_Index(v).DisOwn();
				break;
			}
			
		}
	}

	if (!this->database->Get_Vehicle_At_Index(v).Is_Taken()) {

		//throws exception if the user is setting the same owner again
		this->database->Get_Vehicle_At_Index(v).SetOwner(this->database->Get_Person_At_Index(p));
		std::cout << "Succesful operaton !" << std::endl;
	}

}


void Command::Execute_Release()
{

	if (this->database->Get_Size_of_Vehicles() == 0 || this->database->Get_Size_of_Persons() == 0) {
		throw std::runtime_error("There is nothing in our database!");
	}

	unsigned int owner_id = stoi(this->arg1);

	if (!Is_There_Duplicated_Person(owner_id)) throw std::invalid_argument("There isnt such person id in our database");
	if (!Is_There_Duplicated_Vehicle(this->arg2)) throw std::invalid_argument("There isnt such vehicle in our database");

	// finds vehicle
	std::size_t v = 0;
	for (std::size_t i = 0; i < this->database->Get_Size_of_Vehicles(); i++) {
		if (this->arg1 == this->database->Get_Vehicle_At_Index(i).GetUniRegNum()) v = i; break;
	}

	//find person
	std::size_t p = 0;
	for (std::size_t i = 0; i < this->database->Get_Size_of_Persons(); i++) {
		if (owner_id == this->database->Get_Person_At_Index(i).GetUniNum()) p = i; break;
	}

	//removes veh from person
	for (std::size_t i = 0; i < this->database->Get_Person_At_Index(p).GetOwnVehs().size(); i++) {
		if (this->arg2 == this->database->Get_Person_At_Index(p).GetOwnVehs().at(i)->GetUniRegNum()) {
			this->database->Get_Person_At_Index(p).GetOwnVehs().erase(this->database->Get_Person_At_Index(p).GetOwnVehs().begin() + i);
			this->database->Get_Vehicle_At_Index(v).DisOwn();
			break;
		}
	}

	std::cout << "Succesfull operation" << std::endl;
}

void Command::Execute_Remove()
{
	//if the database is empty throws exception
	if (this->database->Get_Size_of_Vehicles() == 0 && this->database->Get_Size_of_Persons() == 0) {
		throw std::runtime_error("There is nothing in our database!");
	}

	//helper vars to tell me what is the argument for command REMOVE
	bool per = false;
	bool veh = false;

	//helper vars to tell me their location
	std::size_t p = 0;
	std::size_t v = 0;

	//Checks is the given argument vehicles registration number and gets its location
	for (std::size_t i = 0; i < this->database->Get_Size_of_Vehicles(); i++) {
		if (this->arg1 == this->database->Get_Vehicle_At_Index(i).GetUniRegNum()) veh = true; p = i; break;
	}

	//Chekcs is the given argument Person's id and gets its location
	unsigned int num = stoi(this->arg1);
	for (std::size_t i = 0; i < this->database->Get_Size_of_Persons(); i++) {
		if (num == this->database->Get_Person_At_Index(i).GetUniNum()) per = true; v = i; break;

	}

	//If the both checkers are false then the user has inputed something that it is not in the database and therefore throwing exception
	if (!per && !veh) throw std::invalid_argument("You have entered invalid argument");

	// if there is found Person 
	if (per) {

		//if he doesnt belong cars then we delete him from the database
		if (this->database->Get_Person_At_Index(p).GetOwnVehs().size() == 0) {
			this->database->RemovePerson(p);
		}
		else {
			//asking the user is he sure that he wants to delete person
			bool answer;
			std::cout << "This person has registrated vehicles are you sure (0-1): ";
			std::cin >> answer;

			//if he/she choose no return again for input
			if (!answer) { throw std::runtime_error("You decided not to delete"); }

			//if he/she chooses yes disowning all his cars
			if (answer) {

				for (std::size_t i = 0; i < this->database->Get_Size_of_Vehicles(); i++) {

					if (this->database->Get_Vehicle_At_Index(i).GetOwner().GetUniNum() == this->database->Get_Person_At_Index(p).GetUniNum()) {

						this->database->Get_Vehicle_At_Index(i).DisOwn();

					}
					this->database->RemovePerson(p);
					std::cout << "Succesfull operation" << std::endl;
					break;
				}
			}
		}

	}  //if it is found Vehicle with that id
	if (veh) {

		//If it doesnt belong to anyone delete it from the database
		if (!this->database->Get_Vehicle_At_Index(v).Is_Taken()) {
			this->database->RemoveVehicle(v);
		}
		else {

			//asking the user is he/she sure
			bool answer;
			std::cout << "This vehicle is registrated to a person are you sure (0-1): ";
			std::cin >> answer;

			//if  he/she type no then going back to input
			if (!answer) { std::cin.clear(), std::cin.ignore(10000, '\n'); }

			//if  he/she yes then removing this car from its owner
			if (answer) {

				for (std::size_t i = 0; i < this->database->Get_Vehicle_At_Index(v).GetOwner().GetOwnVehs().size(); i++) {


					if (this->database->Get_Vehicle_At_Index(v).GetUniRegNum() == this->database->Get_Vehicle_At_Index(v).GetOwner().GetOwnVehs().at(i)->GetUniRegNum()) {

						this->database->Get_Vehicle_At_Index(v).GetOwner().GetOwnVehs().erase(this->database->Get_Vehicle_At_Index(v).GetOwner().GetOwnVehs().begin() + i);
						this->database->RemoveVehicle(v);
						std::cout << "Succesfull operator" << std::endl;
						break;
					}

				}


			}
		}

	}

}

void Command::Execute_Show()
{

	//chekcer is used to transform itslef to uppercase as i dont want to change arg1
	std::string checker = this->arg1;
	std::size_t v = 0, p = 0;

	//helper vars to tell me what is the argument for command REMOVE
	bool veh = false;
	bool per = false;

	//chekcs if the chekcer is equal to PEOPLE
	if (str_toupper(checker) == "PEOPLE") {

		std::cout << std::endl;
		std::cout << "There are " << this->database->Get_Size_of_Persons() << " person registrated." << std::endl;

		for (std::size_t i = 0; i < this->database->Get_Size_of_Persons(); i++) {
			
			//displays all the person
			std::cout << this->database->Get_Person_At_Index(i);

		}
		return;
	}

	//chekcs if the chekcer is equal to VEHICLE
	if (str_toupper(checker) == "VEHICLES") {

		std::cout << std::endl;
		std::cout << "There are " << this->database->Get_Size_of_Vehicles() << " vehicles registrated." << std::endl;

		for (std::size_t i = 0; i < this->database->Get_Size_of_Vehicles(); i++) {

			//displaying all the vehicles
			std::cout << this->database->Get_Vehicle_At_Index(i);

		}
		return;
	}

	for (std::size_t i = 0; i < this->database->Get_Size_of_Vehicles(); i++) {
		if (this->arg1 == this->database->Get_Vehicle_At_Index(i).GetUniRegNum()) {
			v = i; veh = true;
		}
	}

	//if there is found vehicle
	if (veh) {
		//print vehicle
		std::cout << this->database->Get_Vehicle_At_Index(v);

		//prints its owner
		std::cout <<"Owner: " <<this->database->Get_Vehicle_At_Index(v).GetOwner();
		return;
	}

	//if not chekcs is there found Person object
	if (!veh) {

		unsigned int owner_id = stoi(this->arg1);
		for (std::size_t i = 0; i < this->database->Get_Size_of_Persons(); i++) {
			if (owner_id == this->database->Get_Person_At_Index(i).GetUniNum()) {
				p = i; per = true;
			}
		}
	}

	//if found Person object
	if (per) {

		std::cout << this->database->Get_Person_At_Index(p);

		for (std::size_t i = 0; i < this->database->Get_Size_of_Vehicles(); i++) {
			if (this->database->Get_Person_At_Index(p).GetUniNum() == this->database->Get_Vehicle_At_Index(i).GetOwner().GetUniNum()) {
				
				std::cout << this->database->Get_Vehicle_At_Index(i);

			}
		}

		
		return;
	}
	
	if (!veh && !per) {
		throw std::invalid_argument("You have entered invalid argument!");
	}


}

void Command::Execute_Save()
{

	//creating the file with the given directory
	std::ofstream data(this->arg1);
	if (!data) {

		//if the dir was wrong throws exception
		throw std::invalid_argument("You have entered wrong directory");
	}

	std::cout << "Save succsefull" << std::endl;
	this->database->SaveText(data);


}

Command::Command(std::string command, std::string args, Database& data_base)
{

	//if command dont eqieals to the commands throws excpetion
	this->command = str_toupper(command);
	std::string person = "PERSON", vehicle = "VEHICLE", acquire = "ACQUIRE", release = "RELEASE", remove = "REMOVE", show = "SHOW", save = "SAVE";


	if (this->command.compare(person)!=0 && this->command.compare(vehicle)!=0 && this->command.compare(acquire)!=0 && this->command.compare(release) &&
		this->command.compare(remove)!=0 && this->command.compare(show)!=0 && this->command .compare(save)!=0) {
		throw std::invalid_argument("You have entered unrecognizable command!");
	}
	
	//pointing to the database whe are ysing
	this->database = &data_base;

	if (this->command == "PERSON") {

		//removing all the white spaces
		Remove_Leading_Whitespaces(args);

		//chekcs if the user printed person's name with quation marsk
		if (Does_Arg_Contains_2_QuotationMarks(args)) { this->arg1 = Get_Argument_within_QuotationMark(args); }

		else { this->arg1 = Get_Other_Argument(args); args.erase(0, arg1.size()); }


		//removing all the white spaces
		Remove_Leading_Whitespaces(args);

		//Gets the other argumet
		this->arg2 = Get_Other_Argument(args);

		//erasint the recently gotten argumetn
		args.erase(0, arg2.size());

		Execute_Person();

	}

	if (this->command == "VEHICLE") {
		
		//removing all the white spaces
		Remove_Leading_Whitespaces(args);

		//Gets the first argumet
		this->arg1 = Get_Other_Argument(args);
		//erasing the recently gotten argument
		args.erase(0, arg1.size());

		//removing all the white spaces
		Remove_Leading_Whitespaces(args);

		//chekcs if the user printed person's name with quation marsk
		if (Does_Arg_Contains_2_QuotationMarks(args)) { this->arg2 = Get_Argument_within_QuotationMark(args); }

		else { this->arg2 = Get_Other_Argument(args); args.erase(0, arg2.size());}
		args.erase(0, arg2.size());

		Execute_Vehicle();

	}

	if (this->command == "ACQUIRE") {

		//removing all the white spaces
		Remove_Leading_Whitespaces(args);
		this->arg1 = Get_Other_Argument(args);
		args.erase(0, arg1.size());

		//removing all the white spaces
		Remove_Leading_Whitespaces(args);
		this->arg2 = Get_Other_Argument(args);
		args.erase(0, arg2.size());

		Execute_Acquire();

	}
	
	if (this->command == "RELEASE") {

		//removing all the white spaces
		Remove_Leading_Whitespaces(args);
		this->arg1 = Get_Other_Argument(args);
		args.erase(0, arg1.size());

		//removing all the white spaces
		Remove_Leading_Whitespaces(args);
		this->arg2 = Get_Other_Argument(args);
		args.erase(0, arg2.size());


		Execute_Release();

	}

	if (this->command == "REMOVE") {

		//removing all the white spaces
		Remove_Leading_Whitespaces(args);
		this->arg1 = Get_Other_Argument(args);
		args.erase(0, arg1.size());

		Execute_Remove();

	}


	if (this->command == "SHOW") {

		//removing all the white spaces
		Remove_Leading_Whitespaces(args);
		this->arg1 = Get_Other_Argument(args);
		args.erase(0, arg1.size());

		Execute_Show();

	}

	if (this->command == "SAVE") {

		//removing all the white spaces
		Remove_Leading_Whitespaces(args);
		this->arg1 = Get_Argument_within_QuotationMark(args);

		Execute_Save();
		
	}


}

std::string& Command::GetCommand()
{
	return this->command;
}

std::string& Command::GetFirstArg()
{
	return this->arg1;
}

std::string& Command::GetSecondArg()
{
	return this->arg2;
}

