#include "Homework2.h"

//Registration
bool Registration::validate()
{
	try
	{
		size_t length = 0; //length of the regional code
		//measuring it
		for (unsigned int i = 0; i < 8; i++)
		{
			if (isalpha(registration[i]))
			{
				length++;
			}
			else
			{
				break;
			}
		}

		if(length == 0 || length > 2) //if its length is not 1 or 2, its invalid
		{
			throw std::invalid_argument("Invalid regional code");
		}

		for (int i = length; i < length + 4; i++) //starting after the regional code the next 4 chars must be digits
		{
			if (!isdigit(registration[i]))
			{
				throw std::invalid_argument("Invalid serial number");
			}
		}
		
		for (unsigned int i = length + 4; i < length + 6; i++) //last 2 chars must be letters
		{
			if (!isalpha(registration[i]))
			{
				throw std::invalid_argument("Invalid serial number");
			}
		}
	}
	catch (const std::invalid_argument& ia)
	{
		std::cerr << "Invalid registration: " << ia.what() << std::endl;
		return false;
	}
	return true;
}

Registration::Registration(const std::string registration) : registration(registration)
{	
}

std::string Registration::getRegistration()
{
	return registration;
}

//Person

Person::Person(const std::string name, unsigned int idNum) : name(name), idNum(idNum)
{
}

void Person::addVehicle(Vehicle& vehicle) 
{
	vehicles.push_back(vehicle.getRegistration());
}

void Person::removeVehicle(Vehicle& vehicle)
{
	for (unsigned int i = 0; i < vehiclesCount(); i++)
	{
		if (vehicles[i] == vehicle.getRegistration())
		{
			vehicles.erase(vehicles.begin() + i);
		}
	}
}

size_t Person::vehiclesCount()
{
	return vehicles.size();
}

std::string Person::getName()
{
	return name;
}

unsigned int Person::getID()
{
	return idNum;
}

std::string Person::getVehicleAt(std::size_t pos)
{
	return vehicles[pos];
}

//Vehicle

bool Vehicle::hasOwner()
{
	if (owner != nullptr)
	{
		return true;
	}
	return false;
}

Vehicle::Vehicle(const std::string registration, const std::string description) : registration(registration), description(description)
{
	owner = nullptr;
}

void Vehicle::setOwner(Person& person)
{
	owner = &person;	
}

void Vehicle::removeOwner(Person& person)
{
	if (hasOwner())
	{
		owner = nullptr;
	}
	else
	{
		throw std::runtime_error("This vehicle does not yet have an owner.");
	}
}

Person& Vehicle::getOwner()
{
	//handling null case with exception, anywhere I look for a given vehicle's owner, I check if hasOwner(), so i have something to return.
	try
	{
		if (hasOwner())
		{
			return *owner;
		}
		else
		{
			throw std::runtime_error("This vehicle does not have an owner.");
		}
	}
	catch (const std::runtime_error& ra)
	{
		std::cerr << "Runtime error: " << ra.what() << std::endl;
	}
}

std::string Vehicle::getRegistration()
{
	return registration.getRegistration();
}

std::string Vehicle::getDescription()
{
	return description;
}

//PersonDatabase

PersonDatabase::PersonDatabase()
{
}

bool PersonDatabase::validate(Person person)
{
	try {
		for (unsigned int i = 0; i < personArray.size(); i++)
		{
			if (personArray[i].getID() == person.getID())
			{
				throw std::runtime_error("A person with the same ID Number already exists in the database.");
			}
		}
	}
	catch (std::runtime_error& ra)
	{
		std::cerr << "Runtime error: " << ra.what() << std::endl;
		return false;
	}
	return true;
}

size_t PersonDatabase::size()
{
	return personArray.size();
}

Person& PersonDatabase::at(size_t pos)
{
	//not throwing exceptions for the at functions since I only use them to access elements within the given database's size.
	return personArray[pos];
}

void PersonDatabase::insert(Person& person)
{
	if (validate(person) == true)
	{
		personArray.push_back(person);   
	}
}

void PersonDatabase::erase(Person& person)
{
	for (unsigned int i = 0; i < personArray.size(); i++)
	{
		if (personArray[i].getID() == person.getID())
		{
			personArray.erase(personArray.begin()+i);
		}
	}
}

void PersonDatabase::print()
{
	for (unsigned int i = 0; i < personArray.size(); i++)
	{
		std::cout << personArray[i].getName() << " " << personArray[i].getID() << std::endl;
	}
}

