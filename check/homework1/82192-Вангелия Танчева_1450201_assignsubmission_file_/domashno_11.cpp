#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <stdexcept>
#include "MyString.h"
#include "Vehicle.h"
#include "Garage.h"

using namespace std;

MyString::MyString() : str{ nullptr }
{
    str = new char[1];
    str[0] = '\0';
    str_size = 0;
};

MyString::MyString(char* value)
{
    if (value == nullptr || value == "")
    {
        str = new char[1];
        str[0] = '\0';
        str_size = 0;
    }
    else
    {
        int i;

        for (i = 0; value[i] != '\0'; ++i)
        {

        }

        str_size = i;

        str = new char[str_size + 1];

        for (i = 0; i <= str_size; i++)
        {
            str[i] = value[i];
        }

    }
}

MyString::MyString(const char* value)
{
    if (value == nullptr || value == "")
    {
        str = new char[1];
        str[0] = '\0';
        str_size = 0;
    }
    else
    {
        int i;

        for (i = 0; value[i] != '\0'; ++i)
        {

        }

        str_size = i;

        str = new char[str_size + 1];

        for (i = 0; i <= str_size; i++)
        {
            str[i] = value[i];
        }

    }
}

MyString::MyString(const MyString& source)
{
    str = new char[source.size() + 1];

    for (int i = 0; i < source.size(); i++)
    {
        str[i] = source.str[i];
    }

    str[source.size()] = '\0';

    str_size = source.size();
}

MyString& MyString::operator=(const MyString& source)
{
    if (this == &source)
    {
        return *this;
    }

  ///    delete[] str;

    str = new char[source.size() + 1];

    for (int i = 0; i < source.size(); i++)
    {
        str[i] = source.str[i];
    }

    str[source.size()] = '\0';

    str_size = source.size();

    return *this;
}

char& MyString::at(size_t pos)
{
    /*try
    {
        return str[pos];
    }
    catch (const out_of_range& oor)
    {
        //cout << "Out of range error: " << endl;
    }*/
    if (pos < 0 || pos >= str_size)
    {
        throw std::out_of_range("Position out of range!");
    }

    return str[pos];

}

const char& MyString::at(size_t pos) const
{
    if (pos < 0 || pos >= str_size)
    {
        throw std::out_of_range("Position out of range!");
    }

    return str[pos];

}

char& MyString::operator[](size_t pos)
{
    assert(pos < str_size);
    return str[pos];
}

const char& MyString::operator[](size_t pos) const
{
    assert(pos < str_size);
    return str[pos];
}

char& MyString::front()
{
    assert(!empty());
    return str[0];
}

const char& MyString::front() const
{
    assert(!empty());
    return str[0];
}

char& MyString::back()
{
    assert(!empty());
    return str[str_size - 1];
}

const char& MyString::back() const
{
    assert(!empty());
    return str[str_size - 1];
}

bool MyString::empty() const
{
    if (str_size == 0)
        return true;
    else
        return false;
}

size_t MyString::size() const
{
    return str_size;
}

void MyString::clear()
{
    delete[] str;
    str = new char[1];
    str[0] = '\0';

    str_size = 0;
}

void MyString::push_back(char c)
{
    ///Strong exception guarantee
    char* temp_str = new char[str_size + 2];

    for (int i = 0; i < str_size; i++)
    {
        temp_str[i] = str[i];
    }

    temp_str[str_size] = c;
    temp_str[str_size + 1] = '\0';

    str_size = str_size + 1;

   /// delete[] str;

    str = temp_str;
    temp_str = nullptr;
    delete[] temp_str;

    return;
}

void MyString::pop_back()
{
    assert(!empty());
    char* temp_str = new char[str_size];

    for (int i = 0; i < str_size - 1; i++)
    {
        temp_str[i] = str[i];
    }

    temp_str[str_size - 1] = '\0';

    str_size = str_size - 1;

    delete[] str;
    str = temp_str;

    temp_str = nullptr;
    delete[] temp_str;

    return;
}

MyString& MyString::operator+=(char c)
{
    push_back(c);

    return *this;
}

MyString& MyString::operator+=(const MyString& source)
{
    char* temp_str = new char[str_size + source.str_size + 1];

    ///Присвояваме низът отляво
    for (int i = 0; i < str_size; i++)
    {
        temp_str[i] = str[i];
    }

    for (int i = str_size, j = 0; i < str_size + source.str_size; i++, j++)
    {
        temp_str[i] = source.str[j];
    }

    temp_str[str_size + source.str_size] = '\0';

    str_size = str_size + source.str_size;



    delete[] str;
    str = temp_str;

    temp_str = nullptr;
    delete[] temp_str;

    return *this;
}

MyString MyString::operator+(char c) const
{
    MyString temp(str);

    temp += c;

    return temp;
}

MyString MyString::operator+(const MyString& source) const
{
    MyString temp(str);

    temp += source;

    return temp;
}

