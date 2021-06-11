#include "registration.hpp"

Registration::Registration(const char* str){
	if(!str)throw std::invalid_argument("Registration cannot be null!");
	if(!isValid(str)){
		throw std::invalid_argument("Invalid registration number!");
	}
	strcpy(registration, str);
}


bool Registration::isValid(const char* str){
	if(!str){return false;}

	static std::regex rx(R"([A-Z]{1,2}[0-9]{4}[A-Z]{2})");
	
	return std::regex_match(str, rx);
}

bool Registration::operator==(const char* str) const{
	if(!str) throw std::invalid_argument("Registration should not be null!"); 
	if(strcmp(str,registration)==0){
		return true;
	}
	return false;
}

const char* Registration::toString() const{ 
	return registration;
}
