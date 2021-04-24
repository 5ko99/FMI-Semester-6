#pragma once
#include <iostream>
#include <exception>

class MyString {
private:
	char* string;
	int length;
	void copy(const MyString& other);
public:
	void print() const;
	void clear();
	void push_back(char element);
	void pop_back();
	MyString();
	MyString(const char* str);
	MyString(const MyString& other);
	~MyString();
	MyString& operator=(const MyString& other);
	MyString& operator+=(char c);
	MyString& operator+=(const MyString& rhs);
	MyString operator+(char c) const;
	MyString operator+(const MyString& rhs) const;
	bool empty() const;
	bool operator==(const MyString& rhs) const;
	bool operator<(const MyString& rhs) const;
	char& operator[](std::size_t pos);
	const char& operator[](std::size_t pos) const;
	char& at(std::size_t pos);
	const char& at(std::size_t pos) const;
	char& front();
	const char& front() const;
	char& back();
	const char& back() const;
	const char* c_str() const;
};

class Vehicle {
private:
	MyString reg;
	MyString desc;
	std::size_t size;

public:
	Vehicle(const char* registration, const char* description, std::size_t space);
	const char* registration() const;
	const char* description() const;
	std::size_t space() const;
};

class Garage {
private:
	std::size_t capacity;
	std::size_t vehicleCount;
    std::size_t used;
	
	Vehicle** vehicleArray;

	void copy(const Garage& other);

public:
	void insert(Vehicle& v);
	void erase(const char* registration);
	void clear();
	Garage();
	Garage(std::size_t size);
	Garage(const Garage& other);
	~Garage();
	Garage& operator=(const Garage& other);
	bool empty() const;
	const Vehicle& at(std::size_t pos) const;
	const Vehicle& operator[](std::size_t pos) const;
	const Vehicle* find(const char* registration) const;
	std::size_t size() const;	
};

