#include "saveCommand.h"

SaveCommand::SaveCommand(const std::vector<std::string>& arguments)
{
	this->arguments = arguments;
}

void SaveCommand::execute(System& receiver)
{
    if (receiver.getFile() == arguments[0])
    {
        std::cout << "This file already exists! Would you like to overwrite it?" << std::endl;
		char answer;
		std::cin >> answer;
		if (answer == 'n')
		{
			std::cout << "Saving of the data canceled!" << std::endl;
			std::cin.ignore();
			return;
		}

		while (answer != 'y' && answer != 'n')
		{
			std::cout << "Please type \'y\' if you want to overwrite the file or \'n\' otherwise! ";
			std::cin >> answer;
		}
		std::cout << "The file was overwiritten!" << std::endl;
		std::cin.ignore();
    }
    receiver.setFile(arguments[0]);
	receiver.saveData();
}
