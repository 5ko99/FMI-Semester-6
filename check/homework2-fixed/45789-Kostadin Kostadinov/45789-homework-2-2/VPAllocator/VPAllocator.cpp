#include "VPAllocator.hpp"

/*bool isEqualString(std::string str_1, std::string str_2) {
    if (str_1 == str_2) return true;
    if (str_1.size() != str_2.size()) return false;
    size_t len = str_1.size();
    const char* ch_1 = str_1.c_str();
    const char* ch_2 = str_2.c_str();
    for (size_t i = 0; i < len; i++) {
        if (std::toupper(ch_1[i]) != std::toupper(ch_2[i])) return false;
    } 
    return true;
}*/

bool VPAllocator::isValidUUID(const std::string uuid) const {
    size_t len = uuid.size();
    for (size_t i = 0; i < len; i++) {
        if (uuid[i] < '0' || uuid[i] > '9') return false;
    }
    return true;
}



/*unsigned VPAllocator::strToInt(const std::string str) const {
    unsigned buffer = 0;
    for(size_t i = 0; i < str.size(); i++) {
        buffer *= 10;
        buffer += (str[i] - '0');
    }
    return buffer;
}

std::string VPAllocator::intToStr(const unsigned num) const {
    std::string buffer;
    unsigned buf=num;
    while (buf != 0) {
        buffer.insert(0, 1, ((buf % 10) + '0'));
        buf /= 10;
    }
    return buffer;
}*/

size_t VPAllocator::findIDVeh(const std::string veh_id) const {
    for (size_t i = 0; i < v_list.size(); i++) {
        //if (!v_list[i]) continue;
        if (!strcmp(v_list[i]->getReg().c_str(), veh_id.c_str())) {
            return i;
        }
    }
    return v_list.size();
}

size_t VPAllocator::findIDPer(const std::string owner_id) const {
    for (size_t i = 0; i < p_list.size(); i++) {
        //if (!p_list[i]) continue;
        if (strToInt(owner_id) == p_list[i]->getUUID() ) {
            return i;
        }
    }
    return p_list.size();
}

void VPAllocator::releaseAll(Person& p) {
    for (size_t i = 0; i < p.vehicleCount(); i++) {
        p.getVehicleAtInd(i)->removeOwner();
    }
    p.removeAllVehicles();
}

bool VPAllocator::confirm(std::string message) {
    char answer;
    std::cout << message <<" Are you sure you want to proceed?";
    do {
        std::cout << "(Y/N):";
        std::cin >> answer;
    } while (toupper(answer) != 'Y' || toupper(answer) != 'N');
    std::cin.ignore();
    return toupper(answer) == 'Y';
}

void VPAllocator::printPeople() {
    if(p_list.empty()) {
        std::cout << "No people found!\n";
    }
    for(size_t i = 0; i < p_list.size(); i++) {
        p_list[i]->printAll();
    }
}

void VPAllocator::printVehicles() {
    if(v_list.empty()) {
        std::cout << "No vehicles found!\n";
    }
    for(size_t i = 0; i < v_list.size(); i++) {
        v_list[i]->printAll();
    }
}

VPAllocator::VPAllocator() {}
	
VPAllocator::~VPAllocator() {
    for(size_t i = 0; i < v_list.size(); i++) {
        if(v_list[i]) delete v_list[i];
    }
    v_list.clear();

    for(size_t i = 0; i < p_list.size(); i++) {
        if(p_list[i]) delete p_list[i];
    }
    p_list.clear();
}

void VPAllocator::newVehicle(const std::string reg, const std::string descr) {
    if (findIDVeh(reg) < v_list.size()) {
        throw std::invalid_argument("A vehicle with this registration already exisits!");
    }

    Registration buffer(reg);
    Vehicle *veh = new Vehicle(buffer, descr);
    v_list.push_back(veh);
}

void VPAllocator::newPerson(const std::string name, const std::string id) {
    if (findIDPer(id) < p_list.size()) {
        throw std::invalid_argument("A person with this ID already exisits!");
    }

    if (!isValidUUID(id)) {
        throw std::invalid_argument("The ID should be only numbers");
    }

    Person *per = new Person(name, strToInt(id));
    p_list.push_back(per);
}

