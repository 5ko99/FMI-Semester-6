#include<iostream>
#include<string>
#include<vector>
#include "ICommand.h"
#include "commandLineParser.h"
#include "console.h"
#include "system.h"


int main()
{
	System receiver;
	Console::run(receiver);
	
	return 0;
}
