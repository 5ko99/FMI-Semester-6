# ifndef INTERFACE_H
# define INTERFACE_H
# include "Person.h"
# include "Vehicle.h"
# include "Registration.h"
# include "Commands.h"
# include <string>
enum Comands {
	VEHICLE,
	PERSON,
	AQUIRE,
	RELEASE,
	REMOVE,
	SAVE,
	SHOW,
	EXIT
};
class Interface {

	Comands c;
	Commands cm;
public:
	void setEnum( std::string&);
	friend void runCommand( Interface&);
	friend void loadInfo(Interface &);
	void Run();
};

# endif
