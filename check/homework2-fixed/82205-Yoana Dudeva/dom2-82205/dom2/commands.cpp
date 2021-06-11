#include "commands.h"
#include "exceptions.h"

using std::cout;
using std::endl;
using std::cerr; 
using std::cin; 


void getAllArguments(std::string command, std::string& first, std::string& second, std::string& third)
{
	int pos = command.find(" ");
	first = command.substr(0, pos); 
	command = command.substr(pos+1);

	second = getSingleArgument(command); 

	if (!command.empty())
	{
		third = getSingleArgument(command); 
	}

}

std::string getSingleArgument(std::string& command)
{
	int firstQuotation = -1; 
	int lastQuotation = -1; 
	int j = 0; 

	std::string str; 

	if (command.at(0) == '\"')
	{
		firstQuotation = 0; 
		for (int i = 1 ; i < command.size(); ++i)
		{
			if (command.at(i) == '\"')
			{
				lastQuotation = i; 
			}
		}

		if (lastQuotation == -1)
		{
			throw std::invalid_argument("Only one quotation mark\n");
		}

		for (++firstQuotation; firstQuotation < lastQuotation; ++firstQuotation)
		{
			str.push_back(command.at(firstQuotation));
		}

		if (lastQuotation == command.size()-1 || lastQuotation == command.size())
		{
			command = "";
		}
		else
		{
			command = command.substr(lastQuotation+2);
		}
	}
	else
	{
		for (; j < command.size(); ++j)
		{
			if (command.at(j) != ' ')
			{
				str.push_back(command.at(j));
			}
			else
			{
				if (j == command.size()-1)
				{
					command = "";
				}
				else
				{
					command = command.substr(j+1);
				}

				return str; 
			}
		}

		command = "";
		
	}

	return str; 
}

size_t getEmptyRowNumber(std::string fileName)
{
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		throw FileProblem();  
	}

	int linesCounter = 1; size_t emptyRow; 
	while (!file.eof())
	{
		std::string buff;
		getline(file, buff);
		if (buff.empty())
		{
			emptyRow = linesCounter; 
			break; 
		}
		linesCounter++;
	}
	file.close();

	return emptyRow;
}



void Data::copy(const Data& wanted)
{
	this->people = wanted.people; 
	this->vehicles = wanted.vehicles;
}

void Data::clear()
{
	this->people.clear(); 
	this->vehicles.clear(); 
}

bool Data::isItId(std::string str)
{
	for (size_t i = 0; i < str.length(); ++i)
	{
		if (isalpha(str[i]))
		{
			return false;
		}
	}

	return true; 
}

bool Data::isItChar(std::string str)
{
	for (size_t i = 0; i < str.length(); ++i)
	{
		if (!isalpha(str[i]))
		{
			return false;
		}
	}

	return true;
}

int Data::findVehicle(std::string regNumber)
{
	for (int i = 0; i < vehicles.size(); ++i) 
	{
		if (vehicles.at(i).getRegistration().getString() == regNumber) 
		{
			return i;
		}
	}

	return -1;
}

int Data::findPerson(int id)
{
	if (id < 0) 
	{ 
		return -1; 
	}

	for (int i = 0; i < people.size(); ++i) 
	{
		if (people.at(i).getId() == id) 
		{
			return i;
		}
	}

	return -1;
}

Data::Data()
{	
	this->people.clear();
	this->vehicles.clear(); 
}

Data::Data(const Data& other)
{
	copy(other); 
}

Data::Data(std::string fileName)
{
	this->people = Data::readPeople(fileName);
    this->vehicles = Data::readVehicles(fileName);
}

std::vector<Person> Data::readPeople(std::string fileName)
{
	std::ifstream f(fileName, std::ios::in);
	std::vector<Person> people; 

	if (!f.is_open())
	{
		throw FileProblem();
	}

	int line = 1;  
	int count  = getEmptyRowNumber(fileName); 
	std::string row; 
	while (getline(f, row))
	{
		if (line > count)
		{
			Person temp = readPerson(row);
			people.push_back(temp); 
			cout<<"Person is being read from file..."<<endl;
		}	
		line++;
	}
	f.close();

	return people; 
}

Person Data::readPerson(std::string line)
{
	int i = 0;

	//Extract name
	std::string tempName; 
	while(line[i] != ',')
	{
		tempName.push_back(line[i]);
		++i; 
	}
	++i; 
	
	//Extract id
	std::string tempID; 
	while(line[i] != ',')
	{
		tempID.push_back(line[i]);
		++i; 
	}	
	
	std::vector<std::string> tempVehicleArray;

	//Get the person's vehicles into a vector
	while(line[i] != '\0')
	{
		++i; 

		//If person has no cars
		if (line[i] == '\0')
		{
			break; 
		}

		//Extract registration
		std::string tempReg; 
		while(line[i] != ',' && line[i] != '\0')
		{
			tempReg.push_back(line[i]);
			++i; 
		}

		//Add vehicle to the array
		tempVehicleArray.push_back(tempReg);
	}

	//Create the person and add it to the vector 
	Person tempPerson(tempName, stoi(tempID), tempVehicleArray); 
	
	return tempPerson; 
	
}

