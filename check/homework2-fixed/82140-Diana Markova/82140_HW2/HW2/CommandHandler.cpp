//#define _CRT_SECURE_NO_WARNINGS
#include "CommandHandler.h"
#include <cstring>
#include <string>
#include "helpers.h"
#include <stdexcept>

Handler::Handler(const char* loadPath): initialLoadPath(loadPath), d(Data::getInstance())
{
    load(loadPath);
}
Handler::Handler():d(Data::getInstance())
{std::cout<<"Successfully started from an empty base."<<std::endl;}

//------------------------Input------------------------
void Handler::getInput()
{
    std::string line;
    gettingInput=true;
    while(gettingInput)
    {
        std::getline(std::cin, line);
        lp.parseLine(line.c_str());
        try{interpret();}
        catch(const std::invalid_argument &ia){std::cerr<<ia.what()<<'\n';}
        catch(const std::runtime_error &re)   {std::cerr<<re.what()<<'\n';}
        catch(...) {throw;}
    }
}
void Handler::interpret()
{
     if(caseInsensitiveCmp(lp.command(), "")==0) return;
     else if(caseInsensitiveCmp(lp.command(), "VEHICLE")==0) vehicle();
     else if(caseInsensitiveCmp(lp.command(), "PERSON") ==0) person();
     else if(caseInsensitiveCmp(lp.command(), "ACQUIRE")==0) acquire();
     else if(caseInsensitiveCmp(lp.command(), "RELEASE")==0) release();
     else if(caseInsensitiveCmp(lp.command(), "SAVE"   )==0) save();
     else if(caseInsensitiveCmp(lp.command(), "SHOW"   )==0) show();
     else if(caseInsensitiveCmp(lp.command(), "REMOVE" )==0) remove();
     else if(caseInsensitiveCmp(lp.command(), "EXIT"   )==0)
     {
         if(changed==true)
            {
                std::cout<<"Are you sure you want to exit without saving? y/n: ";
                if(readAbinaryAnwser()=='y') gettingInput=false;
                else return;
            }
         gettingInput=false;
     }
     else throw std::runtime_error("Unrecognized command");
}
void Handler::load(const char* arguments)
{
    std::ifstream iFile(arguments);
    if(!iFile)
        {throw std::invalid_argument("Failed to open file. Make sure file exists.");}
    std::string line;
    std::size_t cnt=0;
    std::cout<<".................................."<<std::endl;
    while(std::getline(iFile, line))
    {
        ++cnt;
        lp.parseLine(line.c_str());
        try{interpret();}
        catch(const std::invalid_argument& ia)
        {
            std::cerr<<"Line "<<cnt<<": the following error occurred: ";
            std::cerr<<ia.what()<<'\n';
            throw std::runtime_error("File is corrupted.");
        }
        catch(const std::runtime_error& ia)
        {
            std::cerr<<"Line "<<cnt<<": the following error occurred: ";
            std::cerr<<ia.what()<<'\n';
            throw std::runtime_error("File is corrupted.");
        }
    }
    iFile.close();
    std::cout<<".................................."<<std::endl;
    std::cout<<"Successfully loaded data from file"<<std::endl;
}
//-----------------------Commands----------------------
void Handler::save()
{
    if (lp.numberOfArguments()==0) throw std::invalid_argument("Missing argument.");
    else if(lp.numberOfArguments()>1) throw std::invalid_argument("SAVE takes only one argument.");
    std::ofstream oFile(lp.arguments()[0]);
    if(!oFile.is_open()) throw std::runtime_error("Failed to open file.");
    d.save(oFile);
    oFile.close();
    std::cout<<"Successfully saved data in file"<<std::endl;
    changed=false;
}

void Handler::vehicle()
{
    if(lp.numberOfArguments()>2) throw std::invalid_argument("VEHICLE takes only two arguments.");
    else if(lp.numberOfArguments()<2) throw std::invalid_argument("Missing argument.");
    d.newVehicle(lp.arguments()[0].c_str(), lp.arguments()[1].c_str());
    std::cout<<"Successfully created vehicle"<<std::endl;
    changed=true;
}

void Handler::person()
{
    if(lp.numberOfArguments()>2) throw std::invalid_argument("PERSON takes only two arguments.");
    else if(lp.numberOfArguments()<2) throw std::invalid_argument("Missing argument.");
    unsigned int argument2Num=strToUnsigned(lp.arguments()[1].c_str());
    d.newPerson(lp.arguments()[0].c_str(), argument2Num);
    std::cout<<"Successfully created person"<<std::endl;
    changed=true;
}
void Handler::acquire()
{
    if(lp.numberOfArguments()>2) throw std::invalid_argument("ACQUIRE takes only two arguments.");
    else if(lp.numberOfArguments()<2) throw std::invalid_argument("Missing argument.");
    d.acquire(lp.arguments()[0].c_str(), lp.arguments()[1].c_str());
    std::cout<<"Person successfully acquired vehicle"<<std::endl;
    changed=true;
}
void Handler::release()
{
    if(lp.numberOfArguments()>2) throw std::invalid_argument("RELEASE takes only two arguments.");
    else if(lp.numberOfArguments()<2) throw std::invalid_argument("Missing argument.");
    d.release(lp.arguments()[0].c_str(), lp.arguments()[1].c_str());
    std::cout<<"Vehicle successfully released"<<std::endl;
    changed=true;
}
void Handler::remove()
{
    if (lp.numberOfArguments()==0) throw std::invalid_argument("Missing argument.");
    else if(lp.numberOfArguments()>1) throw std::invalid_argument("REMOVE takes only one argument.");
    d.remove(lp.arguments()[0].c_str());
    changed=true;
}
void Handler::show()
{
    if (lp.numberOfArguments()==0) throw std::invalid_argument("Missing argument.");
    else if(lp.numberOfArguments()>1) throw std::invalid_argument("SHOW takes only one argument.");
    d.show(lp.arguments()[0].c_str());
}

