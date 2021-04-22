#include <iostream>
#include <cassert>

class String
{
    public:
    char* str;
    int len;
    String()
    {
        this->str = new char[1];
        this->str[0] = '\0';
        this->len=0;
    }
    String(const char* str)
    {
        int len=0;
        for (int i = 0; str[i] != '\0'; i++)
        {
            len++;
        }
        this->len = len+1;
        this->str = new char[len+1];
        for (int i = 0; i < this->len; i++)
        {
            this->str[i] = str[i];
        }
    }
    String(const String& other)
    {
        this->len = other.len + 1;
        this->str = new char[this->len];
        for (int i = 0; i < this->len; i++)
        {
            this->str[i] = other.str[i];
        }
    }
    String& operator=(const String &other)
    {
        if (this != &other)
        {
            delete[] this->str;
            this->len = other.len + 1;
            this->str = new char[len];
    
            for (size_t i = 0; i < len; i++)
            {
                this->str[i] = other.str[i];
            }
        }
        return *this;
    }
    char* operator=(char symbol)
    {
        if (symbol == '\0')
        {
            delete[] this->str;
            this->str = new char[1];
            this->len = 1;
            this->str[0] = '\0';
            return this->str;
        }
        delete[] this->str;
        this->str = new char[2];
        this->len = 2;
        this->str[0] = symbol;
        this->str[1] = '\0';
    
        return this->str;
    }
    char& at(std::size_t pos)
    {
        return this->str[pos];
    }
    const char& at(std::size_t pos) const
    {
        return this->str[pos];
    }
    char& operator[](std::size_t pos)
    {
        return this->str[pos];
    }
    const char& operator[](std::size_t pos) const
    {
        return this->str[pos];
    }
    char& front()
    {
        return this->str[0];
    }
    const char& front() const
    {
        return this->str[0];
    }
    char& back()
    {
        return this->str[this->len-1];
    }
    const char& back() const
    {
        return this->str[this->len-1];
    }
    String& operator+=(char c)
    {
        String buffer;
        buffer.str = new char[this->len + 1];
        buffer.len = this->len + 1;
        for (int i = 0; i <= buffer.len; i++)
        {
            if (i < this->len)
                buffer.str[i] = this->str[i];
            else if (i == this->len)
                buffer.str[i] = c;
            else
                buffer.str[i] = '\0';
        }
        delete[] this->str;
        this->str = new char[buffer.len];
        for (int i = 0; i < buffer.len; i++)
        {
            this->str[i] = buffer.str[i];
        }
    
        return *this;
    }
    String operator+(const String &other)
    {
        String result;
        result.str = new char[this->len + other.len + 1];
        result.len = this->len + other.len + 1;
        for (int i = 0, j = 0; i < result.len; i++)
        {
            if (i < this->len)
            {
                result.str[i] = this->str[i];
            }
            else
            {
                result.str[i] = other.str[j];
                j++;
            }
        }
        return result;
    }
    char* operator+=(const String &other)
    {
        String buffer;
        buffer.str = new char[this->len + other.len + 1];
        buffer.len = this->len + other.len + 1;
        for (int i = 0, j = 0; i < buffer.len; i++)
        {
            if (i < this->len)
            {
                buffer.str[i] = this->str[i];
            }
            else
            {
                buffer.str[i] = other.str[j];
                j++;
            }
        }
        delete[] this->str;
        this->str = new char[buffer.len + 1];
        this->len = buffer.len + 1;
        for (int i = 0; i < this->len; i++)
        {
            this->str[i] = buffer.str[i];
        }
        return this->str;
    }
    String operator+(char c)
    {
        String ch;
        ch.str = new char[this->len + 2];
        for (size_t i = 0; i < this->len; i++)
        {
            ch.str[i] = this->str[i];
        }
        ch.str[this->len] = c;
        ch.str[this->len + 1] = '\0';
        return ch;
    }
    bool operator==(String &other)
    {
        for (int i = 0; i < other.len; i++)
        {
            if (this->str[i] != other.str[i])
                return false;
        }
        return true;
    }
    void set_str(const char* s)
    {
	    int len=0;
        for (int i = 0; s[i] != '\0'; i++)
        {
            len++;
        }
	    this->str = new char[len+1];
        this->len = len+1;
	    for (int i = 0; i < this->len; i++)
	    	this->str[i] = s[i];
    }
    int size()
    {
        return this->len;
    }
    void clear()
    {
        delete[] this->str;
        this->len=0;
    }
    char* get_str() const
    {
        return this->str;
    }
    ~String()
    {
        clear();
    }
};

