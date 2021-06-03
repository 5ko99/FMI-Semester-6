#include <iostream>
#include<string>
#include <utility>
#include<fstream>

struct A {
    int a;
    char c;

    explicit A(int a = 0, char c = 'a') : a(a), c(c) {}
};

class Repository {
public:
    Repository(const Repository &) = delete;

    Repository(Repository &&r) = delete;

    Repository &operator=(const Repository &r) = delete;

    Repository &operator=(Repository &&r) = delete;

    static Repository &get() {
        static Repository instance;
        return instance;
    }

    static void open(const std::string &path) {
        get().iOpen(path);
    }

    static void write(const A &a) {
        get().iWrite(a);
    }

    static void read(A &a) {
        get().iRead(a);
    }

private:

    std::string path;
    std::ofstream out;
    std::ifstream in;

    explicit Repository() = default;

    ~Repository() {
        out.close();
        in.close();
    }

    void iOpen(const std::string &_path) {
        path = _path;
        out.open(path, std::ios::app | std::ios::binary | std::ios::out);
        in.open(path, std::ios::in | std::ios::binary);
        if (!out || !in)
            throw std::runtime_error("file not opened!");
    }

    void iWrite(const A &a) {
        out.write((const char *) &a.c, sizeof(char));
        if (!out.good())
            throw std::runtime_error("Error while writing!");
    }

    void iRead(A &a) {
        in.seekg(std::ios::beg);
        in.read((char *) &a.c, sizeof(char));
        if (!in.good())
            throw std::runtime_error("Error while reading!");
    }

    static Repository sInstance;
};


int main() {
    A a(1, 'P');
    Repository::open("file.bin");
    Repository::write(a);
    Repository::write(A(8, 6));
    A a1;
    Repository::read(a1);
    std::cout<<a1.c;
    return 0;
}
