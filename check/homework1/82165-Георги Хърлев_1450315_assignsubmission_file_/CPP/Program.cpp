#include <iostream>
#include<limits>//used to get numeric_limits
#include "Program.h"

using std::cin;
using std::cout;
using std::endl;


Program::Program()
{
	cout << "Creating a garage. Please, enter the capacity of parking places for your new garage:\n";
	size_t capacity = inputSizeT();
	garage = Garage(capacity);
	cout << "\nGarage with capacity of " << capacity << " was created .\n";
}

Program::Program(size_t capacityGarage) {
	garage = Garage(capacityGarage);
}

Program::~Program()
{
	deleteAllVehicles();
	delete[] cars;
	cars = nullptr;
	unparkedCapacity = 0;
	garage.clear();
	unparkedCarsNum = 0;
}


size_t Program::getUnparkedCarsNum() const {
	return unparkedCarsNum;
}
size_t Program::getUnparkedCarsCapacity() const {
	return unparkedCapacity;
}

const Vehicle& Program::getGarageVehAt(size_t index) const {
	return garage[index];
}


void Program::fix_input()
{
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool Program::input_isStrBiggerOrEqual(const char* bigger, const char* smaller)
{
	if (strlen(bigger) != strlen(smaller))
	{
		return (strlen(bigger) > strlen(smaller));
	}
	short br = 0;
	while (bigger[br] != '\0')
	{
		if (smaller[br] > bigger[br])
		{
			return false;
		}
		else if (bigger[br] > smaller[br])
		{
			return true;
		}
		br++;
	}
	return true; //equal
}

size_t Program::input_convertToNum(char str[])
{
	size_t ans = 0;
	short br = 0;
	while (str[br] != '\0')
	{
		ans = ans * 10 + str[br] - '0';
		br++;
	}
	return ans;
}

bool Program::input_isValidNum(char str[])
{
	short br = 0;
	while (str[br] != '\0') //check it it's an valid positive number
	{
		if (str[br] < '0' || str[br]>'9')
		{
			cout << "Please, enter a correct positive number :\n";
			return false;
		}
		br++;
	}
	//check if the number isn't too big for size_t
	if (std::numeric_limits<size_t>::max() == std::numeric_limits<unsigned long long>::max()) {
		const char ULONGMAX[] = "18446744073709551615";
		if (!input_isStrBiggerOrEqual(ULONGMAX, str)) //bigger than Unsinged long long
		{
			cout << "Please, enter smaller number :\n";
			return false;
		}
	}
	else if (std::numeric_limits<size_t>::max() == std::numeric_limits<unsigned int>::max()) {
		const char UINTMAX[] = "4294967295";
		if (!input_isStrBiggerOrEqual(UINTMAX, str)) //bigger than Unsinged long long
		{
			cout << "Please, enter smaller number :\n";
			return false;
		}
	}
	return true;
}

size_t Program::inputSizeT(bool zeroCheck)
{
	char ans[30] = {};
	bool isValid = false;
	do {
		isValid = true;
		try {
			cin >> ans;
		}
		catch (std::exception& e)
		{
			cout << "Please , input a valid number:";
			isValid = false;
			continue;
		}
		if (zeroCheck && strcmp(ans,"0")==0)
		{
			isValid = false;
			cout << "\nValue can not be zero. Input a greater value:";
			continue;
		}

		isValid = input_isValidNum(ans); //will print error msg if something is not right

	} while (!isValid);


	return input_convertToNum(ans);
}


short Program::getOptionInterface()
{
	short ans;
	const short numOfPossibilities = 9;

	cout << "\nChoose your next step .\n";
	cout << "1.Create a new vehicle.\n";
	cout << "2.Add an existing vehicle to the garage.\n";
	cout << "3.Both create and then add the vehicle to the garage.\n";
	cout << "4.Remove vehicle from the garage.\n";
	cout << "5.Destroy vehicle.\n"; //will remove it from the garage as well
	cout << "6.Display garage's cars.\n";
	cout << "7.Display created cars.\n";
	cout << "8.Display cars that are not in the garage.\n";
	cout << "9.End Program.\n";
	//cout << "9.I feel lucky , tell me a joke!\n";

	do {
		cout << "\nEnter you choice:";
		cin >> ans;
		if (!cin)
		{
			fix_input();
			cout << "Please , choose a valid option from 1 to " << numOfPossibilities << endl;
			ans = 0;
		}
		else if (ans <= 0 || ans > numOfPossibilities) {
			cout << "Please , choose a valid option from 1 to " << numOfPossibilities << endl;
		}

	} while (!(ans >= 1 && ans <= numOfPossibilities));

	return ans;
}

bool Program::expandCarsStorage(unsigned num)
{
	Vehicle** newCars;
	try {
		newCars = new Vehicle * [unparkedCapacity + num];
	}
	catch (std::exception& e)
	{
		return false;
	}
	for (size_t i = 0; i < unparkedCarsNum; i++)
	{
		newCars[i] = cars[i];
	}
	delete[] cars;
	cars = newCars;
	unparkedCapacity+=num;
	return true;
}

size_t Program::input_Choice(size_t numOfChoices) {
	size_t ans = 0;
	cout << "Choose car number from 1 to " << numOfChoices << endl;
	do {
		cout << "\nEnter you choice:";
		cin >> ans;
		if (!cin)
		{
			fix_input();
			cout << "Please , enter car number from 1 to " << numOfChoices << endl;
			ans = 0;
		}
		else if (ans <= 0 || ans > numOfChoices) {
			cout << "Please , choose a valid option from 1 to " << numOfChoices << endl;
		}

	} while (!(ans >= 1 && ans <= numOfChoices));
	return ans;
}

Vehicle** Program::getUnparkedCars() const {

	return cars;
}

size_t Program::getGarageSize() const {
	return garage.size();
}

void Program::createVehicle()
{
	char* regnum = new char[10];
	char* description = new char[101];
	for (int i = 0; i < 10; i++)
	{
		regnum[i] = '\0'; 
	}
	for (int i = 0; i < 101; i++)
	{
		description[i] = '\0';
	}
	size_t parkSpace;
	cout << "Creating new Vehicle .\n";
	cout << "Enter registration number:";
	//cin.ignore();
	cin>>regnum;
	cout << "Enter vehicle description up to 100 symbows:";
	cin.ignore();
	cin.getline(description, 100);
	cout << "Input the parking space that the vehicle takes :";
	parkSpace = inputSizeT(true);

	//create such vehicle in cars[x]
	if (unparkedCapacity == unparkedCarsNum)
	{
		if (!expandCarsStorage()) {
			delete[] regnum;
			delete[] description;
			throw - 1;
		}
	}
	cars[unparkedCarsNum++] = new Vehicle(regnum, description, parkSpace);
	//we dont delete dynamic memory as Vehicle will point to it
	cout << "A new vehicle was created.\n";
}

void Program::moveFromUnparkedToGarage(size_t index) {
	garage.insert(*cars[index]);//might throw int exception!
	for (size_t i = index; i < unparkedCarsNum - 1; i++) //we will move them
	{
		cars[i] = cars[i + 1];
	}
	cars[--unparkedCarsNum] = nullptr;
	
}

void Program::addVehicleToGarage()
{
	displayUnparked();
	if (unparkedCarsNum == 0) {

		return;
	}
	size_t ans = input_Choice(unparkedCarsNum);
	
	try {
		moveFromUnparkedToGarage(ans - 1);
	}
	catch (const int& i)
	{
		if (i == 0)
		{
			cout << "Not enough space to park that car in the garage .\n";
			return;
			//throw i;
		}
		else if (i == 1)
		{
			cout << "A car with the same number already exist in the garage. Can not be added.\n";
			return;
			//throw i;
		}
		else //i==-1 memory error
		{
			throw - 1;
		}
	}
	cout << "Vehicle added to garage.\n";
	return;
}

void Program::createAndAddVehicle() //we will skip adding it to cars but directly to the garage if possible
{
	char* regnum = new char[10];
	char* description = new char[101];
	size_t parkSpace;
	cout << "Creating new Vehicle .\n";
	cout << "Enter registration number:";
	cin >> regnum;
	cout << "Enter vehicle description up to 100 symbows:";
	cin >> description;
	cout << "Input the parking space that the vehicle takes :";
	Vehicle* newVeh;
	parkSpace = inputSizeT(true);
	
	try {
		newVeh = new Vehicle(regnum, description, parkSpace);
	}
	catch (std::exception& e)
	{
		delete[] regnum;
		delete[] description;
		throw - 1;
	}

	try {
		garage.insert(*newVeh);
	}
	catch (const int& i)
	{//we will add it to the unparked vehicles instead
		/*delete[] regnum;
		delete[] description;
		newVeh->~Vehicle();*/
		if (i == 0)
		{
			cout << "Not enough space to park that car in the garage .\n";
			//return;
		}
		else if (i == 1)
		{
			cout << "A car with the same number already exist in the garage.\n";
			//return;
		}
		else //i==-1 memory error
		{
			throw - 1;
		}
		if (unparkedCapacity == unparkedCarsNum)
		{
			if (!expandCarsStorage()) {
				delete[] regnum;
				delete[] description;
				newVeh->~Vehicle(); 
				throw - 1;
			}
		}
		cars[unparkedCarsNum++] = new Vehicle(regnum, description, parkSpace);
		//we dont delete dynamic memory as Vehicle will point to it
		cout << "The new Vehicle was created but could not be added.\n";
		return;
	}
	cout << "Vehicle added directly to the garage.\n";
}


void Program::deleteAllVehicles() {
	for (size_t i = 0; i < garage.size(); i++)
	{
		garage[i].~Vehicle();
	}
	for (size_t i = 0; i < unparkedCarsNum; i++)
	{
		cars[i]->~Vehicle();
	}
}

void Program::removeVehicle()//remove from garage and add to cars
{
	displayGarageCars();
	if (garage.empty())
	{
		return;
	}
	cout << "Which car would you like to remove from the garage?\n";
	cout << "Choose car number from 1 to " << garage.size() << endl;
	size_t ans = input_Choice(garage.size());

	if (unparkedCapacity == unparkedCarsNum)
	{
		if (!expandCarsStorage()) {
			cout << "\nUnable to move the car due to no space in the unparked cars list.\n";
			throw - 1;
		}
	}
	const Vehicle* vehToDel = (&garage[ans - 1]);//we need a pointer to the removed Vehicle
	cars[unparkedCarsNum++] = new Vehicle(garage[ans - 1]);//we cant move it as it's const so we should make a copy
	const char* num = vehToDel->registration();//allocates memory for the registration*
	garage.erase(num);//free space from garage
	delete[] num;//delete the registration
	(*vehToDel).~Vehicle();//delete the vehicle we copied
	delete vehToDel;//and delete the pointer to it
	cout << "Vehicle removed from garage.\n";
}

void Program::destroyVeh()
{
	displayAllcars();
	size_t ans = input_Choice(garage.size() + unparkedCarsNum);
	//firstly display garage than unparked
	if (ans <= garage.size())
	{
		const Vehicle* vehToDel = (&garage[ans - 1]);//we need a pointer to the removed Vehicle
		const char* num = vehToDel->registration();//allocates memory for the registration*
		garage.erase(num);//free space from garage
		delete[] num;//delete the registration
		(*vehToDel).~Vehicle();//delete the vehicle we copied
		delete vehToDel;//and delete the pointer to it
	}
	else
	{//in unparked
		ans -= garage.size() + 1;
		cars[ans]->~Vehicle();//delete
		for (size_t i = ans; i < unparkedCarsNum - 1; i++)//move pointers
		{
			cars[i] = cars[i + 1];
		}
		cars[--unparkedCarsNum] = nullptr;
	}
	cout << "The vehicle was destroyed.\n";
}

void Program::displayGarageCars()
{
	if (garage.size() == 0)
	{
		cout << "The garage is currently empty.\n";
		return;
	}

	for (size_t i = 0; i < garage.size(); i++)
	{
		cout << i + 1 << ") ";
		garage[i].printInfo();
	}
	cout << endl;
}

void Program::displayAllcars()
{//firstly display garage than unparked
	for (size_t i = 0; i < garage.size(); i++)
	{
		cout << i + 1 << ") ";
		garage[i].printInfo();
	}
	displayUnparked(garage.size());
}

void Program::displayUnparked(size_t startIndex ) //display from 1 to num
{
	if (garage.size() == 0 && unparkedCarsNum==0)
	{
		cout << "There are no created cars.\n";
		return;
	}
	if (unparkedCarsNum == 0)
	{
		cout << "All available cars are currently parked in the garage!\n";
		return;
	}
	for (size_t i = 0; i < unparkedCarsNum; i++)
	{
		cout << startIndex + 1 << ") ";
		cars[i]->printInfo();
		startIndex++;
	}
}

bool Program::executeOrder(short option)
{
	switch (option)
	{
	case CREATE_VEH:
		createVehicle();
		return true;
	case ADD_VEH:
		addVehicleToGarage();
		return true;
	case CREATE_ADD_VEH:
		createAndAddVehicle();
		return true;
	case DESTROY_VEH:
		destroyVeh();
		return true;
	case REMOVE_VEH:
		removeVehicle();
		return true;
	case DISPLAY_GARAGE_CARS:
		displayGarageCars();
		return true;
	case DISPLAY_ALL_CARS:
		displayAllcars();
		return true;
	case DISPLAY_UNPARKED_CARS:
		displayUnparked();
		return true;
	case EXIT_NUM:
		//TBD
		return false;

	default:
		break;
	}
}




