#pragma once
#include <iostream>
#include <cstddef>
#include <assert.h> 

class MyString 
{
public:

	void setLenght(int agr);

	unsigned int getLenght() const;

	MyString();

	MyString(const MyString& other);

	MyString& operator=(const MyString&);

	~MyString();

	MyString(const char* str);

	char& at(std::size_t pos) ;

	const char& at(std::size_t pos) const;

	char& operator[](std::size_t pos) ;

	const char& operator[](std::size_t pos) const;

	char& front();

	const char& front() const;

	char& back();

	const char& back() const;

	bool empty() const;

	std::size_t size() const;

	void clear();

	void push_back(char c);

	void pop_back();

	MyString& operator+=(char c);

	MyString& operator+=(const MyString& rhs);

	MyString operator+(char c) const;

	MyString operator+(const MyString& rhs) const;

	const char* c_str() const;

	bool operator==(const MyString& rhs) const;

	bool operator<(const MyString& rhs) const;

private:
	char* content;
	unsigned lenght;

};

class Vehicle 
{
public:

	Vehicle() = delete;
	Vehicle(const char* registration, const char* description, std::size_t space);
	Vehicle(const Vehicle& other) = default;
	const char* registration() const;
	std::size_t space() const;
	const char* description() const;
private:

	MyString RegNumber;
	MyString descr;
	std::size_t capacity;
};

class Garage 
{
public:

	Garage(std::size_t size);

	Garage(const Garage& other);

	Garage& operator=(const Garage& other);

	~Garage();

	void insert(Vehicle& v);

	void erase(const char* registration);

	const Vehicle& at(std::size_t pos) const;

	const Vehicle& operator[](std::size_t pos) const;

	bool empty() const;

	void clear();

	std::size_t size() const;

	const Vehicle* find(const char* registration) const;

	void printContent() const;
private:

	std::size_t capacity;
	std::size_t availabe_capacity;
	unsigned cars_inside;
	Vehicle** vehicles;
};