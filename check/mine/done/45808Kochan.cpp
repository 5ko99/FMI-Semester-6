// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Сонер Кочан
// ФН: 45808
// Специалност: Информатика
// Курс: 1ви
// Административна група: 5
// Ден, в който се явявате на контролното: 17/04/2021
// Начален час на контролното: 08:00
// Кой компилатор използвате: Visual C++
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;


class Vehicle
{
	std::string plate;

public:

	Vehicle()
	{
		plate = "";
	}

	void Inilitalizaton()
	{
		std::cout << "Enter a plate: "; std::cin >> plate;
	}

	std::string takePlate()
	{
		return plate;
	}
	void showPlate()
	{
		std::cout << plate << std::endl;
	}
	
	void ShowCar()
	{
		cout << plate << endl;
	}

	~Vehicle()
	{
		std::cout << "KolaChao\n";
	}
};
class VehicleList
{
	std::string s;
	int i;
	int capacity;
	Vehicle* vp;

	public:
		VehicleList()
		{
			s = "";
			i = 0;
			capacity = 20;
			vp = new Vehicle[capacity];
		}

		void index()
		{
			i = 0;
		}

		bool isFull()
		{
			if (i == capacity)
				return true;
			else
				return false;
		}
		bool isFree()
		{
			if (i < capacity)
				return true;
			else
				return false;
		}

		void next()
		{
			bool t;
			t = isFree();
			if (t == 1)
			{
				cout << "\n There is available space \n";
				vp[i].Inilitalizaton();
				i++;
			}
			else
				cout << "\nThere is no Space\n";
		}

		bool LookFor(std::string reg)
		{
			for (int c = 0; c < capacity; c++)
			{
				if (vp[i].takePlate() == reg)
					cout << "\n Vehicle is found!\n";
					return true;
			}
		}

		bool GetRidOf(string reg)
		{
			for (int c = 0; c < capacity; c++)
			{
				if (vp[i].takePlate() == reg)
				{
					cout << "\n The car is found and removed.\n";
					//--i;
					return true;
				}
			}
			return false;
		}

		void ShowVehicles() {
			for (int c = 0; c < i; c++)
			{
				vp[i].ShowCar();
			}
		}
};

int main()
{
	VehicleList a;
	a.index();
	while (19321 > 1)
	{
		int option;
		cout << "1. Add a vehicle to the list.\n";
		cout << "2. Remove a vehicle from the list.\n";
		cout << "3. Display all the vehicles.\n";
		cout << "-------------------------------------\n";

		cin >> option;

		string plate;

		switch (option)
		{
		case 1:
		{
			Vehicle newCar;
			newCar.Inilitalizaton();
			a.next();
			break;
		}

		case 2:
		{
			cout << "\n Enter a plate number that you want to remove: ";
			cin >> plate;
			a.GetRidOf(plate);
		}

		case 3:
		{
			a.ShowVehicles();
			break;
		}
		default:
			break;
		}
	}

	return 0;
}