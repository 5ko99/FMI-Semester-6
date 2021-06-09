//ofstream myfile;
//myfile.open ("example.bin", ios::binary);
//myfile << "Writing this to a file.\n";
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Иван Стоилов
// ФН: 82179
// Специалност: кн1
// Курс: 1-ви
// Административна група: 3-та
// Ден, в който се явявате на контролното: 28.05.2021
// Начален час на контролното: 09:00
// Кой компилатор използвате: GCC 

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#define NDEBUG

class Command
{
private:
    std::string command;

public:
    std::size_t size() const
    {
        std::size_t commandLenght = command.size();
        std::size_t counter = 0;
        char separator = ' ';
        std::size_t parametersCount = 0;

        //skip starting whitespaces
        while (command.at(counter) == ' ')
        {
            counter++;
            if (counter + 1 == commandLenght)
            {
                break;
            }
        }
        //checking if reched end
        if (counter + 1 == commandLenght)
        {
            return parametersCount;
        }
        //counting first parameter

        if(command.at(counter) != ' ')
        {
            parametersCount++;
        }

        while (command.at(counter) != ' ')
        {
            counter++;
            if (counter + 1 == commandLenght)
            {
                break;
            }
        }

        if (counter + 1 == commandLenght)
        {
            return parametersCount;
        }
        //skipping whitespaces
        while (command.at(counter) == ' ')
        {
            counter++;
            if (counter + 1 == commandLenght)
            {
                break;
            }
        }
        //check if command is ended
        if (counter + 1 == commandLenght)
        {
            return parametersCount;
        }
        //counting second paramter

        if(command.at(counter) != ' ')
        {
            parametersCount++;
        }

        while (command.at(counter) != ' ')
        {
            counter++;
            if (counter + 1 == commandLenght)
            {
                break;
            }
        }

        if (counter + 1 == commandLenght)
        {
            return parametersCount;
        }
        //skipping whitespaces
        while (command.at(counter) == ' ')
        {
            counter++;
            if (counter + 1 == commandLenght)
            {
                break;
            }
        }
        //check if command ended
        if (counter + 1 == commandLenght)
        {
            return parametersCount;
        }
        //counting third parameter
        while (command.at(counter) != ' ')
        {
            counter++;
            if (counter + 1 == commandLenght)
            {
                break;
            }
        }

        if(command.at(counter) != ' ')
        {
            parametersCount++;
        }

        if (counter + 1 == commandLenght)
        {
            return parametersCount;
        }

    }

    Command(std::string command)
    {
        this->command = command;
    }

    std::string &operator[](std::size_t i)
    {
        std::string result;
        std::size_t counter = 0;
        std::size_t resultCounter = 0;
        std::size_t lenght = size();

        if(i>=size() || i<0)
        {
            throw std::out_of_range("the index is inavalid");
        }

        if (i == 0)
        {

            while (command.at(counter) == ' ')
            {
                counter++;
                if (counter == lenght)
                {
                    throw std::invalid_argument("the command is empty");
                }
                
            }

            while (command.at(counter) !=' ')
            {
                result.at(resultCounter) = command.at(counter);

                ++counter;
                ++resultCounter;

                if (counter == lenght)
                {
                    break;
                }
            }

            return result;
        }
        if(i == 1)
        {
            while (command.at(counter) == ' ')
            {
                counter++;
                if (counter == lenght)
                {
                    throw std::invalid_argument("the command is empty");
                }
                
            }

            while (command.at(counter) !=' ')
            {
                ++counter;

                if (counter == lenght)
                {
                    break;
                }
            }

            while (command.at(counter) == ' ')
            {
                counter++;
                if (counter == lenght)
                {
                    throw std::invalid_argument("the command is empty");
                }
                
            }

            while (command.at(counter) !=' ')
            {
                result.at(resultCounter) = command.at(counter);

                ++counter;
                ++resultCounter;

                if (counter == lenght)
                {
                    break;
                }
            }

            return result;
        }       
        if (i == 2)
        {//skipping first parameter
            while (command.at(counter) == ' ')
            {
                counter++;
                if (counter == lenght)
                {
                    throw std::invalid_argument("the command is empty");
                }
                
            }

            while (command.at(counter) !=' ')
            {
                ++counter;

                if (counter == lenght)
                {
                    break;
                }
            }
            //skipping second parameter
            while (command.at(counter) == ' ')
            {
                counter++;
                if (counter == lenght)
                {
                    throw std::invalid_argument("the command is empty");
                }
                
            }

            while (command.at(counter) !=' ')
            {
                ++counter;

                if (counter == lenght)
                {
                    break;
                }
            }

            while (command.at(counter) == ' ')
            {
                counter++;
                if (counter == lenght)
                {
                    throw std::invalid_argument("the command is empty");
                }
                
            }

            while (command.at(counter) !=' ')
            {
                result.at(resultCounter) = command.at(counter);

                ++counter;
                ++resultCounter;

                if (counter == lenght)
                {
                    break;
                }
            }

            return result;
        }  
    }
};