class Vehicle
{
    public:
    String reg_num;
    String desc;
    size_t num_seats;
    Vehicle()
    {
        reg_num.str = new char[1];
        reg_num.str[0] = '\0';
        reg_num.len = 0;
        desc.str = new char[1];
        desc.str[0] = '\0';
        desc.len = 0;
        num_seats = 0;
    }
    /*В условието пише класът Vehicle да няма default constructor
      Но без него на ред 314 ми дава грешка и ми изисква такъв*/
    Vehicle(const char* registration, const char* description, std::size_t space)
    {
        reg_num.set_str(registration);
        desc.set_str(description);
        num_seats = space;
    }
    Vehicle(Vehicle& other)
    {
        this->reg_num = other.reg_num;
        this->desc = other.desc;
        this->num_seats = other.num_seats;
    }
    const char* registration() const
    {
        char* regnum = new char[reg_num.len];
        for (int i = 0; i < reg_num.len; i++)
        {
            regnum[i] = reg_num.at(i);
        }
        return regnum;
    }
    const char* description() const
    {
        char* description1 = new char[desc.len];
        for (int i = 0; i < desc.len; i++)
        {
            description1[i] = desc.at(i);
        }
        return description1;
    }
    std::size_t space() const
    {
        return num_seats;
    }
};

class Garage
{
    public:
    size_t size_of_garage;
    size_t size_of_vehicles;
    size_t occupation;
    Vehicle* arr_cars;
    Garage(size_t space)
    {
        size_of_garage = space;
        occupation = 0;
        size_of_vehicles = 0;
        arr_cars = nullptr;
    }
    const Vehicle& at(std::size_t pos) const
    {
        assert(pos < size_of_vehicles);
        return arr_cars[pos];
    }
    const Vehicle& operator[](std::size_t pos) const
    {
        return arr_cars[pos];
    }
    void insert(Vehicle& v)
    {
        if (v.space() > size_of_garage - occupation)
        {
            assert(v.space() > size_of_garage - occupation);
        }
        for (int i = 0; i < size_of_vehicles; i++)
        {
            if (arr_cars[i].registration() == v.registration())
            {
                assert(arr_cars[i].registration() == v.registration());
            }
        }
        occupation += v.space();
        Vehicle* new_arr_cars = new Vehicle[size_of_vehicles + 1];
        for (int i = 0; i < size_of_vehicles; i++)
        {
            new_arr_cars[i] = arr_cars[i];
        }
        size_of_vehicles++;
        new_arr_cars[size_of_vehicles - 1] = v;
    }
    void erase(const char* registration)
    {
        int index = -1;
        for (int i = 0; i < size_of_vehicles; i++)
        {
            if (arr_cars[i].registration() == registration)
            {
                index = i;
            }
        }
        if (index == -1)
        {
            return;
        }
        occupation -= arr_cars[index].space();
        arr_cars[index] = arr_cars[size_of_vehicles - 1];
        delete &arr_cars[size_of_vehicles - 1];
        size_of_vehicles--;
    }
    bool empty() const
    {
        if (occupation == 0)
        {
            return true;
        }
        return false;
    }
    std::size_t size() const
    {
        return size_of_vehicles;
    }
    void clear()
    {
        delete[] arr_cars;
        size_of_vehicles = 0;
        occupation = 0;
        arr_cars = nullptr;
    }
    const Vehicle* find(const char* registration) const
    {
        int index = -1;
        for (int i = 0; i < size_of_vehicles; i++)
        {
            if (arr_cars[i].registration() == registration)
            {
                index = i;
            }
        }
        if (index == -1)
        {
            return nullptr;
        }
        return &arr_cars[index];
    }
    ~Garage()
    {
        clear();
    }
};
int main()
{
    return 0;
};