#pragma once
#include<iostream>
#include <cstddef>
#include "Vehicle.h"
#include "MyString.h"

class Garage
{
	std::size_t size_buf;
	std::size_t free_space;
	std::size_t cars;
	Vehicle** vehicle;
public:
	Garage(std::size_t size);
	~Garage();
	void insert(Vehicle& v);
	void erase(const char* registration);
	const Vehicle& at(std::size_t pos) const;
	const Vehicle& operator[](std::size_t pos) const;
	bool empty() const;
	std::size_t size() const;
	void clear();
	const Vehicle* find(const char* registration) const;



};