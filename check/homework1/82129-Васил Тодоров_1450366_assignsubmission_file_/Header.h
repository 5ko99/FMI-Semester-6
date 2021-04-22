#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;
class MyString
{
	char* cstr;
	size_t len;
	MyString(const char* s, size_t n) : cstr(new char[n + 1])
	{
		memcpy(cstr, s, n);
		cstr[n] = '\0';
		len = n;
	}
public:
	MyString(const char* s = "") : MyString(s, strlen(s))
	{}
	MyString(const MyString& astr) : MyString(astr.cstr)
	{}
	~MyString()
	{
		delete[] cstr;
	}
	MyString& operator=(const MyString& astr)
	{
		if (this == &astr) return *this;
		len = astr.len;
		delete[] cstr;
		cstr = new char[len + 1];
		memcpy(cstr, astr.cstr, len + 1);
		return *this;
	}
	char& at(size_t pos)
	{
		if (pos < len)
			return cstr[pos];
		throw out_of_range("invalid position");
	}
	const char& at(size_t pos) const
	{
		if (pos < len)
			return cstr[pos];
		throw out_of_range("invalid position");
	}
	char& operator[](size_t pos)
	{
		assert(pos < len);
		return cstr[pos];
	}
	const char& operator[](size_t pos) const
	{
		assert(pos < len);
		return cstr[pos];
	}
	char& front()
	{
		assert(len);
		return cstr[0];
	}
	const char& front() const
	{
		assert(len);
		return cstr[0];
	}
	char& back()
	{
		assert(len);
		return cstr[len - 1];
	}
	const char& back() const
	{
		assert(len);
		return cstr[len - 1];
	}
	bool empty() const
	{
		return !len;
	}
	size_t size() const
	{
		return len;
	}
	void clear()
	{
		cstr[0] = '\0';
		len = 0;
	}
	void push_back(char c)
	{

		char* p = new char[len + 2];
		memcpy(p, cstr, len);
		p[len++] = c;
		p[len] = '\0';
		delete[] cstr;
		cstr = p;
	}
	void pop_back()
	{
		assert(len);
		cstr[--len] = '\0';
	}
	MyString& operator+=(char c)
	{
		push_back(c);
		return *this;
	}
	MyString& operator+=(const MyString& rhs)
	{
		char* p = new char[len + rhs.len + 1];
		memcpy(p, cstr, len);
		memcpy(p + len, rhs.cstr, rhs.len);
		len += rhs.len;
		p[len] = '\0';
		delete[] cstr;
		cstr = p;
		return *this;
	}
	MyString operator+(char c) const
	{
		char* p = new char[len + 1];
		memcpy(p, cstr, len);
		p[len] = c;
		return MyString(p, len + 1);
	}
	MyString operator+(const MyString& rhs) const
	{
		char* p = new char[len + rhs.len];
		memcpy(p, cstr, len);
		memcpy(p + len, rhs.cstr, rhs.len);
		return MyString(p, len + rhs.len);
	}
	const char* c_str() const
	{
		return cstr;
	}
	bool operator==(const MyString& rhs) const
	{
		if (len != rhs.len)
			return  false;
		return !memcmp(cstr, rhs.cstr, len);
	}
	bool operator<(const MyString& rhs) const
	{
		int test = memcmp(cstr, rhs.cstr, min(len, rhs.len));
		return test < 0 || (test == 0 && len < rhs.len);
	}
};

class Vehicle
{
	MyString registrationNomer;
	MyString descriptionVehicle;
	size_t spaceParking;
public:
	Vehicle(const char* registration, const char* description, size_t space)
		:registrationNomer(registration), descriptionVehicle(description), spaceParking(space)
	{}
	const char* registration() const
	{
		return registrationNomer.c_str();
	}
	const char* description() const
	{
		return descriptionVehicle.c_str();
	}
	size_t space() const
	{
		return spaceParking;
	}
};

class Garage
{
	size_t capacity;
	size_t allocated;
	size_t cnt;
	Vehicle** cars;
public:
	Garage(size_t size) : capacity(size), allocated(0), cnt(0), cars(nullptr)
	{}
	Garage(const Garage& other) : capacity(other.capacity), allocated(other.allocated), cnt(other.cnt)
	{
		cars = new Vehicle * [cnt];
		memcpy(cars, other.cars, cnt * sizeof(Vehicle*));
	}
	Garage& operator=(Garage other)
	{
		swap(capacity, other.capacity);
		swap(allocated, other.allocated);
		swap(cnt, other.cnt);
		swap(cars, other.cars);

		return *this;
	}
	~Garage()
	{
		delete[] cars;
	}
	void insert(Vehicle& v)
	{
		if (allocated + v.space() > capacity) throw length_error("Not enough space");
		for (size_t i = 0; i < cnt; i++)
		{
			if (!strcmp(cars[i]->registration(), v.registration())) throw invalid_argument("There is already a Vehicle by the same registration");
		}
		Vehicle** gar = new Vehicle * [cnt + 1];
		memcpy(gar, cars, cnt * sizeof(Vehicle*));
		gar[cnt++] = &v;
		delete[] cars;
		cars = gar;
		allocated += v.space();
	}
	void erase(const char* registration)
	{
		for (size_t i = 0; i < cnt; i++)
		{
			if (!strcmp(cars[i]->registration(), registration))
			{
				allocated -= cars[i]->space();
				cars[i] = cars[--cnt];
				return;
			}
		}
	}
	const Vehicle& at(size_t pos) const
	{
		if (pos >= cnt) throw out_of_range("Out of range");
		return *cars[pos];
	}
	const Vehicle& operator[](size_t pos) const
	{
		assert(pos < cnt);
		return *cars[pos];
	}
	bool empty() const
	{
		return cnt == 0;
	}
	size_t size()
	{
		return cnt;
	}
	void clear()
	{
		cnt = 0;
		allocated = 0;
	}
	const Vehicle* find(const char* registration) const
	{
		for (size_t i = 0; i < cnt; i++)
		{
			if (!strcmp(cars[i]->registration(), registration))
			{
				return cars[i];
			}
		}
		return nullptr;
	}
};
int getPlusN()
{
	int n;
	while ((!(cin >> n)) || (n < 0))
	{
		cout << "Error: enter a number: ";
		cin.clear();
		cin.ignore(123, '\n');
	}
	cin.clear();
	cin.ignore(123, '\n');
	return n;
}
void addVehicle(Garage& gar)
{
	char reg[20];
	char descr[200];
	size_t size;
	cout << "Enter Vehicle registration: ";
	cin.getline(reg, 20);
	cout << "Enter Vehicle description: ";
	cin.getline(descr, 200);
	cout << "Enter Vehicle size: ";
	size = getPlusN();
	Vehicle* v = new Vehicle(reg, descr, size);
	try { gar.insert(*v); }
	catch (...) { delete v; }
}
void removeVehicle(Garage& gar)
{
	char reg[20];
	cout << "Enter Vehicle registration to remove: ";
	cin.getline(reg, 20);
	delete gar.find(reg);
	gar.erase(reg);
}
void printGar(Garage& gar)
{
	cout << endl;
	for (size_t i = 0; i < gar.size(); i++)
	{
		cout << "Vehicle: " << gar[i].registration() << " with capacity: " << gar[i].space() << ", " << gar[i].description() << endl;
	}
	cout << endl;
}