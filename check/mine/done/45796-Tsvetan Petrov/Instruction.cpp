#include "Instruction.h"


Instruction::Instruction(const std::string instr) {
	unsigned int index = 0;
	while (instr[index] != ' ' && instr[index] != '\0') {
		if (instr[index] >= 'a' && instr[index] <= 'z') {
			command.push_back(instr[index]-32);
		}
		else {
			command.push_back(instr[index]);
		}
		
		index++;

		if (instr[index] == '\0') {
			return;
		}
	}
	
	index++;

	if ( (command == "PERSON" && instr[index] == '"') || command == "PROGRAM.EXE" || command == "SAVE") {
		index++;
		while (instr[index] != '"') {
			first_argument.push_back(instr[index]);
			index++;
			if (instr[index] == '\0') {
				return;
			}
		}
		index++;
		if (instr[index] == '\0') {
			return;
		}
	}
	else {
		while (instr[index] != ' ' && instr[index] != '\0') {			
			first_argument.push_back(instr[index]);
			index++;

			if (instr[index] == '\0') {
				return;
			}

		}
	}
	
	index++;
	while (instr[index] != ' ' && instr[index] != '\0') {
		second_argument.push_back(instr[index]);
		index++;
		if (instr[index] == '\0') {
			return;
		}

	}
	/*index++;
	while (instr[index] != ' ' && instr[index] != '\0') {
		third_argument.push_back(instr[index]);
		index++;
		if (instr[index] == '\0') {
			return;
		}

	}*/
}

std::string Instruction::get_command() const {
	return command;
}
std::string Instruction::get_first_argument() const {
	return first_argument;
}
std::string Instruction::get_second_argument() const {
	return second_argument;
}
//std::string Instruction::get_third_argument() const {
//	return third_argument;
//}
