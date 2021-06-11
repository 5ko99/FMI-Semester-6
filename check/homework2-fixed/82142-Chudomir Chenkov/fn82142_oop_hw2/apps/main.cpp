#include "app.hpp"

int main(int argc, char *argv[]) {
    App app;

    if (argc > 1) app.load_file(argv[1]);

    app.run();

    return 0;
}
