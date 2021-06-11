//============================================================================
// Name        : HomeworkOOPv2.cpp
// Author      : jivko
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;
#include "ClassHeader.h"

int FindVehPtr (vector<Person::Vehicle*>& CurrentPeopleListVehVtr, string& Arg)
{
	int CurrentVehListSize = CurrentPeopleListVehVtr.size() ;
	for (int i = 0; i < CurrentVehListSize; i++)
	{
		Person::Vehicle* TempVeh = CurrentPeopleListVehVtr[i] ;
		TempVeh = CurrentPeopleListVehVtr[i] ;
		if(TempVeh->VehRegStr() == Arg)
			return i ;
	}
	throw 1 ;
}

void GiveName (string& FirstArg)
{
	char c;
	cin >>  c  ;
	for (; ; )
	{
		cin >> c ;
		if (c == 34)
			break ;
		FirstArg = FirstArg + c ;
	}
	return  ;
}

int FindPerson (vector<Person>& PeopleList, vector<Person::Vehicle>& VehList, unsigned& Arg)
{
	int Size = PeopleList.size();
	for (int i = 0; i < Size; i++)
	{
		if(PeopleList[i].m_Identifier == Arg)
			return i ;
	}
	throw 1 ;
}
int FindVeh (vector<Person>& PeopleList, vector<Person::Vehicle>& VehList, string& Arg)
{
	int Size = VehList.size();
	Person::Vehicle temp ;
	for (int i = 0; i < Size; i++)
	{
		temp = VehList[i] ;
		string tempstr = temp.VehRegStr() ;
		if(tempstr == Arg)
			return i ;
	}
	throw 1 ;
}
string StrRework(string& OldString)
{
	int StrLen = OldString.length() ;
	string NewString ;
	for (int i = 0; i < StrLen; i++)
	{
		if (OldString[i] == 34)
		{
			OldString[i] = ' ' ;
		}

			if(OldString[i] >= 97 && OldString[i] <= 122)

			OldString[i] = OldString[i] - 32 ;
		if(OldString[i] == ' ')
		{
			for(int j = 0; j < i; j++)
			{
				NewString = NewString + OldString[j] ;
			}
			for(int j = i+1; j < StrLen; j++)
			{
				NewString = NewString + OldString[j] ;
			}
		}
	}
	int temp = NewString.length() ;
	if(temp != 0)
		return NewString ;
	else return OldString ;
}
bool StrComp(string& left, string& right)
{
	int StrLen = left.length() ;
	int RightStrLen = right.length() ;
	if (StrLen != RightStrLen)
		return false ;
	for (int i = 0; i < StrLen; i++)
	{
		if (left[i] != right[i])
			return false ;
	}
	return true ;
}
void PersonPointerRedo (vector<Person>& PeopleList, vector<Person::Vehicle>& VehList)
{
	Person::Vehicle* Vehiccle ;
	for (int i = 0; i < VehList.size(); i++)
		{
			Vehiccle = &VehList[i] ;
			Person* TempPrsonPtr = Vehiccle->m_Owner ;
			int temp = TempPrsonPtr->m_VehOwned.size() ;
			TempPrsonPtr->m_VehOwned.clear() ;
			TempPrsonPtr->m_VehOwned.resize(temp + 1) ;
			TempPrsonPtr->m_VehOwned[temp - 1] = &VehList[i];
		}
}

