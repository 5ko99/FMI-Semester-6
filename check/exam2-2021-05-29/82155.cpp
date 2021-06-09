// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Пламен Венелинов Динев
// ФН: 82155
// Специалност: Компютърни науки
// Курс: I
// Административна група: 2
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <utility>
#include <cstdint>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <exception>
#include <stdexcept>

class command
{
    std::vector< std::string > args;

    static std::vector<std::string> parse_command (const std::string &s, const std::locale &loc)
    {
        std::vector<std::string> res;
        const char *ptr = s.data();
        const char *end = ptr + s.size();
        while(ptr < end)
        {
            while(ptr<end && std::isspace(*ptr, loc))
                ptr++;
            if(ptr >= end)
                break;
            const char* arg_begin = ptr;
            while(ptr<end && !std::isspace(*ptr, loc))
                ptr++;
            const char* arg_end = ptr;
            std::size_t arg_size = arg_end - arg_begin;
            res.push_back(std::string(arg_begin, arg_size));
        }
        return res;
    }

public:

    explicit command(const std::string &s)
        : args(parse_command(s, std::locale()))
    { }

    command(const command&) = default;
    command(command&&) = default;

    command& operator=(const command&) = default;
    command& operator=(command&&) = default;

    inline std::size_t size() const
    { return args.size(); }

    inline const std::string& operator[] (std::size_t pos) const
    { return args[pos]; }
};

class editor
{
private:
    std::fstream file;
    std::size_t file_size;

public:
    editor() = default;

    editor(const editor&) = delete;
    editor& operator=(const editor&) = delete;

    // move only
    editor(editor&&) = default;
    editor& operator=(editor&&) = default;

    // Отварянето на файл трябва да може да се направи и при създаване на обект от тип editor.
    // За целта класът да има конструктор, който получава път до файл и го отваря.
    // При отварянето на файл, класът да намира размера му и да го запазва в private променлива от тип std::size_t.
    // За намирането на размера да се използва техниката със seek/tell, която разглеждахме на лекциите.
    explicit editor(const char* path)
        : file(path, std::ios::binary | std::ios::in | std::ios::out)
    {
        if(!file.is_open())
            throw std::runtime_error("Could not open the file");

        file.seekg(0, std::ios::end);
        file_size = file.tellg();
    }

    // Класът да има функции open, close, с които да може да отваря и затваря файл.
    // Ако отварянето на файл пропадне, да се хвърля изключение.
    // Функциите на класа, чрез които се работи с файл, могат да работят само ако има успешно отворен файл.
    // Файлът да се отваря в двоичен режим и да се държи отворен до извикване на close или
    // до унищожаване на обекта от тип editor.
    void open(const char* path)
    {
        file.close();
        file.open(path, std::ios::binary | std::ios::in | std::ios::out);
        if(!file.is_open())
            throw std::runtime_error("Could not open the file");

        file.seekg(0, std::ios::end);
        file_size = file.tellg();
    }

    void close() noexcept
    {
        file.close();
    }

    ~editor() = default;

    // Класът да има функция size, която връща размера му като стойност от тип std::size_t.
    inline std::size_t size() const noexcept
    { return file_size; }

    // Класът да има функция edit(std::size_t offset, std::uint8_t value).
    // Тя записва стойността value на позиция offset спрямо началото на файла.
    // Ако offset се намира след края на файла, функцията да не прави нищо,
    // а да хвърля изключение от тип std::invalid_argument.
    void edit(std::size_t offset, std::uint8_t value)
    {
        if(offset >= file_size)
            throw std::runtime_error("Offset is larger than the file size");
        file.seekp(offset, std::ios::beg);
        file.write(reinterpret_cast<const char*>(&value), 1);
        file.flush();
    }

