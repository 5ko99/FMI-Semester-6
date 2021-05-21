// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Пламен Венелинов Динев
// ФН: 82155
// Специалност: Компютърни науки
// Курс: I
// Административна група: 2. група
// Ден, в който се явявате на контролното: 15.05.21 г.
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//

#include <cstddef>
#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>
#include <limits>

class Message
{
public:
    enum class message_type
    {
        INFO=0,
        WARNING,
        ERROR,
        CRITICAL_ERROR,
        ERROR_COUNT
    };

    const message_type type;
    const std::string description;

private:

    static const char* message_type_to_str (message_type t)
    {
        switch (t)
        {
            case message_type::INFO:
                return "INFO"; //break;
            case message_type::WARNING:
                return "WARNING"; //break;
            case message_type::ERROR:
                return "ERROR"; //break;
            case message_type::CRITICAL_ERROR:
                return "CRITICAL"; //break;
            default:
                assert(0); // we should not be here
                break;
        }
    }

public:

    Message(message_type t, const std::string &desc) : type(t), description(desc)
    {}

    Message(message_type t, std::string &&desc) : type(t), description(std::move(desc))
    {}

    Message(const Message &m) = default;

    Message(Message &&m) = default;

    void operator=(const Message&) = delete;
    void operator=(Message&&) = delete;

    friend std::ostream& operator<< (std::ostream &out, const Message& m)
    {
        out << message_type_to_str(m.type) << ": " << m.description;
        return out;
    }

    friend std::ostream& operator<< (std::ostream &out, const Message&& m)
    {
        out << message_type_to_str(m.type) << ": " << m.description;
        return out;
    }

};

class Logger
{
private:
    std::ofstream log_file;

    static std::size_t message_type_stats[(std::size_t)(Message::message_type::ERROR_COUNT)];

    static void update_message_type_stats (Message::message_type t)
    {
        assert((std::size_t)t < (std::size_t)(Message::message_type::ERROR_COUNT));
        message_type_stats[(std::size_t)t]++;
    }

public:
    Logger() = default;
    ~Logger() = default;
    Logger(const Logger&) = delete;
    void operator=(const Logger&) = delete;

    explicit Logger (const char *file_path) : log_file(file_path, std::ios::out | std::ios::app)
    {
        if (!log_file.is_open())
            throw std::runtime_error("Could not open the _log file");
    }

    void open(const char *file_path)
    {
        log_file.close();
        log_file.open(file_path, std::ios::out | std::ios::app);
        if (!log_file.is_open())
            throw std::runtime_error("Could not open the log file");
    }

    Logger& operator<< (const Message &m)
    {
        update_message_type_stats(m.type);
        if(!log_file.is_open())
            throw std::runtime_error("Log file is not opened");
        log_file << m << '\n';
        log_file.flush();
        if(log_file.bad())
        {
            log_file.clear();
            throw std::runtime_error("Error while writing to the log file");
        }
        return *this;
    }

    Logger& operator<< (Message &&m)
    {
        update_message_type_stats(m.type);
        if(!log_file.is_open())
            throw std::runtime_error("Log file is not opened");
        log_file << m << '\n';
        log_file.flush();
        if(log_file.bad())
        {
            log_file.clear();
            throw std::runtime_error("Error while writing to the log file");
        }
        return *this;
    }

    static std::size_t get_message_type_counts (Message::message_type t)
    {
        assert((std::size_t)t < (std::size_t)(Message::message_type::ERROR_COUNT));
        return message_type_stats[(std::size_t)t];
    }
};

std::size_t Logger::message_type_stats[(std::size_t)(Message::message_type::ERROR_COUNT)] = { 0 };

class Configuration
{
private:
    Configuration() = default;

    std::string _configuration_path;
    Logger _log;

    static Configuration c;

public:

    static void load (const char *config_file_path)
    {
        std::ifstream cfg (config_file_path);
        if(!cfg.is_open())
            throw std::runtime_error("Could not open the configuration file");
        std::string log_path;
        std::getline(cfg, log_path);
        if(cfg.bad())
            throw std::runtime_error("Could not read the configuration file");
        cfg.close();

        c._log.open(log_path.c_str());

        c._configuration_path = config_file_path;
    }

    static const char* configuration_path()
    {
        return c._configuration_path.c_str();
    }

    static Logger& log()
    {
        return c._log;
    }
};

Configuration Configuration::c;

int main(int argc, const char *argv[])
{
    const char* configuration = "config.txt";
    if(argc == 2)
        configuration = argv[1];

    // if an exception is thrown here an error message is outputted and the program is killed
    Configuration::load(configuration);

    std::string command, msg;

    while(true)
    {
        try {
            std::cin >> command;
            if (command == "exit")
            {
                break;
            }
            else if(command == "info" || command == "warning" || command == "error" || command == "critical")
            {
                while(std::cin.peek() == ' ') std::cin.get(); //remove whitespaces
                std::getline(std::cin, msg);
                Message::message_type t;
                if(command == "info")
                    t = Message::message_type::INFO;
                else if(command == "warning")
                    t = Message::message_type::WARNING;
                else if(command == "error")
                    t = Message::message_type::ERROR;
                else
                    t = Message::message_type::CRITICAL_ERROR; //default value

                Configuration::log() << Message(t, std::move(msg));
            }
            else if(command == "stats")
            {
                std::cout << "Logger statistics since the start of the program:\n"
                             "  - INFO: " << Logger::get_message_type_counts(Message::message_type::INFO) << "\n"
                             "  - WARNING: " << Logger::get_message_type_counts(Message::message_type::WARNING) << "\n"
                             "  - ERROR: " << Logger::get_message_type_counts(Message::message_type::ERROR) << "\n"
                             "  - CRITICAL: " << Logger::get_message_type_counts(Message::message_type::CRITICAL_ERROR) <<
                             std::endl;
            }
            else
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::clog << "Error: Unknown command\n"
                             "Usage:\n"
                             "msg_type msg\n"
                             "  Puts the message msg in the log file, "
                             "where msg_type is one of \"info\" \"warning\" \"error\" and \"critical\".\n"
                             "stats\n"
                             "  Prints log statistics\n"
                             "exit\n"
                             "  Exits from the program" << std::endl;
            }
        } catch (std::exception &e)
        {
            std::clog << e.what() << std::endl;
        }
    }


	return 0;
}