std::vector<Vehicle> Data::readVehicles(std::string fileName)
{
	std::ifstream f(fileName, std::ios::in);
	std::vector<Vehicle> vehicles; 

	if (!f.is_open())
	{
		throw FileProblem(); 
	}

	int line = 1;  
	std::string row; 
	while (getline(f, row))
	{
		if (row.empty())
		{
			break;
		}
		Vehicle temp = readVehicle(row); 	
		vehicles.push_back(temp); 
		cout<<"A vehicle is being read..."<<endl;	
		
		line++;
	}
	f.close();

	return vehicles; 
} 

Vehicle Data::readVehicle(std::string line)
{
	int i = 0;

	//Extract registration
	std::string tempName; 
	while(line[i] != ',')
	{
		tempName.push_back(line[i]);
		++i; 
	}
	Registration tempRegistration(tempName);
	++i; 
	
	//Extract description
	std::string tempDesc; 
	while(line[i] != ',')
	{
		tempDesc.push_back(line[i]);
		++i; 
	}
	++i;

	//If there is no owner
	if (line[i] == '\0')
	{
		Vehicle tempVehicle(tempRegistration, tempDesc); 
		return tempVehicle; 
	}
	
	//Extract name of owner
	std::string tempOwner; 
	while(line[i] != '-')
	{
		tempOwner.push_back(line[i]);
		++i; 
	}
	++i; 

	//Extract id of owner
	std::string tempID; 
	while(line[i] != '\0')
	{
		tempID.push_back(line[i]);
		++i; 
	}

	Vehicle tempVehicle(tempRegistration, tempDesc, stoi(tempID));

	return tempVehicle; 
	
}

void Data::addVehicle(const Registration &reg, const std::string &desc)
{
	if (findVehicle(reg.getString()) >= 0) {
		cout<<"This vehicle exists!"<<endl;
		return; 
	}

	Vehicle newVehicle(reg, desc);

	this->vehicles.push_back(newVehicle); 

}

void Data::addPerson(const std::string &name, const unsigned int id)
{
	if (findPerson(id) >= 0) {
		cout<<"This person exists!"<<endl;
		return; 
	}

	Person newPerson(name, id); 

	this->people.push_back(newPerson); 
}

void Data::release(unsigned int id, const Registration &reg)
{
	int indexVehicle = findVehicle(reg.getString());

	if (indexVehicle >= 0) 
	{
		int indexPerson = findPerson(id);

		this->vehicles[indexVehicle].eraseOwner();
		this->people[indexPerson].eraseVehicle(vehicles[indexVehicle]);
	}
}

void Data::acquire(unsigned int id, const Registration &reg)
{
	//Find vehicle in array
	int vehicleIndex = findVehicle(reg.getString());

	if (vehicleIndex >= 0) 
	{
		Vehicle wantedVehicle(this->vehicles[vehicleIndex]);

		if (wantedVehicle.isThereAnOwner())
		{
			release(wantedVehicle.getOwnerID(), reg); 
		}

		//Find person in array
		int personIndex = findPerson(id);

		if (personIndex >= 0) 
		{
			Person wantedPerson(this->people[personIndex]); 
			this->people[personIndex].insertVehicle(wantedVehicle);

			//Insert the person as an owner of the vehicle
			this->vehicles[vehicleIndex].insertOwner(wantedPerson);
		}
	}
}

void Data::remove(const std::string &what)
{
	if (what.empty())
	{
		cout<<"There is nothing to remove"<<endl;
		return; 
	}
	
	if (isItId(what))
	{
		unsigned int tempId = stoi(what); 
		int personIndex = findPerson(tempId);

		if (personIndex < 0) 
		{
			cout<<"Could not find that person!"<<endl;
			return;
		}

		Person wantedPerson(people[personIndex]);

		//If the person has vehicles
		if (wantedPerson.getOwnedVehiclesCount() > 0)
		{
			std::string choice; 
			cout<<"Are you sure you want to remove this person?"<<endl<<"Please, write (yes/no): ";
			cin>>choice; 
			
			for (size_t i = 0; i < choice.length(); ++i)
			{
				tolower(choice[i]); 
			}

			//Return if the input is "no" or wrong
			if (choice.compare("no") == 0)
			{
				return; 
			}
			else if (choice.compare("yes") != 0)
			{
				cout<<"Wrong input";
				return;  
			}
		}

		//Release all vehicles
		for (size_t i = 0; i < wantedPerson.getOwnedVehiclesCount(); ++i)
		{
			release(wantedPerson.getId(), wantedPerson.getElement(i));
		}
		
		this->people.erase(this->people.begin()+personIndex); 

		cout<<"Person is removed!"<<endl;
	}
	else if (Registration::validation(what))
	{
		Registration tempReg(what);

		//Find the vehicle in the array
		int vehicleIndex = findVehicle(what);
		if (vehicleIndex >= 0) {
			Vehicle wantedVehicle(this->vehicles[vehicleIndex]);

			//If the vehicle has an owner
			if (wantedVehicle.isThereAnOwner())
			{
				std::string choice; 
				cout<<"Are you sure you want to remove this vehicle?"<<endl<<"Please, write (yes/no): ";
				cin>>choice; 
				
				for (size_t i = 0; i < choice.length(); ++i)
				{
					tolower(choice[i]); 
				}

				//Return if the input is "no" or wrong
				if (choice.compare("no") == 0)
				{
					return; 
				}
				else if (choice.compare("yes") != 0)
				{
					cout<<"Wrong input";
					return;  
				}

				release(wantedVehicle.getOwnerID(), wantedVehicle.getRegistration());
			}

			this->vehicles.erase(this->vehicles.begin()+vehicleIndex); 

			cout<<"Vehicle is removed!"<<endl;
		}
	}
	else 
	{
		cout<<"You did not enter a valid id or registration!"<<endl;
	}
}

