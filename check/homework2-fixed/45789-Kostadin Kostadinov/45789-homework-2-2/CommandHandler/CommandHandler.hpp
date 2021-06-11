#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H
#include "../VPAllocator/VPAllocator.hpp"
#include "../Command/Command.hpp"
#include "../Helpers/Helpers.hpp"

class CommandHandler  
{
public:
	CommandHandler(VPAllocator& vpa);
	CommandHandler(VPAllocator& vpa, std::string path);
	void run();
private:
	VPAllocator* vpa;
	std::vector<std::string> c_list;
	bool choice;
	std::string buffer_choice;
	
	bool execute(Command& command);
	
	void load(std::string path);
	void save(std::string path);
};
#endif
