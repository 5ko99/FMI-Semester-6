#include "CommandController.hpp"

CommandController::CommandController(){}

CommandController::CommandController(std::string path){
    readFromFile(path);
}


void CommandController::startReading(){
    std::string input;
    bool keepReading = true;
    do{
        getline(std::cin, input);
        Command currentCmd(input);
        keepReading = executeCommand(currentCmd, std::cin);
        
    } while(keepReading);
}

void CommandController::readFromFile(std::string fileName){
    std::ifstream file;
    std::string input;
    file.open(fileName);
    bool keepReading = true;
    do{
        getline(file, input);
        if(!file) keepReading = false;
        else {
            Command currentCmd(input);
            keepReading = executeCommand(currentCmd, file);
        }
    } while(keepReading);
}

void CommandController::saveToFile(std::string path){
    std::ofstream file;
    file.open(path);
    for(std::size_t i=0; i<comArr.size(); i++){
        if(i!=0) file<<"\n";
        std::string asd = comArr.at(i).getRaw();
        file<<asd;
    }
    file.close();
}


bool CommandController::executeCommand(const Command& cmd, std::istream& istr){
    std::string firstArg = toUpperCase(cmd[0]);
    //cmd.print();
    
    if(strcmp(firstArg.c_str(), "STOP")==0){
        //keepReading = false;
        std::cout<<"stopped reading\n";
        return false;
    }
    
    else if(strcmp(firstArg.c_str(), "VEHICLE")==0){
        try{
            pvc.createVehicle(cmd[1], cmd[2]);
            comArr.push_back(cmd);
        } catch (const std::exception& e){
            std::cout<<e.what()<<"\n";
        }
    }
    
    else if(strcmp(firstArg.c_str(), "PERSON")==0){
        try{
            pvc.createPerson(cmd[1], cmd[2]);
            comArr.push_back(cmd);
        } catch (const std::exception& e){
            std::cout<<e.what()<<"\n";
        }
        
    }
    
    else if(strcmp(firstArg.c_str(), "ACQUIRE")==0){
        try{
            pvc.acquire(cmd[1], cmd[2]);
            comArr.push_back(cmd);
        } catch (const std::exception& e){
            std::cout<<e.what()<<"\n";
        }
        
    }
    else if(strcmp(firstArg.c_str(), "RELEASE")==0){
        try{
            pvc.release(cmd[1], cmd[2]);
            comArr.push_back(cmd);
        } catch (const std::exception& e){
            std::cout<<e.what()<<"\n";
        }
    }
    else if(strcmp(firstArg.c_str(), "REMOVE")==0){
        try{
            std::size_t idtype = pvc.getIdentificatorType(cmd[1]);
            bool shouldAskPermission = false;
            if(idtype == 1){
                Registration reg(cmd[1].c_str());
                if(pvc.getVehicleById(reg)->getOwnerPtr()) shouldAskPermission = true;
            } else if(idtype == 2){
                if(pvc.getPersonById(strToInt(cmd[1]))->hasVehicles()) shouldAskPermission = true;
            }
            
            if(shouldAskPermission){
                if(&istr == &std::cin)std::cout<<"are you sure you want to do this? Y/N\n";
                std::string inp;
                getline(istr, inp);
                Command approvalCmd(inp);
                
                if(!strcmp(toUpperCase(approvalCmd[0]).c_str(), "YES") || !strcmp(toUpperCase(approvalCmd[0]).c_str(), "Y")){
                    pvc.remove(cmd[1]);
                    comArr.push_back(cmd);
                    comArr.push_back(approvalCmd);
                } else {
                    std::cout<<"cancelling removal\n";
                }
            } else {
                pvc.remove(cmd[1]);
                comArr.push_back(cmd);
            }
            
            
        } catch (const std::exception& e){
            std::cout<<e.what()<<"\n";
        }
    }
    
    else if(strcmp(firstArg.c_str(), "SAVE")==0){
        try{
            saveToFile(cmd[1]);
        } catch(const std::exception& e){
            std::cout<<e.what()<<"\n";
        }
    }
    
    else if(strcmp(firstArg.c_str(), "SHOW")==0){
        try{
            pvc.show(cmd[1]);
        } catch(const std::exception& e){
            std::cout<<e.what()<<"\n";
        }
    }
    
    else {
        std::cout<<"command not recognised\n";
    }
    
    
    return true;
}





