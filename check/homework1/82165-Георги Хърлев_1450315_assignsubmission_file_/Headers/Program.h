#pragma once
#include "Garage.h"

#define CREATE_VEH 1
#define ADD_VEH 2
#define	CREATE_ADD_VEH 3
#define	REMOVE_VEH 4
#define DESTROY_VEH 5
#define DISPLAY_GARAGE_CARS 6
#define DISPLAY_ALL_CARS 7
#define DISPLAY_UNPARKED_CARS 8
#define EXIT_NUM 9

class Program {
private:
	//size_t capacity = 0;
	size_t unparkedCarsNum = 0;
	size_t unparkedCapacity = 0;
	Garage garage;
	Vehicle** cars=nullptr; //unparked
	
	bool expandCarsStorage(unsigned num = 1);
	void fix_input();
public: 
	//It's a good idea most of these to be in private but I need them in public for the tests
	Program();
	Program(size_t capacityGarage); //used for the tests
	~Program();

	short getOptionInterface();
	size_t inputSizeT(bool zeroCheck=false);
	Vehicle** getUnparkedCars() const;
	size_t getUnparkedCarsNum() const;
	size_t getUnparkedCarsCapacity() const;
	size_t getGarageSize() const;
	const Vehicle& getGarageVehAt(size_t index) const;

	bool executeOrder(short option);
	bool input_isStrBiggerOrEqual(const char* bigger, const char* smaller);
	size_t input_convertToNum(char str[]);
	bool input_isValidNum(char str[]);
	void displayUnparked(size_t startIndex = 0);
	void displayAllcars();
	void destroyVeh();
	void removeVehicle();
	void createAndAddVehicle();
	void addVehicleToGarage();
	void moveFromUnparkedToGarage(size_t index);
	void createVehicle();
	void displayGarageCars();
	size_t input_Choice(size_t numOfChoices);
	void deleteAllVehicles(); //deletes both cars and garage vehicles

};