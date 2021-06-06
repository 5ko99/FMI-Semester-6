#include "Repository.h"

void Repository::open(const std::string &s) {
    get().iOpen(s);
}

void Repository::close() {
    get().iClose();
}

void Repository::read() {
    get().iRead();
}

std::vector<Unit> Repository::getData() {
    return get().iGetData();
}

Repository &Repository::get() {
    static Repository instance;
    return instance;
}

void Repository::iOpen(const std::string &_path) {
    path = _path;
    file.open(path, std::ios::in);
    if (!file)
        throw std::runtime_error("File not opened successfully");
}

void Repository::iClose() {
    file.close();
}

void Repository::iRead() {
    if (!file.good())
        throw std::runtime_error("Error before read!");
    file.seekg(0, std::ios::beg);
    while (!file.eof()) {
        Unit u;
        std::string word;
        getline(file, word, ';');
        try {
            u.spend = std::stoi(word);
        } catch (...) {
            break;
        }

        getline(file, word, ';');
        if (word == "Very often ") u.frequency = VERY_OFTEN;
        if (word == "Often") u.frequency = OFTEN;
        if (word == "Sometimes ") u.frequency = SOMETIMES;
        if (word == "Rarely") u.frequency = RARELY;
        getline(file, word, '\r');
        try {
            u.type = std::stoi(word);
        } catch (...) {
            break;
        }
        if (!file.good())
            throw std::runtime_error("Error at read!");
        units.push_back(u);
        getline(file, word);
    }
}

Repository::~Repository() {
    iClose();
}

std::vector<Unit> Repository::iGetData() {
    return units;
}