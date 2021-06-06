#include "Algorithm.h"
#include<algorithm>

bool Knn::iClassifyAUnit(const Unit &p, std::vector<Unit> &arr, unsigned k) {
    for (auto &i : arr)
        i.setEuclideanDistance(p);

    sort(arr.begin(), arr.end());

    unsigned normalBuy = 0;
    unsigned specialBuy = 0;
    for (unsigned i = 0; i < k; ++i) {
        if (arr[i].type == NORMAL_BUY)
            normalBuy++;
        else if (arr[i].type == SPECIAL_BUY)
            specialBuy++;
    }
    return (normalBuy > specialBuy ? NORMAL_BUY : SPECIAL_BUY);
}

void Knn::classifyAUnit(Unit &p, std::vector<Unit> &arr, unsigned int k) {
    p.type = iClassifyAUnit(p, arr, k);
}

void Knn::classifyUnits(std::vector<Unit> &newUnits, std::vector<Unit> &oldUnits, unsigned int k) {
    for (auto &u : newUnits)
        classifyAUnit(u, oldUnits, k);
}

float Knn::calculateAccuracy(const std::vector<Unit> &first, const std::vector<Unit> &second) {
    unsigned guessed = 0;
    for (unsigned i = 0; i < first.size(); ++i)
        if (first[i].type == second[i].type) ++guessed;
    return (float)((float) guessed / (float) first.size());
}

unsigned int Knn::determinateBestK(std::vector<Unit> &known) {
    std::vector<Unit> copy;
    for(unsigned i=0;i<known.size()/3;++i) // remove 1/3 of point
        copy.push_back(known[i]);

    unsigned bestK = 1;
    float bestAcc = 0; // in percent
    for (unsigned short k = 1; k < 40; ++k) {
        classifyUnits(copy, known, k);
        float currAcc = calculateAccuracy(copy,known);
        if(currAcc>bestAcc) {
            bestAcc=currAcc;
            bestK = k;
        }
        if(currAcc==1) break;
    }
    return bestK;
}