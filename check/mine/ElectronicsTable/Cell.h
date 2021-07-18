#pragma once
#include <vector>
#include "CellType.h"

class Table;
using std::vector;

class Cell
{
private:
	CellType* m_content;

	/**
	*	@brief Copies contents from other into the object
	*
	*	@param other - Cell object from which copying will be made
	*/
	void copyFrom(const Cell& other);

	/**
	 * @brief Moves contents from other into the object
	 * @param other - Cell object from which moving will be made
	*/
	void moveFrom(Cell& other);

public:
	/**
	*	@brief Initializes cell with content. Decides what type the cell will be.
	*	Gives ref to formula type if the content is formula type
	*
	*	@param content - content to assign
	*	@param ref 	   - refference to table container
	*/
	Cell(const string& content, const Table& ref);

	/**
	*	@brief Copy constructor
	*
	*	@param other - Cell object from which copying will be made
	*/
	Cell(const Cell& other);

	/**
	*	@brief Copy assignment operator
	*
	*	@param other - Cell object from which copying will be made
	*	@returns *this
	*/
	Cell& operator=(const Cell& other);

	/**
	*	@brief Move constructor
	*
	*	@param other - Cell object from which moving will be made
	*/
	Cell(Cell&& other) noexcept;

	/**
	*	@brief Move assignment operator
	*
	*	@param other - Cell object from which moving will be made
	*/
	Cell& operator=(Cell&& other) noexcept;

	/**
	*	@brief Prints cell's information on the console
	*/
	void print() const;

	/**
	 * @brief Getter
	 *
	 * @return the content behind the pointer(IntegerType/DoubleType/FormulaType/StringType)
	*/
	CellType* getContent() const;

	/**
	 * @brief Getter
	 *
	 * @return the content of the cell interpreted as double(if possible)
	*/
	double getContentAsDouble() const;

	~Cell();
};