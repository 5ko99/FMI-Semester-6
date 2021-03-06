#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include<cstddef>

const size_t MAX_COMMAND_TYPE_LENGTH = 7; 
const size_t MAX_REGISTRATION_LENGTH = 8; 
const size_t MAX_PERSON_NAME_LENGTH = 42; 
const size_t MAX_ID_LENGTH = 4; 
const size_t MAX_PATH_LENGTH = 100;
const size_t MAX_DESCRIPTION_LENGTH = 300; 
const size_t MAX_SHOW_COMMAND_ARGUMENT_LENGTH = 8;
const size_t MAX_ROW_LENGTH = MAX_COMMAND_TYPE_LENGTH
    + MAX_DESCRIPTION_LENGTH + MAX_REGISTRATION_LENGTH;
const char COMMAND_DELIMETER = ' ';
const size_t PLATE_ONE_FRONT_LETTER_LENGTH = 7;
const size_t PLATE_TWO_FRONT_LETTERS_LENGTH = 8;


#endif /*CONSTANTS_H*/
