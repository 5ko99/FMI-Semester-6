/*
 * ClassHeader.h
 *
 *  Created on: May 20, 2021
 *      Author: jivko
 */

#ifndef _ClassHeader
#define _ClassHeader
#include <iostream>
#include <string>
#include <vector>
using namespace std ;

class Registration
{
public:
	string m_CitySymb ;
	string m_SpecialNum ;
	string m_EndSymb ;

	Registration()
	{

	}
	Registration (string& VehReg)
	{
		string CitySymb;
		string SpecialNum ;
		string EndSymb ;
		try
		{
			if(VehReg.length() == 7)
			{
				CitySymb += VehReg[0] ;
				for(int i = 1; i < 5; i++)
					SpecialNum += VehReg[i] ;
				EndSymb += VehReg[5] ;
				EndSymb += VehReg[6] ;
			}else if(VehReg.length() == 8)
					{
						CitySymb += VehReg[0] ;
						CitySymb += VehReg[1] ;
						for(int i = 2; i < 6; i++)
							SpecialNum += VehReg[i] ;
						EndSymb += VehReg[6] ;
						EndSymb += VehReg[7] ;
					}else throw 1 ;
			if ( SpecialNum.length() != 4 || EndSymb.length() != 2)
				throw 1 ;
			if (CitySymb.length() == 1 &&
				!(CitySymb[0] >= 'a' && CitySymb[0] <= 'z') &&
				!(CitySymb[0] >= 'A' && CitySymb[0] <= 'Z'))
					throw 2 ;
			if (CitySymb.length() == 2 &&
				!(CitySymb[0] >= 'a' && CitySymb[0] <= 'z') &&
				!(CitySymb[0] >= 'A' && CitySymb[0] <= 'Z') &&
				!(CitySymb[1] >= 'a' && CitySymb[1] <= 'z') &&
				!(CitySymb[1] >= 'A' && CitySymb[1] <= 'Z'))
					throw 3 ;
			for (int i = 0; i < 4; i++)
				if (SpecialNum[i] < '0' || SpecialNum[i] > '9')
					throw 4 ;
			if (!(EndSymb[0] >= 'a' && EndSymb[0] <= 'z') &&
				!(EndSymb[0] >= 'A' && EndSymb[0] <= 'Z') &&
				!(EndSymb[1] >= 'a' && EndSymb[1] <= 'z') &&
				!(EndSymb[1] >= 'A' && EndSymb[1] <= 'Z'))
					throw 5 ;
		m_CitySymb = CitySymb ;
		m_SpecialNum = SpecialNum ;
		m_EndSymb = EndSymb ;
		}
		catch(...)
		{
			cout << "Registration not correct" ;
		}
	}

	string ShowReg ()
	{
		return m_CitySymb + m_SpecialNum + m_EndSymb ;
	}


};

class Person
{
public:
	class Vehicle
	{
	public:
		Registration m_VehReg ;
		string m_Desc ;
		Person* m_Owner ;
		Vehicle()
		{

		}
		Vehicle (string& VehReg, string& Desc, Person& Owner)
		{
			m_VehReg = Registration(VehReg) ;
			m_Desc = Desc ;
			m_Owner = &Owner ;
		}
		Vehicle (string& VehReg, string& Desc)
		{
			m_VehReg = Registration(VehReg) ;
			m_Desc = Desc ;
		}
		void VehPrint ()
		{
			cout << m_VehReg.ShowReg() << endl << m_Desc << endl << m_Owner->m_Name << endl ;
		}
		string VehRegStr ()
		{
			return m_VehReg.m_CitySymb + m_VehReg.m_SpecialNum + m_VehReg.m_EndSymb ;
		}

	};
	string m_Name ;
	unsigned m_Identifier ;
	vector<Vehicle*> m_VehOwned ;
	Person()
	{

	}
	Person (string& Name , unsigned& Identifier)
	{
		m_Name = Name ;
		m_Identifier = Identifier ;
	}
//	Person& operator=(Person rhs)
//	{
//		m_Identifier = rhs.m_Identifier ;
//		m_Name = rhs.m_Name ;
//		m_VehOwned = rhs.m_VehOwned ;
//		return this ;
//	}
};
#endif