void Data::show(std::string &what)
{
	if (what.empty())
	{
		cout<<"There is nothing to show"<<endl;
		return; 
	}
	
	cout<<endl; 

	if (isItId(what)) 
	{
		int tempId = stoi(what);
		int personIndex = findPerson(tempId);

		if (personIndex >= 0) 
		{
			cout<<"Wanted person: "<<endl;
			cout<<"Name: "<<people[personIndex].getName()<<" ID: "<<people[personIndex].getId()<<endl;
			for (size_t j = 0; j < vehicles.size(); ++j) 
			{
				if (vehicles[j].getOwnerID() == tempId) 
				{
					cout<<"Owned vehicles:"<<endl;
					cout<<"Registration: "<<vehicles[j].getRegistration().getString()
						<<" Description: "<<vehicles[j].getDescription()<<endl;
				}
			}
			cout<<endl;
		}
	}
	else if (Registration::validation(what)) 
	{	
		int vehicleIndex = findVehicle(what);
		if (vehicleIndex >= 0) 
		{
			cout<<"Wanted vehicle:"<<endl;
			cout<< "Registration: "<< vehicles[vehicleIndex].getRegistration().getString()
				<< " Description: " << vehicles[vehicleIndex].getDescription() << endl;

			int personIndex = findPerson(vehicles[vehicleIndex].getOwnerID());
			if (personIndex >= 0) {
				cout<<"Owner of vehicle:"<<endl;
				cout<< "Name: " << people[personIndex].getName()
					<< " ID: " << people[personIndex].getId() << endl << endl;
			}
		}
	}
	else if (isItChar(what))
	{
		for (size_t i = 0; i < what.size(); ++i) 
		{
			what[i] = tolower(what[i]);
		}

		if (what == "people") 
		{
			cout<<"People:"<<endl<<"----------------------"<<endl;
			for (size_t i = 0; i < this->people.size(); ++i)
			{
				cout<<this->people[i].getName()<<" / "<<this->people[i].getId()<<" / "<<this->people[i].getOwnedVehiclesCount()<<endl;
			}
			cout<<endl;
		}
		else if (what == "vehicles") 
		{
			cout<<"Vehicles:"<<endl<<"----------------------"<<endl;
			for (size_t i = 0; i < this->vehicles.size(); ++i)
			{
				cout<<this->vehicles[i].getRegistration().getString()
				<<" / "<<this->vehicles[i].getDescription()<<" / "<<this->vehicles[i].isThereAnOwner()<<endl;
			}
			cout<<endl;
		}
		else
		{
			cout<<"Invalid input"<<endl;
		}
		
	}	
	else 
	{
		cout<<"Invalid input"<<endl;
	}		
		
}

void Data::saveToFile(std::string &fileName)
{
	std::ofstream out(fileName, std::ios::trunc);

	if (!out.is_open()) 
	{
		throw FileProblem();
	}

	for (size_t i = 0; i < vehicles.size(); ++i) 
	{
		out<<vehicles[i].getRegistration().getString()<<','<<vehicles[i].getDescription()<<',';

		if (vehicles[i].isThereAnOwner()) 
		{
			for (size_t j = 0; j < people.size(); ++j) 
			{
				if (people[j].getId() == vehicles[i].getOwnerID()) 
				{
					out<<people[j].getName()<<'-'<<people[j].getId();
				}
			}
		}

		out<<endl;
	}
	
	out<<endl;

	for (size_t i = 0; i < people.size(); ++i) 
	{
		out<<people[i].getName()<<','<<people[i].getId()<<',';

		for (size_t j = 0; j < people[i].getOwnedVehiclesCount(); ++j) 
		{
			out<<people[i].getElement(j)<<',';
		}

		out<<endl;
	}
}

Person Data::getPersonAt(unsigned int index)
{
	return people[index];
}

Vehicle Data::getVehicleAt(unsigned int index)
{
	return vehicles[index];
}

size_t Data::getPeopleSize() const
{
	return this->people.size();
}

size_t Data::getVehicleSize() const
{
	return this->vehicles.size();
}


Data& Data::operator=(const Data& other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}

	return *this; 
}

Data::~Data()
{
	
}
