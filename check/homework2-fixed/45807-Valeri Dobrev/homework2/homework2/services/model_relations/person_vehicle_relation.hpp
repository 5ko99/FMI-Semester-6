#pragma once
#include "../factories/factory.hpp"

class PersonVehicleRelation{
public:
    PersonVehicleRelation() = delete;
    PersonVehicleRelation(const PersonVehicleRelation& pvr) = delete;
    PersonVehicleRelation& operator=(const PersonVehicleRelation& pvr) = delete;

    /**
     * Static method that finds the person and the vehicle by the given ides and then adds the vehicle to the person's list of vehicles and assign owner to the vehicle
     * @param personId
     * @param vehicleId
     */
    static void acquire(const unsigned peronsId, const char* vehicleId);
    /**
     * Static method that finds the person and the vehicle bu the given ides and then removes the vehicle from the person's list of vehicles and assign nullptr as owner to the vehicle'
     * @param personId
     * @param vehicleId
     */
    static void release(const unsigned peronsId, const char* vehicleId);
};
