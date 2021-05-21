//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
//
// Име: Христо Жаблянов
// ФН: 82158
// Специалност: Компютърни науки
// Курс: 1
// Административна група: 2
// Ден, в който се явявате на контролното: 15.05.2021
// Начален час на контролното: 09:00
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::invalid_argument;
using std::ios;
using std::string;
using std::vector;

enum class Type {
    INFO,
    WARNING,
    ERROR,
    CRITICAL,
};

class Message {
  private:
    Type type;
    string description;

  public:
    Message(string input) {
        int pos = input.find_first_of(' ');
        if (pos < 1 || pos >= input.length() - 1)
            throw invalid_argument("Not enough arguments");

        string typestr = input.substr(0, pos);
        if (typestr == "INFO")
            type = Type::INFO;
        else if (typestr == "WARNING") {
            type = Type::WARNING;
        } else if (typestr == "ERROR") {
            type = Type::ERROR;
        } else if (typestr == "CRITICAL") {
            type = Type::CRITICAL;
        } else
            throw invalid_argument(typestr.insert(0, "Unknown command: "));

        description = input.substr(pos + 1);
    }

    Type get_type() const { return type; }

    friend std::fstream& operator<<(std::fstream& os, const Message& m) {
        if (m.type == Type::INFO)
            os << "INFO";
        else if (m.type == Type::WARNING)
            os << "WARNING";
        else if (m.type == Type::ERROR)
            os << "ERROR";
        else
            os << "CRITICAL";
        os << ": " << m.description << endl;
        return os;
    }
};

class Logger {
  private:
    static vector<int> logStats;
    fstream* file;

  public:
    Logger(fstream* _file) : file(_file) {}

    void write(const Message& m) const {
        logStats[(int)m.get_type()]++;
        (*file) << m;
    }
};

vector<int> Logger::logStats = {0, 0, 0, 0};

class Configuration {
  private:
    static bool didInit;
    static Logger logger;
    static fstream file;

    Configuration();

  public:
    static void init(string name = "") {
        if (didInit) return;

        if (name.empty()) name = "config.txt";

        file.open(name, ios::in);
        if (!file.is_open()) throw invalid_argument("Could not load configuration");

        string path;
        file >> path;
        file.close();

        if (path.empty()) throw invalid_argument("Not path in file");

        file.open(path, ios::app);
        if (!file.is_open()) throw invalid_argument("Could not load log file");

        logger = Logger(&file);

        didInit = true;
    }

    static void end() { file.close(); }

    static void log(const Message& m) { logger.write(m); }
};

bool Configuration::didInit = false;

int main(int argc, char** args) {
    try {
        if (argc >= 2)
            Configuration::init(args[1]);
        else
            Configuration::init();
    } catch (invalid_argument& e) {
        cout << e.what() << endl;
        return -1;
    }

    string input;
    while (input != "end") {
        cin >> input;
        Message m(input);
        Configuration::log(m);
    }

    Configuration::end();

    return 0;
}