const char* MyString::c_str() const
{
    char* new_str = new char[str_size + 1];

    for (int i = 0; i < str_size; i++)
    {
        new_str[i] = str[i];
    }

    new_str[str_size] = '\0';

    return new_str;
}

bool MyString::operator==(const MyString& rhs) const
{
    bool flag = true;

    if (str_size == rhs.size())
    {
        for (int i = 0; i < str_size && flag == true; i++)
        {
            if (str[i] != rhs.str[i])
            {
                flag = false;
            }
        }
    }
    else
    {
        flag = false;
    }

    return flag;
}

bool MyString::operator<(const MyString& rhs) const
{
    bool flag = true;
    size_t length;

    if (*this == rhs)
    {
        flag = false;
    }

    if (str_size <= rhs.size())
    {
        length = str_size;
    }
    else
    {
        length = rhs.size();
    }

    for (int i = 0; i < length && flag == true; i++)
    {
        if (str[i] > rhs.str[i])
        {
            flag = false;
        }
    }

    if (flag == true)
    {
        if (str_size > rhs.size())
        {
            flag = false;
        }
    }

    return flag;
}

///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

Vehicle::Vehicle(const char* registration, const char* description,
    size_t space)
{
    MyString temp_reg(registration);
    MyString temp_descr(description);

    this->car_licence_plate = temp_reg;
    this->car_description = temp_descr;

    car_park_space = space;
}

/*!Vehicle::~Vehicle()
{

}*/

const char* Vehicle::registration() const
{
    return this->car_licence_plate.c_str();
}

const char* Vehicle::description() const
{
    return this->car_description.c_str();
}

size_t Vehicle::space() const
{
    return this->car_park_space;
}
///!!!!!!!!!!!GARAGE!!!!!!!!!!!!!!!!!!!!
Garage::Garage(size_t garage_size)
{
    this->garage_size = garage_size;
    this->vehicles = (Vehicle*)malloc(sizeof(Vehicle) * garage_size);

    for (int i = 0; i < garage_size; i++)
    {
        this->vehicles[i] = Vehicle(nullptr, nullptr, 0);
    }
}

/*!Garage::~Garage()
{
    delete[] vehicles;
}*/

void Garage::insert(Vehicle& v)
{
    ///Check for licence plate
    for (int i = 0; i < this->garage_size; i++)
    {
        bool flag = false;

        for (int j = 0; v.registration()[j] == '\0'; j++)
        {
            if (this->vehicles[i].registration()[j] != v.registration()[j])
            {
                flag = true;
            }
        }

        if (flag)
        {
            ///TODO -- Exception
            throw "Can't insert vehicle! Registration number already exists!";
        }
    }

    ///Check for free space
    int next = 0;

    for (int i = 0; i < garage_size && vehicles[i].registration()[0] != '\0'; ++i)
    {
        next = next + 1;
    }

    cout << "next = " << next << endl;

    if (v.space() + next <= this->garage_size)
    {
        for (int i = 0; i < v.space(); i++)
        {
            vehicles[next + i] = v;
        }
    }
    else
    {
        throw "Can't insert vehicle! There is no free space!";
    }

}

void Garage::erase(const char* registration)
{
    if (!empty())
    {
        MyString reg_plate(registration);
        size_t end_index = 0;
        size_t veh_space = 0;

        for (int i = 0; vehicles[i].registration()[0] != '\0'; i++)
        {
            MyString veh_reg_plate(vehicles[i].registration());

            if (reg_plate == veh_reg_plate)
            {
                end_index = i;
                veh_space = vehicles[i].space();
            }
        }

        for (size_t j = end_index + 1; j < garage_size; j++)
        {
            vehicles[j - veh_space] = vehicles[j];

            /*Vehicle(vehicles[j].registration(),
                                              vehicles[j].description(),
                                              vehicles[j].space());*/
        }
        size_t i = 0;

        while (garage_size - veh_space + i < garage_size)
        {
            vehicles[garage_size - veh_space + i] = Vehicle(nullptr, nullptr, 0);
            i++;
        }

    }








    /*!MyString reg(registration);

    bool flag = false;
    int index;
    ///Check if there is such registration plate
    for(int i = 0 ; vehicles[i].registration() != '\0' && flag == false; ++i)
    {

        if(reg == vehicles[i].registration())
        {
            flag = true;
            index = i;
        }
    }

    cout << "start index for erase =" << index << endl;

    if(flag)
    {

    }*/
}

const Vehicle& Garage::at(size_t pos) const
{
    ///out of range exception
    if (vehicles[pos].registration()[0] != '\0')
    {
        return vehicles[pos];
    }
    else
    {
        throw std::out_of_range("Position out of range!");
    }
}

const Vehicle& Garage::operator[](size_t pos) const
{
    assert(pos < garage_size);
    return vehicles[pos];
}

bool Garage::empty() const
{
    bool answer;

    if (vehicles[0].registration()[0] == '\0')
    {
        answer = true;
    }
    else
    {
        answer = false;
    }

    return answer;
}

