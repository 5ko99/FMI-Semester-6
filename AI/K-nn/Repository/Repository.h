#pragma once

#include<string>
#include<vector>
#include<fstream>
#include "Unit.h"

#define PATH "../Data/data.csv"

class Repository {
public:
    Repository(const Repository &) = delete;

    Repository &operator=(const Repository &) = delete;

    static void open(const std::string &s = PATH);

    static void close();

    static void read();

    static std::vector<Unit> getData();

private:
    Repository() = default;

    std::ifstream file;
    std::string path;
    std::vector<Unit> units;

    static Repository &get();

    void iOpen(const std::string &_path);

    void iClose();

    void iRead();

    ~Repository();

    std::vector<Unit> iGetData();
};