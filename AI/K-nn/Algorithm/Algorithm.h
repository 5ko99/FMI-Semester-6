#pragma once
#include "Unit.h"
#include<vector>

class Knn {
public:
    Knn(const Knn &) = delete;

    Knn &operator=(const Knn &) = delete;

    Knn() = delete;

    static void classifyAUnit(Unit& p, std::vector<Unit>& arr, unsigned k);
    static void classifyUnits(std::vector<Unit>& newUnits, std::vector<Unit>& oldUnits, unsigned k);
    static unsigned determinateBestK(std::vector<Unit>& known);
    static float calculateAccuracy(const std::vector<Unit>& first, const std::vector<Unit>& second);

private:
    static bool iClassifyAUnit(const Unit& p, std::vector<Unit>& arr, unsigned k);
};
