// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Валери Добрев
// ФН: 45807
// Специалност: Инфораматика
// Курс: 1
// Административна група: 5
// Ден, в който се явявате на контролното: 17.04
// Начален час на контролното: 08:00
// Кой компилатор използвате: GCC
//
 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include<cctype>


using std::cout;
using std::cin;
using std::endl;


class Registration{
	char registration[9];
	bool isValid(const char* str);
public:
	Registration(const char* str);
	Registration& operator=(const char* str);
	bool operator==(const char* str) const;
	const char* toString() const;


};

class Vehicle{
public:
	const Registration regnum;
	const std::string description;

	Vehicle(const char* regnum, const char* description);


};

class VehicleList{
	Vehicle** vehicles;
	size_t listCapacity;
	size_t numberOfVehicles;
public:
	VehicleList(size_t listCapacity);
	~VehicleList();
	VehicleList(const VehicleList& other);
	VehicleList& operator=(const VehicleList& other);

	void insert(const char* regnum, const char* description);
	const Vehicle& at(size_t position) const;
	const Vehicle& operator[](size_t position)const;
	bool empty()const;
	size_t capacity()const;
	size_t size() const;
	const Vehicle* find(const char* regnum) const;


};

void createVehicle(VehicleList& vl);

const char* getUserInput(const char* msg);

int main()
{
	int capacity;
	cout<<"Enter vehicle list's capacity: ";
	cin>>capacity;
	while(capacity==0){
		cout<<"Invalid capacity! Please insert positive number: ";
		cin>>capacity;
	}
	getchar();
	
	VehicleList vl(capacity);
	for(size_t i=0; i<capacity; i++){
		createVehicle(vl);
	}
	
	const char* registration = getUserInput("Enter vehicle's registration to check if is in the list(exit to stop the program): ");
	while(strcmp(registration, "exit")!=0){
		if(vl.find(registration)){
			cout<<"Vehicle with registration '"<<registration<<"' exists!"<<endl;
		}else{
			cout<<"Vehicle with registration '"<<registration<<"' does not exist!"<<endl;
		}
		delete [] registration;
		registration = getUserInput("Enter vehicle's registration to check if is in the list(exit to stop the program): ");
	}
	delete [] registration;
    
	return 0;
}

void createVehicle(VehicleList& vl){
	const char* regNum = getUserInput("Enter vehicle's registration number: ");
	const char* desc =  getUserInput("Enter vehicle's description: ");

	try{
		vl.insert(regNum, desc);
	}catch(std::exception& e){
		cout << e.what() << endl;
		delete [] regNum;
		delete [] desc;
		createVehicle(vl);
		return;
	}

	delete [] regNum;
	delete [] desc;
}

const char* getUserInput(const char* msg){
	cout<<msg;
	char* buffer = new char[250];
	char c;
	int i=0;
	while(true){
		c= getchar();
		if(c=='\n'){
			break;
		}
		buffer[i]=c;
		i++;
	}
	buffer[i] = '\0';
	return buffer;
}

Registration::Registration(const char* str){
	if(!isValid(str)){
		throw std::invalid_argument("Invalid registration number!");
	}
	strcpy(registration, str);
}
Registration& Registration::operator=(const char* str){
	if(!isValid(str)){
		throw std::invalid_argument("Invalid registration number!");
	}
	strcpy(registration, str);
	return *this;
}

bool Registration::isValid(const char* str){
	size_t len = strlen(str);
	if(len > 8 || len<7){
		return false;
	}

	size_t start = 1;
	if(len == 8){
		start=2;
		if(!isalpha(str[0]) || !isalpha(str[1])){
			return false;
		}
	}else{
		if(!isalpha(str[0])){
			return false;
		}
	}
	for(unsigned int i=start; i<len-2;i++){
		if(!isdigit(str[i])){
			return false;
		}
	}
	if(!isalpha(str[len-2])|| !isalpha(str[len-1])){
		return false;
	}

	return true;
}

bool Registration::operator==(const char* str) const{ 
	if(strcmp(str,registration)==0){
		return true;
	}
	return false;
}

const char* Registration::toString() const{ 
	return registration;
}

Vehicle::Vehicle(const char* regnum, const char* description): regnum(regnum), description(description){}


VehicleList::VehicleList(size_t listCapacity): listCapacity(listCapacity), numberOfVehicles(0), vehicles(new Vehicle*[listCapacity]) {
	if(listCapacity==0){
		throw std::invalid_argument("Capacity should be greater than zero!");
	}
}

VehicleList::~VehicleList(){ 
	for(size_t i=0; i<numberOfVehicles; i++){
		delete vehicles[i];
	}
	delete [] vehicles;
	vehicles = nullptr;
}
VehicleList::VehicleList(const VehicleList& other):VehicleList(other.listCapacity){
	for(size_t i=0; i<other.numberOfVehicles; i++){
		this->vehicles[i] = new Vehicle(other.vehicles[i]->regnum.toString(), other.vehicles[i]->description.c_str());
	}
}

VehicleList& VehicleList::operator=(const VehicleList& other){
	for(size_t i=0; i<numberOfVehicles; i++){
		delete this->vehicles[i];
	}
	delete [] this->vehicles;

	this->listCapacity = other.listCapacity;
	this->numberOfVehicles = other.numberOfVehicles;
	this->vehicles = new Vehicle*[listCapacity];

	for(size_t i=0; i<numberOfVehicles;i++) {
		this->vehicles[i] = new Vehicle(other.vehicles[i]->regnum.toString(), other.vehicles[i]->description.c_str());
	}

	return *this;

}

void VehicleList::insert(const char* regnum, const char* description){
	if(numberOfVehicles == listCapacity) {
		throw std::invalid_argument("The list is full!");
	}
	if(find(regnum)){
		throw std::invalid_argument("The vehicle already exists!");
	}
	vehicles[numberOfVehicles] = new Vehicle(regnum, description);
	numberOfVehicles++;
}


const Vehicle& VehicleList::at(size_t position)const{
	if(position>=numberOfVehicles) {
		throw std::invalid_argument("Invalid position!");
	}
	return *vehicles[position];
}
const Vehicle& VehicleList::operator[](size_t position) const{
	return *vehicles[position];
}

bool VehicleList::empty()const{ return numberOfVehicles == 0; }

size_t VehicleList::capacity()const{ return this->listCapacity; }

size_t VehicleList::size() const{return numberOfVehicles; }

const Vehicle* VehicleList::find(const char* regnum) const{
	for(size_t i=0; i<numberOfVehicles;i++){
		if(this->vehicles[i]->regnum == regnum){
			return vehicles[i];
		}
	}
	return nullptr;
}
