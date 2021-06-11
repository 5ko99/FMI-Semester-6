#ifndef VPALLOCATOR_H
#define VPALLOCATOR_H
#include "../Registration/Registration.hpp"
#include "../Vehicle/Vehicle.hpp"
#include "../Person/Person.hpp"
#include "../Helpers/Helpers.hpp"
	
class VPAllocator {
public:
	VPAllocator();
	~VPAllocator();

	void newVehicle(const std::string reg, const std::string descr);
	void newPerson(const std::string name, const std::string id);
	void acquire(const std::string owner_id, const std::string veh_id);
	void release(const std::string owner_id, const std::string veh_id);
	void removeItem(const std::string query, bool is_linked);
	void remove(const std::string query);
	void show(const std::string query);
	void show();

	bool isItemConnected(const std::string query) const;

	Vehicle* findVehicle(const std::string veh_id) const;
	Person* findPerson(const std::string veh_id) const;
	
	Vehicle* getVListInd(const size_t ind) const;
	size_t vListSize() const;
	Person* getPListInd(const size_t ind) const;
	size_t pListSize() const;


private:
	std::vector<Vehicle*> v_list;
	std::vector<Person*> p_list;

	//unsigned strToInt(const std::string str) const;
	//std::string intToStr(const unsigned num) const;
	
	bool isValidUUID(const std::string veh_id) const;

	size_t findIDVeh(const std::string veh_id) const;
	size_t findIDPer(const std::string owner_id) const;
	
	void releaseAll(Person& p);
	bool confirm(std::string message);

	void printPeople();
	void printVehicles();
};
#endif