//VehicleDatabase

VehicleDatabase::VehicleDatabase()
{
}

bool VehicleDatabase::validate(Vehicle vehicle)
{
	try {
		for (unsigned int i = 0; i < vehicleArray.size(); i++)
		{
			if (vehicleArray[i].getRegistration() == vehicle.getRegistration())
			{
				throw std::runtime_error("A vehicle with the same registration already exists.");
			}
		}
	}
	catch (std::runtime_error& ra) 
	{
		std::cerr << "Runtime error: " << ra.what() << std::endl;
		return false;
	}
	return true;
}

size_t VehicleDatabase::size()
{
	return vehicleArray.size();
}

Vehicle& VehicleDatabase::at(size_t pos)
{
	return vehicleArray[pos];
}

void VehicleDatabase::insert(Vehicle& vehicle)
{
	if (validate(vehicle) == true)
	{
		vehicleArray.push_back(vehicle);
	}
}

void VehicleDatabase::erase(Vehicle& vehicle)
{
	for (unsigned int i = 0; i < vehicleArray.size(); i++)
	{
		if (vehicleArray[i].getRegistration() == vehicle.getRegistration())
		{
			vehicleArray.erase(vehicleArray.begin() + i);
		}
	}
}

void VehicleDatabase::print()
{
	for (unsigned int i = 0; i < vehicleArray.size(); i++)
	{
		std::cout << vehicleArray[i].getRegistration() << " " << vehicleArray[i].getDescription() << std::endl;
	}
}

//Command

Command::Command(PersonDatabase& pd, VehicleDatabase& vd, std::string commandInfo) : pd(pd), vd(vd)
{
	//separating the command type and each argument
	std::string word;
	for (unsigned int i = 0; i < commandInfo.size(); i++)
	{
		if (commandInfo[i] == '"') //The beginning of an argument separated with one or more white-spaces
		{                     
			for (unsigned int j = i+1; j < commandInfo.size(); j++) //Read from i+1
			{
				if (commandInfo[j] != '"')
				{
					word += commandInfo[j];
				}
				else {
					command.push_back(word);
					word.clear();
					i = j+2;   //jumping to a non-whitespace character since we already added the word
					break;
				}
			}
		}
		if (!isspace(commandInfo[i]))
		{
			word += commandInfo[i];
		}
		else {
			command.push_back(word);
			word.clear();
		}
	}
	command.push_back(word);
}

std::string Command::getArgumentAt(size_t pos)
{
	return command[pos];
}

bool Command::existsInPD(unsigned int id)
{
	for (unsigned int i = 0; i < pd.size(); i++)
	{
		if (pd.at(i).getID() == id)
		{
			return true;
		}
	}
	return false;
}

bool Command::existsInVD(std::string registration)
{
	for (unsigned int i = 0; i < vd.size(); i++)
	{
		if (vd.at(i).getRegistration() == registration)
		{
			return true;
		}
	}
	return false;
}

Person& Command::findByID(unsigned int id)
{
	//throwing exception and using the existsInDB functions any time i want to use the findByX functions, to make sure they return something.
	try 
	{
		for (unsigned int i = 0; i < pd.size(); i++)
		{
			if (pd.at(i).getID() == id)
			{
				return pd.at(i);
			}
		}
		throw std::runtime_error("The given ID could not be found in the database");
	}
	catch (const std::runtime_error& re)
	{
		std::cerr << "Runtime error: " << re.what() << std::endl;
	}
	
}

Vehicle& Command::findByReg(std::string registration)
{
	try
	{
		for (unsigned int i = 0; i < vd.size(); i++)
		{
			if (vd.at(i).getRegistration() == registration)
			{
				return vd.at(i);
			}
		}
		throw std::runtime_error("Could not find the given vehicle in the database");
	}
	catch (const std::runtime_error& re)
	{
		std::cerr << "Runtime error: " << re.what() << std::endl;
	}
}

    //Validation
bool Command::validateCommandType()
{
    try
    {
	    if (!_stricmp(command[0].c_str(), "vehicle") || !_stricmp(command[0].c_str(), "person") || !_stricmp(command[0].c_str(), "acquire") ||
		    !_stricmp(command[0].c_str(), "release") || !_stricmp(command[0].c_str(), "remove") || !_stricmp(command[0].c_str(), "save") ||
		    !_stricmp(command[0].c_str(), "show"))
	    {
		    return true;
	    }
	    else
	    {
		    throw std::invalid_argument("Invalid command type");
	    }
    }
    catch (std::invalid_argument& ia)
    {
		std::cerr << ia.what();
	    return false;
    }
}

