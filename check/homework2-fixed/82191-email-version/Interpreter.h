#include <string>

#include "Database.h"

class Interpreter
{
public:
    Interpreter(const Database& database);
    void Process(const std::string& command);
    
    static void ShowHelp();
    
private:
    void ProcessShow(const std::vector<std::string>& args);
    void ProcessSave(const std::vector<std::string>& args);
    void ProcessRemove(const std::vector<std::string>& args);
    void ProcessAcquire(const std::vector<std::string>& args);
    void ProcessRelease(const std::vector<std::string>& args);
    void ProcessInsertVehicle(const std::vector<std::string>& args);
    void ProcessInsertPerson(const std::vector<std::string>& args);
    
private:
    Database m_Database;
};
