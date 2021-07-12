#pragma once
#include <fstream>
#include <string>
#include "Table.h"

using std::fstream;
using std::string;

class DocumentHandler
{
private:
	string m_filePath;
	fstream m_file;
	Table m_table;

	bool m_isSaved = false;
	bool m_isClosed = true;
	bool m_isNew = false;

	DocumentHandler();

	/**
	*	@brief Populates in memory table's cells from the currently opened file
	*/
	void populateTableFromFile();

	/**
	*	@brief Finds rows and longest column of file and initializes empty table with them. If it encounters invalid
	*	cell type - throws
	*/
	void initializeEmptyTableFromFile();

	/**
	*	@brief Reads through the file and initializes table cells
	*/
	void fillTableFromFile();

	/**
	*	@brief Prints menu of commands on the console
	*/
	void menu() const;

public:
	static DocumentHandler& getInstance();

	DocumentHandler(const DocumentHandler& other) = delete;
	DocumentHandler& operator=(const DocumentHandler& other) = delete;
	DocumentHandler(DocumentHandler&& other) = delete;
	DocumentHandler& operator=(DocumentHandler&& other) = delete;

	/**
	 *	@brief Attempts to open file with given path then populates table from the file
	 *
	 *	@param path - path to file
	 *	@returns true if the operation succeeded, false otherwise
	*/
	bool openFile(const string& path);

	/**
	* 	@brief Attempts to close the opened file. If session hasn't been saved then it prompts the user for confirmation
	*	to either save/don't save/cancel. Clears in memory table.
	*
	*	@returns true if the operation succeeded, false if operation has been canceled
	*/
	bool closeFile();

	/**
	* 	@brief Attempts to save the current table into the same file opened by openFile()
	*/
	void saveToFile();

	/**
	*	@brief Saves the current session into file with given path
	*
	*	@param path - path to the new file
	*/
	void saveFileAs(const string& path);

	/**
	 *	@brief Creates new document(in memory) which is empty. If wished to be saved it should be called with "saveas"
	 *
	 *	@returns true if the operation succeeded in creating new document, false if it didn't
	*/
	bool createNewDocument();

	/**
	*	@brief Edits a cell at the given row and column with given content.
	*
	*	@param row	   - row of table
	*	@param col	   - column of table
	*	@param content - content with which it will be edited
	*/
	void editFile(size_t row, size_t col, const string& content);

	/**
	*	@brief Sets the cell at row|col with given content.
	*
	*	@param row		- row of cell
	*	@param col		- col of cell
	*	@param content	- content to assign to the cell
	*/
	void alterCell(size_t row, size_t col, const string& content);

	/**
	*	@brief Executes the main logic of the program
	*/
	void exe();

	/**
	*	@brief Clears the state of the current document
	*
	*	@param turn_off_new   - whether to set m_isNew to false or not
	*	@param turn_off_saved - whether to set m_isSaved to false or not
	*	@param clear_table    - whether to clear the table or not
	*	@param clear_filePath - whether to clear the filePath or not
	*/
	void clearState(bool turn_off_saved = false, bool turn_off_new = false, bool clear_table = false, bool clear_filePath = false);

	/**
	*	@brief Sets the state Saved and New
	*
	*	@param turn_on_saved - whether to set m_isSaved to true, or not
	*	@param turn_on_new	 - whether to set m_isNew to true, or not
	*/
	void setState(bool turn_on_saved = false, bool turn_on_new = false);
};