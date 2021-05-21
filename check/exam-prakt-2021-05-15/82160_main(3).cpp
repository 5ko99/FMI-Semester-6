//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
//
// Име: Цветомир Веселинов Каменов
// ФН: 82160
// Специалност: Компютърни науки
// Курс: 1
// Административна група: 2
// Ден, в който се явявате на контролното: 15.05.2021
// Начален час на контролното: <09:00>
// Кой компилатор използвате: <GCC>
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

enum MessageType
{
    info,
    warning,
    error,
    criticalError,
    unknown = -1
};

class Message
{
    MessageType m_type;
    std::string m_text;

public:
    Message(MessageType type = unknown, std::string text = "")
        : m_type(type), m_text(text) {}

    const std::string printMsgType() const;
    friend std::ostream& operator<<(std::ostream& out, const Message& msg);

    MessageType getMsgType() const;
    std::string getText() const;
};

const std::string Message::printMsgType() const
{
    switch(m_type)
    {
        case info         : return "INFO"           ; break;
        case warning      : return "WARNING"        ; break;
        case error        : return "ERROR"          ; break;
        case criticalError: return "CRITICAL ERROR" ; break;
        default           : return "UNKNOWN MESSAGE"; break;
    }
}

std::ostream& operator<<(std::ostream& out, const Message& msg)
{
    out << msg.printMsgType() << ": " << msg.m_text;

    return out;
}

MessageType Message::getMsgType() const
{
    return m_type;
}

std::string Message::getText() const
{
    return m_text;
}

class Logger
{
    Message m_message;

public:
    static unsigned int infMsgCnt ;
    static unsigned int wrnMsgCnt ;
    static unsigned int errMsgCnt ;
    static unsigned int cErrMsgCnt;
    Logger() : m_message()
    {
    }

    static unsigned int getInfMsgCnt(){return infMsgCnt;}
    static unsigned int getWrnMsgCnt(){return wrnMsgCnt;}
    static unsigned int getErrMsgCnt(){return errMsgCnt;}
    static unsigned int getCErrMsgCnt(){return cErrMsgCnt;}

    friend std::ostream& operator<<(std::ostream& out, const Logger& log);

    ~Logger()
    {
    }
};

unsigned int Logger::infMsgCnt  = 0u;
unsigned int Logger::wrnMsgCnt  = 0u;
unsigned int Logger::errMsgCnt  = 0u;
unsigned int Logger::cErrMsgCnt = 0u;

std::ostream& operator<<(std::ostream& out, const Logger& log)
{
}

int main(int argc, const char* argv [])
{
	return 0;
}

