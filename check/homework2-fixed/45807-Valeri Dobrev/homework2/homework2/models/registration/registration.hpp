#pragma once

#include <iostream>
#include <cstring>
#include<regex>


class Registration{
	char registration[9];
	/** 
     * Method that checks if the registration is in valid format L(L)NNNNLL (L-letter, N - number)
     * @param str
     * @return true if the registration is valid, false otherwise
     */
    bool isValid(const char* str);
public:
    /** 
     * Constructor
     * @param str
     * @throw std::invalid_argument when the registration is invalid
     */
	Registration(const char* str);
	
    /** 
     * Deleted copy and assign operator
     */
    Registration(Registration& other) = delete;
    Registration& operator=(const char* str)=delete;
	
    /** 
     * Equals operator
     * @param str
     */
    bool operator==(const char* str) const;

    /** 
     * Method that returns the registration number in c string format
     */
	const char* toString() const;
};
