//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
//
// Име: Соня Николова Николова
// ФН:  82213
// Специалност: Компютърни науки
// Курс: I
// Административна група: IV
// Ден, в който се явявате на контролното: 15.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>

const int INITIAL_CAPACITY = 2;
const int RESIZE_STEP = 2;

enum Type
{
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class Message
{
private:
    Type type;
    std::string description;

public:
    Message(const Type type, const std::string description);

    Type getType() const;

    friend std::ostream &operator<<(std::ostream &out, const Message &message);
};

Message::Message(const Type type, const std::string description)
{
    this->type = type;
    this->description = description;
}

Type Message::getType() const
{
    return this->type;
}

std::ostream &operator<<(std::ostream &out, const Message &message)
{
    switch (message.type)
    {
    case 0:
        out << "INFO";
        break;
    case 1:
        out << "WARNING";
        break;
    case 2:
        out << "ERROR";
        break;
    case 3:
        out << "CRITICAL";
        break;
    }
    out << ": " << message.description << std::endl;

    return out;
}

class Logger
{
private:
    int cntOfMessages;
    int cntOfInfo;
    int cntOfError;
    int cntOfWarning;
    int cntOfCritical;

    std::string file;
    Message **messages;
    int capacity;
    int size;

    void resize();
    void deallocate();

public:
    Logger() {}
    Logger(const std::string file);
    ~Logger();

    friend std::ostream &operator<<(std::ostream &out, const Logger &log);

    void addMessage(Message &message);

    int getCntMessages() const;
    int getCntInfo() const;
    int getCntError() const;
    int getCntWarning() const;
    int getCntCritical() const;
    std::string getFileName() const;

    static int countOfMessages;
    static int countOfInfo;
    static int countOfError;
    static int countOfWarning;
    static int countOfCritical;
};

static int countOfMessages = 0;
static int countOfInfo = 0;
static int countOfError = 0;
static int countOfWarning = 0;
static int countOfCritical = 0;

Logger::Logger(const std::string file)
{
    this->file = file;

    try
    {
        this->messages = new Message *[INITIAL_CAPACITY];
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < INITIAL_CAPACITY; i++)
    {
        this->messages[i] = nullptr;
    }
    this->capacity = INITIAL_CAPACITY;
    this->size = 0;
}
Logger::~Logger()
{
    this->deallocate();
    this->capacity = 0;
    this->size = 0;
}

void Logger::deallocate()
{
    for (int i = 0; i < this->capacity; i++)
    {
        if (this->messages[i])
        {
            delete this->messages[i];
        }
    }
    delete[] this->messages;
}
void Logger::resize()
{
    this->capacity *= RESIZE_STEP;

    Message **newMessages;
    try
    {
        newMessages = new Message *[this->capacity];
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    for (int i = 0; i < this->capacity; i++)
    {
        newMessages[i] = this->messages[i];
    }
    this->deallocate();
    this->messages = newMessages;
}
void Logger::addMessage(Message &message)
{
    if (this->size == this->capacity)
    {
        this->resize();
    }
    else
    {
        this->messages[this->size] = &message;
        switch (message.getType())
        {
        case 0:
            this->cntOfMessages = ++countOfInfo;
            break;
        case 1:
            this->cntOfWarning = ++countOfWarning;
            break;
        case 2:
            this->cntOfError = ++countOfError;
            break;
        case 3:
            this->cntOfCritical = ++countOfCritical;
            break;
        }
        this->size++;
        countOfMessages++;
    }
}
std::string Logger::getFileName() const
{
    return this->file;
}

int Logger::getCntMessages() const
{
    return this->cntOfMessages;
}
int Logger::getCntInfo() const
{
    return this->cntOfInfo;
}
int Logger::getCntError() const
{
    return this->cntOfError;
}
int Logger::getCntWarning() const
{
    return this->cntOfWarning;
}
int Logger::getCntCritical() const
{
    return this->cntOfCritical;
}

std::ostream &operator<<(std::ostream &out, const Logger &log)
{

    std::ofstream output(log.file.c_str(), std::ios::app);
    if (output.is_open())
    {
        for (int i = 0; i < log.size; i++)
        {
            output << log.messages[i] << std::endl;
        }
        output.close();
    }
    return out;
}

class Configuration
{
private:
    std::string filePath;
    Logger log;
    Configuration() {}

public:
    Configuration(const Configuration &other) = delete;
    Configuration &operator=(const Configuration &other) = delete;
    Configuration &operator=(const Configuration &&other) = delete;

    Configuration(std::string filePath);
};

Configuration::Configuration(std::string filePath)
{
    static Configuration config;
    config.filePath = filePath;
    
}
int main()
{

    Message m1(INFO, "test");
    Message m2(ERROR, "test2");
    std::cout << m1;
    std::cout << m2;
    // Logger log;
    // log.addMessage(m1);
    // log.addMessage(m2);
    // std::cout << log;

    return 0;
}