bool Command::validateArguments()
{
	if (validateCommandType())
	{
		//checking if the arguments are valid for the given command
		try
		{
			if (!_stricmp(command[0].c_str(), "vehicle"))
			{
				//If the user tries to create a vehicle, its registration has to be valid
				Registration toValidate(command[1]);
				if (!toValidate.validate())
				{
					throw std::invalid_argument("registration");
				}
				//If the registration is valid, it has to not be a duplicate
				if (!canInsertV(command[1]))
				{
					throw(command);
				}
			}

			if (!_stricmp(command[0].c_str(), "person"))
			{
				//If the user tries to create a person, his idNum has to be an integer value
				for (unsigned int i = 0; i < command[2].size(); i++)
				{
					if (!isdigit(command[2][i]))
					{
						throw std::invalid_argument("Invalid id");
					}
				}
				//If the idNum is valid, it has to not be a duplicate
				if (!canInsertP(stoi(command[2])))
				{
					throw std::invalid_argument("This person is already in the database");
				}
			}

			if (!_stricmp(command[0].c_str(), "acquire"))
			{
				if (!canAcquire(stoi(command[1]), command[2]))
				{
					throw std::invalid_argument("This person cannot acquire this vehicle");
				}
			}

			if (!_stricmp(command[0].c_str(), "release"))
			{
				if (!canRelease(stoi(command[1]), command[2]))
				{
					throw std::invalid_argument("This person does not own this vehicle, or one/both of them do not exist in the database.");
				}
			}

			if (!_stricmp(command[0].c_str(), "remove"))
			{
				if (!canRemove(command[1]))
				{
					throw std::invalid_argument("This person/vehicle does not exist in the database");
				}
			}

			if (!_stricmp(command[0].c_str(), "save"))
			{
				if (!validateSavePath(command[1]))
				{
					throw std::runtime_error("Could not open file");
				}
			}

			if (!_stricmp(command[0].c_str(), "show"))
			{
				if (!canShow(command))
				{
					throw std::invalid_argument("Invalid arguments for given command, or this person/vehicle does not exist in the database");
				}
			}
		}
		catch (std::invalid_argument& ia)
		{
			std::cerr << "Invalid argument: " << ia.what() << std::endl;
			return false;
		}
		catch (std::runtime_error& re)
		{
			std::cerr << re.what() << std::endl;
			return false;
		}
	}
	return true;
}

bool Command::canInsertP(unsigned int id)
{
	Person toInsert("someone", id); //test person with given id num
	if (!pd.validate(toInsert))
	{
		return false;
	}
	return true;
}

bool Command::canInsertV(std::string registration)
{
	Vehicle toInsert(registration, "vehicle"); //test vehicle with given registration
	if (!vd.validate(toInsert))
	{
		return false;
	}
	return true;
}

bool Command::canAcquire(unsigned int id, std::string registration)
{
	//checking if the vehicle exists in the database
	for (unsigned int i = 0; i < vd.size(); i++)
	{
		if (vd.at(i).getRegistration() == registration)
		{
			break; //If it's in the database then it can't be a duplicate since insertion prompts validation
		}
		if (i == vd.size() - 1)
		{
			return false;
		}
	}

	//checking if the person exists in the database
	for (unsigned int i = 0; i < pd.size(); i++)
	{
		if (pd.at(i).getID() == id)
		{
			break; 
		}
		if (i == pd.size() - 1)
		{
			return false;
		}
	}

	//checking if the relationship is already set
	if (findByReg(registration).hasOwner())
	{
		if (findByReg(registration).getOwner().getID() == id)
		{
			return false;
		}
	}
	return true;
}

bool Command::canRelease(unsigned int id, std::string registration)
{
	//checking if the vehicle exists in the database
	for (unsigned int i = 0; i < vd.size(); i++)
	{
		if (vd.at(i).getRegistration() == registration)
		{
			break; 
		}
		if (i == vd.size() - 1)
		{
			return false;
		}
	}

	//checking if the person exists in the database
	for (unsigned int i = 0; i < pd.size(); i++)
	{
		if (pd.at(i).getID() == id)
		{
			break;
		}
		if (i == pd.size() - 1)
		{
			return false;
		}
	}

	//checking if the owner/vehicle relationship exists between given arguments
	for (unsigned int i = 0; i < findByID(id).vehiclesCount(); i++)
	{
		if (findByID(id).getVehicleAt(i) == registration)
		{
			return true;
		}
	}
	return false;
}