void InfoFromFile (fstream& DBFile, vector<Person>& PeopleList, vector<Person::Vehicle>& VehList)
{
		string NameOrRegStr ;
		unsigned IdentNum = 0 ;
		int SavePos = 0 ;
		vector<int> PersonCounterArr ;
		do
			{
			DBFile.seekg(1, ios::cur) ;
			getline(DBFile, NameOrRegStr, (char)34) ;
			DBFile.seekg(1, ios::cur) ;
			DBFile >> IdentNum ;
			DBFile.seekg(1, ios::cur) ;
			Person temp (NameOrRegStr, IdentNum) ;
			PeopleList.push_back(temp) ;
			SavePos = DBFile.tellg() ;
			getline(DBFile, NameOrRegStr) ;
			if (NameOrRegStr == "Vehicles")
			{
				break ;
			}
			DBFile.seekg(SavePos, ios::beg) ;
		}while(true) ;
		string Description ;
		string OwnerName ;
		int i = 0 ;
		do
			{
				getline(DBFile, NameOrRegStr, ' ') ;
				if(NameOrRegStr == "END")
					break ;
				DBFile.seekg(1, ios::cur) ;
				getline(DBFile, Description, (char)34) ;
				DBFile.seekg(2, ios::cur) ;
				getline(DBFile, OwnerName, (char)34) ;
				int counter = 0 ;
				for (; counter < PeopleList.size() ; counter++) //dobawi preduprejdenie ako nqma sobstwenik
					if (OwnerName == PeopleList[counter].m_Name)
					{
						PersonCounterArr.push_back(counter) ;
						break ;
					}
				Person::Vehicle TempVeh(NameOrRegStr, Description, PeopleList[counter]) ;
				VehList.resize(i+1) ;
				VehList[i] = TempVeh ;
//				PeopleList[counter].m_VehOwned.resize(PeopleList[counter].m_VehOwned.size()+1) ;
//				Person::Vehicle* VehPtr = &VehList[i] ;
//				PeopleList[counter].m_VehOwned[PeopleList[counter].m_VehOwned.size() - 1] = VehPtr ;
				DBFile.seekg(1, ios::cur) ;
				i++ ;
			}while(true) ;
		PersonPointerRedo(PeopleList, VehList) ;
}

