vehicleObj := registration.o vehicle.o person.o
factoryObj := $(vehicleObj) factory.o person_vehicle_relation.o
commandObj :=  $(factoryObj) command.o acquire_command.o release_command.o person_command.o vehicle_command.o \
				remove_command.o show_command.o save_command.o
mainObj := $(commandObj) reader.o

#########################################################
##	Main
#########################################################
all: $(mainObj) main.cpp
	$(CXX) $^ -o main.exe

################################################################################
## Models' object files
################################################################################
registration.o: ./models/registration/registration.hpp ./models/registration/registration.cpp
	$(CXX) -c $^

vehicle.o: ./models/vehicle/vehicle.hpp ./models/vehicle/vehicle.cpp
	$(CXX) -c $^

person.o: ./models/person/person.hpp ./models/person/person.cpp
	$(CXX) -c $^ 

command.o: ./models/commands/command.hpp ./models/commands/command.cpp
	$(CXX) -c $^

acquire_command.o: ./models/commands/acquire/acquire_command.hpp ./models/commands/acquire/acquire_command.cpp
	$(CXX) -c $^ 

release_command.o: ./models/commands/release/release_command.hpp ./models/commands/release/release_command.cpp
	$(CXX) -c $^ 

person_command.o: ./models/commands/person/person_command.hpp ./models/commands/person/person_command.cpp
	$(CXX) -c $^

vehicle_command.o: ./models/commands/vehicle/vehicle_command.hpp ./models/commands/vehicle/vehicle_command.cpp
	$(CXX) -c $^ 

remove_command.o: ./models/commands/remove/remove_command.hpp ./models/commands/remove/remove_command.cpp
	$(CXX) -c $^ 

show_command.o: ./models/commands/show/show_command.hpp ./models/commands/show/show_command.cpp
	$(CXX) -c $^ 
save_command.o : ./models/commands/save/save_command.hpp ./models/commands/save/save_command.cpp
	$(CXX) -c $^ 
################################################################################
## Services' object files
################################################################################
factory.o: ./services/factories/factory.hpp ./services/factories/factory.cpp
	$(CXX) -c $^  

person_vehicle_relation.o: ./services/model_relations/person_vehicle_relation.hpp ./services/model_relations/person_vehicle_relation.cpp
	$(CXX) -c $^

reader.o: ./services/reader/reader.hpp ./services/reader/reader.cpp 
	$(CXX) -c $^
################################################################################
## Tests' files
################################################################################

#################### Models' tests ####################
registration_tests: registration.o ./tests/model_tests/registration_tests.cpp
	$(CXX) $^ -o $@.exe

vehicle_tests: ./tests/model_tests/vehicle_tests.cpp $(vehicleObj)
	$(CXX) $^ -o $@.exe

person_tests: ./tests/model_tests/person_tests.cpp $(vehicleObj)
	$(CXX) $^ -o $@.exe

command_tests: ./tests/model_tests/command_tests.cpp $(commandObj)
	$(CXX) $^ -o $@.exe

#################### Services' tests ####################
vehicle_factory_tests:./tests/services_tests/factory_tests/vehicle_factory_tests.cpp $(factoryObj)
	$(CXX) $^ -o $@.exe


person_factory_tests: ./tests/services_tests/factory_tests/person_factory_tests.cpp  $(factoryObj)
	$(CXX) $^ -o $@.exe

person_vehicle_relation_tests:./tests/services_tests/model_relations_tests/person_vehicle_relation_tests.cpp  $(factoryObj)
	$(CXX) $^ -o $@.exe


clean:
	-rm *.o *.exe