#include "src/cli.h"

int main(int argc, char** args) {
    string path {argc == 2 ? args[1] : "database.txt"};

    try {
        Cli(path).run();
    } catch (invalid_argument& e) {
        cout << "Invalid: " << e.what() << endl;
        return 1;
    }

    return 0;
}
