#pragma once 
#include "ICommand.h"

class ShowCommand : public ICommand
{
public:
	ShowCommand(const std::vector<std::string>& arguments);
	void execute(System& receiver) override;
};
