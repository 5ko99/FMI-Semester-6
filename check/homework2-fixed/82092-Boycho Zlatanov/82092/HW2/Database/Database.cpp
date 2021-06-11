#ifndef Database_H
#define Database_H
#include "Database.hpp"

Database::Datebase()
{
}
Database::~Datebase()
{
}

Person *Database::findPerson(const unsigned int &searchedID)
{
  Person *result = nullptr;
  for (auto cur : people)
  {
    if (cur.getID() == searchedID)
    {
      result = &cur;
    }
  }
  return result;
}

Vehicle *Database::findVehicle(const std::string &toFind)
{
  Vehicle *result = nullptr;
  for (auto cur : cars)
  {
    if (cur.getNumberPlate() == toFind)
    {
      result = &cur;
    }
  }

  return result;
}

void Datebase::person(const std::string &newName, const unsigned int &newID)
{
  Person *test = findPerson(newID);
  if (!test)
  {
    Person X(newName, newID);
    people.push_back(X);
    return;
  }
  std::cout << "Already taken ! ";
  delete test;
}

void Datebase::vehicle(const std::string &newNumberPlate, const std::string &newDescription)
{
  Vehicle *test = findVehicle(newNumberPlate);
  if (!test)
  {
    Vehicle X(newNumberPlate, newDescription);
    cars.push_back(X);
    return;
  }
  std::cout << "Already taken ! ";
  delete test;
}

void Datebase::release(const std::string &ownerID, const std::string &vehicleID)
{
  Person *test = findPerson(ownerID);
  if (!test)
  {
    std::cout << "No such owner ! " << std::endl;
    return;
  }
  releaseVehicle(vehicleID);
  delete test;
}
void Datebase::acquire(const std::string &ownerID, const std::string &vehicleID)
{
  Vehicle *vehicle = findVehicle(vehicleID);
  if (!vehicle)
  {
    std::cout << "No such vehicle ! " << std::endl;
    return;
  }
  else
  {
    releaseVehicle(vehicleID);
  }
  Person *owner = findPerson(ownerID);
  if (!person)
  {
    std::cout << "No such person ! " << std::endl;
    return;
  }

  curPerson->addVehicle(curCar);
  curCar->addOwner(curPerson);
}

void Datebase::remove(const std::string &toRemove)
{
  if (toRemove[0] >= 'A' && toRemove[0] <= 'Z')
  {
    removeVehicle(toRemove);
  }
  else
  {
    unsigned int number = 0;

    for (int i = 0; i < toRemove.length(); ++i)
    {
      number *= 10;
      number += (toRemove[i] - '0');
    }

    removePerson(number);
  }
}

void Datebase::removePerson(const unsigned int &personID)
{
  Person *toRemove = findPerson(personID);

  if (!toRemove)
  {
    std::cout << "No such person!\n";
  }
  else if (toRemove->hasCars())
  {
    std::cout << "Do you want to remove a person, who has vehicles registered? (Y/N)\n";
    char answer;
    std::cin >> answer;

    if (answer == 'Y')
    {
      toRemove->releaseAllVehicles();
      people.erase(*toRemove);
    }
    else if (answer == 'N')
    {
      std::cout << "No actions were performed!\n";
    }
    else
    {
      std::cout << "Invalid answer!\n";
    }
  }
}

void Datebase::removeVehicle(const std::string &vehicleID)
{
  Vehicle *toRemove = findVehicle(vehicleID);

  if (!toRemove)
  {
    std::cout << "No such vehicle!\n";
  }
  else if (toRemove->hasOwner())
  {
    std::cout << "Do you want to remove a vicle that has an owner? (Y/N)\n";
    char answer;
    std::cin >> answer;

    if (answer == 'Y')
    {
      toRemove->removeOwner;
      people.erase(*toRemove);
    }
    else if (answer == 'N')
    {
      std::cout << "No actions were performed!\n";
    }
    else
    {
      std::cout << "Invalid answer!\n";
    }
  }
}

void Datebase::show_people()
{
  for (auto curPerson : people)
  {
    std::cout << curPerson.getPersonName() << " ";
    std::cout << curPerson.getID() << std::endl;
  }
}

void Datebase::showID(std::string curID)
{
  if (detectType() == 0)
  {
    findPerson(curID).print();
  }
  else
  {
    findVehicle(curID).print();
  }
}

void Datebase::showVehicles()
{
  for (auto curPerson : cars)
  {
    std::cout << curCar.getCarNumberPLate() << " ";
    std::cout << curCar.getCarDescription() << std::endl;
  }
}

void Person::serialize(std::ofstream &file)
{
  for(auto curr : people)
  {
    curr.serialize();
  }

  for(auto curr : cars)
  {
    curr.serialize();
  }
}

#endif