bool Command::canRemove(std::string argument)
{
	//Checking if the arguement is an idNum, or a registration
	bool isNum = true;
	for (unsigned int i = 0; i < argument.size(); i++)
	{
		if (!isdigit(argument[i]))
		{
			isNum = false;
		}
	}

	//Checking if the registration exists
	if (isNum == false)
	{
		for (unsigned int i = 0; i < vd.size(); i++)
		{
			if (vd.at(i).getRegistration() == argument)
			{
				return true;
			}
		}
	}

	//Checking if the idNum exists
	if (isNum == true)
	{
		for (unsigned int i = 0; i < pd.size(); i++)
		{
			if (pd.at(i).getID() == stoi(argument))
			{
				return true;
			}
		}
	}
	return false;
}

bool Command::validateSavePath(std::string path)
{
	std::ofstream file2;
	file2.open(path.c_str());
	if (!file2)
	{
		return false;
	}
	return true;
}

bool Command::canShow(std::vector<std::string> command)
{
	//Checking if atleast one of the given arguments is incompatible (!canRemove checks if an <id>-type arguement exists in the database).
	for (unsigned int i = 1; i < command.size(); i++)
	{
		if (_stricmp(command[i].c_str(), "people") && _stricmp(command[i].c_str(), "vehicles") && !canRemove(command[i]))
		{
			return false;
		}
	}
	return true;
}

    //Execution
void Command::execute()
{
	if (!_stricmp(command[0].c_str(), "vehicle"))
	{
		insertV(command[1], command[2]);
	}
	if (!_stricmp(command[0].c_str(), "person"))
	{
		insertP(command[1], stoi(command[2]));
	}
	if (!_stricmp(command[0].c_str(), "acquire"))
	{
		acquire(stoi(command[1]), command[2]);
	}
	if (!_stricmp(command[0].c_str(), "release"))
	{
		release(stoi(command[1]), command[2]);
	}
	if (!_stricmp(command[0].c_str(), "remove"))
	{
		remove(command[1]);
	}
	if (!_stricmp(command[0].c_str(), "save"))
	{
		save(command[1]);
	}
	if (!_stricmp(command[0].c_str(), "show"))
	{
		show(command);
	}

	

}

void Command::insertP(std::string name, unsigned int id)
{
	if (validateCommandType() && validateArguments())
	{
		Person toInsert(name, id);
		pd.insert(toInsert);
	}
}

void Command::insertV(std::string registration, std::string description)
{
	if (validateCommandType() && validateArguments())
	{
		Vehicle toInsert(registration, description);
		vd.insert(toInsert);
	}
}

void Command::acquire(unsigned int id, std::string registration)
{
	if (validateCommandType() && validateArguments())
	{
		if (findByReg(registration).hasOwner())
		{
			//removing the current owner
			release(findByReg(registration).getOwner().getID(), registration);
		}

		findByID(id).addVehicle(findByReg(registration));
		findByReg(registration).setOwner(findByID(id));
	}
}

void Command::release(unsigned int id, std::string registration)
{
	if (validateCommandType() && validateArguments())
	{
		findByID(id).removeVehicle(findByReg(registration));
		findByReg(registration).removeOwner(findByID(id));
	}
}

void Command::remove(std::string argument)
{	
	if (validateCommandType() && validateArguments())
	{
		//checking if the argument is an idNum or a registration
		if (isalpha(argument[0]))
		{
			//it's a registration, removing the corresponding vehicle from the db
			vd.erase(findByReg(argument));
		}
		else
		{
			//it's an id, removing the corresponding person from the db
			pd.erase(findByID(stoi(argument)));
		}
	}
}

