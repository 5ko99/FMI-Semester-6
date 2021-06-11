//
// Created by pgpetrov on 21.05.21 Рі..
//

#ifndef HWUNI2_SRC_COMMANDDISPATCHER_H_
#define HWUNI2_SRC_COMMANDDISPATCHER_H_

#include <iostream>
#include <functional>
#include "DB.h"

class CommandDispatcher {
 public:
  explicit CommandDispatcher(DB &db, std::ostream& sout = std::cout, std::ostream& serr = std::cerr) : db(db), sout(sout), serr(serr) {}
  friend std::istream &operator>>(std::istream &is, CommandDispatcher &cd);
  void dispatchPerson(std::istream &is) const;
  void dispatchVehicle(std::istream &is) const;
  void dispatchAcquire(std::istream &is) const;
  void dispatchRelease(std::istream &is) const;
  void dispatchRemove(std::istream &is) const;
  void dispatchSave(std::istream &is) const;
  void dispatchShow(std::istream &is) const;
  static void dispatchForEntityId(const std::string &id,
                                  const std::function<void(VehicleId)> &fv,
                                  const std::function<void(PersonId)> &fp);
  static const char* USAGE;
 private:
  DB &db;
  std::ostream &sout;
  std::ostream &serr;
};

#endif //HWUNI2_SRC_COMMANDDISPATCHER_H_
