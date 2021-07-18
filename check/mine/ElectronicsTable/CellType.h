#pragma once
#include <string>

using std::string;

/**
*	@brief Abstract class, used for interface purposes only
*/
class CellType
{
public:
	virtual void print() const = 0;
	virtual CellType* clone() const = 0;
	virtual string toString() const = 0;
	virtual string toFileFormat() const = 0;
	virtual double toDouble() const = 0;
	virtual size_t size() const = 0;

	virtual double operator+(const CellType& other) const = 0;
	virtual double operator-(const CellType& other) const = 0;
	virtual double operator*(const CellType& other) const = 0;
	virtual double operator/(const CellType& other) const = 0;
	virtual double operator^(const CellType& other) const = 0;
};