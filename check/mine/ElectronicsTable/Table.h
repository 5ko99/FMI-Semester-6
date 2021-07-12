#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Cell.h"

using std::string;
using std::vector;

class Table
{
private:
	vector<vector<Cell>> m_cells;
	size_t m_rows;
	size_t m_cols;

	/**
	*	@brief Looks up given column to find the longest content
	*
	*	@param col - column to check
	*/
	size_t getLongestContentAtCol(size_t col) const;

	/**
	*	@brief Create a vector of int that contains the longest word for each column
	*
	*	@returns vector<int> filled with size of longest word for each column
	*/
	vector<size_t> getLongestWordPerCol() const;

public:
	/**
	 * @brief Sets rows and cols to 0
	*/
	Table();

	/**
	*	@brief Prints the table on the console
	*/
	void print() const;

	/**
	*	@brief Set a cell at given row and column. Changes entire cell. Expands if row/col is bigger than current
	*
	*	@param row - row index
	*	@param col - col index
	*/
	void setCellAt(size_t row, size_t col, const Cell& cell);

	/**
	*	@brief Expands the table to the given row
	*
	*	@param row - row to where it will expand
	*/
	void expandRows(size_t row);

	/**
	*	@brief Expands the table to the given col
	*
	*	@param col - column to where it will expand
	*/
	void expandCols(size_t col);

	/**
	*	@brief Getter of desired row
	*
	*	@param row - row to be returned
	*/
	const vector<Cell>& operator[](size_t row) const;

	/**
	*	@brief Gets current rows of the table
	*/
	size_t getRows() const;

	/**
	*	@brief Gets current columns of the table
	*/
	size_t getCols() const;

	/**
	*	@brief Checks if the table is empty
	*
	*	@returns true if empty, false otherwise
	*/
	bool empty() const;

	/**
	*	@brief Prints the first row of the table(the one containing A-Z)
	*/
	void printFirstRow() const;

	/**
	*	@brief Prints the rest of the table after the first row
	*/
	void printAfterFirstRow() const;

	/**
	*	@brief Prints the contents of a given cell
	*
	*	@param row				- row of cell
	*	@param col				- column of cell
	*	@param longestWordOfCol - the length of the longest word for the given column
	*/
	void printCellInformation(size_t row, size_t col, size_t longestWordOfCol) const;

	/**
	*	@brief Clears table's rows and columns. Leaves it empty
	*/
	void clearTable();
};