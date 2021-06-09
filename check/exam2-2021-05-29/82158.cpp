//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
//
// Име: Христо Жаблянов
// ФН: 82158
// Специалност: Компютърни науки
// Курс: 1
// Административна група: 2
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 09:00
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::invalid_argument;
using std::ios;
using std::ostream;
using std::size_t;
using std::stoi;
using std::string;
using std::uint8_t;
using std::vector;

class Command {
  private:
    string name;
    vector<string> args;

  public:
    Command(string line) {
        int index = line.find_first_of(" ", 0);
        if (index <= 0) throw invalid_argument("Command should start with its name");

        name = line.substr(0, index);

        for (size_t i = index; i < line.size(); i++) {
            if (line[i] == ' ') continue;

            index = line.find_first_of(" ", i);

            args.push_back(line.substr(i, index));

            i = index;
        }
    }

    size_t size() const { return args.size(); }

    const string& get_name() const { return name; }

    const string& operator[](size_t i) const {
        assert(i <= args.size());
        return i == 0 ? name : args[i - 1];
    }
};

class Editor {
  private:
    fstream file;
    bool opened;
    size_t len;

  public:
    Editor() : opened(false) {}

    Editor(string path) : opened(false) { open(path); }

    ~Editor() {
        if (opened) file.close();
    }

    bool is_opened() const { return opened; }

    size_t size() const { return len; }

    void open(string path) {
        close();

        file.open(path, ios::binary | ios::in | ios::ate);
        if (!file) throw invalid_argument("Could not open file");

        file.seekg(0, ios::end);
        len = file.tellg();
        file.seekg(0, ios::beg);

        opened = true;
    }

    void close() {
        if (!opened) return;
        file.close();
        opened = false;
    };

    void edit(size_t offset, uint8_t value) {
        if (offset >= len) throw invalid_argument("offset is too big");
        if (!opened) throw invalid_argument("file is not opened");

        file.seekp(offset, ios::beg);
        file.write((char*)&value, 1);
        len++;
    }

    void display(ostream& out, size_t offset, size_t limit) {
        if (offset >= len) throw invalid_argument("offset is too big");
        if (offset + limit >= len) limit -= offset + limit - len;
        out << std::setfill('0') << std::setw(2) << std::hex;

        uint8_t* text = new uint8_t(limit - offset);
        file.seekg(offset, ios::beg);
        file.read((char*)text, limit - offset);

        for (size_t i = 0; i < limit - offset; i++) {
            if (i % 6 == 1) out << endl;
            out << (unsigned int)text[i] << " ";
        }

        out << std::dec << std::endl;
        delete[] text;
    }
};

class Processor {
  private:
    Editor* editor;

    bool is_valid(const Command& c) const {
        if ((c.get_name() == "EXIT" || c.get_name() == "SIZE") && c.size() != 0)
            return false;

        if ((c.get_name() == "EDIT" || c.get_name() == "SHOW") && c.size() != 2)
            return false;

        return true;
    }

  public:
    Processor(Editor* _editor) : editor(_editor) {}

    bool is_running() const { return editor->is_opened(); }

    void execute(const Command& c) {
        if (!editor->is_opened()) return;

        if (!is_valid(c)) {
            cout << "Not a valid command\n";
            return;
        }

        if (c.get_name() == "EXIT") {
            editor->close();
        } else if (c.get_name() == "SIZE") {
            cout << editor->size() << endl;
        } else if (c.get_name() == "EDIT") {
            try {
                editor->edit(stoi(c[0]), stoi(c[1]));
            } catch (invalid_argument& e) {
                cout << e.what() << endl << "File length: " << editor->size() << endl;
            }
        } else if (c.get_name() == "SHOW") {
            try {
                editor->display(cout, stoi(c[0]), stoi(c[1]));
            } catch (invalid_argument& e) {
                cout << e.what() << endl << "File length: " << editor->size() << endl;
            } catch (std::bad_alloc& e) {
                cout << "Memory error: " << e.what() << endl;
            }
        }
    }
};

int main(int argc, char** args) {
    if (argc != 1) {
        cout << "Expected file name and nothing more\n";
        return -1;
    }

    Editor* editor;

    try {
        editor = new Editor{string{args[0]}};
    } catch(invalid_argument& e) {
        cout << e.what();
    }

    Processor processor{editor};

    string input;
    while (processor.is_running()) {
        getline(cin, input);
        Command c{input};
        processor.execute(c);
    }

    delete editor;
    return 0;
}