#include"StringHelper.h"

// Turns a string to its lower variant. For example 'AbCdEfG' -> 'abcdefg'
// Private because it is only used inside this class
std::string StringHelper::StringToLower(std::string input) {
    for (int i = 0; i < input.length(); i++)
  	{
  		input[i] = std::tolower(input[i]);
  	}
      
    return input;
}

void StringHelper::StringSplit(const std::string& inputString, std::vector<std::string>& container, char delimeter)
{
    size_t currentPos, previousPos = 0;
    currentPos = inputString.find(delimeter);

    while (currentPos != std::string::npos) {
        container.push_back(inputString.substr(previousPos, currentPos - previousPos));
        
		previousPos = currentPos + 1;

        currentPos = inputString.find(delimeter, previousPos);
    }

    container.push_back(inputString.substr(previousPos, currentPos - previousPos));
}