void VPAllocator::acquire(const std::string owner_id, const std::string veh_id) {
    size_t v_ind = findIDVeh(veh_id);
    size_t p_ind = findIDPer(owner_id);

    if (v_ind == v_list.size() || p_ind == p_list.size()) {
        throw std::invalid_argument("A vehicle/person with this ID could not be found!");
    }
    
    if (v_list[v_ind]->getOwner()) release(intToStr(v_list[v_ind]->getOwner()->getUUID()), veh_id);

    v_list[v_ind]->setOwner(p_list[p_ind]);
    p_list[p_ind]->addVehicle(*v_list[v_ind]);
}

void VPAllocator::release(const std::string owner_id, const std::string veh_id) {
    size_t v_ind = findIDVeh(veh_id);
    size_t p_ind = findIDPer(owner_id);
    if (v_ind == v_list.size() || p_ind == p_list.size()) {
        throw std::invalid_argument("A vehicle/person with this ID could not be found!");
    }
    if (!v_list[v_ind]->getOwner()) {
        throw std::logic_error("Vehicle isn't owned by anyone!");
    }
    v_list[v_ind]->removeOwner();
    p_list[p_ind]->removeVehicle(*v_list[v_ind]);
}

void VPAllocator::removeItem(const std::string query, bool is_linked) {
    size_t ind = findIDVeh(query);

    if (ind < v_list.size()) {
        if (is_linked) {release(intToStr((*v_list[ind]).getOwner()->getUUID()), query);}
        delete v_list[ind];
        v_list.erase(v_list.begin() + ind);
        return;
    }

    ind = findIDPer(query);

    if (ind < p_list.size()) {
        if (is_linked) {releaseAll(*p_list[ind]);}
        delete p_list[ind];
        p_list.erase(p_list.begin() + ind);
        return;
    }

    throw std::invalid_argument("Nothing found!");
}

void VPAllocator::remove(const std::string query) {
    size_t ind = findIDVeh(query);

    if (ind < v_list.size()) {
        if ((*v_list[ind]).getOwner() /*&& confirm("This vehicle already has an owner. ")*/) {
            release(intToStr((*v_list[ind]).getOwner()->getUUID()), query);
        }
        delete v_list[ind];
        v_list.erase(v_list.begin() + ind);
        return;
    }

    ind = findIDPer(query);

    if (ind < p_list.size()) {
        if ((*p_list[ind]).vehicleCount()/* && confirm("This person already has vehicles. ")*/) {
            releaseAll(*p_list[ind]);
        }
        delete p_list[ind];
        p_list.erase(p_list.begin() + ind);
        return;
    }
    throw std::invalid_argument("Nothing found!");
}

void VPAllocator::show(const std::string query) {
    if (isEqualString(query, "PEOPLE")) {
        printPeople();
        return;
    } else if (isEqualString(query, "VEHICLES")) {
        printVehicles();
        return;
    } else {
        size_t ind = findIDVeh(query);

        if (ind < v_list.size()) {
            v_list[ind]->printAll();
            return;
        }

        ind = findIDPer(query);

        if (ind < p_list.size()) {
            p_list[ind]->printAll();
            return;
        }
    }
    std::cerr << "Nothing found!\n";
}

void VPAllocator::show() {
    std::cout << "People:\n"; 
    printPeople();
    std::cout << "Vehicles:\n";
    printVehicles();
}

bool VPAllocator::isItemConnected(const std::string query) const {
    size_t v_ind = findIDVeh(query);
    size_t p_ind = findIDPer(query);
    size_t ind = findIDVeh(query);

    if (ind < v_list.size() && (*v_list[ind]).getOwner()) {
        return true;
    }

    ind = findIDPer(query);
    if (ind < v_list.size() && (*v_list[ind]).getOwner()) {
        return true;
    }
    return false;
}

Vehicle* VPAllocator::findVehicle(const std::string veh_id) const {
    size_t ind = findIDVeh(veh_id);
    if (ind == v_list.size()) return nullptr;
    return v_list[ind];
}

Person* VPAllocator::findPerson(const std::string veh_id) const {
    size_t ind = findIDPer(veh_id);
    if (ind == p_list.size()) return nullptr;
    return p_list[ind];
}

Vehicle* VPAllocator::getVListInd(const size_t ind) const {
    return v_list[ind];
}

size_t VPAllocator::vListSize() const {
    return v_list.size();
}

Person* VPAllocator::getPListInd(const size_t ind) const {
    return p_list[ind];
}

size_t VPAllocator::pListSize() const {
    return p_list.size();
}
