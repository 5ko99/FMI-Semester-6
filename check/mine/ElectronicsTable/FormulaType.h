#pragma once
#include <string>
#include <queue>
#include <stack>
#include "CellType.h"
#include "StringType.h"
#include "Table.h"

using std::queue;
using std::stack;
using std::string;

/**
 * @brief Represents formulas in electronic table. Holds refference to the table that contains it.
 */
class FormulaType : public CellType
{
private:
	string m_value;
	const Table& m_table;

	/**
	 * @brief Applies operator(op) on a and b.
	 *
	 * @param a left opperand
	 * @param b right opperand
	 * @param op operator(+,-,*,/,^)
	 * @return double result after performing operation
	 */
	double applyOperator(StringType& a, StringType& b, char op) const;

	/**
	 * @brief Checks for the precedence of the given operator(op)
	 *
	 * @param op operator to check it's precedence
	 * @return size_t 1 if '+' or '-', 2 if '*' or '/'. 0 otherwise
	 */
	size_t precedence(char op) const;

	double postfix_equation(queue<StringType>& output) const;

	/**
	 * @brief Given infix order equation convert it to postfix then solve it
	 *
	 * @param tokens
	 * @param values
	 * @param operators
	 * @return vector<StringType>
	 */
	double shunting_yard(const vector<string>& tokens) const;

	/**
	 * @brief Calculates inner formula in FormulaType
	 *
	 * @return double result after calculation
	 */
	double calculateFormula() const;

public:
	/**
	*	@brief Initializes m_formula with given string
	*
	*	@param equation - string to be initialized with
	*/
	FormulaType(const string& equation, const Table& table_ref);

	/**
	*	@brief Prints the formula result on the console
	*/
	virtual void print() const final override;

	/**
	*	@brief Creates dynamically allocated copy of this object
	*
	*	@returns The newly allocated FormulaType* object
	*/
	virtual CellType* clone() const final override;

	/**
	 * @brief Creates m_value string fit for file format
	 *
	 * @return string formated content
	 */
	virtual string toFileFormat() const final override;

	/**
	*	@brief Getter
	*
	*	@returns raw string format of formula after calculation
	*/
	virtual string toString() const final override;

	/**
	 * @brief Gets the length of the calculated equation
	 *
	 * @return size_t length of calculated equation
	 */
	virtual size_t size() const final override;

	/**
	 * @brief Gets m_calculated
	 *
	 * @return double the calculated equation
	 */
	virtual double toDouble() const final override;

	/**
	 * @brief Adds other to current object
	 *
	 * @param other object to sum up with
	 * @return double result after addition
	 */
	virtual double operator+(const CellType& other) const final override;

	/**
	 * @brief Subtracts other from current object
	 *
	 * @param other object to subtract with
	 * @return double result after subtraction
	 */
	virtual double operator-(const CellType& other) const final override;

	/**
	 * @brief Multiplies other with current object
	 *
	 * @param other object to multiply with
	 * @return double result after multiplication
	 */
	virtual double operator*(const CellType& other) const final override;

	/**
	 * @brief Divides current object with other
	 *
	 * @param other object to divide with
	 * @return double result after division
	 */
	virtual double operator/(const CellType& other) const final override;

	/**
	 * @brief Raises current object to the power of other
	 *
	 * @param other exponent
	 * @return double result after rasing to the exponent
	 */
	virtual double operator^(const CellType& other) const final override;
};