class Editor
{
private:
    std::ofstream write;
    std::ifstream read;
    std::size_t fileSize;
    std::size_t calculateFileSize()
    {
        read.seekg(0, std::ios::end);
        std::size_t size = read.tellg();
        read.seekg(0, std::ios::beg);

        return size;
    }

public:
    std::size_t getFileSize()
    {
        return fileSize;
    }

    void open(std::string path)
    {
        std::ifstream currentRead(path, std::ios::binary);
        if (!currentRead.is_open())
        {
            throw std::invalid_argument("file connot be opened");
        }
        std::ofstream currentWrite(path, std::ios::binary);

        this->read.swap(currentRead);
        this->write.swap(currentWrite);
        currentRead.close();
        currentWrite.close();
    }
    void close()
    {
        write.close();
        read.close();
    }
    Editor(){};

    Editor(const std::string path)
    {
        open(path);
        fileSize = calculateFileSize();
    }

    ~Editor()
    {
        close();
    }  

    void edit(std::size_t offset, std::uint8_t value)
    {

    }  

    void display(std::ostream& out, std::size_t offset, std::size_t limit)
    {

    }
};


//todo: finish Processor
class Processor
{
private:
    Editor editor;

public:
    bool is_valid(Command command)
    {
        if(command.size() == 0)
        {
            return false;
        }
        else if(command.size() == 1)
        {
            std::string commandArgument = command[0];

            if (commandArgument == "EXIT" || commandArgument == "SIZE")
            {
                return true;
            }
            else
            {
                return false;
            }
            
        }
        else if(command.size() == 3)
        {
            std::string commandName = command[0];
            std::string commandFirstArgument = command[1];
            std::string commandSecondArgument = command[2];

            if (commandName != "SHOW" || commandName != "EDIT")
            {
                return false;
            }
            
            //check if the argument are digits

            for (std::size_t i = 0; i < commandFirstArgument.size(); i++)
            {
                if (commandFirstArgument.at(i) < 48 || commandFirstArgument.at(i)>57)
                {
                    return false;
                }
                
            }
            
            for (std::size_t i = 0; i < commandSecondArgument.size(); i++)
            {
                if (commandSecondArgument.at(i) < 48 || commandSecondArgument.at(i)>57)
                {
                    return false;
                }
                
            }

        }        
    }

    void execute(Command command)
    {
        try
        {
            if(!is_valid(command))
            {
                throw std::invalid_argument("the command is invalid");
            }
        }
        catch(const std::exception& e)
        {
            throw e;
        }
        
        if(command.size() == 1)
        {
            std::string commandArgument = command[0];

            if (commandArgument == "EXIT")
            {
                editor.~Editor();
            }
            else if(commandArgument == "SAVE")
            {
                std::cout << editor.getFileSize() << " byte(s)";
            }
            
        }

    }
};



int main(int argc, char* argv[])
{
	return 0;
}