size_t Garage::size() const
{
    MyString temp_reg("");

    size_t br = 0;

    if (!empty())
    {
        for (int i = 0; vehicles[i].registration()[0] != '\0' && i < garage_size; i++)
        {
            MyString vehicle_reg(vehicles[i].registration());
            cout << vehicle_reg.c_str() << endl;

            cout << "Ha" << endl;
            if (!(temp_reg == vehicle_reg))
            {
                temp_reg = vehicle_reg;
                ++br;
            }

        }
    }

    return br;
}

void Garage::clear()
{
    for (int i = 0; i < garage_size && vehicles[i].registration()[0] != '\0'; i++)
    {
        ///Vehicle* temp_vehicles;
        ///temp_vehicles = (Vehicle*)malloc(sizeof(Vehicle) * garage_size);

        vehicles[i] = Vehicle(nullptr, nullptr, 0);



        ///delete[] vehicles;
        ///vehicles = temp_vehicles;

        ///temp_vehicles = nullptr;
        ///delete[] temp_vehicles;
    }

    return;
}

const Vehicle* Garage::find(const char* registration) const
{
    Vehicle* v = nullptr;
    MyString reg_plate(registration);
    bool flag = false;

    if (!empty())
    {
        for (int i = 0; i < garage_size
            && vehicles[i].registration()[0] != '\0' && flag == false; i++)
        {
            MyString temp_reg_plate(vehicles[i].registration());

            if (reg_plate == temp_reg_plate)
            {
                flag = true;
                v[0] = Vehicle(vehicles[i].registration(),
                    vehicles[i].description(),
                    vehicles[i].space());
            }
        }
    }


    if (flag == false)
    {
        return nullptr;
    }

    return v;
}

void Garage::print()
{
    cout << "-----------------------------------" << endl;
    for (int i = 0; i < garage_size; i++)
    {
        if (vehicles[i].registration()[0] == '\0')
        {
            cout << "Spot[" << i << "]: empty" << endl;
        }
        else
        {
            cout << "Spot[" << i << "].car_description: " << vehicles[i].description() << endl;
            cout << "Spot[" << i << "].car_registration: " << vehicles[i].registration() << endl;
            cout << "Spot[" << i << "].car_space: " << vehicles[i].space() << endl;
        }
    }
    cout << "-----------------------------------" << endl;
}



int main()
{
    MyString m;
    ///char *ptr = nullptr;

    //MyString d("hey");
    //MyString p("Hello World!");
    //MyString s("hoa");
    //MyString ss("hos");


    MyString d("hey");
    MyString p("Hello World!");
    MyString s("hoa");
    MyString ss("hos");


    MyString dp;

    dp = d;


    //cout << m.size() << endl;
    //cout << d.size() << endl;
    //cout << testm[0] << endl;

    cout << dp.size() << endl;
    cout << p.back() << endl;
    cout << m.empty() << endl;
    cout << dp.empty() << endl;
    dp.clear();
    cout << dp.size() << endl;
    dp = d;
    dp.push_back('s');
    cout << dp.size() << endl;
    //d.pop_back();
    //d.pop_back();
    //cout << d.size() << endl;
    //d+='M';
    //cout << d.size() << endl;
    //d+=s;

    //cout << d.size() << endl;
    dp = d + p;
    cout << dp.size() << endl;

    cout << dp.c_str() << endl;

    if (s == ss)
    {
        cout << "s = ss" << endl;
    }
    else
    {
        cout << "s != ss" << endl;
    }

    if (s < ss)
    {
        cout << "s < ss" << endl;
    }
    else
    {
        cout << "s !< ss" << endl;
    }


    const MyString reg("E3987MB");
    const MyString descr("Mercedes");
    size_t sp = 2;

    const MyString reg1("B3987BA");
    const MyString descr1("Suzuki");
    size_t sp1 = 1;

    Vehicle v(reg.c_str(), descr.c_str(), sp);
    Vehicle v1(reg1.c_str(), descr1.c_str(), sp1);

    cout << v.registration() << endl;

    cout << v.description() << endl;

    cout << v.space() << endl;

    Garage g(5);

    g.insert(v);

    g.insert(v1);

    cout << "g[1].reg = " << g[1].registration() << endl;
    cout << "g[2].descr = " << g[2].description() << endl;

    cout << g.empty() << endl;

    cout << g.size() << endl;

    //g.clear();

    cout << g.empty() << endl;


    /*if(g.find("E3987MB") != nullptr)
    {
        const Vehicle* v_found;
        v_found = g.find("B3987BA");
        cout << v_found[0].description()<< endl;
    }*/

    g.erase("E3987MB");
    //g.erase("B3987BA");

    g.print();


    //MyString err("1");

    //cout << err.front() << endl;
    //cout << d.str << endl;

    //MyString ms("abc");

    //cout << m.empty();


    /*Point p1(10, 20);
    Point p2 = p1;

    p1.getX();

    ///p2.setX(p1.getX());


    ///p1.setX(1);

    ///cout << p1.getY() << endl;

    cout << "p2.x = " << p2.x << endl;
    cout << "p2.y = " << p2.y << endl;*/





    return 0;
}