    // Класът да има функция display(std::ostream& out, std::size_t offset, std::size_t limit).
    // Функцията извежда, на потока <out>, подобно на шестнадесетичен редактор, съдържанието на файла,
    // започвайки от позиция <offset>. Извежданато да приключи или когато се изведат точно <limit> на брой байта,
    // или се достигне краят на файла. Ако позицията <offset> се намира след края на файла, да не се извеждат нищо,
    // а да се хвърли изключение от тип std::invalid_argument. За точния формат, в който да се извеждат данните,
    // вижте описанието на командата SHOW по-долу.
    // SHOW <offset> <limit> Извежда на екрана, подобно на шестнадесетичен редактор, съдържанието на файла,
    // започвайки от позиция <offset>. Извежданато да приключи или когато се изведат <limit> на брой байта,
    // или се достигне края на файла. Ако позицията <offset> се намира след края на файла, да не се извеждат байтове,
    // а вместо това да се изведе съобщение, което уведомява потребителя колко е размерът на файла. Както <offset>,
    // така и <limit> да се въвеждат като числа в десетичен запис.
    // При извеждането да се използва познатия ви от шестнадесетичните редактори формат.
    // Байтовете да се извеждат един след друг, разделени с интервали.
    // Всеки байт да се изведе в шестнадесетичен запис – число с точно две цифри, при нужда, с водеща нула.
    // След всеки 16 изведени байта, да се извежда нов ред. В началото на всеки от изведените редове да се извежда
    // отстъпа на първия байт в него спрямо началото на файла. В края на задачата е показан нагледен пример за това
    // как трябва да изглежда извеждането.
    // Упътване: за извеждане в шестнадесетичен режим, използвайте манипулатора std::hex.
    // За запълване с водещи нули и точна широчина, използвайте std::setfill и std::setw.
    // За да можете да работите с тях, включете заглавния файл <iomanip>. Например:
    void display(std::ostream& out, std::size_t offset, std::size_t limit)
    {
        if(offset >= file_size)
            throw std::runtime_error("Offset is larger than the file size");
        limit = std::min(limit, file_size-offset);
        file.seekg(offset, std::ios::beg);
        std::vector<uint8_t> tmp_buffer(limit);
        file.read(reinterpret_cast<char*>(tmp_buffer.data()), limit);

        std::size_t cur_tmp_buffer_pos=0;
        while (limit > 0)
        {
            out << std::setfill('0') << std::setw(8) << std::hex << offset << ' ';
            std::size_t bytes_in_line = std::min<std::size_t>(limit, 16);
            for(size_t i=0; i<bytes_in_line; i++)
            {
                out << std::setfill('0') << std::setw(2) << std::hex
                    << static_cast<unsigned int>(tmp_buffer[cur_tmp_buffer_pos++])
                    << ' ';
                limit--; offset++;
            }
            out << '\n';
        }
    }
};

class processor
{
private:
    editor e;
    std::ostream &out;
    std::ostream &err;

public:

    processor(const char *path, std::ostream& _out, std::ostream &_err)
        : e(path), out(_out), err(_err)
    { }

    processor(const processor&) = delete;
    processor& operator=(const processor&) = delete;

    // move only
    processor(processor&&) = default;
    processor& operator=(processor&&) = default;

    // Класът да има предикат is_valid, която получава обект от тип command и връща true или false,
    // в зависимост дали командата е коректна или в нея има грешка.
    static bool is_valid(const command &c)
    {
        if(c.size() <= 0)
            return false; // there is no command
        if(c[0] == "EXIT" && c.size() == 1)
            return true; // EXIT
        if(c[0] == "SIZE" && c.size() == 1)
            return true; // SIZE
        if(c[0] == "EDIT" && c.size() == 3)
            return true; // EDIT <offset> <byte>
        if(c[0] == "SHOW" && c.size() == 3)
            return true; // SHOW <offset> <limit>
        return false;
    }

    // Класът да има функция execute, която получава команда и я изпълнява.
    // returns true if EXIT command is ran
    bool execute(const command &c) noexcept
    {
        if(!is_valid(c))
        {
            err << "Could not execute command:\n"
                   "Invalid command/invalid argument!\n";
            err.flush();
            return false;
        }
        // here c.size() is at least 1
        if(c[0] == "EXIT")
            return true;
        try {
            if(c[0] == "SIZE")
            {
                out << std::setfill(' ') << std::setw(0) << std::dec
                    << e.size() << " byte(s)\n";
            }
            else if(c[0] == "EDIT") // EDIT <offset> <byte>
            {
                std::size_t offset;
                unsigned long byte;
                try {
                    offset = std::stoull(c[1]);
                    byte = std::stoul(c[2], nullptr, 16);
                } catch(std::exception &e)
                {
                    throw std::invalid_argument("Invalid argument for command EDIT");
                }
                if(byte > std::numeric_limits<uint8_t>::max())
                    throw std::invalid_argument("Argument byte is larger than a byte.");
                e.edit(offset, static_cast<uint8_t>(byte));
                out << "OK!\n";
            }
            else if(c[0] == "SHOW") // SHOW <offset> <limit>
            {
                std::size_t offset;
                std::size_t limit;
                try {
                    offset = std::stoull(c[1]);
                    limit = std::stoull(c[2]);
                } catch(std::exception &e)
                {
                    throw std::invalid_argument("Invalid argument for command EDIT");
                }
                e.display(out, offset, limit);
            }
        } catch (std::exception &e)
        {
            err << "Could NOT execute command! Reason:\n" << e.what() <<'\n';
            err.flush();
        }

        return false;
    }

};

int main(int argc, const char *argv[])
{
//    command c("TEst asd das");
//    std::cout << c.size() << ' ' << c[0] << ' ' << c[1] << ' ' << c[2] << '\n';

//    editor e("test.bin");
//    e.display(std::cout, 50, 20);
//    std::cout << "-------------------\n";
//    e.display(std::cout, 96, 20);

    if(argc != 2)
    {
        std::clog << "Binary file not supplied as argument!\n";
        std::clog.flush();
        std::exit(EXIT_FAILURE);
    }

    processor p(argv[1], std::cout, std::clog);
    std::string cur_command;
    while(std::cin.good())
    {
        std::cin.clear();
//        std::cout << "> ";
        std::getline(std::cin, cur_command);
        bool time_to_exit = p.execute(command(cur_command));
        if(time_to_exit)
            break;
    }

    return 0;
}