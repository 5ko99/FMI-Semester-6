// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Мария Роглева
// ФН: 82172
// Специалност: КН
// Курс: 1
// Административна група: 3
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: <тук попълнете часа за вашата група>
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

enum commands{EXIT, SIZE, EDIT, SHOW};
class editor;

class command
{
private:
	std::string com;
	std::vector<int> arguments;

public:
	command(std::string input) //had letters
	{
		std::size_t i = 0;
		for(i; i<input.size(); ++i)
		{
			if(input[i] == ' ' || i == input.size()-1)
			{
				com = input.substr(0, i);
				break;
			}
		}
		std::cout<<com;
		++i;
		while(i<input.size())
		{
			std::size_t marker = i;
			for(i; i<input.size(); ++i)
			{
				if(input[i] == ' ' || i == input.size()-1)
				{
					std::string temp = input.substr(marker, i-marker);
					// int number = std::stoi(temp);                          //Защо не работи това??????
					
				
					// arguments.push_back(number);
					
					break;
				}
			}
		}
	}

	int operator[](std::size_t pos)
	{
		if(pos <= arguments.size())
		{
			return arguments[pos-1];
		}
		if(pos == 0)
		{
			getCom();//
		}
	}

	std::string getCom()
	{
		return com;
	}

	bool isLetter(char a)
	{
		if((a > 'a' && a < 'z') || (a > 'A' && a < 'Z'))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool isNumber(char a)
	{
		if((a > '1' && a < '9') || (a == '0'))
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	std::size_t size() const
	{
		return arguments.size();
	}
};

class processor
{
private:
	commands cm;

public:

	bool is_valid(command& com)
	{
		
		if(com.getCom() == "SIZE")
		{
			cm = SIZE;
		}
		if(com.getCom() == "EDIT")
		{
			cm = EDIT;
		}
		if(com.getCom() == "SHOW")
		{
			cm = SHOW;
		}

		switch (cm)
		{
		case SIZE:
			if(com.size() == 0)
			{
				return true;
			}
			break;
		case EDIT:
			if(com.size() == 2)
			{
				return true;
			}
			break;
		case SHOW:
			if(com.size() == 2)
			{
				return true;
			}
			break;		
		default:
			return false;
			break;
		}
	}

	void execute()
	{
		try
		{
			editor help("path"); 
			switch (cm)
			{
			case SIZE:
				std::cout<<help.size()<<'\n';
				break;
			case EDIT:
				//help.edit()
				break;
			case SHOW:
			
				break;		
			default:
			
				break;
			}
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		
		}
	}

};

class editor
{
private:
	bool openedFile = false;
	std::size_t fileSize = 0;
	std::fstream* file;

public:
	editor()
	{
	}

	editor(std::string path)
	{
		open(path);
	}

	void open(std::string path)
	{
		if(!openedFile)
		{
			std::fstream file(path, std::ios::out | std::ios::in | std::ios::binary);
			if(file)
			{
				openedFile = true;
				file.seekg(std::ios::end);
				fileSize = file.tellg();
				this->file = &file;
			}
			else{
				throw std::runtime_error("Unable to open this file");
			}
		}
		else{
			throw std::runtime_error("Please close the current file, before trying to open a new one.");
		}
	}

	void close()
	{
		file->close();
		openedFile = false;
		fileSize = 0;
	}

	std::size_t size()
	{
		return fileSize;
	}

	void edit(std::size_t offset, std::uint8_t value)
	{
		if(offset<fileSize)
		{
			file->seekp(offset);
			file->write((char*)& value, sizeof(uint8_t));
		}
		else
		{
			throw std::invalid_argument("");
		}
	}

	void display(std::ostream& out, std::size_t offset, std::size_t limit)
	{

	}


};





int main()
{
	command com("abv 292");

	return 0;
}