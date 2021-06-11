//
// Created by pgpetrov on 21.05.21 Рі..
//

#include <algorithm>
#include <iomanip>
#include <fstream>
#include "CommandDispatcher.h"

const char* CommandDispatcher::USAGE =
    "VEHICLE <registration> <description>\n"
    "PERSON <name> <id>\n"
    "ACQUIRE <owner-id> <vehicle-id>\n"
    "RELEASE <owner-id> <vehicle-id>\n"
    "REMOVE <what>\n"
    "SAVE <path>\n"
    "SHOW [PEOPLE|VEHICLES|<id>]\n";

bool prompt(std::istream &is, const std::string &str) {
  std::cout << str;
  char ans;
  while (is.get(ans) && std::tolower(ans) != 'y' && std::tolower(ans) != 'n') {
  }
  is.ignore();
  return ans == 'y';
}

std::istream &operator>>(std::istream &is, CommandDispatcher &cd) {
  cd.sout << "$: ";
  std::string tmp;
  std::getline(is, tmp);
  std::istringstream line(tmp);

  std::string command;
  if (line >> command) {
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);
    try {
      try {
        line.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        if (command == "person") {
          cd.dispatchPerson(line);
        } else if (command == "vehicle") {
          cd.dispatchVehicle(line);
        } else if (command == "acquire") {
          cd.dispatchAcquire(line);
        } else if (command == "release") {
          cd.dispatchRelease(line);
        } else if (command == "remove") {
          cd.dispatchRemove(line);
        } else if (command == "save") {
          cd.dispatchSave(line);
        } else if (command == "show") {
          cd.dispatchShow(line);
        } else {
          throw std::invalid_argument("Command not found!");
        }
      } catch(std::istream::failure &error) {
        throw std::invalid_argument(error.what());
      }
    } catch (std::invalid_argument &error) {
      cd.serr << "Incorrect command format: " << error.what() << std::endl;
      cd.sout << "Correct usage is:" << std::endl;
      cd.sout << CommandDispatcher::USAGE;
    } catch (std::logic_error &error) {
      cd.serr << "Command failed!" << std::endl;
      cd.serr << error.what() << std::endl;
    }
  }
  return is;
}

void CommandDispatcher::dispatchPerson(std::istream &is) const {
  std::string name;
  PersonId id;
  is >> std::quoted(name);
  is >> id;
  db.add_person(name, id);
  sout << "Added person with id " << id << " successfully!" << std::endl;
}

void CommandDispatcher::dispatchVehicle(std::istream &is) const {
  std::string registration;
  std::string description;
  is >> registration;
  is >> std::quoted(description);
  db.add_vehicle(registration, description);
  sout << "Added vehicle with registration " << registration << " successfully!" << std::endl;
}

void CommandDispatcher::dispatchAcquire(std::istream &is) const {
  PersonId owner_id;
  std::string vehicle_id;
  is >> owner_id >> vehicle_id;
  db.transfer_vehicle(owner_id, vehicle_id);
  sout << "Transfered vehicle with registration " << vehicle_id << " to person with id " << owner_id << std::endl;
}

void CommandDispatcher::dispatchRelease(std::istream &is) const {
  PersonId owner_id;
  std::string vehicle_id;
  is >> owner_id >> vehicle_id;
  db.release_vehicle(owner_id, vehicle_id);
  sout << "Released vehicle with registration " << vehicle_id << " from person with id " << owner_id << std::endl;
}

void CommandDispatcher::dispatchRemove(std::istream &is) const {
  std::string id;
  is >> id;
  dispatchForEntityId(id, [&](VehicleId vehicle_id) {
    auto owner = db.vehicle(vehicle_id).owner(); // may throw logic_error if vehicle is not found
    if (owner) {
      std::ostringstream prompt_msg;
      prompt_msg << "Are you sure you want to delete vehicle with registration " << vehicle_id
                 << " that is owned by person with id " << owner->id() << "? (y/n)" << std::endl;
      if (!prompt(std::cin, prompt_msg.str())) { //input from is to prompt may throw exception
        return;
      }
    }
    db.remove_vehicle(vehicle_id);
    sout << "Successfully removed vehicle with registration " << vehicle_id  << "." << std::endl;
  }, [&](PersonId person_id) {
    auto& person = db.person(person_id);
    if (!person.owned_vehicles().empty()) {
      std::ostringstream prompt_msg;
      prompt_msg << "Are you sure you want to delete person with id " << person_id
                 << " that owns " << person.owned_vehicles().size() << " vehicles? (y/n)" << std::endl;
      if (!prompt(std::cin, prompt_msg.str())) { //input from is to prompt may throw exception
        return;
      }
    }
    db.remove_person(person_id);
    sout << "Successfully removed person with id " << person_id  << "." << std::endl;
  });
}

void CommandDispatcher::dispatchSave(std::istream &is) const {
  std::string filename;
  is >> std::quoted(filename);
  std::ofstream file(filename);
  db.show_all(file);
}

void CommandDispatcher::dispatchShow(std::istream &is) const {
  std::string what;
  is >> what;
  if (what == "PEOPLE") {
    db.show_people(sout);
  } else if (what == "VEHICLES") {
    db.show_vehicles(sout);
  } else {
    dispatchForEntityId(what, [this](VehicleId vehicle_id) {
      db.vehicle(vehicle_id).verbose_print(sout);
    }, [this](PersonId person_id) {
      db.person(person_id).verbose_print(sout);
    });
  }
}
void CommandDispatcher::dispatchForEntityId(const std::string& id,
                                            const std::function<void(VehicleId)>& fv,
                                            const std::function<void(PersonId)>& fp) {
  try {
    PersonId person_id(std::stoul(id));
    fp(person_id);
  } catch (std::invalid_argument &error1) {
    try {
      VehicleId vehicle_id(id);
      fv(vehicle_id);
    } catch (std::invalid_argument &error2) {
      std::ostringstream ss;
      ss << "Could not convert argument " << id << " neither to a person id nor a vehicle id!" << std::endl;
      ss << error1.what() << std::endl;
      ss << error2.what() << std::endl;
      throw std::invalid_argument(ss.str());
    }
  }
}
