#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

//Не разбирам много какъв е смисъла да имаме отделен тип данни Registration
struct Registration
{
    string reg;
    Registration(string reg = ""): reg(reg) {}
};

bool operator == ( const Registration& obj1, const Registration& obj2 )
{
    return obj1.reg == obj2.reg;
}
class Vehicle
{
private:
    Registration r;
    string description;
    unsigned int owner;
public:
    Vehicle(Registration r,string description = "", unsigned int owner = 0):r(r),description(description), owner(owner)
    {

    }
    void print()
    {
        cout<<r.reg<<" "<<description<<" "<<owner<<endl;
    }
    string get_description()
    {
        return description;
    }
    unsigned int get_owner()
    {
        return owner;
    }
    void set_owner(unsigned int owner)
    {
        this->owner = owner;
    }
    Registration& get_r()
    {
        return r;
    }
    void set_r(string r)
    {
        this->r.reg = r;
    }


};

class Person
{
private:
    string name;
    unsigned int id;
    vector<Vehicle*> cars;
public:
    Person(string name ="", unsigned id = 0): name(name), id(id) {}

    Person(const Person& other)
    {
        copy(other);
    }

    Person& operator=(const Person& other)
    {
        if (&other != this)
        {
            copy(other);
        }

        return *this;
    }

    copy(const Person& other)
    {
        this->name = other.name;
        this->id = other.id;
        vector<Vehicle*>().swap(cars);// clear and reallocating
        cars.resize(other.cars.size());
        for(int i = 0; i < cars.size(); i++)
        {
            cars.push_back(other.cars[i]);
        }
    }
    void print ()
    {
        cout<<name<<" "<<id<<endl;
    }
    void print_cars ()
    {
        int n = cars.size();
        for(int i = 0; i < n; i++)
        {
            (*cars[i]).print();
        }
    }
    void remove_all_cars()
    {
        vector<Vehicle*>().swap(cars);
    }
    bool is_exist_car(Vehicle &c)
    {
        for(int i = 0; i < cars.size(); i++)
        {
            if(cars[i] == (&c) )
                return true;
        }
        return false;
    }
    void remove_car (string r)
    {
        int m = cars.size();
        for(int i = 0; i < m; i++)
        {
            if( ((*cars[i]).get_r()). reg == r)
            {
                (*cars[i]).set_owner(0);
                cars.erase( cars.begin() + i);
                return;
            }
        }
        return;
    }
    void add_car(Vehicle& c)
    {
        cars.push_back(&c);
    }
    string name_get()
    {
        return name;
    }
    void name_set(string name)
    {
        this->name = name;
    }
    unsigned int id_get()
    {
        return id;
    }
    void id_set(unsigned int id)
    {
        this->id = id;
    }

};


