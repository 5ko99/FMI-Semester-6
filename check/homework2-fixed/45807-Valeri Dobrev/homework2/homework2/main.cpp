#include<fstream>
#include "./services/reader/reader.hpp"


int main(int argc, char **argv){
    PersonFactory* personFactory = PersonFactory::getInstance();
    VehicleFactory* vehicleFactory = VehicleFactory::getInstance();

    if(argc>1){
        std::ifstream f(argv[1]);
        Reader::read(f);
        f.close();
    }

    Reader::read(std::cin);

    personFactory->destroy();
    vehicleFactory->destroy();
}
