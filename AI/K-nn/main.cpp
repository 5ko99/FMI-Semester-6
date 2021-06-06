#include "Algorithm/Algorithm.h"
#include "Repository/Repository.h"

int main() {
    Repository::open();
    Repository::read();
    std::vector<Unit> data = Repository::getData();
    unsigned k = Knn::determinateBestK(data);
    Unit u1(500,OFTEN), u2(600,SOMETIMES),
    u3(1200,VERY_OFTEN),u4(5000,SOMETIMES),u5(100,RARELY),
    u6(1350,RARELY),u7(50,VERY_OFTEN),u8(150,OFTEN),u9(5000,SOMETIMES),u10(4999,RARELY);
    std::vector<Unit> newData;
    newData.push_back(u1);newData.push_back(u2);newData.push_back(u3);newData.push_back(u4);newData.push_back(u5);
    newData.push_back(u6);newData.push_back(u7);newData.push_back(u8);newData.push_back(u9);newData.push_back(u10);
    Knn::classifyUnits(newData,data,k);
    printf("Algorithm executed with K=%d\n",k);
    for(const auto& u : newData)
        u.print();
    return 0;
}
