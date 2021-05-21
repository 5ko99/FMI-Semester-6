//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
//
// Име: Венета Славчева Кирева
// ФН: 82184
// Специалност: Компютърни науки
// Курс: 1
// Административна група: 3
// Ден, в който се явявате на контролното: 15.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате:  GCC
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

enum messageType {
    info,
    warning,
    error,
    criticalError
};

class Message
{
    messageType type;
    string description;

    public:

        messageType getType()
        {
            if (type > 3 || type < 0)
            {
                throw invalid_argument("Type is invalid");
                cout << "Type is invalid";
            }
            return this->type;
        }

        Message (messageType setType, string setDescription)
        {
            this->type = setType;
            this->description.c_str() = setDescription.c_str();
        }


        void operator<<(std::ifstream file)
        {
            switch (type) {
                case 0:
                {
                    file << "INFO: ";
                    break;
                }
                case 1:
                {
                    file << "WARNING: ";
                    break;
                }
                case 2:
                {
                    file << "ERROR: ";
                    break;
                }
                case 3:
                {
                    file << "CRITICAL: ";
                    break;
                }
                default:
                {
                    throw invalid_argument("Unrecognised type");
                    break;
                }
            }

            file << description.c_str() << "\n";
        }
};


class Logger
{
    std::fstream log;

    static int countInfo;
    static int countWarning;
    static int countError;
    static int countCritical;

    public:


        Logger(string fileName)
        {
            log.open(fileName, ios::app);
            if (!log.good())
            {
                throw bad_exception("Invalid file path");
                cout << "Invalid file path";
            }
        }

        ~Logger()
        {
            log.close();
        }

        Logger& operator=(Logger const & other)
        {
            this->log = other->log;
            return *this;
        }

        static Logger operator<<(Message m)
        {
            this->log << m;

            if (m.getType() == 0) {
                countInfo++;
            }
            else if (m.getType() == 1) {
                countWarning++;
            }
            else if (m.getType() == 2) {
                countError++;
            }
            else if (m.getType() == 3) {
                countCritical++;
            }
        }

        static void getInfoCount()
        {
            cout << countInfo << "\n";
        }
        static void getWarningCount()
        {
            cout << countWarning << "\n";
        }
        static void getErrorCount()
        {
            cout << countError << "\n";
        }
        static void getCriticalCount()
        {
            cout << countCritical << "\n";
        }
};

class Configuration
{
    string configFile;
    Logger configLog;

    Logger create(string f = "config.txt")
    {
        Logger temp(f);
        return temp;
    }

    public:

        Configuration(Configuration&) = delete;

        Configuration* getInstance(string file)
        {
            Configuration* temp;
            temp.create(file);
            return &temp;
        }

        Logger& getLogger (){
            return configLog;
        }
};

int countInfo = 0;
int countWarning = 0;
int countError = 0;
int countCritical = 0;

int main(string file = "config.txt")
{
    try {
        Configuration config;
        Configuration *ptr = config.getInstance(file);
        char response;
        do {
            cout << "Do you want to log a message? \nEnter y/n: \n";
            cin >> response;
            cout << "Enter message code: ";
            int messageCode;
            cin >> messageCode;
            cout << "\n Enter message description:\n";
            string description;
            cin >> description;
            Message newMessage(messageCode, description);
            config.getLogger() << newMessage;
            cout << "\nInfo Messages Count: " << config.getLogger().getInfoCount() << "\n";
            cout << "Warning Messages Count: " << config.getLogger().getWarningCount() << "\n";
            cout << "Error Messages Count: " << config.getLogger().getErrorCount() << "\n";
            cout << "Critical Messages Count: " << config.getLogger().getCriticalCount()<< "\n";

        } while (response == 'y');
    }
    catch (...)
    {
        cout << "Error has occurred \n";
    }

    return 0;
}