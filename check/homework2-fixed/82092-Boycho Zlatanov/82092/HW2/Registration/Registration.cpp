#ifndef Registration_H
#define Registration_H

Registration::Registration() {}

Registration::Registration(const Registration &other)
{
  strcpy(this->numberPlate, other.c_str());
}

Registration::~Registration() {}

bool Registration::validationOfNumberPlate(char plate[])
{
  int br = 0;

  if (strlen(plate) < 7 || strlen(plate) > 9)
  {
    return false;
  }
  else if (strlen(plate) == 7)
  {
    if (plate[0] < 'A' || plate[0] > 'z')
    {
      return false;
    }
    else
    {
      br = 1;
    }
  }
  else if (strlen(plate) == 8)
  {
    if ((plate[0] < 'A' || plate[0] > 'z') && (plate[1] < 'A' || plate[1] > 'z'))
    {
      return false;
    }
    else
    {
      br = 2;
    }
  }
  for (int i = 0; i < 4; i++, br++)
  {
    if (plate[br] < '0' || plate[br] > '9')

      return false;
  }

  return !((plate[br] < 'A' || plate[br] > 'z') && (plate[br + 1] < 'A' || plate[br + 1] > 'z'));
}

bool Registration::operator==(const std::string &other)
{
  return (strcmp(NumberPlate, Y.c_str()) == 0);
}

void Registration::setNumberPlate()
{
  std::cout << "Input number plate: " << std::endl;
  std::cin >> numberPlate;
  if (validationOfNumberPlate(numberPlate))
  {
    std::cout << "This is a valid number! " << std::endl;
  }
  else
  {
    std::cout << "Invalid number! " << std::endl;
  }
}

std::string Registration::getNumberPlate()
{
  std::string result(numberPlate);

  return result;
}

#endif
