#include <string> 
#include <iostream>
#include "Registration.h"
using namespace std;

Registration::Registration()
{
	for (size_t i = 0; i < 8; i++)
	{
		cin >> registration[i];
	}
}