class InformationBase
{
private:
    vector<Vehicle> vehicles;
    vector<Person> people;

public:
    void start_menu()
    {
        cout<<"(Y = yes, N = no)"<<endl;
        cout<<"Do you want to load data from file ?"<<endl;
        string response;
        cin>>response;
        if(response == "Y")
        {
            string filename;
            cin>>filename;
            load_data_from_file(filename);
        }
        cout<<"---MENU---"<<
        "0. EXIT"<<endl<<"1. VEHICLE <registration> <description>"<<endl
        <<"2. PERSON <name> <id>"<<endl<<"3. ACQUIRE <owner-id> <vehicle-id>"<<endl
        <<"4. RELEASE <owner-id> <vehicle-id>"<<endl<<"5. REMOVE <what>"<<endl
        <<"6. SAVE <path>"<<endl<<"7.SHOW [PEOPLE|VEHICLES|<id>]"<<endl;
        int option;
        cin>>option;
        while(option != 0)
        {
            if(option == 1)
            {
                string b,d;
                cin>>b>>d;
                Registration r;
                r.reg = b;
                add_vehicle(r,d);

            }
            else if(option == 2)
            {
                string name,id;
                cin>>name>>id;
                stringstream a(id);
                int  x = 0;
                a>>x;
                add_person(x, name);
            }
            else if(option == 3)
            {
                string id,reg;
                cin>>id>>reg;
                stringstream a(id);
                int  x = 0;
                a>>x;

                acquuire(x,reg);
            }
            else if(option == 4)
            {
                string id,reg;
                cin>>id>>reg;
                stringstream a(id);
                int  x = 0;
                a>>x;
                realease (x, reg);
            }
            else if(option == 5)
            {
                string s;
                cin>>s;
                remove (s);
            }
            else if(option == 6)
            {
                string file;
                cin>>file;
                save_all_data_to_file(file);
            }
            else if(option == 7)
            {
                string s;
                cin>>s;
                show(s);
            }
            else
            {
                cout<<"Invalid option"<<endl;
                break;
            }
        }
    }
    void save_all_data_to_file(string filename)
    {
        ofstream out(filename, ios::out);
        out<<"VEHICLES:"<<endl;
        int m = vehicles.size();
        for(int i = 0; i < m; i++)
        {
            out<<vehicles[i].get_r().reg<<" "<<vehicles[i].get_description()<<endl;
        }
        out<<"PEOPLE :"<<endl;
        int n = people.size();
        for(int i = 0; i < n; i++)
        {
            out<<people[i].name_get()<<" "<<people[i].id_get()<<endl;
        }
        out.close();

    }
    void load_data_from_file (string filename)
    {
        ifstream in(filename, ios::in);
       // cout<<in.is_open();
        while(!in.eof())
        {
            string what;
            in>>what;
            if(valid_reg(what) )
            {
                string des;
                in>>des;
                vehicles.push_back(Vehicle(what,des,0));

            }
            else
            {
                string number;
                in>>number;
                stringstream a(number);
                int x = 0;
                a>>x;
                people.push_back (Person(what,x) );
            }
        }
           in.close();
    }
    void show (string what)
    {
        if(what == "PEOPLE")
        {
            int n = people.size();
            for(int i =0; i < n; ++i)
            {
                people[i].print();
            }
        }
        else if(what == "VEHICLES")
        {
            int m = vehicles.size();
            for(int i = 0; i < m; i++)
            {
                vehicles[i].print();
            }
        }
        else if( valid_reg(what) )
        {
            int m = vehicles.size();
            for(int i = 0; i < m; i++)
            {
                if(vehicles[i].get_r().reg == what )
                {
                    vehicles[i].print();
                    return;
                }
            }
        }
        else
        {
            stringstream number(what);
            int x = 0;
            number >> x;
            int n = people.size();
            for(int i =0 ; i < n; i++)
            {
                if(people[i].id_get() == x)
                {
                    people[i].print();
                    people[i].print_cars();
                }
            }
        }
    }
    void remove (string what)
    {
        if(valid_reg(what) )
        {
            int n = people.size();
            int m = vehicles.size();
            for(int i = 0; i < m; i++)
            {
                if( vehicles[i].get_r().reg == what )
                {
                    string response;
                    if(vehicles[i].get_owner() != 0)
                    {
                        cout<<"this vehicle has owner. You still want to remove it ?"<<endl;
                        cout<<" ( Y = yes, N = no )"<<endl;
                        cin>>response;
                        if(response != "Y")
                            return;
                    }
                    for(int j = 0; j < n; j++)
                    {
                        if(people[j].id_get() == vehicles[i].get_owner())
                        {
                            people[j].remove_car(what);;
                        }
                    }
                    vehicles.erase( vehicles.begin() + i);
                    return;
                }
            }
        }
        else
        {
            stringstream number(what);
            int x = 0;
            number >> x;
            int n = people.size();
            int m = vehicles.size();
            for(int i = 0; i < m; i++)
            {
                if(vehicles[i].get_owner() == x)
                {
                    vehicles[i].set_owner(0);
                }
            }
            for(int  i = 0; i < n; i++)
            {
                if(people[i].id_get() == x)
                {
                    people[i].remove_all_cars();
                    people.erase(people.begin() + i );
                    return;

                }
            }
        }
    }
    void add_person(unsigned int id, string name)
    {
        int n = people.size();
        for(int i = 0; i < n; i++)
        {
            if(people[i].id_get() == id)
            {
                cout<<"There is person with this id already"<<endl;
                return;
            }
        }
        people.push_back(Person(name,id) );
    }
    void acquuire(unsigned int id, string r )  // person with this id now posses car with #reg ( if this car already have owner -> realease )
    {
        int n = people.size();
        int m = vehicles.size();
        for(int i = 0; i < n; i++)
        {
            if(people[i].id_get() == id)
            {
                for(int j = 0; j  < m; j++)
                {
                    if( (vehicles[j].get_r()). reg ==  r )
                    {
                        if(vehicles[j]. get_owner() != 0)
                        {
                            realease ( vehicles[j]. get_owner(), (vehicles[j]. get_r()).reg );
                            vehicles[j].set_owner(id);
                        }
                        else
                        {
                            vehicles[j].set_owner(id);
                        }
                    }
                }
            }
        }
    }

    void realease ( unsigned int id, string r ) // Person with this id no longer posses car with #owner
    {
        int n = people.size();
        for(int i = 0; i < n; i++)
        {
            if(people[i].id_get() == id)
            {
                people[i].remove_car(r);
            }
        }
    }

    void add_vehicle(Registration r, string description)
    {
        if(!valid_reg(r.reg))
        {
            cout<<"This is not valid reg number! The request was denied"<<endl;
            return ;
        }
        int n =vehicles.size();
        for(int i = 0; i < n; ++i)
        {
            if(vehicles[i].get_r() == r)
            {
                cout<<"Invalid registration!There is car alredy with this reg number. The request was denied"<<endl;
                return;
            }
        }
        Vehicle c(r,description,0);
        vehicles.push_back(c);
    }
    bool valid_reg(string r)
    {
        if('A' <= r[0] && r[0] <= 'Z')
        {
            if('A' <= r[1] && r[1] <= 'Z')
            {
                if('0' <= r[2] && r[2] <= '9' && '0' <= r[3] && r[3] <= '9' && '0' <= r[4] && r[4] <= '9' && '0' <= r[5] && r[5] <= '9' )
                {
                    if('A' <= r[6] && r[6] <= 'Z' && 'A' <= r[7] && r[7] <= 'Z' && r.size() == 8)
                    {
                        return true;
                    }
                    return false;
                }
                return false;
            }
            else if('0' <= r[1] && r[1] <= '9')
            {
                if('0' <= r[2] && r[2] <= '9' && '0' <= r[3] && r[3] <= '9' && '0' <= r[4] && r[4] <= '9')
                {
                    if('A' <= r[5] && r[5] <= 'Z' && 'A' <= r[6] && r[6] <= 'Z' && r.size() == 7)
                    {
                        return true;
                    }
                    return false;
                }
                return false;
            }
            return false;
        }
        return false;
    }

};
