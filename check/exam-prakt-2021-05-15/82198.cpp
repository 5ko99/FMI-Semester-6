//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
//
// Име: Александър Костадинов
// ФН: 82198
// Специалност: КН
// Курс: първи
// Административна група: 4
// Ден, в който се явявате на контролното: 15.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>

enum type
{
    UNKNOWN = -1,
    INFO = 1,
    WARNING,
    ERROR,
    CRITICAL,
};

class Message
{
private:
    std::string description;
    int type;

public:
    Message(std::string desc, int type)
    {
        this->description = desc;
        switch (type)
        {
        case 1:
            this->type = INFO;
            break;
        case 2:
            this->type = WARNING;
            break;
        case 3:
            this->type = ERROR;
            break;
        case 4:
            this->type = CRITICAL;
            break;

        default:
            throw std::invalid_argument("Wrong message type");
            break;
        }
    }

    friend std::ostream &operator<<(std::ostream &out, const Message &message)
    {
        out << message.type << " ";
        out << message.description;

        return out;
    }

    const int get_message_type() const { return this->type; }
};

class Logger
{
private:
    std::string file_name;

public:
    static size_t count_of_messages_type1;
    static size_t count_of_messages_type2;
    static size_t count_of_messages_type3;
    static size_t count_of_messages_type4;
    Logger()
    {
    }

    void set_logger_file(std::string s)
    {
        this->file_name = s;
    }

    Logger operator<<(const Message &message)
    {
        std::ofstream out(this->file_name, std::ios::app);

        if (out.is_open())
        {
            out << message << "\n";

            if (message.get_message_type() == 1)
            {
                count_of_messages_type1++;
            }
            else if (message.get_message_type() == 2)
            {
                count_of_messages_type2++;
            }
            else if (message.get_message_type() == 3)
            {
                count_of_messages_type3++;
            }
            else if (message.get_message_type() == 4)
            {
                count_of_messages_type4++;
            }
        }

        out.close();
    }

    static int *get_number_of_types_messages()
    {
        try
        {
            int *types = new int[4];

            types[0] = count_of_messages_type1;
            types[1] = count_of_messages_type2;
            types[2] = count_of_messages_type3;
            types[3] = count_of_messages_type4;

            return types;
        }
        catch (...)
        {
            std::cerr << "Could not get the number of type-messages!" << '\n';
            return nullptr;
        }

        return nullptr;
    }
};

size_t Logger::count_of_messages_type1 = 0;
size_t Logger::count_of_messages_type2 = 0;
size_t Logger::count_of_messages_type3 = 0;
size_t Logger::count_of_messages_type4 = 0;

class Configuration
{
private:
    std::string file_name;
    Logger log;
    static Configuration *config;

    Configuration(std::string file_name)
    {
        this->file_name = file_name;

        std::ifstream in(file_name);
        std::string line;
        if (in.is_open())
        {
            in >> line;
        }

        if (!line.empty())
        {
           log.set_logger_file(line);
        }
        else
        {
            throw std::invalid_argument("There is no file to log to!\n");
        }
        
        

        in.close();
    }

public:
    static Configuration *get_config(std::string file_name)
    {
        if (!config)
        {
            config = new Configuration(file_name);
        }
        else
        {
            
            throw std::logic_error("Config already exists!\n");
        }

        return config;
    }

    Logger &get_logger()
    {
        return this->log;
    }
};

Configuration *Configuration::config = nullptr;

int main(int argc, char *argv[])
{
    Configuration *config;

    if (argv[1])
    {
        config = config->get_config(argv[1]);
    }
    else
    {
        std::string default_file = "config.txt";
        config = config->get_config(default_file);
        //  Configuration *config2 = config->get_config(default_file);
    }

    while (true)
    {
        std::cout << "If you want to exit press 6\n";
        std::cout << "Add a message: \n";
        int k;
        char *message;
        std::cin >> k;
        std::cin.ignore();
        std::cin.getline(message, 100);

        if (k == 6)
        {
            return 0;
        }

        Message message1(message, k);

        config->get_logger() << message1;
    } 

    return 0;
}