int main() {
	string args ;
	cin >> args ;
	try{
		fstream DBFile(args, ios::in|ios::out) ;
	if(!DBFile.is_open())
	{
		cout << "File not open...Creating file" << endl ;
		DBFile.close() ;
		throw 1 ;
	}
	}catch (...)
	{
		args = "Info.txt" ;
		fstream DBFile(args, ios::in|ios::out) ;
	}
	fstream DBFile("Info.txt", ios::in|ios::out) ;
	//Create Vectors
	vector<Person> PeopleList ;
	vector<Person::Vehicle> VehList ;
	//pull info from file
	InfoFromFile(DBFile, PeopleList, VehList) ;
	//interface
	cout << "Command to exit program is EXIT" ;
	string CommandStr ;
	string FirstArg ;
	string SecArg ;
	string Commands[7] {"VEHICLE", "PERSON", "ACQUIRE", "RELEASE", "SAVE", "SHOW", "EXIT"} ;
	int CommandArrCount = 0 ;

		do
		{
			try
			{
				cin >> CommandStr ;
				for(; ; CommandArrCount++)
				{
					if(CommandArrCount == 7)
						throw 1 ;
					string Str1 = StrRework(CommandStr);
					string Str2 = Commands[CommandArrCount] ;
					if(StrComp(Str1, Str2))
						break ;
				}
				switch(CommandArrCount)
				{
				case 0 : //VEHICLE
					{
						cin >> FirstArg >> SecArg ;
						int temp = VehList.size() ;
						VehList.resize(temp + 1) ;
						Person::Vehicle TempVeh(FirstArg, SecArg) ;
						VehList[temp] = TempVeh ;
						cout << "object created" ;
						break ;
					}
				case 1 : //Person
				{
					unsigned Id = 0 ;
//					char InputInfo[256] ;
					GiveName(FirstArg) ;
					cin >> Id ;
					int temp = VehList.size() ;
					Person TempPer(FirstArg, Id) ;
					PeopleList.resize(temp + 1) ;
					PeopleList[temp] = TempPer ;
					break ;
				}
				case 2 : //AQUIRE
				{
					unsigned Id = 0 ;
					cin >> Id >> FirstArg ;
					int PlacePers = FindPerson(PeopleList, VehList, Id) ;
					int PlaceVeh  = FindVeh(PeopleList, VehList, FirstArg) ;
					int PlaceVehPtr = 0 ;
					Person::Vehicle TempVehicle ;
					TempVehicle = VehList[PlaceVeh] ;
					TempVehicle.m_Owner = &PeopleList[PlacePers] ;
					VehList[PlaceVeh] = TempVehicle ;
					PlaceVehPtr = FindVehPtr(PeopleList[PlacePers].m_VehOwned, FirstArg) ;
					PeopleList[PlacePers].m_VehOwned[PlaceVehPtr] = &VehList[PlaceVeh] ;
					break ;
				}
				case 3 ://Release
				{
					unsigned Id = 0 ;
					cin >> Id >> FirstArg ;
					int PlacePers = FindPerson(PeopleList, VehList, Id) ;
					int PlaceVeh  = FindVeh(PeopleList, VehList, FirstArg) ;
					int PlaceVehPtr = 0 ;
					Person::Vehicle TempVehicle ;
					TempVehicle = VehList[PlaceVeh] ;
					TempVehicle.m_Owner = nullptr ;
					VehList[PlaceVeh] = TempVehicle ;
					PlaceVehPtr = FindVehPtr(PeopleList[PlacePers].m_VehOwned, FirstArg) ;
					PeopleList[PlacePers].m_VehOwned[PlaceVehPtr] = &VehList[PlaceVeh] ;
					break ;
				}
				case 4 ://REMOVE
				{
					char c ;
					cin >> c ;
					if (c >= 65)
						{
							FirstArg = FirstArg + c ;
							cin >> FirstArg ;
							int VehListSize = VehList.size() ;
							int PlaceVeh = FindVeh(PeopleList, VehList, FirstArg) ;
							vector<Person::Vehicle> TempVehList ;
							TempVehList.resize(VehListSize - 1) ;
							for (int i = 0; i < PlaceVeh ; i++)
							{
								TempVehList[i] = VehList[i] ;

							}
							for (int i = PlaceVeh + 1; i < VehListSize ; i++)
							{
								TempVehList[i] = VehList[i] ;

							}
							VehList = TempVehList ;
						}else
						{
							unsigned Id = (int)c - 48 ;
							unsigned temp ;
							cin >> temp ;
							Id = temp*10 ;
							int PerListSize = PeopleList.size() ;
							int PlacePer = FindPerson(PeopleList, VehList, Id) ;
							vector<Person> TempPerList ;
							TempPerList.resize(PerListSize - 1) ;
							for (int i = 0; i < PlacePer ; i++)
							{
								TempPerList[i] = PeopleList[i] ;

							}
							for (int i = PlacePer + 1; i < PerListSize ; i++)
							{
								TempPerList[i] = PeopleList[i] ;

							}
							PeopleList = TempPerList ;
						}
					break ;
				}
				case 5 : // SAVE
				{
					DBFile.close() ;
					cin >> args ;
					fstream DBFile(args, ios::app) ;
					int PerListSize = PeopleList.size() ;
					int VehListSize = VehList.size() ;
					for (int i = 0; i < PerListSize; i++)
						DBFile << (char)34 << PeopleList[i].m_Name << (char)34 << ' ' << PeopleList[i].m_Identifier << endl ;
					DBFile << "Vehicles" << endl ;
					Person::Vehicle tempVeh ;
					for (int i = 0; i < VehListSize; i++)
					{
						tempVeh = VehList[i] ;
						DBFile << tempVeh.VehRegStr() << ' ' << tempVeh.m_Desc << ' ' << (char)34 << tempVeh.m_Owner->m_Name << (char)34 << endl ;
					}
					break ;
				}
				case 6 :
				{
					return 0 ;
				}
				}
			}catch(...)
			{
				cout << "error, wrong input" << endl ;
			}
		}while(true) ;
	return 0;
}
