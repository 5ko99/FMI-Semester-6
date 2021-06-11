#include "reader.hpp"

void Reader::read(std::istream& stream){
    std::string line;


    while(std::getline(stream, line)){
        if(to_upper(line) == "EXIT") break;
        createCommand(line); 
    }
}

std::string Reader::to_upper(const std::string& string){
    std::string result;
    for(char c: string){
        if(c >='a' && c <= 'z'){
            result.push_back(c-32);
        }else{
            result.push_back(c);
        }
    }
    return result;
}

std::vector<std::string> Reader::readArgs(std::istream& is){
    
    std::string arg;
    std::vector<std::string> args;
    

    while(std::getline(is, arg, ' ')){
        args.push_back(arg);
        arg.clear();
    }
    return args;
}

void Reader::createCommand(const std::string& line){
    

    std::string command;

    std::stringstream ss(line);   
    getline(ss, command, ' ');

    std::vector<std::string> args = readArgs(ss);
    
     

    command = to_upper(command);

    Command* c = nullptr;

    if(command == "VEHICLE"){
        c = new VehicleCommand(args);
    }else if(command == "PERSON"){
        c = new PersonCommand(args);
    }else if(command == "REMOVE"){
        args.push_back("false");
        c = new RemoveCommand(args);
    }else if(command == "ACQUIRE"){
        c = new AcquireCommand(args);
    }else if(command == "RELEASE"){
        c = new ReleaseCommand(args);
    }else if(command == "SHOW"){
        c = new ShowCommand(args);
    }else if(command == "SAVE"){
        c = new SaveCommand(args);
    }else{
        std::cout<<"Unknown command "<<command << std::endl;
        return;
    }

    if(c){    
        try{
            c->execute();

        }catch(std::exception& e){
            std::cout<<e.what();
            //Checks if the user is trying to delete object with relations 
            if(std::string(e.what()).find("Are you sure") != std::string::npos){
                //Ask for permission
                std::cout <<" [y/n]: "; 
                std::string ans;
                std::cin>>ans;
                std::cin.ignore();
                ans = to_upper(ans);
                if(ans == "Y" || ans == "YES"){
                    //Update the arguments to true so that the object is deleted
                    std::vector<std::string> args = c->getArguments();
                    args[1] = "true";
                    c->setArguments(args);
                    c->execute();
                }
            }
            std::cout<<"\n";
            delete c;
        }
    }
}