void Command::save(std::string path)
{
	if (validateCommandType() && validateArguments())
	{
		std::ofstream file2;
		file2.open(path); //validation has tested if the output file can be opened

		//writing the databases to the file
		for (unsigned int i = 0; i < pd.size(); i++)
		{
			file2 << "PERSON" << " " << '"' << pd.at(i).getName() << '"' << " " << pd.at(i).getID() << std::endl;
		}

		for (unsigned int i = 0; i < vd.size(); i++)
		{
			file2 << "VEHICLE" << " " << vd.at(i).getRegistration() << " " << vd.at(i).getDescription() << std::endl;
		}

		//writing all owner/vehicle relationships set with acquire
		for (unsigned int i = 0; i < pd.size(); i++)
		{
			for (unsigned int j = 0; j < pd.at(i).vehiclesCount(); i++)
			{
				file2 << "ACQUIRE" << " " << pd.at(i).getID() << " " << pd.at(i).getVehicleAt(i) << std::endl;
			}
		}
		file2.close();
	}
}

void Command::show(std::vector<std::string> arguments)
{
	if (validateCommandType() && validateArguments())
	{
		for (unsigned int i = 1; i < arguments.size(); i++)
		{
			if (!_stricmp(arguments[i].c_str(), "people"))
			{
				pd.print();
			}
			if (!_stricmp(arguments[i].c_str(), "vehicles"))
			{
				vd.print();
			}
			if (canRemove(arguments[i]))
			{
				if (isalpha(arguments[i][0])) //its a registration
				{
					Vehicle toShow = findByReg(arguments[i]); //copying the vehicle here so i dont have to look for it again
					//attempting to show the vehicle's owner
					if (toShow.hasOwner())
					{
						std::cout << "The owner of this vehicle and his id number: " << std::endl;
						std::cout << toShow.getOwner().getName() << " " << toShow.getOwner().getID() << std::endl;
					}
					else
					{
						std::cout << "This vehicle does not have an owner.";
					}
				}
				else //its an idNum
				{
					Person toShow = findByID(stoi(arguments[i])); 
					//showing the person's vehicles
					std::cout << "The vehicles this person owns: " << std::endl;
					for (unsigned int j = 0; j < toShow.vehiclesCount(); j++)
					{
						std::cout << toShow.getVehicleAt(j) << " " << findByReg(toShow.getVehicleAt(j)).getDescription() << std::endl;
					}
				}
			}

		}
	}
}

//non-class functions
void readFromFile(VehicleDatabase& vd, PersonDatabase& pd)
{
	std::string source;
	std::ifstream file1;

	do {
		std::cout << "Enter file location: " << std::endl;
		std::cin >> source;
		file1.open(source);
		if (!file1)
		{
			std::cout << "Could not open file" << std::endl;
		}
	} while (!file1);

	std::string line;
	std::vector<std::string> fileText;

	//storing all the lines in the file in a vector (asuming each line is information for a separate vehicle/person)
	while (getline(file1, line))
	{
		fileText.push_back(line);
	}
	file1.close();

	std::string Word; //temp for each "word" in each line
	std::vector<std::string> Info; //temp vector to store those words (resets after each line is read and interpreted)


	//Reading the file line by line
	for (unsigned int i = 0; i < fileText.size(); i++)
	{
		//Reading every line word by word
		for (unsigned int j = 0; j < fileText[i].size(); j++)
		{
			if (fileText[i][j] == '"') //similar to the check in the constructor with arguements in the command class
			{
				for (unsigned int k = j + 1; k < fileText[i].size(); k++)
				{
					if (fileText[i][k] != '"')
					{
						Word += fileText[i][k];
					}
					else {
						Info.push_back(Word);
						Word.clear();
						j = k+2; //sends us to the next character thats not a white-space
						break;
					}
				}
			}
			
			if (!isspace(fileText[i][j]))
			{
				Word += fileText[i][j];
			}
			else //If we reached a white-space(in a word not wrapped in quotations), add the current word to the vector and clear the word string
			{
				Info.push_back(Word);
				Word.clear();
			}
		}
		//Adding the last word
		Info.push_back(Word);
		Word.clear();

		//Reading the line vector
		if (Info[0][0] == 'p' || Info[0][0] == 'P') //If its information for a person (case insensitve)
		{
			const std::string name = Info[1];
			unsigned int idNum = stoi(Info[2]);
			Person toInsert(name, idNum); //Creating an object from the file information
			pd.insert(toInsert); //inserting it	
		}
		if (Info[0][0] == 'v' || Info[0][0] == 'V') //same for vehicle
		{
			const std::string registration = Info[1];
			const std::string description = Info[2];
			Vehicle toInsert(registration, description);
			vd.insert(toInsert);	
		}

		Info.clear();
	}
}
