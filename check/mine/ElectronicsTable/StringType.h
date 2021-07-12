#pragma once
#include "CellType.h"
#include <string>

using std::string;

class StringType : public CellType
{
private:
	string m_value;

public:
	/**
	*	@brief Initializes string
	*
	*	@param str - string to be initialized with
	*/
	StringType(const string& str);

	/**
	*	@brief prints m_string on the console
	*
	*/
	virtual void print() const final override;

	/**
	*	@brief Creates dynamically allocated copy of this object
	*
	*	@returns The newly allocated StringType* object
	*/
	virtual CellType* clone() const final override;

	/**
	 * @brief Creates string fit for file
	 *
	 * @return string for file write
	 */
	virtual string toFileFormat() const final override;

	/**
	*	@brief Getter
	*
	*	@returns inner string
	*/
	virtual string toString() const final override;

	/**
	 * @brief Gets the length of the inner string
	 *
	 * @return size_t length
	 */
	virtual size_t size() const final override;

	/**
	 * @brief If string is valid double or integer then return it. Otherwise return 0
	 *
	 * @return double converted string to double
	 */
	virtual double toDouble() const final override;

	/**
	 * @brief Adds inner string(toDouble) with other
	 *
	 * @param other object with which addition will be made
	 * @return double result after addition
	 */
	virtual double operator+(const CellType& other) const final override;

	/**
	 * @briefoperator+Subtracts inner string(toDouble) with other
	 *
	 * @param other object with which subtraction will be made
	 * @return double result after subtraction
	 */
	virtual double operator-(const CellType& other) const;

	/**
	 * @brief Multiplies other with current object's inner string(toDouble)
	 *
	 * @param other object with which multiplication will be made
	 * @return double result after multiplication
	 */
	virtual double operator*(const CellType& other) const;

	/**
	 * @brief Divides inner string(toDouble) with other
	 *
	 * @param other object with which division will be made
	 * @return double result after multiplication
	 */
	virtual double operator/(const CellType& other) const;

	/**
	 * @brief Raises inner string(toDouble) to the power exponent other
	 *
	 * @param other exponent value
	 * @return double result after raising to the power
	 */
	virtual double operator^(const CellType& other) const;
};