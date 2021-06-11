#include "PVDatabase/PVDatabase.h"

int main(int argc,char* argv[]) {
    PVDatabase pVDatabase;
    pVDatabase.setUp(argc, argv);
    pVDatabase.readCommands();
    return 0;
}
