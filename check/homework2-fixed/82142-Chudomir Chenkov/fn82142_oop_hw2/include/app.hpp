#ifndef _APP_HPP_
#define _APP_HPP_

#include "cmd.hpp"
#include "databasemanager.hpp"

class App {
  public:
    App()=default;

    void run();
    void handle(const CMD::Command& cmd);

    void load_file(const std::string &path);
    void save_to_file(const std::string &path);

  private:
    DatabaseManager db_manager;
};

#endif // _APP_HPP_
