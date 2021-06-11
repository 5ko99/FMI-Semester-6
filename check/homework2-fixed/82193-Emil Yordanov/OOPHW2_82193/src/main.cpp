#include<iostream>
#include<fstream>
#include<cstring>
#include<exception>
#include<vector>

#include"main.h"

/* For reference:
 * argc == Arguments count (int)
 * argv == Arguments values (char *)
 */
int main(int argc, char * argv[]) {
    // Engine that decides what to do with user commands
    CMDEngine cmdEngine = CMDEngine();

    // Used to save all commands to a file when needed
    std::string commandOrderData = std::string("");

    VehicleManager vManager = VehicleManager();
    PersonManager pManager = PersonManager();

    // Initial file reading section
    if(argc > 1) {
        try {
            if(argc > 2) {
                // Throws an exception because there are too much arguments
                throw std::exception();
            }
            std::string inputFilePath = argv[1];
            std::ifstream inputFile(inputFilePath);
            
            std::string fileCMDs = std::string("");
            
            inputFile >> fileCMDs;

            std::vector<std::string> cmdRows;
            StringHelper::StringSplit(fileCMDs, cmdRows, '\n');

            // Separate by '\n' and pass through CMD algorithm
            for(size_t iterator = 0; iterator < cmdRows.size(); iterator++) {
                std::vector<std::string> cmdArguments;
                StringHelper::StringSplit(cmdRows[iterator], cmdArguments);

                std::string userCMD = std::string("");

                std::string firstArgument = std::string("");
                std::string secondArgument = std::string("");

                if(cmdArguments.size() > 3 || cmdArguments.size() < 2) {
                    // Throws an exception because there are too much/not enough command arguments
                    throw std::exception();
                }
                else {
                    userCMD = cmdArguments[0];

                    firstArgument = cmdArguments[1];

                    if(cmdArguments.size() == 3) {
                        secondArgument = cmdArguments[2];
                    }

                    // For more info check 'ParseCMDToData' implementation
                    cmdEngine.ParseCMDToData(userCMD, firstArgument, secondArgument, commandOrderData, pManager, vManager);
                }
            }
        }
        catch (...) {
            std::cout << "Unhandled exception: An unexpected error occurred while reading your file!" << std::endl;
        }    
    }

    while(true) {
        std::string userCMD = std::string("");

        std::string firstArgument = std::string("");
        std::string secondArgument = std::string("");

        std::cin >> userCMD;

        try {
            // For more info check 'ParseCMDToData' implementation
            bool toContinue = cmdEngine.ParseCMDToData(userCMD, firstArgument, secondArgument, commandOrderData, pManager, vManager);

            if(!toContinue) {
                break;
            }
        }
        catch(...) {
            std::cout << "Unhandled exception: An unexpected error occurred while processing your command!" << std::endl;
        }
    }

    return 0;
}
