/*
 * commandparser.h
 *
 *  Created on: 23.05.2021 Рі.
 *      Author: plamen
 */

#ifndef SRC_COMMANDPARSER_H_
#define SRC_COMMANDPARSER_H_

#include <iostream>

class command_parser
{
//	//singleton stuff
//public:
//
//	static command_parser& get_instance();
//
//private:
//	command_parser() {}
//
//public:
//
//	command_parser(const command_parser&) = delete;
//	command_parser(command_parser&&) = delete;
//	void operator=(const command_parser&)  = delete;
//	void operator=(command_parser&&) = delete;
//
//	//real implementation

private:

	static bool ask_user_yes_no (std::istream &in, std::ostream &out);

	static void parse_command_vehicle (std::istream &in, std::ostream *out);
	static void parse_command_person (std::istream &in, std::ostream *out);
	static void parse_command_acquire (std::istream &in, std::ostream *out);
	static void parse_command_release (std::istream &in, std::ostream *out);
	static void parse_command_remove (std::istream &in, std::ostream *out);
	static void parse_command_save (std::istream &in, std::ostream *out);
	static void parse_command_show (std::istream &in, std::ostream *out);

public:
	static void parse (std::istream &in, std::ostream *out);

};

#endif /* SRC_COMMANDPARSER_H_ */
