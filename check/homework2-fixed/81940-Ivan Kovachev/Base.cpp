#include "Base.h"

std::vector<std::string> Base::splitLine(const std::string & Line)
{
	std::stringstream strStream;
	strStream << Line;
	std::string part;
	std::vector<std::string> vectResult;

	while (strStream >> part)
		vectResult.push_back(part);
	return vectResult;
}

Base::Base(std::istream & in, std::ostream & out) : in(in), out(out) {}

Base::~Base() {}

void Base::start()
{
	while (true)
	{
		std::string Line;
		getline(in, Line);
		if (Line.empty()) continue;
		std::vector<std::string> lineSplit = splitLine(Line);
		if (lineSplit[0] == "exit")
		{
			out << "Exiting..." << std::endl;
			break;
		}
		else
		{
			processInput(lineSplit);
		}

		out << std::endl;
	    //if (lineSplit[0] == "open") system("cls");
	}
}
