# include "Interface.h"
# include <algorithm>
# include <iostream>
# include <fstream>
# include <string>
void toUpper(std::string& str) {
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
}
bool isDigit(const std::string& s) {
	std::size_t size = s.size();
	for (std::size_t i = 0; i < size; i++) {
		if (!(std::isdigit(s[i])))
			return false;
	}
	return true;
}
void inputStr(std::string& str) {

	char buff;
	std::cin >> buff;
	if (buff == '"') {
		std::getline(std::cin, str, '"');
	}
	else {
		std::cin >> str;
		str.insert(0, 1, buff);
	}
}
void Interface::setEnum( std::string& str) {
    toUpper(str);
	if (str == "VEHICLE")
		this->c = VEHICLE;
	if (str == "PERSON")
		this->c = PERSON;
	if (str == "AQUIRE")
		this->c = AQUIRE;
	if (str == "RELEASE")
		this->c = RELEASE;
	if (str == "REMOVE")
		this->c = REMOVE;
	if (str == "SAVE")
		this->c = SAVE;
	if (str == "SHOW")
		this->c = SHOW;
	if (str == "EXIT")
		this->c = EXIT;
}
void loadInfo(Interface & inter) {
	std::ifstream in;
	std::string str;
	std::cin >> str;
	in.open(str);
	while (!in) {
		std::cerr << "no such file found, please enter again";
		std::cin >> str;
		in.open(str);
		
	}
	while (!in.eof()) {
		std::string comand;
		in >> comand;
		inter.setEnum(comand);
		switch (inter.c) {
		case VEHICLE: {
			std::string r, descr;
			in >> r;
			std::getline(in, descr);
			Registration reg(r);
			inter.cm.newVehicle(reg, descr);
			break;
		}case PERSON: {
			std::string name;
			unsigned int id;
			std::getline(in, name);
			in >> id;
			inter.cm.newPerson(name, id);
			break;
		}case AQUIRE: {
			std::string str;
			unsigned int id;
			in >> str;
			in >> id;
			inter.cm.Aquire(id, str);
			break;
		}case RELEASE: {
			std::string str;
			unsigned int id;
			in >> str;
			in >> id;
			inter.cm.Release(id, str);
			break;
		}case REMOVE: {
			std::string temp;
			in >> temp;
			if (isDigit(temp)) {
				int tempNum = std::stoi(temp);
				inter.cm.remove(tempNum);
			}
			inter.cm.remove(temp);
			break;
		}case SAVE: {
			std::string path;
			in >> path;
			inter.cm.Save(path);
			break;
		}case SHOW: {
			std::string temp;
			in >> temp;
			if (isDigit(temp)) {
				int tempNum = std::stoi(temp);
				inter.cm.display(tempNum);
			}
			inter.cm.display(temp);
			break;
		}
		}
	}
	in.close();
}
void  runCommand(Interface& inter) {
	switch (inter.c){
	case VEHICLE: {
		std::string temp;
		std::string reg;
		try {
			inputStr(temp);
			std::cin  >> reg;
		Registration r(reg);
		inter.cm.newVehicle(r, temp);
		}
		catch (const std::exception & e) {
			std::cerr << "Bad input\n";
			std::cout << e.what()<<"\n";
			std::cin.ignore();
			std::cin.clear();
			inputStr(temp);
			std::cin >> reg;
			Registration r(reg);
			inter.cm.newVehicle(r, temp);
		}
		break;
	}case PERSON: {
		std::string temp;
		unsigned int t;

		try {
			inputStr(temp);
			std::cin  >> t;
		inter.cm.newPerson(temp, t);
		}
		catch (...) {
			std::cin.ignore();
			std::cin.clear();
			inputStr(temp);
			std::cin >> t;
			inter.cm.newPerson(temp, t);
		}
		
		break;
	}case AQUIRE: {
		unsigned int i;
		std::string r;
		try {
			std::cin >> i >> r;
			Registration reg(r);
			inter.cm.Aquire(i, reg);
		}catch(const std::exception & e) {
			std::cerr << e.what() << "\n";
			std::cin >> i >> r;
			Registration reg(r);
			inter.cm.Aquire(i, reg);
		}
		break;
	}case RELEASE: {
		unsigned int i;
		std::string r;
		try{
			std::cin >> i >> r;
			Registration reg(r);
			inter.cm.Release(i, reg);
		}
		catch (const std::exception& e) {
			std::cout << e.what() << "\n";
			std::cout << "please enter information again!\n";
			std::cin >> i >> r;
			Registration reg(r);
			inter.cm.Release(i, reg);
		}
		
		break;
	}case REMOVE: {
			std::string s;
			std::cin >> s;
			try {
				if (isDigit(s)) {
					int temp = std::stoi(s);
					if (temp < 0) {
						temp = abs(temp);
					}
					inter.cm.remove(temp);
				}
				else {
					Registration r(s);
					inter.cm.remove(r);
				}
			}
			catch (const std::exception& e) {
				std::cin >> s;

				if (isDigit(s)) {
					int temp = std::stoi(s);
					if (temp < 0) {
						temp = abs(temp);
					}
					inter.cm.remove(temp);
				}
				else {
					Registration r(s);
					inter.cm.remove(r);
				}
			}
			break;
	}case SAVE: {
		std::string s;
		std::cin >> s;
		try {
			inter.cm.Save(s);
		}
		catch (const std::exception& e) {
			std::cout << e.what();
			std::cin >> s;
			inter.cm.Save(s);
		}break;
	}case SHOW: {
		std::string s;
		std::cin >> s;
		try {
			if (isDigit(s)) {
				int temp = std::stoi(s);
				if (temp < 0) {
					temp = abs(temp);
				}
				inter.cm.display(temp);
			}
			else {

				inter.cm.display(s);;
			}
		}
		catch (const std::exception& e) {
			std::cout << e.what();
			std::cin >> s;
			if (isDigit(s)) {
				int temp = std::stoi(s);
				if (temp < 0) {
					temp = abs(temp);
				}
				inter.cm.display(temp);
			}
			else {

				inter.cm.display(s);;
			}
		}
		break;
	}
	}
}
void Interface::Run() {
	bool flag;
	std::cout << "Do you wish to load information ?\n";
	std::cin >> flag;
	if (flag) {
		 loadInfo(*this);
	}
	while (true) {
		std::cout << "Please enter comand\n";
		std::string str;
		std::cin >> str;
		this->setEnum(str);
		runCommand(*this);
		if (this->c == EXIT) {
			std::cout << "Do you really wish to exit?\n";
			bool flag;
			std::cin >> flag;
			if (flag) {
				std::cout << "Do you want  to save ?\n";
				bool flag;
				std::cin >> flag;
				if (flag) {
					std::string path;
					std::cin >> path;
					try { cm.Save(path); }
					catch (...) {
						std::cout << "Please try again";
						std::cin >> path;
						cm.Save(path);
					}
				}
				break;
			}
		}
	}
}
